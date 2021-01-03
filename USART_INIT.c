#include "USART_INIT.h"


#define COM1_BUFFER_LEN 36u
ALLData_Struct xUart_Handler[3];
static char ucCom1Buffer[2][ COM1_BUFFER_LEN ] = {0};

/**   USART2  PC    **/
/*
		UART4_TX->PA2		UART4_RX->PC3
*/

void Device_Usart1_ENABLE_Init(u32 baud_rate)
{
 /* -------------- Enable Module Clock Source ----------------------------*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_DMA2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    /* -------------- Configure GPIO ---------------------------------------*/
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        USART_DeInit(USART1);

        USART_InitStructure.USART_BaudRate = baud_rate;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_Even;
        USART_InitStructure.USART_Mode = USART_Mode_Rx;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_Init(USART1, &USART_InitStructure);

        USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

        USART_ClearFlag(USART1, USART_FLAG_IDLE);
        USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

        USART_Cmd(USART1, ENABLE);
    }

    /* -------------- Configure NVIC ---------------------------------------*/
    {
        NVIC_InitTypeDef NVIC_InitStructure;
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
    }

    //DMA2 stream5 ch4  or (DMA2 stream2 ch4)    !!!!!!! P206 of the datasheet
    /* -------------- Configure DMA -----------------------------------------*/
    {
        DMA_InitTypeDef DMA_InitStructure;
        DMA_DeInit(DMA2_Stream2);

        DMA_InitStructure.DMA_Channel = DMA_Channel_4;
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (USART1->DR);
        DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ucCom1Buffer[0][0];
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
        DMA_InitStructure.DMA_BufferSize = sizeof(ucCom1Buffer)/2;
        DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
        DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
        DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
        DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
        DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
        DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
        DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
        DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
        DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
        DMA_Init(DMA2_Stream2, &DMA_InitStructure);
        DMA_DoubleBufferModeConfig(DMA2_Stream2, (uint32_t)(uint32_t)&ucCom1Buffer[1][0], DMA_Memory_0);
        DMA_DoubleBufferModeCmd(DMA2_Stream2, ENABLE);
        DMA_Cmd(DMA2_Stream2, DISABLE); //Add a disable
        DMA_Cmd(DMA2_Stream2, ENABLE);
    }
}

void Device_Usart2_ENABLE_Init(u32 bound)
{




}


/**   USART4   用来读取裁判系统    **/
/*
		UART4_TX->PC10		UART4_RX->PC11
*/

void Device_Usart4_ENABLE_Init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef UART_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    USART_DeInit(UART4);
    USART_StructInit(&UART_InitStructure);

    UART_InitStructure.USART_BaudRate = bound;//波特率
    UART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8位数据
    UART_InitStructure.USART_StopBits = USART_StopBits_1;   //在帧结尾传输1个停止位
    UART_InitStructure.USART_Parity = USART_Parity_No;    //禁用奇偶校验
    UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制失能
    UART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //发送、接收使能
    USART_Init(UART4, &UART_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;                   //U4DMATC中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);        //usart IDLE line interrupt  enabled

    xUart_Handler[sercom4].USART=UART4;
    xUart_Handler[sercom4].TxBinarySemaphore=xSemaphoreCreateBinary();     //semaphore

    //串口4发送数据队列创建
    osMessageQDef_t TxCOM4;
    TxCOM4.queue_sz=45;     		 ///< number of elements in the queue
    TxCOM4.item_sz=sizeof(u8);  ///< size of an item

    xUart_Handler[sercom4].TxMessage_Queue=osMessageCreate(&TxCOM4,NULL);

    //串口4接收数据队列创建
    osMessageQDef_t RxCOM4;
    RxCOM4.queue_sz=45;

    RxCOM4.item_sz=sizeof(u8);
    xUart_Handler[sercom4].RxMessage_Queue=osMessageCreate(&RxCOM4,NULL);

    USART_Cmd(UART4, ENABLE);
}


/*
	 USART6_TX->PC6		USART6_RX->PC7
// function: USB转串口初始端口
*/

void Device_Usart6_ENABLE_Init(u32 bound)
{
    /* -------------- Enable Module Clock Source ----------------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_DMA2 ,ENABLE);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
    /* -------------- Configure GPIO ---------------------------------------*/
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
        GPIO_Init(GPIOC, &GPIO_InitStructure);


        USART_DeInit(USART6);

        USART_InitStructure.USART_BaudRate = bound;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_Init(USART6, &USART_InitStructure);

        USART_DMACmd(USART6, USART_DMAReq_Rx, ENABLE);
    }
    /* -------------- Configure NVIC ---------------------------------------*/
    {
        NVIC_InitTypeDef NVIC_InitStructure;
        NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 9;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
    }
    /* -------------- Configure DMA -----------------------------------------*/
    {
//        DMA_InitTypeDef DMA_InitStructure;
//        DMA_DeInit(DMA2_Stream1);




    }
}

//串口总线空闲中断：在检测到接收数据之后，数据总线上一个字节的时间内没有接收到数据则发生中断
void UART4_IRQHandler(void)
{
    u8 Res;
//	static uint32_t this_time_rx_len = 0;
//	datarevice Buffer;
    BaseType_t  TaskWoken;
    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
        //clear the idle pending flag
        USART_ClearITPendingBit(UART4, USART_IT_RXNE);
        (void)UART4->SR;
        (void)UART4->DR;
        Res =USART_ReceiveData(UART4);	//读取接收到的数据
        xQueueSendFromISR(xUart_Handler[sercom4].RxMessage_Queue,&Res,&TaskWoken);
    }
}

void USART6_IRQHandler(void)
{









}

