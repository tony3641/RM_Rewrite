# RoboMaster Summer Camp 2018 Team **Deep♂Dark**
![team](https://img.shields.io/badge/Team-Deep%E2%99%82Dark-yellow.svg)     ![group](https://img.shields.io/badge/Group-14-blue.svg)
fuck keil :point_down::thumbsdown:  

the rewrite of RoboMaster Summer Camp control framework.

# ChangeLog
 - 7/19
    * 建立工程
    * 添加 `motor_device.h` ,  `motor_device.c` , `motor_operation.h`，重新封装电机结构
 - 7/20
    * 完善电机 PID 
    * CAN 通信无法发送单电机电流，故重写该部分调用
 - 7/22
    * 修复全部电机空指针问题
    * 尝试使用状态机实现自动程序
    * 以上全部未经测试 :joy:
- 7/26
    * 弃用电机指针，改为全局共享值变量
    * 无法正常运行
