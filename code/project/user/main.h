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
/*  2017-7-15 *xunqian.hu      * Creation of the file                                                                         */
/*             *                 *                                                                                                                    */
/*****************************************************************************/
/*  Target : stm32                                                                                                                              */
/*  Crystal: 72Mhz                                                                                                                              */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                                                                                                      */
/*  Include Files                                                                                                                                   */
/*                                                                                                                                                      */
/*****************************************************************************/

#ifndef _HEADER_MAIN_
#define _HEADER_MAIN_
#include "stm32f10x.h"
//
#define CMD_NO_ACTION 0
//#define CMD_TOrwAREA 1
#define CMD_A_RECOVER 1//���յ�A
#define CMD_B_RECOVER 2//���յ�B
#define CMD_RETURN 3//���յ�C���˱�
#define CMD_REJECTACCEPT 4//��ֹ����Ʊ��
#define CMD_ACCEPT 5//�������Ʊ��



#define OFF 0
#define ON 1

//cmd
#define WXDLE 0X10        //���Ʒ�
#define WXSTX 0X02        //���ݰ���ʼ��־
#define WXETX 0X03        //���ݰ�������־
#define WXEOT 0X04        //ͨѶ��ֹ��־
#define WXENQ 0X05        //����ִ��ȷ��
#define WXACK 0X06        //������ȷ��Ӧ
#define WXNAK 0X15        //���մ����Ӧ

//E2��ַ
//#define E2ERR_ADDR 0x22	//E2���ϴ洢�ĵ�ַ
//#define E2BOXA_STATUS 0x23	//Ʊ��װж�洢��ַ
//#define E2BOXB_STATUS 0x24	//Ʊ��װж�洢��ַ
//#define E2BOXC_STATUS 0x25	//Ʊ��װж�洢��ַ
#define ABOX_TICKETS_ADDR 0x40       //AƱ����������ַ��ѭ����10��32λ�ۼ�ֵ��10����ַ8λ
#define BBOX_TICKETS_ADDR 0x80       //BƱ����������ַ��ѭ����10��32λ�ۼ�ֵ��10����ַ8λ
#define CBOX_TICKETS_ADDR 0x120       //CƱ����������ַ��ѭ����10��32λ�ۼ�ֵ��10����ַ8λ
#define MAX_EE_AREA 10
#define AREA_A 1
#define AREA_B 2
#define AREA_C 3
#define A 0
#define B 1
#define C 2
#define model_ADDR   0x20//ģ�����ʹ洢��ַ
#define model_SERIAL_ADDR   0x21//ģ�����кŻ���ַ����20��8λ���к�

//���ת�������ٶ�
//uint8 cw;
//uint16 speed;
//��ת����
#define STOP 0        //ֹͣ
#define COROTATION 1        //��ת
#define ROLLBACK 2        //��ת

//��Ʊʱ��
#define DROP_T1  150
#define DROP_T2  150
#define DROP_T3  200
#define DCT_T1     20
#define DCT_T2     20
#define DCT_T3     40

// ��ȡ��Ϣʱ��
#define READ_MAS  20   //2//��״̬��ʱ��60ms
#define INTI_OVER_TIME 500
//һ��ʱ��
#define SECOND  5000
//һ��ʱ��
#define COM_OVER_TIME  10

//Ʊ��״̬
#define EXISTENCE 1         //����
#define INEXISTENCE 0       //������
#define DIG_TICKET 2        //��Ʊ������
#define WAITING 4        //�ȴ�������


//ģ��ģʽ:����or����
#define open_model 0
#define close_model 1
//����/��ֹ����TOKEN����
#define prohibit 0
#define allow 1


//ͨ��λ��
#define A_gallery 1//Aͨ��
#define B_gallery 2//Bͨ��
#define C_gallery 3 //Cͨ��

typedef struct//�ṹ��
{
	uint32  limit_cnt;
	uint8	limit_en;
}CNT;

typedef union//�����塢������
{
	uint8	status[18];
	struct
	{	
		//U�ʹ��������ڵ�Ϊ1���ڵ�Ϊ0
		uint8   checkticks1;//sens1:��Ʊ�ڶ��䴫�������ڵ�Ϊ0
		uint8   checkticks2;//sens2:��Ʊ�ڵ�����رռ��U�ʹ�����
		uint8   checkticks3;//sens3:��Ʊ�ڵ�����򿪼��U�ʹ�����
		uint8   checkticks4;//sens4�˱ҿڷ��⴫�������ڵ�Ϊ0
		uint8   checkticks5;//sens5:���տڷ��⴫�������ڵ�Ϊ0
		uint8   checkticks6;//sens6:���������⴫�������ڵ�Ϊ0
		uint8   checkticks7;//sens7:�ּ�ڵ����A��ͨ���U�ʹ�����
		uint8   checkticks8;//sens8:�ּ�ڵ����B��ͨ���U�ʹ�����		
		uint8   checkticks9;//����
		uint8   checkticks10;//����
		uint8   checkticks11;//����
		//��λ����
		uint8   checkticks12;//s1��AƱ�䵽λ  0����λ 1��δ��λ
		uint8   checkticks13;//s2��BƱ�䵽λ  0����λ 1��δ��λ
		uint8   checkticks14;//s3��CƱ�䵽λ  0����λ 1��δ��λ
		uint8   checkticks15;//����
		uint8   checkticks16;//����
		uint8   checkticks17;//����
		uint8   checkticks18;//����
	}SENSORS_STATUS;
}SENSORS;

typedef struct
{
	uint8	addr;
	uint8	data[4];
}EE_SAVE;

typedef union
{
    uint8   code[53];
    struct
    {
        uint8   len;        //��ǰ���ĳ���
    	uint8	act_code;   //��Ӧ��
    	uint8	result;     //���ؽ��:'e'   'w'   's'
        uint8   err_code;   //���ϴ���
        uint8   info[49];   //������Ϣ
    }MESSAGE;
}RETURN_CODE;

typedef enum //ö��
{
	com_ok = 0,					         //�޴���
	no_card_at_RW_area=0x01,		    //�޿���������
	multi_card_at_RW_area=0x02,			//���ſ���������
	card_at_RW_area=0x03,              //�п����������澯
	box1_non_existent = 0x39,		  //AƱ��δ��λ
	box2_non_existent=0x3a,			 //BƱ��δ��λ	
	box3_non_existent=0x3b,         // CƱ��δ��λ	(Ԥ��)
	card_block_at_RW_area = 0x3f,  //Ʊ������������Ʊ	
	sens_err=0x63,		           //����������
	sole1_err=0X64,                //��Ʊ�ڵ����1����
	sole2_err=0X65,               //���յ����2����
	rf232A_err,                  //����A����
	rf232B_err,                  //����B����
	open_entry_err=0x40,        //�����ʧ��
	CLOSE_entry_err=0x41,      //�ر����ʧ��
	//MOTOR_err=0x42,	           //�������
	change_A_err=0x43,	  //�л�Aͨ������
	change_B_err=0x44,	//�л�Bͨ������
	change_C_err=0x45,//�л�Cͨ������
	write_model_SERIAL_err,		//дģ�����к�ʧ��
    invalid_parameter=0x31,//������Ч
    //up_sens_err,	//��Ʊ�ڶ��䴫��������
   // down_sens_err,  //�ּ�ڶ��䴫��������
    //up_usens_err,  //��Ʊ�ڵ����U�ʹ���������
    //down_usens_err, //�ּ�ڵ����U�ʹ���������
    //detection_sens_err,//��Ʊ�ڼ�������䴫��������
}CMD_STATUS;

typedef struct
{
    uint8 re_data[30];              //���յ�������
    uint8 re_index;                 //���ռ���
    uint8 re_flag;                  //�Ƿ������ɱ�־1:�������0:δ���
}RESEIVE;

extern void SOLEA_OFF(void);


#endif

