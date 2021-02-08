/**
  ******************************************************************************
  * @file    switch_sensor.c
  * @author  Waveshare Team
  * @version 
  * @date    2021-02-08
  * @brief   switch_sensor.
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

#define switch_pin 28

int main()
{
    stdio_init_all();
    gpio_init(switch_pin);
    gpio_set_dir(switch_pin,0);
    while(1)
    {
        if(gpio_get(switch_pin))
        {
            printf("switch_sensor get ON");
        }
        else{
            printf("switch_sensor get OFF");
        }
        sleep_ms(1000);
    }


    return 0;
}
