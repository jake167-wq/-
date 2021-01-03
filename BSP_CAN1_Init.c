//#include "BSP_CAN1_Init.h"

///*----CAN1_TX-----PA12----*/
///*----CAN1_RX-----PA11----*/

//Can_DataStruct xCan_Handler[2];

///*************************************************************************
//函数名称：CAN1_Configuration
//函数功能：初始化CAN1配置为1M波特率
//*************************************************************************/
//void CAN1_Configuration(void)
//{
//    /*****************************************定义各模块结构体变量**********************************************/
//    CAN_InitTypeDef        CAN_InitStruct;
//    CAN_FilterInitTypeDef  CAN_InitFilter;
//    GPIO_InitTypeDef       GPIO_InitStruct;
//    /*******************************************使能时钟**********************************************/
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

//    /*******************************配置CAN输出段所对应的IO口复用功能*********************************/
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_Init(GPIOA, &GPIO_InitStruct);

//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);


//    /********************************************复位CAN1**********************************************/
//    CAN_DeInit(CAN1);
//    CAN_StructInit(&CAN_InitStruct);
//    /*************************************初始化CAN总线模式及波特率************************************/
//    CAN_InitStruct.CAN_TTCM = DISABLE;													//失能时间触发通信模式
//    CAN_InitStruct.CAN_ABOM = DISABLE;													//失能自动的总线关闭管理
//    CAN_InitStruct.CAN_AWUM = DISABLE;													//失能自动唤醒模式
//    CAN_InitStruct.CAN_NART = DISABLE;													//使能自动重发功能
//    CAN_InitStruct.CAN_RFLM = DISABLE;													//接收FIFO上溢后不锁定，后一条覆盖前一条
//    CAN_InitStruct.CAN_TXFP = ENABLE;														//使能发送FIFO的优先级
//    CAN_InitStruct.CAN_Mode = CAN_Mode_Normal;								//设置CAN总线工作在回环模式
//    /*************************************
//    	BaudRate = 1 / NominalBitTime,
//    	NominalBitTime = tq + tBS1 + tBS2,
//    	tBS1 = tq x (TS1[3:0] + 1),
//    	tBS2 = tq x (TS2[2:0] + 1),
//    	tq = (BRP[9:0] + 1) x tPCLK,
//    	tPCLK = APB 时钟周期
//    	***********************************/
//    CAN_InitStruct.CAN_SJW  = CAN_SJW_1tq;
//    CAN_InitStruct.CAN_BS1 = CAN_BS1_9tq;
//    CAN_InitStruct.CAN_BS2 = CAN_BS2_4tq;
//    CAN_InitStruct.CAN_Prescaler = 3;   																//CAN BaudRate 42/(1+9+4)/3=1Mbps
//    CAN_Init(CAN1, &CAN_InitStruct);
//    /*************************************初始化过滤器组************************************/
//    //CAN1的过滤器组从0-13
//    CAN_InitFilter.CAN_FilterNumber = 0;													//选择过滤器组0
//    CAN_InitFilter.CAN_FilterMode = CAN_FilterMode_IdMask;				//设置标识符列表模式
//    CAN_InitFilter.CAN_FilterScale = CAN_FilterScale_32bit;				//设置过滤器组0的位宽为32
//    CAN_InitFilter.CAN_FilterIdHigh = 0x0000;											//设置所有过滤标识符ID都被允许
//    CAN_InitFilter.CAN_FilterIdLow = 0x0000;
//    CAN_InitFilter.CAN_FilterMaskIdHigh = 0x0000;									//设置所有的ID都为不用关心，都不被过滤
//    CAN_InitFilter.CAN_FilterMaskIdLow = 0x0000;
//    CAN_InitFilter.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;									//给该过滤器分配一个FIFO0
//    CAN_InitFilter.CAN_FilterActivation=ENABLE;
//    CAN_FilterInit(&CAN_InitFilter);															//滤波器初始化

//    xCan_Handler[CANCOM1].CANx=CAN1;
//    xCan_Handler[CANCOM1].TxBinarySemaphore=xSemaphoreCreateBinary();

//    //创建CAN1的发送数据队列
//    osMessageQDef_t TxCOM1;
//    TxCOM1.queue_sz=50;        ///< number of elements in the queue
//    TxCOM1.item_sz=sizeof(CanTxMsg);
//    xCan_Handler[CANCOM1].TxMessage_Queue=osMessageCreate(&TxCOM1,NULL);

//    //创建CAN1的接收数据队列
//    osMessageQDef_t RxCOM1;
//    RxCOM1.queue_sz=50;        ///< number of elements in the queue
//    RxCOM1.item_sz=sizeof(CanRxMsg);
//    xCan_Handler[CANCOM1].RxMessage_Queue=osMessageCreate(&RxCOM1,NULL);


//    /***************************************使能CAN中断*************************************/
//    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
//    CAN_ITConfig(CAN1,CAN_IT_TME,DISABLE);
//}

///*************************************************************************
//函数名称：CAN1_TX_IRQHandler
//函数功能：CAN1的发送中断函数
//*************************************************************************/
////void CAN1_TX_IRQHandler(void)
////{
////    if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET)
////    {
////        CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
////    }
////}


///*************************************************************************
//函数名称：CAN1_RX0_IRQHandler
//函数功能：CAN1的接收中断函数
//********************************************0*****************************/

////void CAN1_RX0_IRQHandler(void)
////{
////    CanRxMsg rx_message;
////    if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
////    {

////        CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
////        BaseType_t  TaskWoken;
////        //将CAN1接收到的数据放到接收数据队列中
////        xQueueSendFromISR(xCan_Handler[CANCOM1].RxMessage_Queue,&rx_message,&TaskWoken);
////    }
////    CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
////}


