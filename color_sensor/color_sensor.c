/**
  ******************************************************************************
  * @file    color_sensor.c
  * @author  Waveshare Team
  * @version 
  * @date    2021-02-08
  * @brief   color_sensor.
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
#include <stdlib.h>
#include <stdarg.h>

#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const uint LED_PIN = PICO_DEFAULT_LED_PIN;
#define S0 18 // Please notice the Pin's define
#define S1 19
#define S2 20
#define S3 21
#define OUT 17

long int g_count = 0; // count the frequecy
long int g_array[3];  // store the RGB value
long int g_flag = 0;  // filter of RGB queue
float g_SF[3];        // save the RGB Scale factor

// Init TSC230 and setting Frequency.
void TSC_Init()
{
    gpio_init(S0);
    gpio_init(S1);
    gpio_init(S2);
    gpio_init(S3);

    gpio_set_dir(S0, GPIO_OUT);
    gpio_set_dir(S1, GPIO_OUT);
    gpio_set_dir(S2, GPIO_OUT);
    gpio_set_dir(S3, GPIO_OUT);

    gpio_put(S0, 0); // GPIO_OUT FREQUENCY SCALING 2%
    gpio_put(S1, 1);
}

// Select the filter color
void TSC_FilterColor(int Level01, int Level02)
{
    if (Level01 != 0)
        Level01 = 1;
    if (Level02 != 0)
        Level02 = 1;
    gpio_put(S2, Level01);
    gpio_put(S3, Level02);
}
void TSC_Count(uint gpio, uint32_t events)
{
    g_count++;
}

void TSC_WB(int Level0, int Level1) //White Balance
{
    g_count = 0;
    g_flag++;
    TSC_FilterColor(Level0, Level1);
}
bool TSC_Callback(struct repeating_timer *t)
{
    switch (g_flag)
    {
    case 0:
        printf("->WB Start\r\n");
        TSC_WB(0, 0); //Filter without Red
        break;
    case 1:
        printf("->Frequency R=%d\r\n", g_count);
        g_array[0] = g_count;
        TSC_WB(1, 1); //Filter without Green
        break;
    case 2:
        printf("->Frequency G=%d\r\n", g_count);
        g_array[1] = g_count;
        TSC_WB(0, 1); //Filter without Blue
        break;
    case 3:
        printf("->Frequency B=%d\r\n", g_count);
        printf("->WB Endr\n");
        g_array[2] = g_count;
        TSC_WB(1, 0); //Clear(no filter)
        break;
    default:
        g_count = 0;
        break;
    }

    return true;
}

int main()
{
    stdio_init_all();
    TSC_Init();

    struct repeating_timer timer;
    add_repeating_timer_ms(-1000, TSC_Callback, NULL, &timer);

    gpio_set_irq_enabled_with_callback(OUT, GPIO_IRQ_EDGE_RISE, true, &TSC_Count);

    sleep_ms(4000);
    for (int i = 0; i < 3; i++)
    {
        printf("%d\r\n", g_array[i]);
    }
    g_SF[0] = 255.0 / g_array[0]; //R Scale factor
    g_SF[1] = 255.0 / g_array[1]; //G Scale factor
    g_SF[2] = 255.0 / g_array[2]; //B Scale factor
    printf("%f\r\n", g_SF[0]);
    printf("%f\r\n", g_SF[1]);
    printf("%f\r\n", g_SF[2]);

    while (1)
    {
        g_flag = 0;

        for (int i = 0; i < 3; i++)
        {
            printf("%d\r\n", (int)(g_array[i] * g_SF[i]));
        }

        sleep_ms(4000);
    }
}
