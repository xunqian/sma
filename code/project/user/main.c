/*******************************************************************************
*                 
*                 		       ά�ڻ���
--------------------------------------------------------------------------------
* ������: 	����ʽ����ģ��
* ��  ��: ����TOKEN
****************************************************************************/
/*                                                                                                                                                      */
/*    Copyright (C) - WINGAIN Intelligent Equipment - All rights reserved                                                */
/*                                                                                                                                                      */
/*****************************************************************************/
/*                                                                                                                                                      */
/*  Except if expressly provided in a dedicated License Agreement, you are                                           */
/*  not authorized to:                                                                                                                         */
/*                                                                                                                                                      */
/*  1. Use, copy, modify or transfer this software component, module or                                             */
/*  product, including any accompanying electronic or paper documentation                                          */
/*  (together, the "Software").                                                                                                            */
/*                                                                                                                                                       */
/*  2. Remove any product identification, copyright, proprietary notices or                                            */
/*  labels from the Software.                                                                                                               */
/*                                                                                                                                                      */
/*  3. Modify, reverse engineer, decompile, disassemble or otherwise attempt                                      */
/*  to reconstruct or discover the source code, or any parts of it, from the                                           */
/*  binaries of the Software.                                                                                                                */
/*                                                                                                                                                       */
/*  4. Create derivative works based on the Software (e.g. incorporating the                                        */
/*  Software in another software or commercial product or service without a                                        */
/*  proper license).                                                                                                                              */
/*                                                                                                                                                      */
/*  By installing or using the "Software", you confirm your acceptance of the                                        */
/*  hereabove terms and conditions.                                                                                                   */
/*                                                                                                                                                      */
/*****************************************************************************/

/*****************************************************************************/
/*  History:                                                                                                                                        */
/*****************************************************************************/
/*  Date       * Author          * Changes                                                                                               */
/*****************************************************************************/
/*  2017-6-21 * xunqian.hu     * Creation of the file                                                                         */
/*             *                 *                                                                                                                    */
/*****************************************************************************/
/*  Target : stm32                                                                                                                 */
/*  Crystal: 72Mhz                                                                                                                              */
/*****************************************************************************/

/*******************************************************************************/

#include "public.h"
#include "usart.h"
#include "systick.h"
#include "time.h" 
#include "main.h"
#include "variables_def.h"
#include "reg.h"
#include "string.h"
//#include "rfid.h"
void read_sensorstatus(void);

/*******************************************************************************
* �� �� ��         : delay
* ��������		   : ��ʱ������delay(6000000)��ʱԼ1s
* ��    ��         : i
* ��    ��         : ��
*******************************************************************************/
void delay(u32 i)
{
	while(i--);
}


/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   �����˶���LED                                                   */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   number                                                                  */
/*  number��Ӧ (abcdefg dp)���øߵ���LED                                                     */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/

void Write_LED(uint8 number)
{	//number��Ӧ (abcdefg dp)
	if((number&0x80)==0x80)
		GPIO_WriteBit(LED_A_PORT, LED_A_BIT_NUM, Bit_RESET);
	else
		GPIO_WriteBit(LED_A_PORT, LED_A_BIT_NUM, Bit_SET);
	if((number&0x40)==0x40)
		GPIO_WriteBit(LED_B_PORT, LED_B_BIT_NUM, Bit_RESET);
	else
		GPIO_WriteBit(LED_B_PORT, LED_B_BIT_NUM, Bit_SET);
	if((number&0x20)==0x20)
		GPIO_WriteBit(LED_C_PORT, LED_C_BIT_NUM, Bit_RESET);
	else
		GPIO_WriteBit(LED_C_PORT, LED_C_BIT_NUM, Bit_SET);
	if((number&0x10)==0x10)
		GPIO_WriteBit(LED_D_PORT, LED_D_BIT_NUM, Bit_RESET);
	else
		GPIO_WriteBit(LED_D_PORT, LED_D_BIT_NUM, Bit_SET);
	if((number&0x08)==0x08)
		GPIO_WriteBit(LED_E_PORT, LED_E_BIT_NUM, Bit_RESET);
	else
		GPIO_WriteBit(LED_E_PORT, LED_E_BIT_NUM, Bit_SET);
	if((number&0x04)==0x04)
		GPIO_WriteBit(LED_F_PORT, LED_F_BIT_NUM, Bit_RESET);
	else
		GPIO_WriteBit(LED_F_PORT, LED_F_BIT_NUM, Bit_SET);
	if((number&0x02)==0x02)
		GPIO_WriteBit(LED_G_PORT, LED_G_BIT_NUM, Bit_RESET);
	else
		GPIO_WriteBit(LED_G_PORT, LED_G_BIT_NUM, Bit_SET);	
}
/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   �����˶���LED ��ʾ��0-F��DP��                                                 */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   number                                                                  */
/*  number��Ӧ0-F,	����DP,number����λ��1                                                    */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/

void LED_Display(uint8 number)
{
	if((number&0x10)==0x10)
		GPIO_WriteBit(LED_DP_PORT, LED_DP_BIT_NUM, Bit_RESET);
	else
		GPIO_WriteBit(LED_DP_PORT, LED_DP_BIT_NUM, Bit_SET);
   switch(number&0x0f)
   {
   	case 1://ef		
		Write_LED(0x0c);
		break;
	case 2://abdeg
		Write_LED(0xda);
		break;
	case 3://abcdg
		Write_LED(0xf2);
		break;
	case 4://bcfg
		Write_LED(0x66);
		break;
	case 5://acdfg
		Write_LED(0xb6);
		break;
	case 6://acdefg
		Write_LED(0xbe);
		break;
	case 7://abc
		Write_LED(0xe0);
		break;
	case 8://abcdefg
		Write_LED(0xfe);
		break;
	case 9://abcfg
		Write_LED(0xe6);
		break;
	case 0://abcdef
		Write_LED(0xfc);
		break;
	case 0x0a://cdeg
		Write_LED(0x3a);
		break;
	case 0x0b://cdefg
		Write_LED(0x3e);
		break;
	case 0x0c://deg
		Write_LED(0x1a);
		break;
	case 0x0d://bcdeg
		Write_LED(0x7a);
		break;
	case 0x0e://adefg
		Write_LED(0x9e);
		break;
	case 0x0f://aefg
		Write_LED(0x8e);
		break;
	default:
		break;
   }			
}
/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   GPIO initialization                                                     */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
static void vGPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // configure the following GPA IO as input FLOATING IO
    // ------------------------------------------------------------------
    // | 15  14  13  12  11  10  9    8     7    6     5    4      3   2   1        0  |
    // |                                    SENS1                                      |
    // ------------------------------------------------------------------
    GPIO_InitStructure.GPIO_Pin =  GPA_IN_BITMAPS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	// configure the following GPA IO as OUTPUT IO
	// ------------------------------------------------------------------
	// | 15  14  13  12  11  10  9	 8	 7	  6 	5	 4		3	2	1		 0	|
	// |									                                       LED_F    LED_G|
	// ------------------------------------------------------------------
	GPIO_InitStructure.GPIO_Pin =  GPA_OUT_BITMAPS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// configure the following GPBIO as input FLOATING IO
	// ------------------------------------------------------------------
	// | 15  14  13  12  11  10  9 8	 7	  6 	  5	 4		3	2	1		 0	|
	// |								 IN6 IN5                                                 |
	// ------------------------------------------------------------------
	GPIO_InitStructure.GPIO_Pin =  GPB_IN_BITMAPS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)0;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// configure the following GPB IO as OUTPUT  IO
	// ------------------------------------------------------------------
	// | 15  14  13  12  11  10   9	   8	     7	6 	5	 4		3	2	1		 0	|
	// |					    SOLE3	SOLE4 SOLE5 		                                                      |
	// ------------------------------------------------------------------
	GPIO_InitStructure.GPIO_Pin =  GPB_OUT_BITMAPS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// configure the following GPC IO as input FLOATING IO
	// ------------------------------------------------------------------
	// | 15  14  13  12  11  10  9	 8	     7	   6 	5	 4		3	2	1		 0	|
	// |					   SENS2 SENS3 SENS4 SENS5                                                     |
	// ------------------------------------------------------------------
	GPIO_InitStructure.GPIO_Pin =  GPC_IN_BITMAPS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)0;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// configure the following GPC IO as OUTPUT IO
	// ------------------------------------------------------------------
	// |   15         14           13          12  11  10  9  8  7  6 	5 4      3	         2	          1		   0	      |
	// |LED_B    LED_A   MOTOR_2F2						LED_E   LED_D      LED_DP   LED_C    |
	// ------------------------------------------------------------------
	GPIO_InitStructure.GPIO_Pin =  GPC_OUT_BITMAPS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// configure the following GPD IO as input FLOATING IO
	// ------------------------------------------------------------------
	// | 15      14        13      12       11       10          9	      8  7	  6    5	4    3 2	1	 0	|
	// |SENS6 SENS7 SENS8 SENS9 SENS10 SENS11	 SENS12	  IN4 IN3	IN2 IN1				|
	// ------------------------------------------------------------------
	GPIO_InitStructure.GPIO_Pin =  GPD_IN_BITMAPS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)0;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	// configure the following GPD IO as input OUTPUT IO
	// ------------------------------------------------------------------
	// | 15  14  13  12  11  10  9	   8	      7	  6 	5	 4		3	2	1		 0	|
	// |					       SENS_POWER	                                                                  |
	// ------------------------------------------------------------------
	GPIO_InitStructure.GPIO_Pin =  GPD_OUT_BITMAPS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	// configure the following GPE IO as input FLOATING IO
	// ------------------------------------------------------------------
	// | 15      14   13  12   11  10  9  8  7  6 5 4        3	        2	      1 0	|
	// |KEY2 KEY1		                               V_CHECK1 V_CHECK2      |
	// ------------------------------------------------------------------
	GPIO_InitStructure.GPIO_Pin =  GPE_IN_BITMAPS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)0;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	// configure the following GPE IO as OUTPUT IO
	// ------------------------------------------------------------------
	// | 15  14  13      12     11    10       9        8       7	           6 	    |  
	// |		   OUT1 OUT2 OUT3 OUT4  OUT5  OUT6 OUT7 MOTOR_2F1   |
	// |      5	           4	        3 2	          1           0	    |
	// |MOTOR_1F2  MOTOR_1F1             SOLE1  SOLE2    |
	// ------------------------------------------------------------------
	GPIO_InitStructure.GPIO_Pin =  GPE_OUT_BITMAPS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

    OutGPA = (u16)(0x0003);//0000 0000 0000 0011
    OutGPB = (u16)(0x0000);//0000 0000 0000 0000   
    OutGPC = (u16)(0xc00f);//1100 0000 0000 1111	
    OutGPD = (u16)(0x0760);//0000 0000 0000 0001
	OutGPE = (u16)(0x0000);//0000 0000 0000 0000
	GPIO_Write(GPIOA, OutGPA);
    GPIO_Write(GPIOB, OutGPB);
    GPIO_Write(GPIOC, OutGPC);
	GPIO_Write(GPIOD, OutGPD);
	GPIO_Write(GPIOE, OutGPE);
}
/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Pre-setup hardware registers                                            */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
static void prvSetupHardware(void)
{
    /* Start with the clocks in their expected state. */
    RCC_DeInit();

    /* Enable HSE (high speed external clock). */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Wait till HSE is ready. */
    while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
    {
    }

    /* 2 wait states required on the flash. */
    *((unsigned long *) 0x40022000) = 0x02;

    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz. */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL. */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready. */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source. */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source. */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }

    /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE and AFIO clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC
                           | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);

    /* SPI2 Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);


    /* Set the Vector Table base address at 0x08000000 */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    /* Configure HCLK clock as SysTick clock source. */
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

    vGPIOInit();
}

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//У��
//����*ptr  ����ָ��
//���� len  У�����ݳ���
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/

uint8 Check_LRC(uint8 *ptr, uint8 len)   
{  
  uint8 lrc=0; 
  while(len--!=0)   
  { 
    lrc ^= (*ptr);
    ptr++;  
  }  
  return(lrc);  
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//���������
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          NULL                                                                                */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
 void SOLEA_ON(void)//��Ʊ�ڴ�
    {
    	SOLE1_ON;			
    }
 void SOLEA_OFF(void)//��Ʊ�ڹر�
    {
      SOLE1_OFF;
   }    
 void SOLEB_ON(void)//�˱ҿڵ������
    {     
        SOLE2_ON;		  
	} 
 void SOLEB_OFF(void)//�˱ҿڵ�����ر�
    {
        SOLE2_OFF;	 
    }
 void SOLEC_ON(void)//���տڵ������
    {     
        SOLE3_ON;		  
	} 
 void SOLEC_OFF(void)//���տڵ�����ر�
    {
        SOLE3_OFF;	 
    }
  void SOLED_ON(void)//���õ����1��
    {     
        SOLE4_ON;		  
	} 
 void SOLED_OFF(void)//����1�����1�ر�
    {
        SOLE4_OFF;	 
    }
 void SOLEE_ON(void)//���õ����2��
    {     
        SOLE5_ON;		  
	} 
 void SOLEE_OFF(void)//���õ����2�ر�
    {
        SOLE5_OFF;	 
    }
 
 /*****************************************************************************/
 /* Function Description:																													   */
 /*****************************************************************************/
 //ģ�������򿪺���
 //����time �򿪵����ʱ��
 
 /*****************************************************************************/
 /* Parameters: 																																 */
 /*****************************************************************************/
 /* 																																					*/
 /* 																																					*/
 /* 																																					*/
 /*****************************************************************************/
 /* Return Values:			�Ƿ�ɹ�																							 */
 /*****************************************************************************/
 /* 																																					 */
 /*   NULL																																			 */
 /* 																																					 */
 /*****************************************************************************/
 void SoleB_Open(uint16 time)
 {
	 SOLEB_ON(); 
	 drop_tic_time = time;
	 while(drop_tic_time)
	 {
		 read_sensorstatus();
		 if(antenna ==INEXISTENCE)
			 break;  
	 }
	 if(drop_tic_time==0)
	 {
		 SOLEB_OFF();			 
	 }
		 
 }
  void SoleC_Open(uint16 time)
 {
	 SOLEC_ON(); 
	 drop_tic_time = time;
	 while(drop_tic_time)
	 {
		 read_sensorstatus();
		 if(antenna ==INEXISTENCE)
			 break;  
	 }
	 if(drop_tic_time==0)
	 {
		 SOLEC_OFF();			 
	 }
		 
 }
 /*****************************************************************************/
 /* Function Description:																													   */
 /*****************************************************************************/
 //ģ�������򿪺���
 //����time �򿪵����ʱ��
 
 /*****************************************************************************/
 /* Parameters: 																																 */
 /*****************************************************************************/
 /* 																																					*/
 /* 																																					*/
 /* 																																					*/
 /*****************************************************************************/
 /* Return Values:			�Ƿ�ɹ�																							 */
 /*****************************************************************************/
 /* 																																					 */
 /*   NULL																																			 */
 /* 																																					 */
 /*****************************************************************************/
 void SoleA_Open(uint16 time)
 {
	 SOLEA_ON();
	 drop_tic_time = time;
	 while(drop_tic_time)
	 {
		 read_sensorstatus();
		 if(antenna ==EXISTENCE)
			 break;
		 
	 }
 }
 /*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//���ֵ������������

/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
 void KEEP_SOLE_STOP(void)
 	{
		MOTOR_1F1_RESET;
		MOTOR_1F2_RESET;
 	}
void KEEP_SOLE_A(void)
 {
 	MOTOR_1F1_RESET;
	MOTOR_1F2_SET;
	drop_tic_time = 50;//1��
	 while(drop_tic_time)
	 {
		 read_sensorstatus();
		 if(sens.SENSORS_STATUS.checkticks7 ==0x00)
			 break;
	 }
	 KEEP_SOLE_STOP();		
 }
 void KEEP_SOLE_B(void)
 	{
		MOTOR_1F1_SET;
		MOTOR_1F2_RESET;
		drop_tic_time = 50;//1��
		 while(drop_tic_time)
		 {
			 read_sensorstatus();
			 if(sens.SENSORS_STATUS.checkticks8 ==0x00)
				 break;
		 }
		 KEEP_SOLE_STOP();
 	}


void motor_rotation (void)
{
}
 /*****************************************************************************/
 /* Function Description:																													   */
 /*****************************************************************************/
 //BIT��1����
 //����:bҪ��λ���ֽ�
 //����:indexҪ��λ�����к�
 /*****************************************************************************/
 /* Parameters: 																																 */
 /*****************************************************************************/
 /* 																																					*/
 /* 																																					*/
 /* 																																					*/
 /*****************************************************************************/
 /* Return Values:			��λ����ֽ�																						*/
 /*****************************************************************************/
 /* 																																					 */
 /* 																																   */
 /* 																																					 */
 /*****************************************************************************/
 
 uint8 GetBit(uint8 b, uint8 index)//����indexλ��Ϊ1
		{ 
			 b |=(1 << index);
			 return b;			 
		}
 /*****************************************************************************/
 /* Function Description:																													   */
 /*****************************************************************************/
 //BIT��0����
 //����:bҪ��λ���ֽ�
 //����:indexҪ��λ�����к�
 /*****************************************************************************/
 /* Parameters: 																																 */
 /*****************************************************************************/
 /* 																																					*/
 /* 																																					*/
 /* 																																					*/
 /*****************************************************************************/
 /* Return Values:			��λ����ֽ�																						*/
 /*****************************************************************************/
 /* 																																					 */
 /* 																																   */
 /* 																																					 */
 /*****************************************************************************/
 
 
 uint8 SetBit(uint8 b, uint8 index) //����indexλ��Ϊ0
		{
			 b&= ~(1 << index);//��0
			 return b;
		}

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//������Ӧ����
//����cmd  ��Ӧ�������ֽ�
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
void cmd_act(uint8 cmd)
{    
	USART_SendData(USART1,WXDLE);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
	USART_SendData(USART1,cmd); 
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//�ظ���λ������
//����*cmd �ظ�������ָ��
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
void cmd_reseive(RETURN_CODE *cmd)
{
    uint8 i,temp,len;
    uint8 *p;
    p = cmd->code;
    len = *p;
    p++;
    temp = Check_LRC(p,len);    
	USART_SendData(USART1,WXDLE);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
	USART_SendData(USART1,WXSTX);  
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
    for(i=0;i<len;i++)
    {
        if(*p == WXDLE)
        {
            USART_SendData(USART1,WXDLE);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
        }
		
		USART_SendData(USART1,*p); 
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
        p++;
    }
    USART_SendData(USART1,WXDLE);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
    USART_SendData(USART1,WXSTX);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
	USART_SendData(USART1,temp);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//�幷����ȡ������״̬
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
void read_sensorstatus(void)
{	
	if(wdt_reseten == 1)
		//WDR();
	sens_last = sens;	//SENSORS���������
	sens.status[0] = GPIO_ReadInputDataBit(SENS1_PORT, SENS1_BIT_NUM);
	sens.status[1] = GPIO_ReadInputDataBit(SENS2_PORT, SENS2_BIT_NUM);
	sens.status[2] = GPIO_ReadInputDataBit(SENS3_PORT, SENS3_BIT_NUM);
	sens.status[3] = GPIO_ReadInputDataBit(SENS4_PORT, SENS4_BIT_NUM);
	sens.status[4] = GPIO_ReadInputDataBit(SENS5_PORT, SENS5_BIT_NUM);
	sens.status[5] = GPIO_ReadInputDataBit(SENS6_PORT, SENS6_BIT_NUM);
	sens.status[6] = GPIO_ReadInputDataBit(SENS7_PORT, SENS7_BIT_NUM);
	sens.status[7] = GPIO_ReadInputDataBit(SENS8_PORT, SENS8_BIT_NUM);
	sens.status[8] = GPIO_ReadInputDataBit(SENS9_PORT, SENS9_BIT_NUM);
	//sens.status[9] = GPIO_ReadInputDataBit(SENS10_PORT, SENS10_BIT_NUM);
	//sens.status[10] = GPIO_ReadInputDataBit(SENS11_PORT, SENS11_BIT_NUM);
	//sens.status[11] = GPIO_ReadInputDataBit(SENS12_PORT, SENS12_BIT_NUM);
	//��λ����
	sens.status[12] = GPIO_ReadInputDataBit(IN1_PORT, IN1_BIT_NUM);
	sens.status[13] = GPIO_ReadInputDataBit(IN2_PORT, IN2_BIT_NUM);
	sens.status[14] = GPIO_ReadInputDataBit(IN3_PORT, IN3_BIT_NUM);
	//sens.status[15] = GPIO_ReadInputDataBit(IN4_PORT, IN4_BIT_NUM);
	//sens.status[16] = GPIO_ReadInputDataBit(IN5_PORT, IN5_BIT_NUM);
	//sens.status[17] = GPIO_ReadInputDataBit(IN6_PORT, IN6_BIT_NUM);
	//��ڴ�����:1.��������2.��ڴ������ڵ�3.��������Ʊ
	if((receive_limits==allow)&&(sens.SENSORS_STATUS.checkticks1 ==0x00)
		&&(sens.SENSORS_STATUS.checkticks6 !=0x00))
	{	
		detection=EXISTENCE;//������п�
		sole_open_over_time=3000;//������򿪳�ʱʱ������
		SOLEA_ON();	//���Ϸ������
	}
	if((sens_last.SENSORS_STATUS.checkticks1 == 0x00)&&(sens.SENSORS_STATUS.checkticks1 != 0x00))
	{
		sole_openleave_over_time=200;//������򿪺��뿪��������ʱʱ������				
	}	
    if(sens.SENSORS_STATUS.checkticks6 ==0x00) 
    {		
		SOLEA_OFF();	//�ر��Ϸ������		
    	detection=INEXISTENCE;//����������־
        antenna = EXISTENCE;
        antenna_LED_ON;
    }
	else
	{
		antenna = INEXISTENCE;
        antenna_LED_OFF;	
	}
	if((sens_last.SENSORS_STATUS.checkticks4 == 0x00)
		&&(sens.SENSORS_STATUS.checkticks4 != 0x00))
	{
		 antenna = INEXISTENCE;
		 SOLEB_OFF();
	}
	if((sens_last.SENSORS_STATUS.checkticks5 == 0x00)
		&&(sens.SENSORS_STATUS.checkticks5 != 0x00))
	{
		antenna = INEXISTENCE;
		SOLEC_OFF();
	}	
	if(sens.SENSORS_STATUS.checkticks7 ==0x00)
	{
		current_gallery=A_gallery;
		gallery_LED_ON;		
	}
	if(sens.SENSORS_STATUS.checkticks8 ==0x00)
	{
		current_gallery=B_gallery;
		gallery_LED_OFF;
	}
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//�����ж�
//����*re_comm Ҫ���͵�����
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
void model_status_anto(RETURN_CODE *re_comm)
{  
    if(sens.SENSORS_STATUS.checkticks12== 0)
        re_comm->MESSAGE.info[0] |= 0x01;        //A��λ
    else
        re_comm->MESSAGE.info[0] &= 0xfe;        //Aδ��λ
    if(sens.SENSORS_STATUS.checkticks13== 0)
        re_comm->MESSAGE.info[0] |= 0x02;        //B��λ
    else
        re_comm->MESSAGE.info[0] &= 0xfd;        //Bδ��λ
     if(sens.SENSORS_STATUS.checkticks14== 0)
        re_comm->MESSAGE.info[0] |= 0x04;        //C��λ
    else
        re_comm->MESSAGE.info[0] &= 0xfb;        //Cδ��λ
     if(detection == EXISTENCE)
        re_comm->MESSAGE.info[2] |= 0x01;        //������п�
    else
        re_comm->MESSAGE.info[2] &= 0xfe ;        //������޿�   
    if(antenna == EXISTENCE)
        re_comm->MESSAGE.info[0] |= 0x08;        //�������п�
    else
        re_comm->MESSAGE.info[0] &= 0xf7 ;        //�������޿�
   
	if(current_gallery==B_gallery)
	{
		re_comm->MESSAGE.info[0] |= 0x20;		 //5,6λ��10
		re_comm->MESSAGE.info[0] &= 0xef;		 //5,6λ��10		
	}
	if(current_gallery==A_gallery)
	{
		re_comm->MESSAGE.info[0] |= 0x10;		 //5,6λ��01
		re_comm->MESSAGE.info[0] &= 0xdf;		 //5,6λ��01		
	}		
	if(sens.SENSORS_STATUS.checkticks2 == 0)
		re_comm->MESSAGE.info[0] &= 0xbf;		 //��ڹر���0	
	if(sens.SENSORS_STATUS.checkticks3 == 0)
		re_comm->MESSAGE.info[0] |= 0x40;		 //��ڴ���1	    
} 
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
/*   �������Լ�                                                                                                                     */
/*                                                                                                                                                      */
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   *re_code: ���صĴ������Լ�״̬                                                                      */
/*                                                                                                                                                      */
/*****************************************************************************/
/* Return Values:                                                                                                                               */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
void sensor_self_check(RETURN_CODE *re_code)
{
    //uint8 i;
	sole_open_over_time=5000;
	SOLEA_ON();
	SOLEB_ON();
	sole_openleave_over_time=1000;//������򿪺��뿪��������ʱʱ������
	delay(200);
    read_sensorstatus();
	re_code->MESSAGE.info[1]=0;
	//SENSOR_LED_OFF;
	 if(sens.SENSORS_STATUS.checkticks9 == sens_last.SENSORS_STATUS.checkticks9)
    {
        re_code->MESSAGE.info[1] =GetBit(re_code->MESSAGE.info[1], 2);
	    re_code->MESSAGE.err_code = sens_err; 
		//SENSOR_LED_ON;
    }
    if(sens.SENSORS_STATUS.checkticks11 == sens_last.SENSORS_STATUS.checkticks11)
    {
        re_code->MESSAGE.info[1] =GetBit(re_code->MESSAGE.info[1], 3);
	    re_code->MESSAGE.err_code = sens_err; 
		//SENSOR_LED_ON;
    }    
	delay(20);
	SOLEA_OFF();
	SOLEB_OFF();      
    read_sensorstatus();
    SensorP_OFF;
    delay(200);
    read_sensorstatus();     
    SensorP_ON; 
	delay(20);  
    if(sens.SENSORS_STATUS.checkticks1 == sens_last.SENSORS_STATUS.checkticks1)
    	{
	    	re_code->MESSAGE.info[1] =GetBit(re_code->MESSAGE.info[1], 0);
	     	re_code->MESSAGE.err_code = sens_err;
		//	SENSOR_LED_ON;
    	}
    else if(sens.SENSORS_STATUS.checkticks2 == sens_last.SENSORS_STATUS.checkticks2)
       {
	    	re_code->MESSAGE.info[1] =GetBit(re_code->MESSAGE.info[1], 1);
	     	re_code->MESSAGE.err_code = sens_err;
		//	SENSOR_LED_ON;
    	}    
	else if(sens.SENSORS_STATUS.checkticks3 == sens_last.SENSORS_STATUS.checkticks3)
		{
			if(model==close_model)
				{
					re_code->MESSAGE.info[1] =GetBit(re_code->MESSAGE.info[1], 4);
	     			re_code->MESSAGE.err_code = sens_err;
			//		SENSOR_LED_ON;
				}
		}
		
  read_sensorstatus(); 
  antenna = INEXISTENCE;    //�����������־
}

 
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//���״̬
//���� *re_comm Ҫ���͵�����
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
void check_modelstatus(RETURN_CODE *re_comm)//-------------------------------������ʵʱ״̬����
{
    read_sensorstatus();
    model_status_anto(re_comm);
}
 
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//ģ�������򿪺���
//����time �򿪵����ʱ��
//����mode �ж��ǽ������߻��ǳ�����
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
void Sole_Open(uint16 time,uint8 mode)
{
    drop_tic_time = time;
    while(drop_tic_time)
    {
        read_sensorstatus();
        if(antenna == mode)
            break;
    }
} 
 
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//ģ���ʼ��
//����*re_comm �ظ�������ָ��
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
void module_init(RETURN_CODE *re_comm)
{	
	sum_open_over_time=0;
	LED_ON;//�˱ҿ�ָʾ���� 
	read_sensorstatus();
   	SOLEB_ON();
	SOLEA_ON();
	delay(1000000);
	//if((sens.SENSORS_STATUS.checkticks6!=0)&&(sens.SENSORS_STATUS.checkticks4!=0))
	SOLEB_OFF();
	SOLEA_OFF();
	SOLEC_ON();
	read_sensorstatus();
	if(current_gallery==B_gallery)
	{
		KEEP_SOLE_A();
	}
	read_sensorstatus();
	if(current_gallery==A_gallery)
	{
		KEEP_SOLE_B();
	}
	delay(1000000);
    SOLEC_OFF();
	read_sensorstatus();
	if(current_gallery==B_gallery)
	{
		KEEP_SOLE_A();
	}
	check_modelstatus(re_comm);
	detection=INEXISTENCE;	  //��ռ������־
	antenna = INEXISTENCE;    //�����������־	
    LED_OFF;//�˱ҿ�ָʾ����   
}  
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//����ģʽ
//����cmd ��ǰ������
//����*act ���ص�����ָ��
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/* ��Ʊ����Ʊ������       Ʊ����                                                                                                                                             */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
void normal_working(uint8 cmd,RETURN_CODE *act)
{
    //uint8 time=3;
    switch(cmd)
    { 
   
		case CMD_REJECTACCEPT://�ܾ�����
		{
			drop_tic_time = DROP_T1;
	        while(drop_tic_time)
	              {
	                	SOLEA_OFF();//�ر����
	                	//delay_us(50);
	       			    read_sensorstatus();                    
	                    if(sens.SENSORS_STATUS.checkticks9 ==0x10)//U�ʹ������ڵ�Ϊ0
	                    	break;                    
	              }	   
						                    
	       	if(drop_tic_time == 0)
	                {
	                    //act->MESSAGE.info[2] = 0;
	                    act->MESSAGE.result = 'e';
	                    act->MESSAGE.err_code = CLOSE_entry_err;
	                }
	         else
	                {
	                    //act->MESSAGE.info[2] = 1;
	                    act->MESSAGE.result = 's';
	                    act->MESSAGE.err_code = com_ok;
	                }           
			break;
		}
		case CMD_ACCEPT://��������
		 {
            if(antenna==0)//��������Ʊ
            {
                
	              drop_tic_time = DROP_T1;
	                while(drop_tic_time)
	                {
	                	SOLEA_ON();
	                    read_sensorstatus();	                    
	                    if(sens.SENSORS_STATUS.checkticks9 ==0x00)//U�ʹ������ڵ�Ϊ0
	                    	break;                    
	                }	                
	                if(drop_tic_time == 0)
	                {
	                    //act->MESSAGE.info[2] = 0;
	                    act->MESSAGE.result = 'e';
	                    act->MESSAGE.err_code = open_entry_err;
	                }
	                else
	                {
	                    //act->MESSAGE.info[2] = 1;
	                    act->MESSAGE.result = 's';
	                    act->MESSAGE.err_code = com_ok;
	                }
                }
				else
                {
                    //act->MESSAGE.info[2] = 1;
                    act->MESSAGE.result = 'e';
                    act->MESSAGE.err_code = card_at_RW_area;
                }
				 break;
            }            		
        default: 
            break;
            
    }
} 

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//ͨ���������
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
void check_command(void)//�������
{
    static RETURN_CODE re_code;
		//static SENS  sens_code; 
    //static uint8 tic_num1[2],tic_num2[2];
    //static uint8 tic_flag1=0,tic_flag2=0;
		//uint8 retemp;
    uint8 *p;
    uint8 i=0,j=0;
   // memset(re_code.code,0,53);
    if(1 == receive_ok)
    {
        communication_step = 1;
        switch(inbox[0])
        {
            case 0x0:           //���»ظ��ϴ�����
            {
                cmd_reseive(&re_code);
                break;
            }
            case 0x81:          //��ʼ��    
            {
                re_code.MESSAGE.act_code = inbox[0];
                re_code.MESSAGE.err_code = com_ok;
                module_init(&re_code);         		
				re_code.MESSAGE.info[3] = once_rec_num; 
				if(re_code.MESSAGE.err_code != box1_non_existent&&
					re_code.MESSAGE.err_code != box2_non_existent&&
					re_code.MESSAGE.err_code != com_ok)
					re_code.MESSAGE.result = 'e';
                else if(re_code.MESSAGE.err_code == box1_non_existent||
					re_code.MESSAGE.err_code == box2_non_existent)
                    re_code.MESSAGE.result = 'w';
                else
                    re_code.MESSAGE.result = 's';
                re_code.MESSAGE.len = 7;
                cmd_reseive(&re_code);
				once_rec_num=0;//���λ���TOKEN��������
                normal_start = 1;
                break;
            }
            case 0x82:          //��ģ��״̬
            {
                re_code.MESSAGE.act_code = inbox[0];
                check_modelstatus(&re_code);					
                re_code.MESSAGE.result = 's';
                re_code.MESSAGE.err_code = com_ok;
                re_code.MESSAGE.len = 6;
                cmd_reseive(&re_code);
                normal_start = 1;
                break;
            }
           case 0x83:          //��������TOKEN
            {
                re_code.MESSAGE.act_code = inbox[0];
				re_code.MESSAGE.err_code = com_ok;               
                receive_limits=allow;
                if(re_code.MESSAGE.err_code != com_ok)
                    re_code.MESSAGE.result = 'e';
                else
                    re_code.MESSAGE.result = 's';                
                re_code.MESSAGE.len = 3;
                cmd_reseive(&re_code);
                normal_start = 1;
                break;
            }
           case 0x84:          //��ֹ����TOKEN
            {
                re_code.MESSAGE.act_code = inbox[0];
				re_code.MESSAGE.err_code = com_ok;                
                receive_limits=prohibit;
                if(re_code.MESSAGE.err_code != com_ok)
                    re_code.MESSAGE.result = 'e';
                else
                    re_code.MESSAGE.result = 's';                
                re_code.MESSAGE.len = 3;
                cmd_reseive(&re_code);
                normal_start = 1;
                break;
            }           
            case 0x86:          //����
            {
				re_code.MESSAGE.act_code = inbox[0];	
				read_sensorstatus();//��ȡ��ǰͨ��ֵ				
				if(1==inbox[1])
				{
					if(current_gallery==B_gallery)
					{
						KEEP_SOLE_A();
					}						
					if(drop_tic_time!=0)
						{
						 	re_code.MESSAGE.err_code = com_ok;
						    drop_tic_time=0;
						}
					 
					else if(current_gallery==A_gallery)
							re_code.MESSAGE.err_code = com_ok;
						else								
							re_code.MESSAGE.err_code = change_A_err;
				}				
				if(2==inbox[1])
				{
					if(current_gallery==A_gallery)
					{
						KEEP_SOLE_B();
					}						
					if(drop_tic_time!=0)
						{
						 	re_code.MESSAGE.err_code = com_ok;
						    drop_tic_time=0;
						}
					 
					else if(current_gallery==B_gallery)
							re_code.MESSAGE.err_code = com_ok;
						else								
							re_code.MESSAGE.err_code = change_B_err;
				}			  
			    if(antenna==EXISTENCE)
			   	{
					if((1==inbox[1])||(2==inbox[1]))
						SoleC_Open(DROP_T2);
					else if(3==inbox[1])
						SoleB_Open(DROP_T2);	
					if(drop_tic_time==0)
						antenna=0;					
			   	}
			    else
			   		re_code.MESSAGE.err_code =no_card_at_RW_area;					
                check_modelstatus(&re_code);//��ȡģ��״̬�ϴ�                	
                re_code.MESSAGE.info[3] = once_rec_num;
                if(re_code.MESSAGE.err_code ==com_ok)
                    re_code.MESSAGE.result = 's';
				else if(re_code.MESSAGE.err_code ==no_card_at_RW_area)
					re_code.MESSAGE.result = 'w';
				else
					re_code.MESSAGE.result = 'e';				
                re_code.MESSAGE.len = 7;
                cmd_reseive(&re_code);
				once_rec_num=0;//���λ���TOKEN��������
                break;
            }
            case 0x87:          //��λ��������д����    
            {
                re_code.MESSAGE.act_code = inbox[0];
                check_modelstatus(&re_code);
                re_code.MESSAGE.result = 's';
                re_code.MESSAGE.err_code = com_ok;
                re_code.MESSAGE.len = 3;
                cmd_reseive(&re_code);                
                wdt_reseten = 0;
                normal_start = 1;
                break;
            }
            case 0x88:          //���汾��
            {
                p = re_code.MESSAGE.info;
                re_code.MESSAGE.act_code = inbox[0];
                re_code.MESSAGE.result = 's';
                re_code.MESSAGE.err_code = com_ok;
                for(i=0;i<sizeof(MODULE_VERSION);i++)
                {
                    *p = MODULE_VERSION[i];
                    p++;
                }
                for(i=0;i<sizeof(CPU_VERSION);i++)
                {
                    *p = CPU_VERSION[i];
                    p++;
                }
                re_code.MESSAGE.len = 18;
                cmd_reseive(&re_code);
                normal_start = 1;
                break;
            }
       	    /*case 0x89:          //�����к�
            {
                p = re_code.MESSAGE.info;
                re_code.MESSAGE.act_code = inbox[0];
                re_code.MESSAGE.result = 's';
                re_code.MESSAGE.err_code = com_ok;
				for(i=0;i<20;i++)
					{
						MODULE_SERIAL[i]=EEPROM_read(model_SERIAL_ADDR+i);						
						*p = MODULE_SERIAL[i];
						 p++;
					}
					
                for(i=0;i<sizeof(MODULE_SERIAL);i++)
                {
                    *p = MODULE_SERIAL[i];
                    p++;
                }               
                re_code.MESSAGE.len = 23;
                cmd_reseive(&re_code);
                normal_start = 1;
                break;
       	    }
            	*/
            case 0x8A:              //��ȡ���ӱ�ǩTAG����
            {
                re_code.MESSAGE.act_code = inbox[0];
                if(3==inbox[1]||4==inbox[1])
               {      
                       //re_code.MESSAGE.err_code = ReadRFIDBLOCK(inbox[1],inbox[2],re_code.MESSAGE.info);
                      if(re_code.MESSAGE.err_code == com_ok)
                       {
                            re_code.MESSAGE.result = 's';
                           normal_start = 1;
                        }
                     else
                      {
                           re_code.MESSAGE.result = 'e';
                          normal_start = 2;
                       }
                }
                 else
                    {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                    }
                re_code.MESSAGE.len = 19;
                cmd_reseive(&re_code);                
                break;
            }
         case 0x8B:              //д����ӱ�ǩTAG����
            {
                re_code.MESSAGE.act_code = inbox[0];
                if(3==inbox[1]||4==inbox[1])
                    {
                    
                        //re_code.MESSAGE.err_code = WriteRFIDBLOCK(inbox[1],inbox[2],&inbox[3]);
                        if(re_code.MESSAGE.err_code == com_ok)
                          {
                               re_code.MESSAGE.result = 's';
                               normal_start = 1;
                           }
                       else
                         {
                            re_code.MESSAGE.result = 'e';
                             normal_start = 2;
                          }
                    }
                else
                    {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                    }
                re_code.MESSAGE.len = 3;
                cmd_reseive(&re_code);                
                break;               
            }  
       
       case 0x8C:              //��ȡ���ӱ�ǩ���������
            {
                re_code.MESSAGE.act_code = inbox[0];
		         if(3==inbox[1]||4==inbox[1])
                 {
                   // re_code.MESSAGE.err_code = ReadRFID_Serial_Number(inbox[1],re_code.MESSAGE.info);                
       
                   if(re_code.MESSAGE.err_code == com_ok)
                     {
                       re_code.MESSAGE.result = 's';
                       normal_start = 1;
                      }
                    else
                       {
                          re_code.MESSAGE.result = 'e';
                          normal_start = 2;
                        }
                    }
                else
                    {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                    }
                re_code.MESSAGE.len = 7;
                cmd_reseive(&re_code);
                //inbox[0] = 0;
                break;
            }
			 case 0x8D:          //�����˱ҿ�ָʾ��
            {
                re_code.MESSAGE.act_code = inbox[0];
				re_code.MESSAGE.err_code = com_ok;
				if(inbox[1]==1)//ʹ����λ������
					{
						LED_control_flag=1;
						if(inbox[2]==1)
							LED_ON;//�˱ҿ�ָʾ����
						else
							LED_OFF;//�˱ҿ�ָʾ����
					}
				else//��ʹ����λ������
               	    LED_control_flag=0;
               	re_code.MESSAGE.result = 's';
                re_code.MESSAGE.len = 3;
                cmd_reseive(&re_code);
                normal_start = 1;
                break;
            }		
			  case 0x8F:          //����ģ��ģʽ:����or����
            {
                re_code.MESSAGE.act_code = inbox[0];
								re_code.MESSAGE.err_code = com_ok;
               	//EEPROM_write(model_ADDR,inbox[1]);   
               	re_code.MESSAGE.result = 's';
                re_code.MESSAGE.len = 3;
                cmd_reseive(&re_code);
                normal_start = 1;
                break;
            }
			 case 0x90:          //��ȡģ��ģʽ:����or����
            {
                re_code.MESSAGE.act_code = inbox[0];
								re_code.MESSAGE.err_code = com_ok;   
               	//re_code.MESSAGE.info[0]=EEPROM_read(model_ADDR);
               	re_code.MESSAGE.result = 's';
                re_code.MESSAGE.len = 4;
                cmd_reseive(&re_code);
                normal_start = 1;
                break;
            }
			 case 0xF0:              //������ۼ�ֵ
            {
                re_code.MESSAGE.act_code = inbox[0];
                re_code.MESSAGE.result = 's';
                re_code.MESSAGE.err_code = com_ok;
                p = re_code.MESSAGE.info;
                for(i=0;i<3;i++)
                {
                    for(j=0;j<4;j++)
                    {
                        *p = (box_num[i] >> 8*j) & 0xff;
                        p++;
                    }
                }
                re_code.MESSAGE.len = 15;
                cmd_reseive(&re_code);
				normal_start = 1;
                break;
            }
	/*	case 0xfd:  //д���к�
        {
                re_code.MESSAGE.act_code = inbox[0];
                for(i=0;i<20;i++)
                	{
                		EEPROM_write(model_SERIAL_ADDR+i,inbox[i+1]);
						MODULE_SERIAL[i]=EEPROM_read(model_SERIAL_ADDR+i);
						if(MODULE_SERIAL[i]!=inbox[i+1])
							re_code.MESSAGE.result = 'e';
						else
							re_code.MESSAGE.result = 's';
                	}
                if(re_code.MESSAGE.result== 's')
                	re_code.MESSAGE.err_code = com_ok;
				else
					re_code.MESSAGE.err_code =write_model_SERIAL_err;
                re_code.MESSAGE.len = 3;
                cmd_reseive(&re_code);
				normal_start = 1;
                break;
        }	 
			 */
        case 0xfe:  //��������ͨ����������������򿪹ضϵ�λ
        {
                re_code.MESSAGE.act_code = inbox[0];
				check_modelstatus(&re_code);	
                sensor_self_check(&re_code);
                re_code.MESSAGE.result = 's';
                re_code.MESSAGE.err_code = com_ok;
                re_code.MESSAGE.len = 6;
                cmd_reseive(&re_code);
				normal_start = 1;
                break;
        }
		 default:
                break;
        }
       for(i=0;i<60;i++)
            inbox[i] = 0;
        receive_ok = 0;
	}
  
} 
/****************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/
int main()
{	
	static RETURN_CODE re_code;
	normal_start = 1;
	prvSetupHardware();	
	time_init();  //��ʱ��3��ʼ��	
	usart_all_init();
	module_init(&re_code);
	while(1)
	{
		read_sensorstatus();		
		check_command();
	}
}


