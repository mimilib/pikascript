#include "beep.h" 

/*********************************************************************************
************************�������� STM32F407���Ŀ�����******************************
**********************************************************************************
* �ļ�����: beep.c                                                               *
* �ļ�������beep��ʼ��                                                           *
* �������ڣ�2017.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ������������ӦIO�ڳ�ʼ��                                                 * 
**********************************************************************************
*********************************************************************************/
					  	 
    
//BEEP��ӦIO��ʼ��
void BEEP_Init(void)
{   
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOG_CLK_ENABLE();           //����GPIOEʱ��
  
  //��ʼ����������Ӧ����GPIOG7
    GPIO_Initure.Pin=GPIO_PIN_7;  
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_RESET);   //��������Ӧ����GPIOG7����,�رշ�����  ��������������
}






