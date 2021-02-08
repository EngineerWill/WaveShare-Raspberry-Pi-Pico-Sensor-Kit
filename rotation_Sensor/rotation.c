/**
  ******************************************************************************
  * @file    rotation.c
  * @author  Waveshare Team
  * @version 
  * @date    2021-02-08
  * @brief   rotation.
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
#define PinA 27
#define PinB 26
#define PinSW 22
uint64_t time = 0;
int32_t count = 0;
int32_t num = 0;

void blinkA()
{
    if ((time_us_64() - time) > 3000)
    {
        if (gpio_get(PinB))
        {
            count++;
        }
        else
        {
            count--;
        }
    }

    time = time_us_64();
}

void init()
{
    gpio_init(PinA);
    gpio_init(PinB);
    gpio_init(PinSW);
    gpio_set_irq_enabled_with_callback(PinA, GPIO_IRQ_LEVEL_LOW, true, &blinkA);
    gpio_set_dir(PinA, 0);
    gpio_set_dir(PinB, 0);
    gpio_set_dir(PinSW, 0);
}
int main()
{
    stdio_init_all();
    init();
    time = time_us_64();

    while (1)
    {
        if (num != count)
        {
            num = count;
            printf("%ld\r\n", num);
        }
        if(!gpio_get(PinSW))
        {
            
            printf("Switch on\r\n");
            while(!gpio_get(PinSW));
        }
    }

    return 0;
}
