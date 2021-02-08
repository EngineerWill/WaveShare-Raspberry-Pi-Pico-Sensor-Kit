/**
  ******************************************************************************
  * @file    dht11.c
  * @author  Waveshare Team
  * @version 
  * @date    2021-02-08
  * @brief   dht11.
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
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const uint LED_PIN = PICO_DEFAULT_LED_PIN;
const uint DHT_PIN = 15;
const uint MAX_TIMINGS = 85;

typedef struct {
    float humidity;
    float temp_celsius;
} dht_reading;

void read_from_dht(dht_reading *result);
uint DHT11_Read_Data(dht_reading *result);
int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_init(DHT_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (1) {
        dht_reading reading;
        DHT11_Read_Data(&reading);
        float fahrenheit = (reading.temp_celsius * 9 / 5) + 32;
        printf("Humidity = %.1f%%, Temperature = %.1fC (%.1fF)\n",
               reading.humidity, reading.temp_celsius, fahrenheit);

        sleep_ms(2000);
    }
}

void DHT11_Rst(void)	   
{                 
	gpio_set_dir(DHT_PIN, GPIO_OUT);	//SET OUTPUT
    gpio_put(DHT_PIN, 0); 	//GPIOA.0=0
    sleep_ms(20);    	//Pull down Least 18ms
    gpio_put(DHT_PIN,1);	//GPIOA.0=1 
	sleep_us(30);     	//Pull up 20~40us
}

uint DHT11_Check(void) 	   
{   
	uint retry=0;
	gpio_set_dir(DHT_PIN, GPIO_IN);//SET INPUT	 
    while (gpio_get(DHT_PIN)&&retry<100)//DHT11 Pull down 40~80us
	{
		retry++;
		sleep_us(1);
	};	 
	if(retry>=100)
		return 1;
	else 
		retry=0;
    while (!gpio_get(DHT_PIN)&&retry<100)//DHT11 Pull up 40~80us
	{
		retry++;
		sleep_us(1);
	};
	if(retry>=100)
		return 1;//chack error	    
	return 0;
}

uint DHT11_Read_Bit(void) 			 
{
 	uint retry=0;
	while(gpio_get(DHT_PIN)&&retry<100)//wait become Low level
	{
		retry++;
		sleep_us(1);
	}
	retry=0;
	while(!gpio_get(DHT_PIN)&&retry<100)//wait become High level
	{
		retry++;
		sleep_us(1);
	}
	sleep_us(40);//wait 40us
	if(gpio_get(DHT_PIN))
		return 1;
	else 
		return 0;		   
}

uint DHT11_Read_Byte(void)    
{        
    uint i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}

uint DHT11_Read_Data(dht_reading *result)  
{        
 	uint buf[5];
	uint i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			result->humidity=buf[0];
			result->temp_celsius=buf[2];
		}
	}
	else 
		return 1;
	return 0;	    
}
uint DHT11_Init(void)
{

	DHT11_Rst();  
	return DHT11_Check();    
}