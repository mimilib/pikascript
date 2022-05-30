<p align="center">
	<img alt="logo" src="document/image/144221063-a85b2cb0-0416-493f-9afb-56cff31e977d.jpg" width="300">
</p>
<h1 align="center" style="margin: 30px 0 30px; font-weight: bold;">PikaScript</h1>
<h4 align="center">Cross platform ultra lightweight embedded Python engine</h4>
<p align="center">
	<a href="https://gitee.com/lyon1998/pikascript/stargazers"><img src="https://gitee.com/lyon1998/pikascript/badge/star.svg?theme=gvp"></a>
	<a href="https://gitee.com/lyon1998/pikascript/members"><img src="https://gitee.com/lyon1998/pikascript/badge/fork.svg?theme=gvp"></a>
	<a href="https://github.com/pikastech/pikascript/stargazers"><img src="https://img.shields.io/github/stars/pikastech/pikascript?style=flat-square&logo=GitHub"></a>
	<a href="https://github.com/pikastech/pikascript/network/members"><img src="https://img.shields.io/github/forks/pikastech/pikascript?style=flat-square&logo=GitHub"></a>
	<a href="https://github.com/pikastech/pikascript/watchers"><img src="https://img.shields.io/github/watchers/pikastech/pikascript?style=flat-square&logo=GitHub"></a>
	<a href="https://github.com/pikastech/pikascript/issues"><img src="https://img.shields.io/github/issues/pikastech/pikascript.svg?style=flat-square&logo=GitHub"></a>
	<a href="https://github.com/pikastech/pikascript/blob/master/LICENSE"><img src="https://img.shields.io/github/license/pikastech/pikascript.svg?style=flat-square"></a>
  <a href="https://github.com/pikasTech/pikascript/actions/workflows/CI.yml"><img src="https://github.com/pikasTech/pikascript/actions/workflows/CI.yml/badge.svg"> </a>
</p>

<p align="center">
	<a href="README_zh.md" >中文页</a> |
	<a href="https://whycan.com/f_55.html" >Forum</a> |
	<a href="https://pikadoc.readthedocs.io/en/latest/index.html" >Documents</a> |
	<a href="https://space.bilibili.com/5365336/channel/detail?cid=202329">Videos</a> |
        <a href="../../tree/master/bsp#platform-support">BSP</a> |
	<a href="https://pikadoc.readthedocs.io/en/latest/%E5%8C%85%E7%AE%A1%E7%90%86%E5%99%A8%E4%B8%8E%E6%A8%A1%E5%9D%97%E7%AE%A1%E7%90%86.html">Package Manager</a> |
	<a href="https://pikadoc.readthedocs.io/en/latest/%E4%BB%8E%20RT-Thread%20%E8%BD%AF%E4%BB%B6%E5%8C%85%E5%BC%80%E5%A7%8B.html" >RT-Thread package</a> |
	<a href="https://pikadoc.readthedocs.io/en/latest/%E5%A6%82%E4%BD%95%E5%8F%82%E4%B8%8E%E7%A4%BE%E5%8C%BA%E8%B4%A1%E7%8C%AE.html" >Contribute</a> |
	<a href="https://pikadoc.readthedocs.io/en/latest/%E5%95%86%E4%B8%9A%E5%90%88%E4%BD%9C%E6%96%B9%E5%BC%8F.html">Business</a> 
</p>

[![image](document/image/147997370-ff37b6e7-25b2-4174-aa64-c1fb92cede04.png)](https://pikastech.github.io/pikascript/dev/bench/)

# 1. Abstract

PikaScript is an ultra-lightweight Python engine with zero dependencies and zero-configuration, that can run with 4KB of RAM and 32KB of flash (such as STM32G030C8 and STM32F103C8).

<img src="https://user-images.githubusercontent.com/88232613/147799704-d79345da-a2b9-4593-b1eb-ff9de127429a.png" width="500"/>

It's very easy to bind C function to python module with the help of Pika Pre-compiler.Only write the API of python in `.pyi` and the bindings are autoly generated by Pre-compiler.

The Pre-compiler is fully open-source, and the source code is in the [tools](https://github.com/pikasTech/pikascript/tree/master/tools) folder.

![image-20220520233540245](document/image/image-20220520233540245.png)

# Get PikaScript:

## Use Online Project Generator
Generator url:
http://pikascript.com

Note: You need the [Community Edition license (Now Free)](https://www.keil.com/pr/article/1299.htm) to build Keil projects, and the version of Keil should be newer than v5.36.

[![](https://user-images.githubusercontent.com/88232613/169705287-afb58c8f-1b03-4155-abb2-1b432d5b852e.png)](http://pikascript.com)

## Use Pika package manager [PikaPackage.exe](https://pikadoc.readthedocs.io/en/latest/%E5%8C%85%E7%AE%A1%E7%90%86%E5%99%A8%E4%B8%8E%E6%A8%A1%E5%9D%97%E7%AE%A1%E7%90%86.html)

1. Run the [PikaPackage.exe](https://gitee.com/Lyon1998/pikascript/attach_files/907478/download) directly, then the pikascript repo would be downloaded auto in the /tmp/pikascript folder of your current disc partition.

2. Add [requestment.txt](/bsp/stm32g030c8/pikascript/requestment.txt) to the same folder of PikaPackage.exe then run [PikaPackage.exe](../../raw/master/tools/pikaPackageManager/pikaPackage.exe). The [run-time core](../../tree/master/src), [pre-compiler](../../tree/master/tools/pikaCompiler) and [moudles](../../tree/master/package) would be installed in the current folder.

3. Released modules：[packages.toml](packages.toml)

# Quick Start

You can use [simulation project](https://pikadoc.readthedocs.io/en/latest/Keil%20%E4%BB%BF%E7%9C%9F%E5%B7%A5%E7%A8%8B.html) to quick start without hardware，or use the out-of-the-box develop board [Pika-Pi—Zero](https://item.taobao.com/item.htm?spm=a2126o.success.result.1.76224831Y0X1gO&id=654947372034).

![image](https://user-images.githubusercontent.com/88232613/141252834-93011ca7-f84b-4192-8e61-0e242796f62c.png)

The board based on STM32G030C8T6 MCU, only 64kB Flash, 8kB RAM can run PikaScript with total peripheral device (GPIO、TIME、IIC、RGB、KEY、LCD、RGB). 
CH340 is deployed to support USB to serial with Type-C USB, support download python script py serial, there are 4 RGB on the board and support the [LCD](https://item.taobao.com/item.htm?spm=a1z10.3-c.w4002-23991764791.12.16f97c58fsLjVk&id=660745643102).

# Related Projects

- ⭐ PikaScript Bluepill Demo In PlatformIO — Python-like REPL 🐍🔌
https://github.com/maxgerhardt/pikascript-pio-bluepill

- ⭐ PikaScript Bluepill Demo In GCC 🐍
https://github.com/Chandler-Kluser/pikascript_gcc_bluepill

# Document

https://pikadoc.readthedocs.io/en/latest/index.html

## Folders
[src](../../tree/master/src) - core code

[bsp](../../tree/master/bsp) - mcu/board support

[port](../../tree/master/port) - OS support

[document](../../tree/master/document) - developt document

[examples](../../tree/master/examples) - example scripts

[package](../../tree/master/package) - packages and moudles

[pikaCompiler](../../tree/master/tools/pikaCompiler) - pre-compiler write by Rust, used to bind C function to python moudle.

[pikaPackageManager](../../tree/master/tools/pikaPackageManager) - pacakge manager

# 2.Platform support

## MCU support
|MCU|bsp|gpio|uart|pwm|adc|i2c|
|---|---|---|---|---|---|---|
|stm32g030c8|√|√|√|√|√|√|
|stm32g070cB|√|√|√|√|√|√|
|stm32f103c8|√|√|√|√|√|√|
|stm32f103rb|√|√|√|√|√|√|
|stm32f103ze|√|√|√|√|√|√|
|stm32f103rc|√|√|√|√|√|√|
|stm32f401cc|√|√|√|√|√|√|
|stm32f411ce|√|√|√|√|√|√|
|stm32f407ze|√| | | | | |
|stm32f407zg|√| | | | | |
|stm32h750vb|√| | | | | |
|stm32f051r8|√| | | | | |
|ch582|√|√|√| |√|√|
|ch32v103r8t6|√|√| | | | |
|cm32m101a|√| | | | | |
|w801|√| | | | | |
|w806|√|√|√|√|√|√|
|apm32f030r8|√| | | | | |
|apm32e103vb|√| | | | | |
|bl-706|√| | | | | |
|Raspberry Pico|√| | | | | |
|ESP32C3|√| | | | | |
|TC264D|√| | | | | |
|devc|√| | | | | |

## Board support
|Board|bsp|gpio|uart|pwm|adc|i2c|rgb|lcd|arm-2d|
|---|---|---|---|---|---|---|---|---|---|
|[Pika-Pi-Zero](https://item.taobao.com/item.htm?spm=a230r.1.14.1.4f2e27a8R0qWJn&id=654947372034&ns=1&abbucket=15#detail)|√|√|√|√|√|√|√|√|√|

|Board|bsp|arm-2d|
|---|---|---|
|QEMU-arm2d|√|√|

|Board|bsp|LED|KEY|
|---|---|---|---|
|SmartLoong|√|√|√|√|

## OS support

|OS|port|GPIO|TIME|PWM|
|---|---|---|---|---|
|RT-Thread|√|√|√|√|
|vsf|√|√| | |

|OS|port|Google Test|Benchmark|
|---|---|---|---|
|linux|√|√|√|

# 3.Characteristic
### (1)Run environment

Support run in mcu without OS or file system. Can run in everywhere with **RAM ≥ 4kB** and **FLASH ≥ 32kB**，such as stm32g030, stm32f103c8t6，esp8266.

### (2)Develop enviroment

#### Support REPL by serial.

<img src="assets/1641178790145-2f026e70-4ba1-4e9a-b05f-c602b2bd8cad.png" width="400" alt="微信交流群"/><br/>

#### Support run and program python scripts by serial.

<img src="document/image/134841230-85de6734-8467-4245-93a5-d452b5022b42.gif" width="400" alt="微信交流群"/><br/>

Support IDEs like Keil, IAR, RT-Thread studio and segger embedded studio to develop C moudle.

Support build tools like CMake, makeFile and Scons.

Zero dependencies, zero configuration,  out-of-the-box, easy to integrated into privious C projcet.

Eazy to extern customized C moudles.

Support linux.

### (3)Syntax 

Support subaggregate of python 3 standard syntax.

Support class and method define, encapsulation-inheritance-polymorphism and moudles in `.pyi ` of C module.

|Syntax|Compile-Time|Run-Time|Shell|
|---|---|---|---|
|Module Define          |√|-|-|
|Module Import          |√|√|√|
|Class Define           |√|√|√|
|Class Inherit          |√|√|√|
|Method Define          |√|√|√|
|Method Override        |√|√|√|
|Method Invoke          |√|√|√|
|Argument Define        |√|√|√|
|Argument Assignment    |√|√|√|
|Object New             |√|√|√|
|Object Free            |√|√|√|
|Object Nest            |√|√|√|
|Control flow           |√|√|√|

#### Operator

| + | - | * | / | == | > | < | >= | <= | % | ** | // | != | & | >> | << | and | or | not | += | -= | *= | /= |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|√|√|√|√|√|√|√|√|√|√|√|√|√|√|√|√|√|√|√|√|√|√|√|

#### Control flow

| Syntax | State | Comment |
| --- | --- | --- |
| if | √ | |
| while | √ | |
| for in [list] | √ | ([PikaStdData.List](https://pikadoc.readthedocs.io/en/latest/PikaStdData%20%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84.html)) |
| for in range(a, b) | √ |  |
| for in [dict] | √ | ([PikaStdData.Dict](https://pikadoc.readthedocs.io/en/latest/PikaStdData%20%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84.html)) |
| if elif else | √ | |
| for break/continue | √ ||
| while break/continue | √ ||

#### Module

| Syntax | Python Module | C Module |
| --- | --- | --- |
| import [module] | √ | √ |
| import [module] as | √ | - |
| from [module] import [class/function>]| √ | - |
| from [module] import [class/function>] as | √ | - |
| from [module] import * | - | PikaObj Module Only |

#### List/Dict
| Syntax | State | Comment |
| --- | --- | --- |
| l = list() | √  | Need to enable the built-in-list in [configuration](https://pikadoc.readthedocs.io/en/latest/%E4%BC%98%E5%8C%96%E5%86%85%E5%AD%98%E5%8D%A0%E7%94%A8%E3%80%81%E9%85%8D%E7%BD%AE%20libc.html). |
| l = [a, b, c] | √  | Need to enable the built-in-list in [configuration](https://pikadoc.readthedocs.io/en/latest/%E4%BC%98%E5%8C%96%E5%86%85%E5%AD%98%E5%8D%A0%E7%94%A8%E3%80%81%E9%85%8D%E7%BD%AE%20libc.html). |
| d = dict() | √ | Need to enable the built-in-dict in [configuration](https://pikadoc.readthedocs.io/en/latest/%E4%BC%98%E5%8C%96%E5%86%85%E5%AD%98%E5%8D%A0%E7%94%A8%E3%80%81%E9%85%8D%E7%BD%AE%20libc.html). |
| d = {a:"x", b:"y", c:"z"} | -  | |

#### Exception

| try except | try except else | try except as | 
| --- | --- | --- |
| - | - | - |

#### Slice

| Syntax | str | bytes | list (PikaStdData.List) |
| --- | --- | --- | --- |
| test[i] | √ | - | √ |
| test[a : b : c] | - | - | - |
| test[a :] | - | - | - |

#### Other keywords/Syntax

| yield | is | comprehensions |
| --- | --- | --- |
| - | - | - |

### (4)Develop standard.

Readability first, nearly never use macro function and global argument.

Complete unit testes based on google test.

# 4.Both talk and show the code：

## Telegram

<img alt="tg" src="https://user-images.githubusercontent.com/88232613/158211488-0c27a35b-8ae4-4012-9954-f13cc374fdf7.jpg" width="300">

https://t.me/+JL3TZ9k-Lfg2OWE1

## E-mail: liang6516@outlook.com

## Tencent QQ： 645275593

# 5.Demo 

The scripts in demos are in the [examples](examples) folder.

## Demo 01 GPIO

``` python
import PikaStdLib
import STM32G0

mem = PikaStdLib.MemChecker()
io1 = STM32G0.GPIO()
time = STM32G0.Time()

io1.init()
io1.setPin('PA8')
io1.setMode('out')
io1.enable()
io1.low()

print('hello pikascript')
print('mem.max :')
mem.max()
print('mem.now :')
mem.now()

while True:
    io1.low()
    time.sleep_ms(500)
    io1.high()
    time.sleep_ms(500)

```

![Hnet-image (2)](document/image/132943428-f2b365ca-140e-42f4-936c-db6a7d9f8dee.gif)

## Demo 02 USART

``` python
import PikaStdLib
import STM32G0

time = STM32G0.Time()
uart = STM32G0.UART()
uart.init()
uart.setId(1)
uart.setBaudRate(115200)
uart.enable()

while True:
    time.sleep_ms(500)
    readBuff = uart.read(2)
    print('read 2 char:')
    print(readBuff)

```
![Hnet-image (3)](document/image/132943365-0f7059b3-4f9d-4989-a5ec-2cce72b0cc96.gif)


## Demo 03 ADC

``` python
import PikaStdLib
import STM32G0

time = STM32G0.Time()
adc1 = STM32G0.ADC()

adc1.init()
adc1.setPin('PA1')
adc1.enable()

while True:
    val = adc1.read()
    print('adc1 value:')
    print(val)
    time.sleep_ms(500)

```

![mmexport1631351523907](document/image/132944185-0a01b1ba-8cf7-4f9f-9d73-fe9cbcd52f0b.png)


## Demo 04 PWM output

``` python
import PikaStdLib
import STM32G0

time = STM32G0.Time()
pwm = STM32G0.PWM()
pwm.setPin('PA8')
pwm.setFrequency(2000)
pwm.setDuty(0.5)
pwm.enable()

while True:
    time.sleep_ms(500)
    pwm.setDuty(0.5)
    time.sleep_ms(500)
    pwm.setDuty(0.001)
    
```

## Demo 05 RGB

``` python
import STM32G0
import PikaPiZero
import PikaStdLib

rgb = PikaPiZero.RGB()
mem = PikaStdLib.MemChecker()

rgb.init()
rgb.enable()

print('hello 2')
print('mem used max:')
mem.max()

while True:
    print('flowing')
    rgb.flow()

```

## Demo 06 Snake(Need LCD)

``` python
from PikaObj import *
import PikaStdLib
import PikaPiZero
import STM32G0

# hardware init
lcd = PikaPiZero.LCD()
lcd.init()
lcd.clear('white')
key = PikaPiZero.KEY()
key.init()
time = STM32G0.Time()
x_max = 120
y_max = 150

# snake init
s = PikaPiZero.Point()
w = 9
h = 9
s.x = 50
s.y = 10
len = 0
while len < 3:
    b = s
    i = 0
    while i < len:
        b = b.next
        i = i + 1
    b.next = PikaPiZero.Point()
    b.next.x = b.x - 10
    b.next.y = b.y
    b.next.prev = b
    len = len + 1
# ring link
b.next = s
s.prev = b

i = 0
b = s
while i < len:
    lcd.fill(b.x, b.y, w, h, 'blue')
    b = b.next
    i = i + 1

print('snake lengh')
print(len)

# fruit init
f = PikaPiZero.Point()
f.x = 30
f.y = 20
lcd.fill(f.x, f.y, w, h, 'green')

# memory check
mem = PikaStdLib.MemChecker()
print('mem used max:')
mem.max()

# main loop
d = 0
isUpdate = 1
isEat = 0
while True:
    if isUpdate:
        # isUpdate = 0
        # check eat fruit
        if f.x == s.x and f.y == s.y:
            # have eat fruit
            isEat = 1
            f.x = f.x + 30
            if f.x > x_max:
                f.x = f.x - x_max
            f.y = f.y + 30
            if f.y > y_max:
                f.y = f.y - y_max
            lcd.fill(f.x, f.y, w, h, 'green')
        # move snake by the direction
        if d == 0:
            x_new = s.x + 10
            y_new = s.y
            if x_new > x_max:
                x_new = 0
        elif d == 1:
            x_new = s.x
            y_new = s.y - 10
            if y_new < 0:
                y_new = y_max
        elif d == 2:
            x_new = s.x
            y_new = s.y + 10
            if y_new > y_max:
                y_new = 0
        elif d == 3:
            x_new = s.x - 10
            y_new = s.y
            if x_new < 0:
                x_new = x_max
        if isEat:
            isEat = 0
            b_new = PikaPiZero.Point()
            b_new.x = x_new
            b_new.y = y_new
            b_new.prev = s.prev
            b_new.next = s
            s.prev.next = b_new
            s.prev = b_new
            s = b_new
            len = len + 1
            print('snake lengh')
            print(len)
            print('mem used max:')
            mem.max()
        # drow the snake and fruit
        # clear last body
        lcd.fill(s.prev.x, s.prev.y, w, h, 'white')
        # new body
        s.prev.x = x_new
        s.prev.y = y_new
        # head is last body
        s = s.prev
        lcd.fill(s.x, s.y, w, h, 'blue')
        b = s
        i = 0
    # scan key
    key_val = key.get()
    if key_val == 0:
        d = 0
        isUpdate = 1
    elif key_val == 1:
        d = 1
        isUpdate = 1
    elif key_val == 2:
        d = 2
        isUpdate = 1
    elif key_val == 3:
        d = 3
        isUpdate = 1
	
```

![image](https://user-images.githubusercontent.com/88232613/150269059-1fe3d62d-0c1b-40f4-9298-0d787f476a20.png)

The maximum RAM usage of these demos is only 3.56K, which is 4.56K if the 1K stack is included, and the maximum Flash usage is 30.4K. Refer to the 20K RAM and 64K Flash of STM32F103C8T6, less than 25% RAM and less than 50% Flash are used.

A quick comparison can be made between the microPython's MCU STM32F405RG and the PikaScript's MCU STM32G070CB.

## RAM resource comparison
![image](document/image/132944731-a55ece1d-061f-4b91-ba87-bd6547be96a7.png)

## Flash Resource Comparison
![image](document/image/132944745-e9cf598d-e75f-40bb-873e-911819d535b7.png)

## Reference price comparison (take the selling price of 10 pieces in Lichuang Mall on September 11, 2021 as reference)
![image](document/image/132944757-2b5cfda8-f93f-4456-8d7f-4e4767954056.png)

## About the custom extern module ？

In addition to device drivers, developing custom Python modules for MCU is very easy. The following two demos are extensions of the custom module, which developed python interfaces for the ARM-2D image driver library.

## Boxes~
![Hnet-image (7)](document/image/132945282-bfd310df-8063-456d-b90c-6b798a2c8ed5.gif)

## Rotating suns~
![Hnet-image (6)](document/image/132945107-e473a2cc-9fbc-47f9-aaed-a28d3ad1048c.gif)

# 6.Test and develop Core

## Test core in docker (recommend)
step1: Clone the repo
``` shell
git clone https://github.com/pikastech/pikascript
cd pikascript/docker 
```

step2: build and run the docker contianer
```
sh build.sh
sh run.sh
```

step3: init the port/linux
``` shell	
cd port/linux
sh pull-core.sh
sh init.sh
```

step4: test the core 
``` shell
sh gtest.sh
sh ci_benchmark.sh
```

step5: Run the REPL
``` shell
sh run.sh
```

# 7.Contribute

## [How to contribute](https://pikadoc.readthedocs.io/en/latest/%E5%A6%82%E4%BD%95%E5%8F%82%E4%B8%8E%E7%A4%BE%E5%8C%BA%E8%B4%A1%E7%8C%AE.html)

| Contribute log | Contributer |
| --- | --- |
| Add [PLOOC](https://github.com/GorgonMeducer/PLOOC) support for PikaScript Core | [GorgonMeducer](https://github.com/GorgonMeducer) |
| Donate：500¥ (ctypes 相关） | 蒋太平 |
| fix linux install script | [Maximilian Gerhardt](https://github.com/maxgerhardt) |
| ch582 package | [梦程MI](https://gitee.com/dreamcmi) |
| ch582 BSP | [梦程MI](https://gitee.com/dreamcmi) |
| Donate：EC600X QuecPython Develop board| 移远通信 武加玉 |
| Performance Point: 900->1400 | [GorgonMeducer](https://github.com/GorgonMeducer) |
| stm32f051r8 BSP |[unsigned](https://gitee.com/unsigned0)|
| stm32f407ze BSP |[unsigned](https://gitee.com/unsigned0)|
| devc BSP |[unsigned](https://gitee.com/unsigned0)|
| TC264D BSP |[unsigned](https://gitee.com/unsigned0)|
| PikaVM improvement | [GorgonMeducer](https://github.com/GorgonMeducer) |
| W801Device package | 刘延(微信名) |
| W806 bsp | 刘延(微信名) |
| Donate：ESP32C3 5pic，linker|启明云端 沧御|
| Donate：LS1C101 mcu 10pic, LS1c101 develop board，debuger|龙芯俱乐部 石南|
| PikaVSF OS package | [versaloon](https://github.com/versaloon) |
| ESP32C3 BSP |沧御|
| Donate：ESP32 board、ink lcd*4 | name(微信名) |
| Donate：smartloong board | 龙芯俱乐部 石南 |
| package/STM32F1 | [sjy](https://gitee.com/shanjiayang) |
| package/STM32F103RBBooter | [sjy](https://gitee.com/shanjiayang) |
| bsp/stm32f103rb | [sjy](https://gitee.com/shanjiayang) |
| QEMU ARM-2D simulation proejct | [liuduanfei](https://github.com/liuduanfei) |
| Donate：GD32E103TB2 2 pic | 信息牛(微信名) |
| Rt-thread bsp、port、module| [Meco Jianting Man](https://github.com/mysterywolf) |
| Donate：EC600S-CN 4G| 移远模块 |
| Donate：BL706 board|博流智能 [bouffalolab](https://github.com/bouffalolab)|
| Donate：CM32M101A 开发板| 孟巍(微信名) |
| Donate：APM32F030R8 board | 极海半导体 陈成 |
| Donate：APM32E103VB board | 极海半导体 陈成 |
| Donate：APEX-Link| 极海半导体 陈成 |
| corde format，add gitattributes| [Meco Jianting Man](https://github.com/mysterywolf) |
| demo/simulation-keil | 千帆(微信名) |
| demo/stm32f103zet6/demo01-led-stm32f103zet6 | [甜航](https://github.com/easyzoom) |
| demo/stm32f103zet6/demo02-led-stm32f103zet6_tworoot | [甜航](https://github.com/easyzoom) |
| demo/stm32f407zgt/demo01-led-stm32f407vgt | [甜航](https://github.com/easyzoom) |

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=pikastech/pikascript&type=Date)](https://star-history.com/#pikastech/pikascript&Date)