# Video-Image-Processing

[![](https://img.shields.io/badge/author-TongxinV-green.svg)](https://github.com/TongxinV)
[![GitHub issues](https://img.shields.io/github/issues/TongxinV/Video-Image-Processing.svg)](https://github.com/TongxinV/Video-Image-Processing/issues)



DoING 基于嵌入式的视觉运动控制

> 还在进行...

### Environment

* Arch：s5pv210 cortex-A8
* OS：linux2.6.35
* Camera：映美精 DFK 22BUC03 USB2.0 CCD摄像头


### Features

* 图像采集 | 视频显示
* 图像处理 | 提取信息
* 利用串口发送消息(undetermined)
* 控制步进电机


### Tree


    .
    ├── app
    │   ├── app.pro
    │   └── main.cpp
    ├── bin
    │   
    ├── include
    │   ├── c1image.h
    │   ├── c1painter.h
    │   ├── c1screen.h
    │   ├── codec
    │   │   ├── e1bitmap.cpp
    │   │   └── e1bitmap.h
    │   └── smdkv210
    │       ├── linuxfbscreen.h
    │       ├── showvideo.h
    │       └── videodevice.h
    ├── lib
    │   
    ├── src
    │   ├── c1image.cpp
    │   ├── c1painter.cpp
    │   ├── c1screen.cpp
    │   ├── smdkv210
    │   │   ├── linuxfbscreen.cpp
    │   │   ├── showvideo.cpp
    │   │   └── videodevice.cpp
    │   └── src.pro
    │ 
    ├── complex.pro
    ├── complex.pro.user
    └── README.md


### License


---
author：@TongxinV
