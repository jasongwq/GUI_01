#ifndef __GALILEO_0920_
#define __GALILEO_0920_

#ifdef __cplusplus
extern "C" {
#endif

//重定义IO口
//与DAC5687相连的引脚
#define SDO_OUT       PC10_OUT
#define SDO_IN        PC10_In
#define Clr_SDO       Clr_C10
#define Set_SDO       Set_C10
#define SDO           C10


#define SDIO5687_OUT  PC11_OUT
#define SDIO5687_IN   PC11_In
#define Clr_SDIO5687  Clr_C11
#define Set_SDIO5687  Set_C11

#define SCLK_OUT       PC12_OUT
#define SCLK_IN        PC12_In
#define Clr_SCLK       Clr_C12
#define Set_SCLK       Set_C12

#define SDENB_OUT      PD2_OUT
#define SDENB_IN       PD2_In
#define Clr_SDENB      Clr_D2
#define Set_SDENB      Set_D2

#define RESETB_OUT      PE1_OUT
#define RESETB_IN       PE1_In
#define Clr_RESETB      Clr_E1
#define Set_RESETB      Set_E1

//与ADF4360相连的引脚
#define CE4360_OUT    PC6_OUT
#define CE4360_IN     PC6_In
#define Clr_CE4360    Clr_C6
#define Set_CE4360    Set_C6

#define LE4360_OUT    PC7_OUT
#define LE4360_IN     PC7_In
#define Clr_LE4360    Clr_C7
#define Set_LE4360    Set_C7

#define DATA4360_OUT  PC8_OUT
#define DATA4360_IN   PC8_In
#define Clr_DATA4360  Clr_C8
#define Set_DATA4360  Set_C8

#define CLK4360_OUT    PC9_OUT
#define CLK4360_IN     PC9_In
#define Clr_CLK4360    Clr_C9
#define Set_CLK4360    Set_C9

//与LED相连的引脚
#define LED_OUT      PC13_OUT
#define LED_IN       PC13_In
#define Clr_LED      Clr_C13
#define Set_LED      Set_C13

#ifdef __cplusplus
}
#endif
#endif


