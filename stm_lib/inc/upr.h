#include "stm32f10x_conf.h"
#include "delay_.h"


// Define for configure MUX

#define PORT_IMUX_UPR GPIOB
#define IMUX_UPR_1 GPIO_Pin_3
#define IMUX_UPR_2 GPIO_Pin_4
#define IMUX_UPR_3 GPIO_Pin_5
#define IMUX_UPR_ALL GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5

#define PORT_IMUX_SET GPIOB
#define IMUX_SET_1 GPIO_Pin_6
#define IMUX_SET_2 GPIO_Pin_7
#define IMUX_SET_3 GPIO_Pin_8
#define IMUX_SET_ALL GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8
///////////////////////////////////////////////////////////
#define PORT_OMUX_UPR GPIOA
#define OMUX_UPR_1 GPIO_Pin_7
#define OMUX_UPR_2 GPIO_Pin_8
#define OMUX_UPR_3 GPIO_Pin_9
#define OMUX_UPR_ALL GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9

#define PORT_OMUX_SET GPIOA
#define OMUX_SET_1 GPIO_Pin_10
//#define OMUX_SET_2  GPIO_Pin_11
#define OMUX_SET_3 GPIO_Pin_12
//#define OMUX_SET_ALL  GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12
/////////////////////////////////////////////////////////////
#define PORT_IMUX_SUM_UPR GPIOB
#define IMUX_SUM_UPR_1 GPIO_Pin_0
#define IMUX_SUM_UPR_2 GPIO_Pin_1
#define IMUX_SUM_UPR_3 GPIO_Pin_2
#define IMUX_SUM_UPR_ALL GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2



void iconfig(uint8_t channal);
void oconfig(uint8_t channal);
void reset_IO(void);

