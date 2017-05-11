/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_OBJECTS_H
#define MBED_OBJECTS_H

#include "cmsis.h"
#include "PortNames.h"
#include "PeripheralNames.h"
#include "PinNames.h"

#ifdef __cplusplus
extern "C" {
#endif
	
#define rock_width 16
#define rock_height 16
static unsigned char rock[] = {
   0x01, 0xe0, 0x07, 0xb0, 0x1c, 0x18, 0x30, 0x0c, 0x60, 0x06, 0x40, 0x03,
   0x40, 0x01, 0x60, 0x01, 0x20, 0x01, 0x30, 0x01, 0x30, 0x01, 0x18, 0x03,
   0x0c, 0x06, 0x06, 0x0c, 0x03, 0x78, 0x00, 0xc0 };

struct gpio_irq_s {
    uint32_t port;
    uint32_t pin;
    uint32_t ch;
};

struct port_s {
    __IO uint32_t *reg_dir;
    __IO uint32_t *reg_out;
    __I  uint32_t *reg_in;
    PortName port;
    uint32_t mask;
};

struct pwmout_s {
    __IO uint32_t *MR;
    LPC_PWM_TypeDef *pwm;
    uint32_t channel;
};

struct serial_s {
    LPC_UART_TypeDef *uart;
    int index;
};

struct analogin_s {
    ADCName adc;
};

struct dac_s {
    DACName dac;
};

struct can_s {
    LPC_CAN_TypeDef *dev;
    int index;
};

struct i2c_s {
    LPC_I2C_TypeDef *i2c;
};

struct spi_s {
    LPC_SSP_TypeDef *spi;
};

#include "gpio_object.h"

#ifdef __cplusplus
}
#endif

#endif
