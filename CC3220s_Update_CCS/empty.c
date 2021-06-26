/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== empty.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
//#include <ti/drivers/SPI.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/Watchdog.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* XDC Module Headers */
#include <xdc/std.h>
#include <xdc/runtime/System.h>





UART_Handle uart;
UART_Params uartParams;

I2C_Transaction i2cTransaction = {0};
I2C_Handle i2cHandle;


bool status;
uint8_t readBuffer[7];
uint8_t writeBuffer[0x200F + 0x02];

//test, zo kan je ten allen tijde deze variabele uitlezen.
uint16_t pointer;
uint32_t WriteCount;



void initialize_C3220S()
{
    /* Call driver init functions */
    GPIO_init();
    I2C_init();
    //SPI_init();
    UART_init();
    // Watchdog_init();


    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.stopBits = UART_STOP_ONE;
    uartParams.parityType = UART_PAR_NONE;
    uartParams.baudRate = 9600;

    uart = UART_open(CONFIG_UART_0, &uartParams);

    if (uart == NULL) {
        /* UART_open() failed */
        while (1);
    }


    I2C_Params params;
    I2C_Params_init(&params);
    params.bitRate = I2C_100kHz;

    i2cHandle = I2C_open(0, &params);

    if (i2cHandle == NULL) {
        // Error opening I2C
        while (1) {}
    }



    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_D10, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(RSTN, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(MFIO, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Turn on user LED */
    GPIO_write(CONFIG_GPIO_LED_D10, CONFIG_GPIO_LED_OFF);
    GPIO_write(RSTN, CONFIG_GPIO_LED_ON);                  //P03
    GPIO_write(MFIO, CONFIG_GPIO_LED_ON);                  //P08

}

uint8_t MAXM86146_enter_bootloader()
{
    //Bootloader  //OLD version MSBL3.1.7
    GPIO_write(RSTN, CONFIG_GPIO_LED_ON);              //be sure the RSTN and MFIO are high
    GPIO_write(MFIO, CONFIG_GPIO_LED_ON);
    usleep(100);
    GPIO_write(RSTN, CONFIG_GPIO_LED_OFF);
    usleep(100); //=2ms ??
    usleep(100);
    GPIO_write(MFIO, CONFIG_GPIO_LED_OFF);
    usleep(100);
    usleep(100);
    usleep(100);
    GPIO_write(RSTN, CONFIG_GPIO_LED_ON);
    int i;
    for(i = 0; i<25; i++)
    {
        usleep(100);
    }


    writeBuffer[0] = 0x01;
    writeBuffer[1] = 0x00;
    writeBuffer[2] = 0x08;
    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = writeBuffer;
    i2cTransaction.writeCount = 3;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    usleep(100);

    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = NULL;
    i2cTransaction.writeCount = 0;
    i2cTransaction.readBuf = readBuffer;
    i2cTransaction.readCount = 1;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    usleep(100);

    return readBuffer[0];
}

void MAXM86146_enter_application()
{
    GPIO_write(RSTN, CONFIG_GPIO_LED_ON);
    GPIO_write(MFIO, CONFIG_GPIO_LED_OFF);
    usleep(100);
    GPIO_write(RSTN, CONFIG_GPIO_LED_OFF);
    usleep(100); //=2ms ??
    usleep(100);
    GPIO_write(MFIO, CONFIG_GPIO_LED_ON);
    usleep(100);
    usleep(100);
    usleep(100);
    GPIO_write(RSTN, CONFIG_GPIO_LED_ON);
    int i;
    for(i = 0; i<25; i++)
    {
        usleep(100);
    }

    sleep(2);
}

void GET_MSBL_DATA(uint32_t a, char* value)
{
    uint32_t x = a & 0x000000FF;
    uint32_t y = (a & 0x0000FF00)>>8;
    uint32_t z = (a & 0x00FF0000)>>16;

    usleep(100);
    usleep(100);
    UART_write(uart, &z, 1);
    usleep(100);
    usleep(100);
    UART_write(uart, &y, 1);
    usleep(100);
    usleep(100);
    UART_write(uart, &x, 1);
    UART_read(uart, value, 1);
}


uint8_t MAXM86146_bootloader_flash_bytes(int d, uint32_t a, uint32_t b)
{
    usleep(100);

    writeBuffer[0] = 0x80;
    writeBuffer[1] = d;

    WriteCount = (b-a)+1+2;

    pointer = 2;
    char value;
    for(; a <= b; a++)
    {
        GET_MSBL_DATA(a, &value);
        writeBuffer[pointer] = (int)value;
        pointer++;
    }

    usleep(100);

    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = writeBuffer;
    i2cTransaction.writeCount = WriteCount;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
       if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
           // I2C slave address not acknowledged
       }
       while(1);
    }
    uint16_t i;
    for(i = 0; i<340; i++)
    {
        usleep(100);
    }

    sleep(3);

    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = NULL;
    i2cTransaction.writeCount = 0;
    i2cTransaction.readBuf = readBuffer;
    i2cTransaction.readCount = 1;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    usleep(100);
    sleep(3);

    return readBuffer[0];
}

uint8_t MAXM86146_bootloader_number_of_pages()
{
    usleep(100);
    char value;
    GET_MSBL_DATA(0x00000044, &value);

    writeBuffer[0] = 0x80;
    writeBuffer[1] = 0x02;
    writeBuffer[2] = 0x00;
    writeBuffer[3] = (int)value;

    usleep(100);

    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = writeBuffer;
    i2cTransaction.writeCount = 4;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }
    uint16_t i;
    for(i = 0; i<340; i++)
    {
        usleep(100);
    }

    sleep(1);

    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = NULL;
    i2cTransaction.writeCount = 0;
    i2cTransaction.readBuf = readBuffer;
    i2cTransaction.readCount = 1;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    usleep(100);

    return readBuffer[0];
}

void MAXM86146_connect_to_pc()
{
    GPIO_write(CONFIG_GPIO_LED_D10, CONFIG_GPIO_LED_ON);

    char input = 0;
    int x;
    for (x = 0; x<256; x++)
    {
        int i;
        for(i = 0; i<100; i++)
        {
            usleep(100);
        }
        UART_write(uart, &input, 1);
        input++;
    }
    while(input != 0x73)
    {
        UART_read(uart, &input, 1); //Waiting for startsignal PC Software
    }

    GPIO_write(CONFIG_GPIO_LED_D10, CONFIG_GPIO_LED_OFF);
}

uint8_t MAXM86146_bootloader_erase()
{
    usleep(100);

    writeBuffer[0] = 0x80;
    writeBuffer[1] = 0x03;

    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = writeBuffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    uint16_t i;
    for(i = 0; i<700; i++)
    {
        usleep(100);
    }

    sleep(1);

    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = NULL;
    i2cTransaction.writeCount = 0;
    i2cTransaction.readBuf = readBuffer;
    i2cTransaction.readCount = 1;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    usleep(100);

    return readBuffer[0];
}

void MAXM86146_bootloader_version()
{
    usleep(100);

    writeBuffer[0] = 0x81;
    writeBuffer[1] = 0x00;

    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = writeBuffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    usleep(100);

    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = NULL;
    i2cTransaction.writeCount = 0;
    i2cTransaction.readBuf = readBuffer;
    i2cTransaction.readCount = 4;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    int w = readBuffer[0];
    int x = readBuffer[1];
    int y = readBuffer[2];
    int z = readBuffer[3];

    usleep(100);
}

void MAXM86146_read_mode(int* mode)
{
    usleep(100);

    writeBuffer[0] = 0x02;
    writeBuffer[1] = 0x00;
    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = writeBuffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    usleep(100);
    usleep(100);

    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = NULL;
    i2cTransaction.writeCount = 0;
    i2cTransaction.readBuf = readBuffer;
    i2cTransaction.readCount = 2;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    *mode = readBuffer[1];

    usleep(100);
}

void MAXM86146_sensor_hub_status()
{
    usleep(100);

    writeBuffer[0] = 0x00;
    writeBuffer[1] = 0x00;
    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = writeBuffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    usleep(100);
    usleep(100);

    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = NULL;
    i2cTransaction.writeCount = 0;
    i2cTransaction.readBuf = readBuffer;
    i2cTransaction.readCount = 7;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    usleep(100);
}


void *mainThread(void *arg0)
{
    int error;
    int mode;

    initialize_C3220S();

    MAXM86146_connect_to_pc(); //Only needed to flash the bootloader

    error = MAXM86146_enter_bootloader();
    while(error);

    //MAXM86146_sensor_hub_status();

    MAXM86146_read_mode(&mode);
    while(mode != 0x08);

    //MAXM86146_bootloader_version();

    error = MAXM86146_bootloader_number_of_pages();
    while(error);

    error = MAXM86146_bootloader_flash_bytes(0x00, 0x28, 0x32);
    while(error);

    error = MAXM86146_bootloader_flash_bytes(0x01, 0x34, 0x43);
    while(error);

    error = MAXM86146_bootloader_erase();
    while(error);

    error = MAXM86146_bootloader_flash_bytes(0x04, 0x0004C, 0x0205B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x0205C, 0x0406B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x0406C, 0x0607B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x0607C, 0x0808B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x0808C, 0x0A09B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x0A09C, 0x0C0AB);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x0C0AC, 0x0E0BB);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x0E0BC, 0x100CB);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x100CC, 0x120DB);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x120DC, 0x140EB);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x140EC, 0x160FB);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x160FC, 0x1810B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x1810C, 0x1A11B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x1A11C, 0x1C12B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x1C12C, 0x1E13B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x1E13C, 0x2014B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x2014C, 0x2215B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x2215C, 0x2416B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x2416C, 0x2617B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x2617C, 0x2818B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x2818C, 0x2A19B);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x2A19C, 0x2C1AB);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x2C1AC, 0x2E1BB);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x2E1BC, 0x301CB);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x301CC, 0x321DB);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x321DC, 0x341EB);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x341EC, 0x361FB);
    while(error);
    error = MAXM86146_bootloader_flash_bytes(0x04, 0x361FC, 0x3820B);
    while(error);

    MAXM86146_enter_application();

sleep(1);

    writeBuffer[0] = 0x01;
    writeBuffer[1] = 0x00;
    writeBuffer[2] = 0x00;
    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = writeBuffer;
    i2cTransaction.writeCount = 3;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    usleep(100);
    sleep(1);

    i2cTransaction.slaveAddress = 0x55;
    i2cTransaction.writeBuf = NULL;
    i2cTransaction.writeCount = 0;
    i2cTransaction.readBuf = readBuffer;
    i2cTransaction.readCount = 1;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    if (status == false) {
        if (i2cTransaction.status == I2C_STATUS_ADDR_NACK) {
            // I2C slave address not acknowledged
        }
        while(1);
    }

    usleep(100);




//    char value;
    while (1) {
        /*
        usleep(100);
        GET_MSBL_DATA(0x00000000, &value);
        while(value != 0x6D) {}
        GPIO_toggle(CONFIG_GPIO_LED_D10);

        UART_write(uart, &input, 1);
        //UART_read(uart, &input, 1);
        GPIO_toggle(CONFIG_GPIO_LED_D10);
        input++;

        sleep(1);
        input = 0x62;
        UART_write(uart, &input, 1);
        //UART_read(uart, &input, 1);
        GPIO_toggle(CONFIG_GPIO_LED_D10);
        sleep(1);
        input = 0x63;
        UART_write(uart, &input, 1);
        //UART_read(uart, &input, 1);
        GPIO_toggle(CONFIG_GPIO_LED_D10);

*/

    }
}
