/**
  ******************************************************************************
  * @file    adc_sensor.c
  * @author  Waveshare Team
  * @version 
  * @date    2021-02-08
  * @brief   adc_sensor.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#define ADC_CHANNEL     0
#define ADC_PIN         (ADC_CHANNEL+26)
#define SENSOR_STATUS_PIN 22

void adc_task(void)
{
	const float conversion_factor = 3.3f / (1 << 12);
    uint16_t result = adc_read();
    float conversion_result=result*conversion_factor;
	if(!(gpio_get(SENSOR_STATUS_PIN))){
		printf("\r\nD:%d      A:%.3f   S: ON\r\n", result, conversion_result);
	} else {
		printf("\r\nD:%d      A:%.3f   S: OFF\r\n", result, conversion_result);
	}
}

void init()
{
    //adc init
    adc_init();
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(ADC_PIN);
    // Select ADC input 0 (GPIO26)
    adc_select_input(ADC_CHANNEL);

    gpio_init(SENSOR_STATUS_PIN);
    gpio_set_dir(SENSOR_STATUS_PIN,0);

}
int main() {
    stdio_init_all();

    init();

    while (1) {

        adc_task();
        sleep_ms(1000);
    }
}

