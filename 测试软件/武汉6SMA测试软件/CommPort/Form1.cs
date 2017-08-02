using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;



namespace CommPort
{
    public partial class form1 : Form
    {
        public form1()
        {
            InitializeComponent();
        }

       // DateTime DateTime1, DateTime2;
        private void Form1_Load(object sender, EventArgs e)
        {
            this.MaximumSize = this.Size;
            this.MinimumSize = this.Size;
            button2.Enabled = false;
            button3.Enabled = false;
            button4.Enabled = false;
            button5.Enabled = false;
            button6.Enabled = false;
           
            button9.Enabled = false;
            button10.Enabled = false;
            button11.Enabled = false;
            button12.Enabled = false;
            button13.Enabled = false;
           
            button15.Enabled = false;
            button16.Enabled = false;
            button17.Enabled = false;
            button18.Enabled = false;
            button19.Enabled = false;
            textBox2.Enabled = false;
            comboBox1.Enabled = false;
            comboBox2.Enabled = false;
            cbCommPort.Items.Clear();
            foreach (string strName in SerialPort.GetPortNames())
            {
                cbCommPort.Items.Add(strName);
            }
            if (cbCommPort.Items.Count > 0)
            {
                cbCommPort.SelectedIndex = 0;

            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (button1.Text == "打开串口")
            {
                try
                {
                    serialPort.PortName = cbCommPort.SelectedItem.ToString();
                    serialPort.BaudRate = 115200;
                    serialPort.Open();
                    button1.Text = "关闭串口";
                    button2.Enabled = true;
                    button3.Enabled = true;
                    button4.Enabled = true;
                    button5.Enabled = true;
                    button6.Enabled = true;
                   
                    button9.Enabled = true;
                    button10.Enabled = true;
                    button11.Enabled = true;
                    button12.Enabled = true;
                    button13.Enabled = true;
                    
                    button15.Enabled = true;
                    button16.Enabled = true;
                    button17.Enabled = true;
                    button18.Enabled = true;
                    button19.Enabled = true;
                    textBox2.Enabled = true;
                    comboBox1.Enabled = true;
                    comboBox2.Enabled = true;

                }
                catch (Exception ex)
                {
                    MessageBox.Show("打开串口时错误：" + ex.Message);
                }

            }
            else
            {
                if (serialPort.IsOpen)
                {
                    serialPort.Close();
                }

                button1.Text = "打开串口";
                button2.Enabled = false;
                button3.Enabled = false;
                button4.Enabled = false;
                button5.Enabled = false;
                button6.Enabled = false;
               
                button9.Enabled = false;
                button10.Enabled = false;
                button11.Enabled = false;
                button12.Enabled = false;
                button13.Enabled = false;
               
                button15.Enabled = false;
                button16.Enabled = false;
                button17.Enabled = false;
                button18.Enabled = false;
                button19.Enabled = false;
                textBox2.Enabled = false;
                comboBox1.Enabled = false;
                comboBox2.Enabled = false;
            }

        }

        private byte GetLrc(byte[] bytes, int size)
        {
            byte lrc = bytes[0];
            for (int i = 1; i < size; i++)
            {
                lrc ^= bytes[i];
            }
            return lrc;
        }

        private string ByteToHexString(byte[] bytes)
        {
            string str = BitConverter.ToString(bytes).Replace("-", "\t");
            return str;
        }

        private void button14_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x00, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("打开入口\tPC-->>模块：\t" + "打开入口" + "\n");
        }

        private void button15_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x06, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("获取版本信息\tPC-->>模块：\t" + "获取版本信息" + "\n");

        }


        private void button2_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x01, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);//55
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("初始化模块\tPC-->>模块：\t" + "初始化模块" + "\n");

        }

        private void button3_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x02, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);//56
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("切换通道1\tPC-->>模块：\t" + "切换到通道1" + "\n");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x03, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);//58
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("切换通道2\tPC-->>模块：\t" + "切换到通道2" + "\n");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x04, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);//50
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("切换通道3\tPC-->>模块：\t" + "切换到通道3" + "\n");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x07, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);//53
            serialPort.Write(sendBuff, 0, sendBuff.Length);
           // DateTime1 = DateTime.Now;
            textBox1.AppendText("回收车票\tPC-->>模块：\t" + "回收车票" + "\n");
        }



        private void button7_Click(object sender, EventArgs e)//清空接收区域的数据
        {
            if (textBox1.Text.Trim() != "")
            {
                textBox1.Clear();
            }

        }

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
           
            System.Threading.Thread.Sleep(100);
            int bytes = serialPort.BytesToRead;
            byte[] buffer = new byte[bytes];
            if (bytes == 0)
            {
                return;
            }

            serialPort.Read(buffer, 0, bytes);
            int i, j = 0, LEN = 0;
            byte[] temp1 = new byte[bytes], temp2 = new byte[bytes], temp3 = new byte[bytes];
            int count = 0;
            for (i = 0; i < bytes; i++)
            {
                if (buffer[i] == 0x55)
                {
                    count++;
                    if (buffer[1] != 0x01 && count != 2)
                    {
                        LEN = buffer[i + 1];
                    }
                }

                if (count == 2)
                {                                       
                        temp2[j++] = buffer[i];                    
                }
            }
            for (i = 0; i < LEN + 3; i++)
            {
                temp1[i] = buffer[i];
            }
            if (temp1[0] == 0x55)
                read_comm_data(temp1, LEN + 3);
            if (temp2[0] == 0x55&&temp2[1]!=0)
                read_comm_data(temp2, LEN + 3);
            if (temp3[0] == 0x55)
                read_comm_data(temp3, LEN + 3);
           // DateTime2 = DateTime.Now;




        }
        //index从0开始 
        //获取取第index位 
        public static int GetBit(byte b, int index) { return ((b & (1 << index)) > 0) ? 1 : 0; }
        //将第index位设为1 
        public static byte SetBit(byte b, int index) { return (byte)(b | (1 << index)); }
        //将第index位设为0 
        public static byte ClearBit(byte b, int index) { return (byte)(b & (byte.MaxValue - (1 << index))); }
        //将第index位取反 
        /*private string DateDiff(DateTime DateTime1, DateTime DateTime2)
        {
            string dateDiff = null;

            TimeSpan ts1 = new TimeSpan(DateTime1.Ticks);
            TimeSpan ts2 = new TimeSpan(DateTime2.Ticks);
            TimeSpan ts = ts1.Subtract(ts2).Duration();
            dateDiff =  ts.Milliseconds.ToString() + "毫秒";
            return dateDiff;
        }*/
        public static byte ReverseBit(byte b, int index) { return (byte)(b ^ (byte)(1 << index)); }
        public void read_comm_data(byte[] temp, int len)
        {
            //string TimeString=DateDiff(DateTime1, DateTime2);
           // textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText(TimeString + "\n"); }));
            switch (temp[2])
            {
                case 0x00:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到打开入口命令\t" + "\n"); }));
                    break;
                case 0x01:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到初始化命令\t" + "\n"); }));
                    break;
                case 0x02:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到切换到票箱1命令\t" + "\n"); }));
                    break;
                case 0x03:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到切换到票箱2命令\t" + "\n"); }));
                    break;
                case 0x04:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到切换到票箱3命令\t" + "\n"); }));
                    break;
                case 0x05:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到读取模块状态命令\t" + "\n"); }));
                    break;
                case 0x06:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到获取版本号命令\t" + "\n"); }));
                    break;
                case 0x07:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到回收命令\t" + "\n"); }));
                    break;
                case 0x08:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到退票命令\t" + "\n"); }));
                    break;
                case 0x09:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到读取TAC数据命令\t" + "\n"); }));
                    break;
                case 0x0A:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到读取TAC数据命令\t" + "\n"); }));
                    break;
                case 0x0B:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到关闭入口命令\t" + "\n"); }));
                    break;
                case 0x0C:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到打开退币口指示灯命令\t" + "\n"); }));
                    break;
                case 0x0D:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块接收到关闭退币口指示灯命令\t" + "\n"); }));
                    break;
                case 0x80:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "初始化失败\t" + "\n"); }));
                    break;
                case 0x82:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "切换到A票箱失败\t" + "\n"); }));
                    break;
                case 0x83:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "切换到B票箱失败\t" + "\n"); }));
                    break;
                case 0x84:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "切换到退票口失败\t" + "\n"); }));
                    break;
                case 0x85:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "回收或退币失败\t" + "\n"); }));
                    break;
                case 0x86:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "未读到TAC数据\t" + "\n"); }));
                    break;
                case 0x88:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块复位失败\t" + "\n"); }));
                    break;
                case 0x89:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "允许接收TOKEN失败\t" + "\n"); }));
                    break;
                case 0x8A:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "禁止接收TOKEN失败\t" + "\n"); }));
                    break;
                case 0x8B:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "传感器自检失败\t" + "\n"); }));
                    break;
                case 0xB5:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "模块状态为：\t" + "\n"); }));
                    if (GetBit(temp[3],0)==1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("A票箱存在," ); }));
                    }
                  else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText( "A票箱不存在,"); }));
                    }
                    if (GetBit(temp[3], 1) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText( "B票箱存在,"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("B票箱不存在,"); }));
                    }
                    if (GetBit(temp[3],2) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("C票箱存在,"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("C票箱不存在,"); }));
                    }
                    if (GetBit(temp[3], 3) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("天线区有票,"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText( "天线区无票,"); }));
                    }
                    if (GetBit(temp[3], 4) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("通道在1位置。" + "\n"); }));
                    }
                    if (GetBit(temp[3], 5) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("通道在2位置。" + "\n"); }));
                    }
                    if (GetBit(temp[3], 6) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("通道在3位置。" + "\n"); }));
                    }
                    if (GetBit(temp[3], 7) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("投币口打开" + "\n"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("投币口关闭" + "\n"); }));
                    }

                    if (GetBit(temp[4], 0) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("入票口对射传感器故障,"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("入票口对射传感器正常,"); }));
                    }
                    if (GetBit(temp[4], 1) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("分拣口对射传感器故障,"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("分拣口对射传感器正常,"); }));
                    }
                    if (GetBit(temp[4], 2) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("入票口U型传感器故障,"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("入票口U型传感器正常,"); }));
                    }
                    if (GetBit(temp[4], 3) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("分拣口U型传感器故障,"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("分拣口U型传感器正常,"); }));
                    }
                    if (GetBit(temp[4], 4) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("检测区对射传感器故障。" + "\n"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("检测区对射传感器正常。" + "\n"); }));
                    }
                         
                    break;
                case 0x90:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "传感器状态为：\t" + "\n"); }));
                    if (GetBit(temp[3], 0) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("A票箱存在,"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("A票箱不存在,"); }));
                    }
                    if (GetBit(temp[3], 1) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("B票箱存在,"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("B票箱不存在,"); }));
                    }
                    if (GetBit(temp[3], 2) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("C票箱存在,"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("C票箱不存在,"); }));
                    }
                    if (GetBit(temp[3], 3) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("天线区有票,"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("天线区无票,"); }));
                    }
                    if (GetBit(temp[3], 4) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("通道在1位置。" + "\n"); }));
                    }
                    if (GetBit(temp[3], 5) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("通道在2位置。" + "\n"); }));
                    }
                    if (GetBit(temp[3], 6) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("通道在3位置。" + "\n"); }));
                    }
                    if (GetBit(temp[3], 7) == 1)
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("投币口打开" + "\n"); }));
                    }
                    else
                    {
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("投币口关闭" + "\n"); }));
                    }
                    break;
                case 0x97:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "回收或退币成功\t" + "\n"); }));
                    break;
                case 0x98:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "SMA初始化成功\t" + "\n"); }));
                    break;
                case 0x99:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "有物体进入SMA\t" + "\n"); }));
                    break;
                case 0xA8:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "复位成功\t" + "\n"); }));
                    break;
                case 0xA9:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "允许接收TOKEN设置成功\t" + "\n"); }));
                    break;
                case 0xAA:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "禁止接收TOKEN设置成功\t" + "\n"); }));
                    break;
                case 0xA0:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "TAC数据为：\t" + "\n"); }));
                    byte[] buff = new byte[25];
                    Array.Copy(temp, 0, buff, 0, 25);
                    ByteToHexString(buff);
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "电子标签数据为\t" + ByteToHexString(buff) + "\n"); }));
                    break;

                case 0xA1:
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "固件版本号为：\t" + "\n"); }));
                    byte[] buff1 = new byte[2];
                    Array.Copy(temp, 3, buff1, 0, 2);//原数组，开始位，目标数组，开始位，数据长度
                    ByteToHexString(buff1);
                    textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "SMA固件版本为\t" + ByteToHexString(buff1) + "\n"); }));

                    break;
                case 0xA3:                   
                    if (temp[3]==0x00)
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "写TAC数据成功\t" + "\n"); }));
                    if (temp[3] == 0x01)
                        textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText("接收到数据\t模块-->>PC\t" + "写TAC数据失败\t" + "\n"); }));
                    break;
            }
        }





        private void button16_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x08, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("直接退票\tPC-->>模块：\t" + "直接退票" + "\n");           
        }        
        private void button17_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x05, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("获得模块状态\tPC-->>模块：\t" + "获得模块状态" + "\n");
        }

        private void button10_Click_1(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[6];
            sendBuff[0] = 0x55;
            sendBuff[1] = 0x03;
            sendBuff[2] = 0x09;
            sendBuff[3] = 0x01;
            switch (comboBox1.Text)
            {
                case "page8":
                    sendBuff[4] = 0x08;
                    break;
                case "page9":
                    sendBuff[4] = 0x09;
                    break;
                case "page10":
                    sendBuff[4] = 0x0A;
                    break;
                case "page11":
                    sendBuff[4] = 0x0B;
                    break;
                default:
                    sendBuff[4] = 0x08;
                    break;
            }

            sendBuff[5] = GetLrc(sendBuff, 5);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("读tag1数据\tPC-->>模块：\t" + "读tag1数据" + "\n");
        }

        private void button11_Click_1(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[6];
            sendBuff[0] = 0x55;
            sendBuff[1] = 0x03;
            sendBuff[2] = 0x09;
            sendBuff[3] = 0x02;
            switch (comboBox1.Text)
            {
                case "page8":
                    sendBuff[4] = 0x08;
                    break;
                case "page9":
                    sendBuff[4] = 0x09;
                    break;
                case "page10":
                    sendBuff[4] = 0x0A;
                    break;
                case "page11":
                    sendBuff[4] = 0x0B;
                    break;
                default:
                    sendBuff[4] = 0x08;
                    break;
            }
            sendBuff[5] = GetLrc(sendBuff, 5);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("读tag2数据\tPC-->>模块：\t" + "读tag2数据" + "\n");
        }

        private void button12_Click_1(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[22];
            sendBuff[0] = 0x55;
            sendBuff[1] = 19;
            sendBuff[2] = 0x0A;
            sendBuff[3] = 0x01;

            switch (comboBox2.Text)
            {
                case "page8":
                    sendBuff[4] = 0x08;
                    break;
                case "page9":
                    sendBuff[4] = 0x09;
                    break;
                case "page10":
                    sendBuff[4] = 0x0A;
                    break;
                case "page11":
                    sendBuff[4] = 0x0B;
                    break;
                default:
                    sendBuff[4] = 0x08;
                    break;
            }
            byte[] byteArray = System.Text.Encoding.ASCII.GetBytes(textBox2.Text);
            if (byteArray.Length < 17)
            {
                for (int i = 0; i < byteArray.Length; i++)
                {
                    byteArray[i] = (byte)(byteArray[i] - 0x30);
                }
                Array.Copy(byteArray, 0, sendBuff, 5, byteArray.Length);
                sendBuff[21] = GetLrc(sendBuff, 21);
                serialPort.Write(sendBuff, 0, sendBuff.Length);
                textBox1.AppendText("写tag1数据\tPC-->>模块：\t" + "写tag1数据" + "\n");
            }
            else
            {
                textBox1.AppendText("写tag1数据\tPC-->>模块：\t" + "写入数据长度大于15位,\t请重新输入数据！" + "\n");
            }
        }

        private void button13_Click_1(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[22];
            sendBuff[0] = 0x55;
            sendBuff[1] = 19;
            sendBuff[2] = 0x0A;
            sendBuff[3] = 0x02;

            switch (comboBox2.Text)
            {
                case "page8":
                    sendBuff[4] = 0x08;
                    break;
                case "page9":
                    sendBuff[4] = 0x09;
                    break;
                case "page10":
                    sendBuff[4] = 0x0A;
                    break;
                case "page11":
                    sendBuff[4] = 0x0B;
                    break;
                default:
                    sendBuff[4] = 0x08;
                    break;
            }
            byte[] byteArray = System.Text.Encoding.ASCII.GetBytes(textBox2.Text);
            if (byteArray.Length < 17)
            {
                for (int i = 0; i < byteArray.Length; i++)
                {
                    byteArray[i] = (byte)(byteArray[i] - 0x30);
                }
                Array.Copy(byteArray, 0, sendBuff, 5, byteArray.Length);
                sendBuff[21] = GetLrc(sendBuff, 21);
                serialPort.Write(sendBuff, 0, sendBuff.Length);
                textBox1.AppendText("写tag2数据\tPC-->>模块：\t" + "写tag2数据" + "\n");
            }
            else
            {
                textBox1.AppendText("写tag2数据\tPC-->>模块：\t" + "写入数据长度大于15位,\t请重新输入数据！" + "\n");
            }
            //byte[] buff8 = new byte[21];
            //Array.Copy(sendBuff, 0, buff8, 0, 21);
            //ByteToHexString(buff8);
            //textBox1.Invoke(new EventHandler(delegate { textBox1.AppendText(ByteToHexString(buff8) + "\n"); }));
        }

        private void button8_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x0B, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("关闭入口\tPC-->>模块：\t" + "关闭入口" + "\n");
        }

        private void button9_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x0B, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("允许接收TOKEN\tPC-->>模块：\t" + "允许接收TOKEN" + "\n");
        }

        private void button18_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x0C, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("禁止接收TOKEN\tPC-->>模块：\t" + "禁止接收TOKEN" + "\n");
        }

        private void button19_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x0E, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("测试传感器\tPC-->>模块：\t" + "测试传感器" + "\n");
        }

        
       
    }
}

      

    

