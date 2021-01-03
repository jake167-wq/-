#include "rc.h"
#include "stm32f4xx.h"


void RC_Init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num)
{
    /* -------------- Enable Module Clock Source ----------------------------*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_DMA2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //PA10  usart1 rx
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

        USART_DeInit(USART1); //����Ĭ�ϴ���1

        USART_InitStructure.USART_BaudRate = 100000;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_Even; //żУ��
        USART_InitStructure.USART_Mode = USART_Mode_Rx;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_Init(USART1, &USART_InitStructure); //���ô���1

        USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE); //����dma rx

        USART_ClearFlag(USART1, USART_FLAG_IDLE);      //��������жϱ�־λ
        USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); //�����ж�

        USART_Cmd(USART1, ENABLE); //ʹ�ܴ���1
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
    //2��DMA  ÿ�� DMA �������� 8 ����������ÿ���������ж�� 8 ��ͨ��    ��2*8*8 ͨ��
    /* -------------- Configure DMA -----------------------------------------*/
    {
        DMA_InitTypeDef DMA_InitStructure;
        DMA_DeInit(DMA2_Stream2); //����DMA2��2ͨ��

        DMA_InitStructure.DMA_Channel = DMA_Channel_4;                          //ͨ��4
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (USART1->DR);   //��Χ��ַ
        DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rx1_buf;              //�ڴ��ַ
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;                 //ģʽ��Χ���ڴ�
        DMA_InitStructure.DMA_BufferSize = dma_buf_num;                         //����һ�δ����������Ĵ�С
        DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        //��Χ��ַ�Ĵ���������
        DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 //�ڴ��ַ����
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //��Χ����Ϊ��λ
        DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         //�ڴ�����Ϊ��λ
        DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         //ѭ��ģʽ
        DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 //������ȼ�
        DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;                  //��ʹ��FIFO
        DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
        DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
        DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
        DMA_Init(DMA2_Stream2, &DMA_InitStructure); //����
        DMA_DoubleBufferModeConfig(DMA2_Stream2, (uint32_t)rx2_buf, DMA_Memory_0);
        DMA_DoubleBufferModeCmd(DMA2_Stream2, ENABLE); //˫����ģʽ
        DMA_Cmd(DMA2_Stream2, DISABLE);                //Add a disable
        DMA_Cmd(DMA2_Stream2, ENABLE);
    }
}
void RC_unable(void)
{
    USART_Cmd(USART1, DISABLE);
}
void RC_restart(uint16_t dma_buf_num)
{
    USART_Cmd(USART1, DISABLE);
    DMA_Cmd(DMA2_Stream2, DISABLE);
    DMA_SetCurrDataCounter(DMA2_Stream2, dma_buf_num);

    USART_ClearFlag(USART1, USART_FLAG_IDLE);

    DMA_ClearFlag(DMA2_Stream2, DMA_FLAG_TCIF2);
    DMA_ClearITPendingBit(DMA2_Stream2, DMA_IT_TCIF2);
    DMA_Cmd(DMA2_Stream2, ENABLE);
    USART_Cmd(USART1, ENABLE);
}