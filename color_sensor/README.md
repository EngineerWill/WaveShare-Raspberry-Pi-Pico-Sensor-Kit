# Color_Sensor(EN)
## Instructions
This examples can be used for Color_Sensor
Moudle_Pin | Pico_GPIO
---|---
VCC | 3.3V
GND | GND
S0 | GPIO18
S1 | GPIO19
S2 | GPIO20
S3 | GPIO21
OUT | GPIO17
## How to use
1. Download the relative codes to the development board.
2. Place a white paper at the top of the sensor in a distance of 1cm.
3. Power up the development board, and input a High level to LED port to
light up 4 bright white LED indicators.
4. Wait for 2 seconds or more after power up (automatic white adjustment
is conducted during this period).
5. After the adjustment completed, place an objective to be measured at
the front side of the sensor. Then, you can see relative data of RGB are
outputted. A color check list is helpful for finding out what the measured
color it is.
## Considerations
1. Light interference from outside should be avoided, which may affect
the result of color identification. It is recommended to place the light
source and Color Sensor in a close, light reflection free box for testing.
2. White balance adjustment is required whenever Color Sensor module
is reset or light source is changed.

---

# Color_Sensor(CN)
## 介绍
这个例程可用于Color_Sensor
## 引脚连接
Moudle_Pin | Pico_GPIO
---|---
VCC | 3.3V
GND | GND
S0 | GPIO18
S1 | GPIO19
S2 | GPIO20
S3 | GPIO21
OUT | GPIO17
## 使用方法
1. 将配套程序下载到开发板中。
2. 将白纸放置在传感器四个高亮白色 LED 一面（下称正面）的上方 1CM 处。
3. 给开发板上电。此时 LED 端口接入高电平，四个高亮白色 LED 点亮。
4. 上电之后等待 2 秒钟以上（此时正在调整白平衡）。
5. 调整结束以后，把传感器正面对着待测物体，串口输出对应的 RGB 数据，
参考颜色对照表，可知探测到的颜色。
## 注意事项
1. 颜色识别时要避免外界光线的干扰，否则会影响颜色识别的结果，最好
把 Color Sensor 和光源等放置在一个封闭、无反射的盒子中测试。
2. 每次 Color Sensor 模块重启或者更换光源时，都需要进行白平衡调整。
