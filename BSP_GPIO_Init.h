#ifndef _GPIO_INIT_H
#define _GPIO_INIT_H
#include "sys.h"
/*=========�ɿ���==========*/

/*===========================*/
/*=========�һ�����==========*/

/*===========================*/
/*=========�ϰ��鹦��========*/

/*===========================*/
/*=========��ҩ��============*/

/*===========================*/
/*==========��Ԯ=============*/
/*===========================*/
//void GPIO_Init();
//��ŷ�
#define AC_TF_Channel_1_ON  GPIO_SetBits(GPIOD,GPIO_Pin_2)         //���跧�Ŵ�
#define AC_TF_Channel_1_OFF GPIO_ResetBits(GPIOD,GPIO_Pin_2)

#define AC_TF_Channel_2_ON  GPIO_SetBits(GPIOC,GPIO_Pin_10)         //�����Ƴ�..
#define AC_TF_Channel_2_OFF GPIO_ResetBits(GPIOC,GPIO_Pin_10)

#define AC_TF_Channel_3_ON  GPIO_SetBits(GPIOB,GPIO_Pin_4)         //��ת����..
#define AC_TF_Channel_3_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_4)

#define AC_TF_Channel_4_ON  GPIO_SetBits(GPIOC,GPIO_Pin_11)         //���ֿ���..
#define AC_TF_Channel_4_OFF GPIO_ResetBits(GPIOC,GPIO_Pin_11)

#define AC_TF_Channel_5_ON  GPIO_SetBits(GPIOB,GPIO_Pin_3)         //��ҩ�䵯��
#define AC_TF_Channel_5_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_3)

#define AC_TF_Channel_6_ON  GPIO_SetBits(GPIOC,GPIO_Pin_12)         //����̧��
#define AC_TF_Channel_6_OFF GPIO_ResetBits(GPIOC,GPIO_Pin_12)

#define AC_TF_Channel_7_ON  GPIO_SetBits(GPIOB,GPIO_Pin_5)         //��Ԯ
#define AC_TF_Channel_7_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_5)

#define AC_TF_Channel_8_ON  GPIO_SetBits(GPIOB,GPIO_Pin_6)         //��Ԯ��
#define AC_TF_Channel_8_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_6)


#define BUZZER_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_9)         	//������
#define BUZZER_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_9)

#define 	GREEN_OFF 			GPIO_SetBits(GPIOB,GPIO_Pin_8);
#define 	GREEN_ON 				GPIO_ResetBits(GPIOB,GPIO_Pin_8);
#define 	RED_OFF 				GPIO_SetBits(GPIOB,GPIO_Pin_9);
#define 	RED_ON 					GPIO_ResetBits(GPIOB,GPIO_Pin_9);
#define 	RED_TOGGLE 			GPIO_ToggleBits(GPIOB,GPIO_Pin_9);
#define 	GREEN_TOGGLE 		GPIO_ToggleBits(GPIOB,GPIO_Pin_8);

#define 	LED2_OFF 			GPIO_SetBits(GPIOB,GPIO_Pin_9);
#define 	LED3_OFF 			GPIO_SetBits(GPIOB,GPIO_Pin_8);

#define 	LED2_ON 			GPIO_ResetBits(GPIOB,GPIO_Pin_9);
#define 	LED3_ON 			GPIO_ResetBits(GPIOB,GPIO_Pin_8);

#define 	D1_OFF 			GPIO_SetBits(GPIOD,GPIO_Pin_2);
#define 	D2_OFF 			GPIO_SetBits(GPIOC,GPIO_Pin_6);
#define 	D3_OFF 			GPIO_SetBits(GPIOB,GPIO_Pin_14);
#define 	D4_OFF 			GPIO_SetBits(GPIOA,GPIO_Pin_15);
#define 	D5_OFF 			GPIO_SetBits(GPIOA,GPIO_Pin_8);
#define 	D6_OFF 			GPIO_SetBits(GPIOB,GPIO_Pin_3);
#define 	D7_OFF 			GPIO_SetBits(GPIOC,GPIO_Pin_10);
#define 	D8_OFF 			GPIO_SetBits(GPIOA,GPIO_Pin_9);
#define 	D9_OFF 			GPIO_SetBits(GPIOB,GPIO_Pin_15);
#define 	D10_OFF 		GPIO_SetBits(GPIOC,GPIO_Pin_7);
#define 	D11_OFF 		GPIO_SetBits(GPIOC,GPIO_Pin_8);
#define 	D12_OFF 		GPIO_SetBits(GPIOB,GPIO_Pin_4);
#define 	D13_OFF 		GPIO_SetBits(GPIOC,GPIO_Pin_11);
#define 	D14_OFF 		GPIO_SetBits(GPIOC,GPIO_Pin_9);
#define 	D15_OFF 		GPIO_SetBits(GPIOC,GPIO_Pin_12);
#define 	D16_OFF 		GPIO_SetBits(GPIOB,GPIO_Pin_7);


#define 	D1_ON 			GPIO_ResetBits(GPIOD,GPIO_Pin_2);
#define 	D2_ON 			GPIO_ResetBits(GPIOC,GPIO_Pin_6);
#define 	D3_ON				GPIO_ResetBits(GPIOB,GPIO_Pin_14);
#define 	D4_ON 			GPIO_ResetBits(GPIOA,GPIO_Pin_15);
#define   D5_ON 			GPIO_ResetBits(GPIOA,GPIO_Pin_8);
#define 	D6_ON 			GPIO_ResetBits(GPIOB,GPIO_Pin_3);
#define 	D7_ON 			GPIO_ResetBits(GPIOC,GPIO_Pin_10);
#define 	D8_ON 			GPIO_ResetBits(GPIOA,GPIO_Pin_9);
#define 	D9_ON 			GPIO_ResetBits(GPIOB,GPIO_Pin_15);
#define 	D10_ON 		  GPIO_ResetBits(GPIOC,GPIO_Pin_7);
#define 	D11_ON 		  GPIO_ResetBits(GPIOC,GPIO_Pin_8);
#define 	D12_ON 		  GPIO_ResetBits(GPIOB,GPIO_Pin_4);
#define 	D13_ON 		  GPIO_ResetBits(GPIOC,GPIO_Pin_11);
#define 	D14_ON 		  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
#define 	D15_ON 		  GPIO_ResetBits(GPIOC,GPIO_Pin_12);
#define 	D16_ON 		  GPIO_ResetBits(GPIOB,GPIO_Pin_7);


#define 	PA4_OFF 		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
#define 	PA5_OFF			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
#define 	PA6_OFF 		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
#define 	PA7_OFF 		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
#define 	PB0_OFF 		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
#define 	PB1_OFF 		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
#define 	PC4_OFF 		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
#define 	PC5_OFF 		GPIO_ResetBits(GPIOC,GPIO_Pin_5);


#define 	PA4_ON 		  GPIO_SetBits(GPIOA,GPIO_Pin_4);
#define 	PA5_ON 		  GPIO_SetBits(GPIOA,GPIO_Pin_5);
#define 	PA6_ON 		  GPIO_SetBits(GPIOA,GPIO_Pin_6);
#define 	PA7_ON 		  GPIO_SetBits(GPIOA,GPIO_Pin_7);
#define 	PB0_ON 		  GPIO_SetBits(GPIOB,GPIO_Pin_0);
#define 	PB1_ON 		  GPIO_SetBits(GPIOB,GPIO_Pin_1);
#define 	PC4_ON 		  GPIO_SetBits(GPIOC,GPIO_Pin_4);
#define 	PC5_ON 		  GPIO_SetBits(GPIOC,GPIO_Pin_5);





void GPIO_Init_Configuration(void);
#endif
