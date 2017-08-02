/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

static uint8 n = 0;
static uint8 receive_buff[256];

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}



void USART1_IRQHandler(void)	//串口1中断函数
{
	//static u8 k;
	USART_ClearFlag(USART1,USART_FLAG_TC);
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=Bit_RESET)//检查指定的USART中断发生与否
	{	
	    uint8 j,k;
	    uint16 i;
	    uint8 LRC_temp;
	    static uint8 com_temp[60];
	    receive_buff[n] = USART_ReceiveData(USART1);
	    switch(communication_step)
	    {
	        case 1:
	        {   
	            if(receive_buff[0] == WXDLE)
	            {
	                if(receive_buff[1] == WXEOT)
	                {
	                    for(i=0;i<=n;i++)
	                        receive_buff[i] = 0;
	                    n = 0xff;
	                    cmd_act(WXEOT);
	                    communication_step = 1;
	                }
	                else if(receive_buff[1] == WXSTX)    //数据包开始
	                {
	                    for(i=0;i<=n;i++)
	                        receive_buff[i] = 0;
	                    n = 0xff;
	                    communication_step = 2;
	                }
	                else if(receive_buff[1] == WXENQ)   //收到命令确认
	                {
	                    for(i=0;i<=n;i++)
	                        receive_buff[i] = 0;
	                    n = 0xff;
	                    receive_ok = 1;//重新发送命令响应数据
	                }
	                else if(receive_buff[1] == WXDLE)   //收到控制符
	                {
	                //注意，收到控制符不需要清除第一个字节，
	                //从第二个字节开始接收下个
	                    for(i=1;i<=n;i++)
	                        receive_buff[i] = 0;
	                    n = 0;
	                    communication_step = 1;//重新发送命令响应数据
	                }
	                else if(n > 1)
	                {
	                    for(i=0;i<=n;i++)
	                        receive_buff[i] = 0;
	                    n = 0xff;
	                }
	            }
	            else
	            {
	                for(i=0;i<=n;i++)
	                    receive_buff[i] = 0;
	                n = 0xff;
	            }
	            break;
	        }
	        case 2:
	        {
	            over_time = SECOND;       //5S时间
	            if(receive_buff[0] == WXDLE && receive_buff[1] == WXSTX)    //接收开始，保持不变
	            {
	                for(i=0;i<=n;i++)
	                    receive_buff[i] = 0;
	                n = 0xff;
	                communication_step = 2;
	            }
	            else if(receive_buff[0] == WXDLE && receive_buff[1] == WXEOT)    //通信中止
	            {
	                for(i=0;i<=n;i++)
	                    receive_buff[i] = 0;
	                n = 0xff;
	                cmd_act(WXEOT);
	                communication_step = 1;
	            }
	            else if(receive_buff[n-2] == WXDLE && receive_buff[n-1] == WXETX)
	            {
	                for(i=n-2,j=0;i>0;i--)
	                {
	                    if(receive_buff[i] == WXDLE)     //判断ETX前面有几个0x10
	                        j++;
	                    else
	                        break;
	                }
	                if((j&0x1) != 0)                //如果是奇数个，表示ETX为结束，否则为数据
	                {
	                    for(i=0,k=0;k<n-2;i++,k++)
	                    {
	                        if(receive_buff[k] == WXDLE)
	                        {
	                            k++;
	                        }
	                        com_temp[i] = receive_buff[k];
	                    }
	                    LRC_temp = Check_LRC(com_temp,i);
	                    if(LRC_temp != receive_buff[n])     //如果校验不对则回复接收错误,并转入状态1
	                    {
	                        cmd_act(WXNAK);
	                        communication_step = 1;
	                    }
	                    else            //回复接收正确，并且转入状态3
	                    {
	                        cmd_act(WXACK);
	                        communication_step = 3;
	                    }
	                    
	                    for(i=0;i<=n;i++)
	                        receive_buff[i] = 0;
	                    n = 0xff;
	                }
	            }
	            else if((n > 70) && (n < 100))
	            {
	                for(i=0;i<=n;i++)
	                    receive_buff[i] = 0;
	                n = 0xff;
	                communication_step = 1;
	            }
	            break;
	        }
	        case 3:
	        {
	            if(receive_buff[0] == WXDLE)
	            {
	                if(receive_buff[1] == WXENQ)        //命令执行确认
	                {
	                    receive_ok = 1;
	                    communication_step = 1;
	                    for(i=0;i<=n;i++)
	                        receive_buff[i] = 0;
	                    for(i=0;i<60;i++)
	                        inbox[i] = com_temp[i];
	                    n = 0xff;
	                }
	                else if(receive_buff[1] == WXSTX)   //数据包开始标志
	                {
	                    for(i=0;i<=n;i++)
	                        receive_buff[i] = 0;
	                    n = 0xff;
	                    communication_step = 2;
	                }
	                else if(receive_buff[1] == WXEOT)    //通信中止
	                {
	                    for(i=0;i<=n;i++)
	                        receive_buff[i] = 0;
	                    n = 0xff;
	                    cmd_act(WXEOT);
	                    communication_step = 1;
	                }
	                else if(receive_buff[1] == WXDLE)   //收到控制符
	                {
	                //注意，收到控制符不需要清除第一个字节，
	                //从第二个字节开始接收下个
	                    for(i=1;i<=n;i++)
	                        receive_buff[i] = 0;
	                    n = 0;          
	                    communication_step = 3;//重新发送命令响应数据
	                }
	                else if(n > 1)
	                {
	                    for(i=0;i<=n;i++)
	                        receive_buff[i] = 0;
	                    n = 0xff;
	                    cmd_act(WXNAK);
	                    communication_step = 1;
	                }
	            }
	            else
	            {
	                for(i=0;i<=n;i++)
	                    receive_buff[i] = 0;
	                n = 0xff;
	                cmd_act(WXNAK);
	                communication_step = 1;
	            }
	            break;
	        }
	    }
	    n++;
	

		/*k=USART_ReceiveData(USART1);
		k++;	
		USART_SendData(USART1,k);//通过外设USARTx发送单个数据
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
		*/
	}
}
void USART2_IRQHandler(void)//串口2中断函数
{
	static u8 k;
	USART_ClearFlag(USART3,USART_FLAG_TC);
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=Bit_RESET)//检查指定的USART中断发生与否
	{
		k=USART_ReceiveData(USART3);
		k++;	
		USART_SendData(USART3,k);//通过外设USARTx发送单个数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==Bit_RESET);	
	}

}
void USART3_IRQHandler(void)	//串口3中断函数
{
	static u8 k;
	USART_ClearFlag(USART3,USART_FLAG_TC);
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=Bit_RESET)//检查指定的USART中断发生与否
	{
		k=USART_ReceiveData(USART3);
		k++;	
		USART_SendData(USART3,k);//通过外设USARTx发送单个数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==Bit_RESET);	
	}
}
void UART4_IRQHandler(void)//串口3中断函数
{
	static u8 k;
	USART_ClearFlag(USART3,USART_FLAG_TC);
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=Bit_RESET)//检查指定的USART中断发生与否
	{
		k=USART_ReceiveData(USART3);
		k++;	
		USART_SendData(USART3,k);//通过外设USARTx发送单个数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==Bit_RESET);	
	}


}
void UART5_IRQHandler(void)//串口3中断函数
{
	static u8 k;
	USART_ClearFlag(USART3,USART_FLAG_TC);
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=Bit_RESET)//检查指定的USART中断发生与否
	{
		k=USART_ReceiveData(USART3);
		k++;	
		USART_SendData(USART3,k);//通过外设USARTx发送单个数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==Bit_RESET);	
	}

}





/**
  *20ms进一次中断
  */

void TIM3_IRQHandler()	 //定时器3中断函数20ms
{	
	 uint16 i;
	 TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	//static uint8 work_light_cnt = 0;
    
     //通信超时计数
    if(communication_step == 2)//超时后返回错误回应
    {
        if(over_time != 0)
            over_time--;
        else
        {
            cmd_act(WXNAK);
            communication_step = 1;
            for(i=0;i<=n;i++)
                receive_buff[i] = 0;
            n = 0xff;
        }
    }
    //计数
    if(drop_tic_time != 0)//超时关闭电磁铁
        drop_tic_time--;
    if(sole_open_over_time != 0)
        sole_open_over_time--;
	if(sole_openleave_over_time != 0)
        sole_openleave_over_time--;
	if((sole_open_over_time==0)||(sole_openleave_over_time==0))
	{			
		SOLEA_OFF();
		detection=INEXISTENCE;//清除检测区标志		
	}	
	if(sole_close_over_time != 0)
        sole_close_over_time--;
	if(sole2_open_over_time != 0)
        sole2_open_over_time--;
	if(sole2_close_over_time != 0)
        sole2_close_over_time--;
    
    if(normal_start == 1)//心跳1S
    {
        if(work_light_cnt == 0)
        {
            work_light_cnt = 100;
            WORK_LIGHT_ON;
        }
        else if(work_light_cnt == 50)
        {
            WORK_LIGHT_OFF;
        }
        work_light_cnt--;
    }
    else if(normal_start == 2)//心跳加速，报故障
    {
        if(work_light_cnt == 0)
        {
            work_light_cnt = 50;
            WORK_LIGHT_ON;
        }
        else if(work_light_cnt == 25)
        {
            WORK_LIGHT_OFF;
        }
        work_light_cnt--;
    }
    else if(normal_start == 0)
        WORK_LIGHT_OFF;        
    //RFID操作超时控制 
    if(g_cbWaitRespDly != 0)//RFID操作超时使能（1s内timeout自减了47次）  
    {
        g_cbWaitRespDly--;
    }	
}
/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
