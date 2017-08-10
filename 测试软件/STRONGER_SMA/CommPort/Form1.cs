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
            Control.CheckForIllegalCrossThreadCalls = false;//这一行是关键     
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            this.MaximumSize = this.Size;
            this.MinimumSize = this.Size;
            button2.Enabled = false;
            button3.Enabled = false;
            button4.Enabled = false;
            button5.Enabled = false;
            button25.Enabled = false;
            button6.Enabled = false;
            button20.Enabled = false;
            button21.Enabled = false; 
            button22.Enabled = false;
            button23.Enabled = false;
            button24.Enabled = false;
            button9.Enabled = false;
            button10.Enabled = false;
            button11.Enabled = false;
            button12.Enabled = false;
            button13.Enabled = false;
            button16.Enabled = false;
            button15.Enabled = false;
            button19.Enabled = false;
            button17.Enabled = false;
            button18.Enabled = false;
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
                    serialPort.BaudRate = 57600;
                    serialPort.Open();
                    button1.Text = "关闭串口";
                    button2.Enabled = true;
                    button3.Enabled = true;
                    button4.Enabled = true;
                    button5.Enabled = true;
                    button25.Enabled = true;
                    button6.Enabled = true;
                    button20.Enabled = true;
                    button21.Enabled = true;
                    button22.Enabled = true;
                    button23.Enabled = true;
                    button24.Enabled = true;
                    button9.Enabled = true;
                    button10.Enabled = true;
                    button11.Enabled = true;
                    button12.Enabled = true;
                    button13.Enabled = true;
                    button16.Enabled = true;
                    button15.Enabled = true;
                    button19.Enabled = true;
                    button17.Enabled = true;
                    button18.Enabled = true;
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
                button25.Enabled = false;
                button6.Enabled = false;
                button20.Enabled = false;
                button21.Enabled = false;
                button22.Enabled = false;
                button23.Enabled = false;
                button24.Enabled = false;
                button9.Enabled = false;
                button10.Enabled = false;
                button11.Enabled = false;
                button12.Enabled = false;
                button13.Enabled = false;
                button16.Enabled = false;
                button15.Enabled = false;
                button19.Enabled = false;
                button17.Enabled = false;
                button18.Enabled = false;
                textBox2.Enabled = false;
                comboBox1.Enabled = false;
                comboBox2.Enabled = false;
            }

        }
        /*****************************************************************************/
        /* Function Description:                                                     */
        /*****************************************************************************/
        //命令异或校验
        //参数[] bytes 需要校验的数据
        //参数size 需要校验数据的数量
        /*****************************************************************************/
        /* Parameters:                                                               */
        /*****************************************************************************/
        /*                                                                           */
        /*                                                                          */
        /*                                                                          */
        /*****************************************************************************/
        /* Return Values:        校验位                                        */
        /*****************************************************************************/
        /*                                                                          */
        /*   lrc检验码                                                                   */
        /*                                                                           */
        /*****************************************************************************/

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
        private static byte[] strToToHexByte(string hexString)
        {
            hexString = hexString.Replace(" ", "");
            if ((hexString.Length % 2) != 0)
                hexString += " ";
            byte[] returnBytes = new byte[hexString.Length / 2];
            for (int i = 0; i < returnBytes.Length; i++)
                returnBytes[i] = Convert.ToByte(hexString.Substring(i * 2, 2), 16);
            return returnBytes;

        }
        public static string byteToHexStr(byte[] bytes)
        {
            string returnStr = "";
            if (bytes != null)
            {
                for (int i = 0; i < bytes.Length; i++)
                {
                    returnStr +="  "+ bytes[i].ToString("X2");
                   
                }
            }
            return returnStr;
        }    
        
        private void button7_Click(object sender, EventArgs e)//清空接收区域的数据
        {
            if (textBox1.Text.Trim() != "")
            {
                textBox1.Clear();
            }

        }
        /*****************************************************************************/
        /* Function Description:                                                     */
        /*****************************************************************************/
        //串口数据接收
        //参数
        /*****************************************************************************/
        /* Parameters:                                                               */
        /*****************************************************************************/
        /*                                                                           */
        /*                                                                          */
        /*                                                                          */
        /*****************************************************************************/
        /* Return Values:          是否成功                                          */
        /*****************************************************************************/
        /*                                                                          */
        /*   NULL                                                                   */
        /*                                                                           */
        /*****************************************************************************/
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
           
            for(i=0;i<bytes;i++)
            {
                temp1[i] = buffer[i];
            }
            read_comm_data(temp1, temp1.Length);
            
 
        }
        //index从0开始 
        //获取取第index位 
        public static int GetBit(byte b, int index)//将第index位设为1 
        { return ((b & (1 << index)) > 0) ? 1 : 0; }

        public static byte SetBit(byte b, int index) //将第index位设为0 
        { return (byte)(b | (1 << index)); }

        public static byte ClearBit(byte b, int index) //将第index位取反 
        { return (byte)(b & (byte.MaxValue - (1 << index))); }
        
        public static byte ReverseBit(byte b, int index)
        { return (byte)(b ^ (byte)(1 << index)); }
     

        public void read_comm_data(byte[] temp, int len)
        {
            string str1 = byteToHexStr(temp);
            textBox1.AppendText("read：\t" + str1 + "\n");        
            
            byte[] send = new byte[2] { 0x10, 0x05 };
            string str2 = byteToHexStr(send);
            if (temp[0] == 0x10 && temp[1] == 0x06)
            {
                textBox1.AppendText("write：\t" + str2 + "\n");
                serialPort.Write(send, 0, send.Length);
            }   
           
        }       

        private void button15_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[6] { 0x10, 0x02, 0x88, 0x10, 0x03, 0x88 };
            //sendBuff[3] = GetLrc(sendBuff, 3);
            string str1 = byteToHexStr(sendBuff);

            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("读版本号write：\t" + str1 + "\n");

        }
        private void button2_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[6] { 0x10, 0x02, 0x81, 0x10, 0x03, 0x81 };
            //sendBuff[3] = GetLrc(sendBuff, 3);
            string str1 = byteToHexStr(sendBuff);

            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("初始化write：\t" + str1 + "\n");

        }

        private void button3_Click(object sender, EventArgs e)
        {
             byte[] sendBuff = new byte[7] { 0x10, 0x02, 0x86, 0x01, 0x10, 0x03, 0x87 };
            //sendBuff[3] = GetLrc(sendBuff, 3);//58
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("回收到A票箱 write:\t" + str1 + "\n");
            
            
        }

        private void button4_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[7] { 0x10, 0x02, 0x86, 0x02, 0x10, 0x03, 0x84 };
            //sendBuff[3] = GetLrc(sendBuff, 3);//58
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("回收到B票箱 write:\t" + str1 + "\n");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[7] { 0x10, 0x02, 0x86, 0x03, 0x10, 0x03, 0x85 };
            // sendBuff[3] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("回收到C票箱 write:\t" + str1 + "\n");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[4] { 0x55, 0x01, 0x07, 0x00 };
            sendBuff[3] = GetLrc(sendBuff, 3);//53
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("回收车票\tPC-->>模块：\t" + "回收车票" + "\n");
        }
             
        private void button17_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[6] { 0x10, 0x02, 0x82,0x10, 0x03, 0x82 };
            // sendBuff[3] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("获取模块状态 write:\t" + str1 + "\n");

            
        }

        private void button10_Click_1(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[8];
            sendBuff[0] = 0x10;
            sendBuff[1] = 0x02;
            sendBuff[2] = 0x8A;
            sendBuff[3] = 0x03;
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
            sendBuff[5] = 0x10;
            sendBuff[6] = 0x03;
            byte[] buff1 = new byte[3];
            Array.Copy(sendBuff, 2, buff1, 0, 3);//原数组，开始位，目标数组，开始位，数据长度
            sendBuff[7] = GetLrc(buff1,3);
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("读取A票箱电子标签write:\t" + str1 + "\n");
        }

        private void button11_Click_1(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[8];
            sendBuff[0] = 0x10;
            sendBuff[1] = 0x02;
            sendBuff[2] = 0x8A;
            sendBuff[3] = 0x04;
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
            sendBuff[5] = 0x10;
            sendBuff[6] = 0x03;
            byte[] buff1 = new byte[3];
            Array.Copy(sendBuff, 2, buff1, 0, 3);//原数组，开始位，目标数组，开始位，数据长度
            sendBuff[7] = GetLrc(buff1, 3);
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("读取B票箱电子标签write:\t" + str1 + "\n");
        }

        private void button12_Click_1(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[24];
            sendBuff[0] = 0x10;
            sendBuff[1] = 0x02;
            sendBuff[2] = 0x8B;
            sendBuff[3] = 0x03;
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
            byte[] byteArray = System.Text.Encoding.ASCII.GetBytes(textBox2.Text);
            if (byteArray.Length < 17)
            {
                for (int i = 0; i < byteArray.Length; i++)
                {
                    byteArray[i] = (byte)(byteArray[i] - 0x30);
                }
                Array.Copy(byteArray, 0, sendBuff, 5, byteArray.Length);//原数组，开始位，目标数组，开始位，数据长度
                sendBuff[21] = 0x10;
                sendBuff[22] = 0x03;
                byte[] buff1 = new byte[20];
                Array.Copy(sendBuff, 2, buff1, 0, 19);//原数组，开始位，目标数组，开始位，数据长度
                sendBuff[23] = GetLrc(buff1, buff1.Length);
                string str1 = byteToHexStr(sendBuff);
                serialPort.Write(sendBuff, 0, sendBuff.Length);
                textBox1.AppendText("设置A票箱电子标签write:\t" + str1 + "\n");
            }
            else
            {
                textBox1.AppendText("写入数据长度大于15位,\t请重新输入数据！" + "\n");
            }
        }

        private void button13_Click_1(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[24];
            sendBuff[0] = 0x10;
            sendBuff[1] = 0x02;
            sendBuff[2] = 0x8B;
            sendBuff[3] = 0x04;
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
            byte[] byteArray = System.Text.Encoding.ASCII.GetBytes(textBox2.Text);
            if (byteArray.Length < 17)
            {
                for (int i = 0; i < byteArray.Length; i++)
                {
                    byteArray[i] = (byte)(byteArray[i] - 0x30);
                }
                Array.Copy(byteArray, 0, sendBuff, 5, byteArray.Length);//原数组，开始位，目标数组，开始位，数据长度
                sendBuff[21] = 0x10;
                sendBuff[22] = 0x03;
                byte[] buff1 = new byte[20];
                Array.Copy(sendBuff, 2, buff1, 0, 19);//原数组，开始位，目标数组，开始位，数据长度
                sendBuff[23] = GetLrc(buff1, buff1.Length);
                string str1 = byteToHexStr(sendBuff);
                serialPort.Write(sendBuff, 0, sendBuff.Length);
                textBox1.AppendText("设置B票箱电子标签write:\t" + str1 + "\n");
            }
            else
            {
                textBox1.AppendText("写入数据长度大于15位,\t请重新输入数据！" + "\n");
            }
        }

       

        private void button9_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[6] { 0x10, 0x02, 0x8D, 0x10, 0x03, 0x8D };
            // sendBuff[3] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("打开退币口指示灯write:\t" + str1 + "\n"); 
        }

        private void button18_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[6] { 0x10, 0x02, 0x8E, 0x10, 0x03, 0x8E };
            // sendBuff[3] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("关闭退币口指示灯write:\t" + str1 + "\n"); 
        }

        private void button19_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[6] { 0x10, 0x02, 0x83, 0x10, 0x03, 0x83 };
            // sendBuff[3] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("允许接收TOKENwrite:\t" + str1 + "\n"); 
        }

        private void button20_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[6] { 0x10, 0x02, 0x84, 0x10, 0x03, 0x84 };
            // sendBuff[3] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("禁止接收TOKENwrite:\t" + str1 + "\n"); 
        }

        private void button21_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[6] { 0x10, 0x02, 0x87, 0x10, 0x03, 0x87 };
            // sendBuff[3] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("模块复位write:\t" + str1 + "\n"); 
        }

        private void button22_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[6] { 0x10, 0x02, 0xF0, 0x10, 0x03, 0xF0 };
            // sendBuff[3] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("读取审计累计值write:\t" + str1 + "\n");
        }

        private void button23_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[7] { 0x10, 0x02, 0x8F, 0x00, 0x10, 0x03, 0x8F };
            //sendBuff[6] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("设置为常开模式write:\t" + str1 + "\n");
        }
        private void button6_Click_1(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[7] { 0x10, 0x02, 0x8F, 0x01, 0x10, 0x03, 0x8E };
            //sendBuff[6] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("设置为常关模式write:\t" + str1 + "\n");
        }
        private void button24_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[6]{ 0x10, 0x02, 0x90, 0x10, 0x03, 0x90 };
            //sendBuff[6] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("读取模块模式write:\t" + str1 + "\n");
        }

        private void button16_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[7] { 0x10, 0x02, 0x8C, 0x03, 0x10, 0x03, 0x8F };
            // sendBuff[3] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("读取A票箱物理编号write:\t" + str1 + "\n");
        }

        private void button25_Click(object sender, EventArgs e)
        {
            byte[] sendBuff = new byte[7] { 0x10, 0x02, 0x8C, 0x04, 0x10, 0x03, 0x88 };
            // sendBuff[3] = GetLrc(sendBuff, 3);//50
            string str1 = byteToHexStr(sendBuff);
            serialPort.Write(sendBuff, 0, sendBuff.Length);
            textBox1.AppendText("读取B票箱物理编号write:\t" + str1 + "\n");
        }


       
        

       
        
       
    }
}

      

    

