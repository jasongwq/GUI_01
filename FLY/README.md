工程使用MDK5编写 Keil.STM32F1xx_DFP.1.1.0
工程结构
./CORE
./FWLIB
./USER
    ./main.cpp           主函数
./TASK
    ./task_display.cpp   显示任务 主要用于触发点击事件
    ./UI.cpp             UI库
    ./UI_USER.cpp        界面配置文件
./SYSTEM
./HARDWARE
./APP
    galileo_0920.c       驱动
./DISPLAY