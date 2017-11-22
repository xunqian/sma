#include "variables_def.h"

//版本号
uint8 MODULE_VERSION[8] = "SMA0001A";
uint8 CPU_VERSION[7] = "V1.0R02";
//序列号
uint8 MODULE_SERIAL[20] = "12345678901234567890";

//看门狗定时复位
uint8   wdt_reseten = 1;
uint16  wdt_resetreg;  

 uint8 sens_selfcheck=0;  //传感器自检标志
 uint8 result=0;
 uint8 detection=0; 		 //检测区是否有卡标志
 uint8 antenna = 0; 		 //天线区是否有卡标志
 uint16 drop_tic_time = 0;	 //通道切换超时时间
 uint16 old_outtime = 0;	 //老化超时时间
 uint16 init_over_time = 0;  //初始化超时
 uint16 over_time = 0;	  //通信超时 
 uint32 sole_open_over_time = 0;//入票口电磁铁打开超时1s 
 uint32 sole_openleave_over_time = 0;//入票口电磁铁打开后离开超时100ms 
 uint32 sole_close_over_time = 0;//入票口电磁铁打开超时1s 
 uint32 sole2_open_over_time = 0;//入票口电磁铁打开超时1s 
 uint32 sole2_close_over_time = 0;//入票口电磁铁打开超时1s 
 //模式设置
uint8 model;  
 //允许/禁止接收设置
uint8 receive_limits;
  //连续回收使能设置
uint8 contri_recover_set;
//通道位置
uint8 current_gallery;
 //心跳灯控制  1表示启动心跳灯，频率1HZ   ；2心跳灯加速，有故障
 //0停止跳动
 uint8 normal_start = 1; 
 //退币口指示灯标志
 uint8 LED_EN=OFF;//模块控制标志
 //退币口指示灯闪烁时间计数
 uint16 flash_cnt=0; 
 //回收or退换票卡数量
 uint32 box_num[3]={0,0,0};
 uint8 sum_open_over_time=0;
 //部件测试控制量
 uint8 LED_NUM=0;
 //通信步骤  
 uint8 communication_step = 1;
  //uart0,与ECU通信发送接收用变量定义
 //通信缓存
uint8	 receive_ok;//uart0数据接收完成标志  1:成功  0:否
uint8	 inbox[60];//接收数据缓存
 //传感器状态
SENSORS sens;
SENSORS sens_last;
 
 //RFID超时延时
 uint16 g_cbWaitRespDly = 0;
 //心跳灯计数
 uint16 work_light_cnt=0;
 //测试回收性能使用
 uint32 time_count=0; 
uint8 LED_control_flag;//0:  模块控制1 :上位机控制
uint16 OutGPA;
uint16 OutGPB;
uint16 OutGPC;
uint16 OutGPD;
uint16 OutGPE;
