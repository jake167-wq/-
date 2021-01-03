#ifndef _USART_INIT_H
#define _USART_INIT_H

#include "main.h"
#include "init.h"

//枚举
enum {sercom2,sercom4,sercom6};



//用于创建队列
typedef struct
{
    USART_TypeDef      *USART;
    SemaphoreHandle_t  TxBinarySemaphore;
    QueueHandle_t      TxMessage_Queue;
    QueueHandle_t      RxMessage_Queue;
} ALLData_Struct;







extern ALLData_Struct xUart_Handler[3];


void Device_Usart1_ENABLE_Init(u32 bound);
void Device_Usart6_ENABLE_Init(u32 bound);
void Device_Usart4_ENABLE_Init(u32 bound);
void Device_Usart2_ENABLE_Init(u32 bound);

#endif

