#ifndef __BSP_CAN1_INIT_H__
#define __BSP_CAN1_INIT_H__
#include "stm32f4xx_can.h"
#include "cmsis_os.h"
void CAN1_Configuration(void);
void CAN2_Configuration(void);

enum {CANCOM1,CANCOM2};
typedef struct
{
    CAN_TypeDef      *CANx;
    SemaphoreHandle_t  TxBinarySemaphore;
    QueueHandle_t    TxMessage_Queue;
    QueueHandle_t    RxMessage_Queue;
} Can_DataStruct;

extern Can_DataStruct xCan_Handler[2];

#endif
