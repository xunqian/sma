/*****************************************************************************/
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
/*  2017-6-21 * xunqian.hu      * Creation of the file                                                                         */
/*             *                 *                                                                                                                    */
/*****************************************************************************/
/*  Target : stm32                                                                                                                               */
/*  Crystal: 72Mhz                                                                                                                              */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                                                                                                      */
/*  Include Files                                                                                                                                   */
/*                                                                                                                                                      */
/*****************************************************************************/

#ifndef _HEADER_VARIABLES_
#define _HEADER_VARIABLES_
#include "stm32f10x.h"
#include "main.h"

//�汾��
extern uint8 MODULE_VERSION[8];
extern uint8 CPU_VERSION[7] ;
//���к�
extern uint8 MODULE_SERIAL[20];

//���Ź���ʱ��λ
extern uint8   wdt_reseten;
extern uint16  wdt_resetreg;

 
 //uart0,��ECUͨ�ŷ��ͽ����ñ�������
 //ͨ�Ż���
 extern uint8	 receive_ok;//uart0���ݽ�����ɱ�־  1:�ɹ�  0:��
 extern uint8	 inbox[60];//�������ݻ���
 extern uint8	n;
 extern uint8   receive_buff[256];
 extern uint8 sens_selfcheck;  //�������Լ��־
 extern uint8  result;
 extern uint8  detection; 		 //������Ƿ��п���־
 extern  uint8 antenna; 		 //�������Ƿ��п���־
 extern uint16 drop_tic_time ;	 //��Ʊ��ʱ,ÿ�δ򿪵������Ӷ�ʱ����ʱ
 extern uint16 init_over_time;  //��ʼ����ʱ
 extern uint16 over_time;	  //ͨ�ų�ʱ
 extern uint32 rotation_over_time ;  //���ÿ����֮���ʱ����
 extern uint32 roll_over_time ;//���ת����ʱ1s 
 extern uint32 sole_open_over_time ;//��Ʊ�ڵ�����򿪳�ʱ1s 
 extern uint32 sole_openleave_over_time ;//��Ʊ�ڵ�����򿪺��뿪��ʱ100ms 
 extern uint32 sole_close_over_time ;//��Ʊ�ڵ�����򿪳�ʱ1s 
 extern uint32 sole2_open_over_time ;//��Ʊ�ڵ�����򿪳�ʱ1s 
 extern uint32 sole2_close_over_time;//��Ʊ�ڵ�����򿪳�ʱ1s 
 
 
 
 //�����ƿ���  1��ʾ���������ƣ�Ƶ��1HZ   ��2�����Ƽ��٣��й���
 //0ֹͣ����
extern  uint8 normal_start; 
 //�˱ҿ�ָʾ�Ʊ�־
 //��λ�����Ʊ�־ 
 //ģ����Ʊ�־
 extern uint8 LED_EN;
 //�˱ҿ�ָʾ����˸ʱ�����
extern  uint16 flash_cnt;
 
 //������״̬
 extern SENSORS sens;
 extern SENSORS sens_last;
 //���λ���Ʊ������
 extern uint8 once_rec_num;
 //���ѭ������
extern  uint8 cycl_count;
 //E2ѭ���������
 extern uint8 A_count_SIGN;
 extern uint8 B_count_SIGN;
 extern uint8 C_count_SIGN;
 //ee�洢������λ
 extern uint8 data[4];
 //ee�洢Ʊ��������ַ����
 extern EE_SAVE e2_Abox[MAX_EE_AREA];
 extern EE_SAVE e2_Bbox[MAX_EE_AREA];
 extern EE_SAVE e2_Cbox[MAX_EE_AREA];
 extern EE_SAVE *headA;
 extern EE_SAVE *headB;
 extern EE_SAVE *headC;
 //����or�˻�Ʊ������
 extern uint32 box_num[3];
 extern uint8 sum_open_over_time;
  
 //ͨ�Ų���
extern uint8 communication_step;
 //ģʽ����
extern  uint8 model; 
 //����/��ֹ��������
extern  uint8 receive_limits;
 //ͨ��λ��
extern uint8 current_gallery;
extern uint8 next_gallery;
 //���ת�������ٶ�
extern uint8 cw;
extern  uint16 speed;
 
 //RFID��ʱ��ʱ
extern  uint16 g_cbWaitRespDly;
extern  uint16 work_light_cnt;
 //���Ի�������ʹ��
extern uint32 time_count;
 //���ܲ���ʱ��ʹ�ܱ�־
extern uint8 time_on;
 //�˱ҿ�ָʾ�ƿ��Ʊ�־
extern uint8 LED_control_flag;//0:  ģ�����1 :��λ������
 
extern uint16 OutGPA;
extern uint16 OutGPB;
extern uint16 OutGPC;
extern uint16 OutGPD;
extern uint16 OutGPE;

//RFID��ʱ��ʱ
extern uint16 g_cbWaitRespDly ;

extern uint8 communication_step;

extern uint8 Check_LRC(uint8 *ptr, uint8 len) ;
extern void cmd_act(uint8 cmd);

#endif

