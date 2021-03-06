//#include "init.h"
//#include "BSP_CAN1_Init.h"

///*----CAN2_TX-----PB13----*/
///*----CAN2_RX-----PB12----*/

///*************************************************************************
//函数名称：CAN2_Configuration
//函数功能：初始化CAN2配置为1M波特率
//*************************************************************************/
//void CAN2_Configuration(void)
//{
//    /*****************************************定义各模块结构体变量**********************************************/
//    CAN_InitTypeDef        CAN_InitStruct;
//    CAN_FilterInitTypeDef  CAN_InitFilter;
//    GPIO_InitTypeDef       GPIO_InitStruct;
//    /*******************************************使能时钟**********************************************/
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

//    /*******************************配置CAN输出段所对应的IO口复用功能*********************************/
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_Init(GPIOB, &GPIO_InitStruct);

//    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);
//    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);


//    /********************************************复位CAN2**********************************************/
//    CAN_DeInit(CAN2);
//    CAN_StructInit(&CAN_InitStruct);
//    /*************************************初始化CAN总线模式及波特率************************************/
//    CAN_InitStruct.CAN_TTCM = DISABLE;													//失能时间触发通信模式
//    CAN_InitStruct.CAN_ABOM = DISABLE;													//失能自动的总线关闭管理
//    CAN_InitStruct.CAN_AWUM = DISABLE;													//失能自动唤醒模式
//    CAN_InitStruct.CAN_NART = DISABLE;													//使能自动重发功能
//    CAN_InitStruct.CAN_RFLM = DISABLE;													//接收FIFO上溢后不锁定，后一条覆盖前一条
//    CAN_InitStruct.CAN_TXFP = ENABLE;														//使能发送FIFO的优先级
//    CAN_InitStruct.CAN_Mode = CAN_Mode_Normal;								//设置CAN总线工作在正常模式
//    /*************************************
//    BaudRate = 1 / NominalBitTime,
//    NominalBitTime = tq + tBS1 + tBS2,
//    tBS1 = tq x (TS1[3:0] + 1),
//    tBS2 = tq x (TS2[2:0] + 1),
//    tq = (BRP[9:0] + 1) x tPCLK,
//    tPCLK = APB 时钟周期
//    ***********************************/
//    CAN_InitStruct.CAN_SJW  = CAN_SJW_1tq;
//    CAN_InitStruct.CAN_BS1 = CAN_BS1_9tq;
//    CAN_InitStruct.CAN_BS2 = CAN_BS2_4tq;
//    CAN_InitStruct.CAN_Prescaler =3;   																//CAN BaudRate 42/(1+9+4)/3=1Mbps
//    CAN_Init(CAN2, &CAN_InitStruct);
//    /*************************************初始化过滤器组************************************/
//    //CAN2的过滤器组从14-27
//    CAN_InitFilter.CAN_FilterNumber = 14;													//选择过滤器组14
//    CAN_InitFilter.CAN_FilterMode = CAN_FilterMode_IdMask;				//设置标识符列表模式
//    CAN_InitFilter.CAN_FilterScale = CAN_FilterScale_32bit;				//设置过滤器组14的位宽为32
//    CAN_InitFilter.CAN_FilterIdHigh = 0x0000;											//设置所有过滤标识符ID都被允许
//    CAN_InitFilter.CAN_FilterIdLow = 0x0000;
//    CAN_InitFilter.CAN_FilterMaskIdHigh = 0x0000;									//设置所有的ID都为不用关心，都不被过滤
//    CAN_InitFilter.CAN_FilterMaskIdLow = 0x0000;
//    CAN_InitFilter.CAN_FilterFIFOAssignment = CAN_Filter_FIFO1;									//给该过滤器分配一个FIFO1
//    CAN_InitFilter.CAN_FilterActivation=ENABLE;
//    CAN_FilterInit(&CAN_InitFilter);															//滤波器初始化

//    xCan_Handler[CANCOM2].CANx=CAN2;
//    xCan_Handler[CANCOM2].TxBinarySemaphore=xSemaphoreCreateBinary();

//    //创建CAN2的发送数据队列
//    osMessageQDef_t TxCOM2;
//    TxCOM2.item_sz=sizeof(CanRxMsg);        ///< number of elements in the queue
//    TxCOM2.queue_sz=10;

////		TxCOM2.item_sz=10;        ///< number of elements in the queue
////		TxCOM2.queue_sz=sizeof(CanTxMsg );
//    xCan_Handler[CANCOM2].TxMessage_Queue=osMessageCreate(&TxCOM2,NULL);

//    //创建CAN2的接受数据队列
//    osMessageQDef_t RxCOM2;
//    RxCOM2.item_sz=sizeof(CanRxMsg);     		///< number of elements in the queue
//    RxCOM2.queue_sz=10;
////      RxCOM2.item_sz=10;
////			RxCOM2.queue_sz=sizeof(CanRxMsg);
//    xCan_Handler[CANCOM2].RxMessage_Queue=osMessageCreate(&RxCOM2,NULL);

//    /***************************************使能CAN中断*************************************/
//    CAN_ITConfig(CAN2,CAN_IT_FMP1,ENABLE);
//    CAN_ITConfig(CAN2,CAN_IT_TME,DISABLE);
//}
///*************************************************************************
//函数名称：CAN2_TX_IRQHandler
//函数功能：CAN2的发送中断函数
//*************************************************************************/
////void CAN2_TX_IRQHandler(void)
////{
////    if(CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET)
////    {
////        CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
////    }
////}


///*************************************************************************
//函数名称：CAN2_RX1_IRQHandler
//函数功能：CAN2的接收中断函数
//*************************************************************************/
////void CAN2_RX1_IRQHandler(void)
////{
////    CanRxMsg rxmessage;
//////	  CanRxMsg rx_message;
////    if(CAN_GetITStatus(CAN2,CAN_IT_FMP1)!= RESET)
////    {
////        CAN_ClearITPendingBit(CAN2, CAN_IT_FMP1);
////        CAN_Receive(CAN2, CAN_FIFO1, &rxmessage);
////        BaseType_t  TaskWoken;

////        //将接收到的数据放到接收队列中
////        xQueueSendFromISR(xCan_Handler[CANCOM2].RxMessage_Queue,&rxmessage,&TaskWoken);
////    }
////    CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
////}

