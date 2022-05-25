using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.IO;
using System.IO.Ports;
using System.Threading;
namespace SWS_RFID
{
    public partial class Form1 : Form
    {
        //public delegate void MyInvoke(string str1, string str2);
        public delegate void MyInvoke();
        private SerialPort com;
        byte[] bytess = new byte[200];
        byte []bytess1= new byte[10];
        byte[] handshaks = new byte[10] { 0x27, 0x21, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x3C, 0x4C };
        byte[] handshake = new byte[10] { 0x27, 0x21, 0xDA, 0x58, 0, 0, 0, 0, 0, 0 };
        UInt16 isopen = 0, nums = 1;

        /*******************************************************************************
** 函数名称 ：CRC16()
** 函数功能 ：CRC校验码计算及检测（当输入的值包含了以完成的CRC校验值时）
** 入口参数 ：接收到的一帧数据的数组首地址及其长度
** 出口参数 ：CRC校验码（当输入的值包含了以完成的CRC校验值时返回零）
********************************************************************************/
        static byte[] aucCRCHi = new byte[256] {
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
            0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
            0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40
        };

        static byte[] aucCRCLo = new byte[256] {
            0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
            0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
            0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
            0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
            0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
            0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
            0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
            0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
            0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
            0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
            0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
            0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
            0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
            0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
            0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
            0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
            0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
            0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
            0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
            0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
            0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
            0x41, 0x81, 0x80, 0x40
        };

        public UInt16 CRC16(byte[] Frame, byte Length)     // 传入要校验的数组名及其长度
        {
            byte CRCHi = 0xFF;
            byte CRCLo = 0xFF;
            int iIndex, i = 0;
            while (Length != 0)
            {
                Length--;
                //iIndex = CRCLo ^ *( Frame++ );
                iIndex = CRCLo ^ (Frame[i++]);
                CRCLo = (byte)(CRCHi ^ aucCRCHi[iIndex]);
                CRCHi = aucCRCLo[iIndex];
            }
            return (UInt16)(CRCHi << 8 | CRCLo);// CRC校验返回值
        }

     
        public Form1()
        {
            InitializeComponent();
        }

        public static void strncpy(byte[] s1, byte[] s2, int num)
        {
            int i;
            for (i = 0; i < num; i++)
            {
                s1[i] = s2[i];
            }
        }

        public static int strncmp(byte[] s1, byte[] s2, int num)
        {
            int i;
            for (i = 0; i < num; i++)
            {
                if (s1[i] == s2[i])
                {
                    if (i == 3)
                        return 1;
                }
                else
                    return 0;
            }
            return 0;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            mifaresanqu.SelectedIndex = 0;

            com = new SerialPort();
            com.BaudRate = 115200;
            com.DataBits = 8;
            com.ReadBufferSize = 100;
            for (nums = 1; nums < 10; nums++)
            {
                com.PortName = "COM" + nums.ToString();
                if (isopen == 0)
                {
                    try
                    {
                        com.Open();             //打开串口
                        com.Write(handshaks, 0, 10);
                        Thread.Sleep(100);
                        com.Read(bytess, 0, com.BytesToRead);
                        System.Text.Encoding.ASCII.GetBytes(com.ReadExisting());
                        com.Close();
                        if (strncmp(bytess, handshake, 4) == 1)
                        {
                            isopen = 1;
                        }
                        else
                        {
                            ;
                        }
                    }
                    catch
                    {
                        ;
                    }
                }
                else
                {
                    nums--;
                    com.PortName = "COM" + nums.ToString();
                    com.Open();
                    this.com.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.OnDataReceived);
                    return;
                }
            }
            MessageBox.Show("没有监测到读卡器，请确保读卡器连接到计算机!");
            //
            //nums=3;
            //com.PortName = "COM" + nums.ToString();
            //com.Open();
            //this.com.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.OnDataReceived);
            //测试完后删除.
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            DialogResult mess = MessageBox.Show("你确定要关闭吗?", "关闭程序", MessageBoxButtons.YesNo);
            if (mess == DialogResult.Yes)
            {
                com.Close();
                Application.ExitThread();
            }
            else
            {
                e.Cancel = true;
            }
        }

        public void DoWork()
        {
            MyInvoke mi = new MyInvoke(UpdateForm);
            //this.BeginInvoke(mi, new Object[] { "我是文本框", "haha"});
            this.BeginInvoke(mi, new Object[] { });
        }

        public static string ToHexString(byte[] bytes) // 0xae00cf => "AE00CF "
        {
            string hexString = string.Empty;
            if (bytes != null)
            {
                StringBuilder strB = new StringBuilder();

                for (int i = 0; i < bytes.Length; i++)
                {
                    strB.Append(bytes[i].ToString("X2"));
                }
                hexString = strB.ToString();
            }
            return hexString;
        }


        public void UpdateForm()
        {
            int s = com.BytesToRead;
            com.Read(bytess, 0,s);
            System.Text.Encoding.ASCII.GetBytes(com.ReadExisting());
            if (CRC16(bytess,(byte)s) == 0)
            {
                toolStripStatusLabel1.Text = "";
                switch (bytess[1]) //根据功能码执行相应功能
                {
                    case 0x18:
                        byte[] new0X18 = bytess.Skip(2).Take(30).ToArray();
                        string str0x18 = Encoding.UTF8.GetString(new0X18);
                        adds.Text = str0x18;
                        break;
                    case 0x19:
                        tabControl1.SelectedIndex = 0;
                        /*
                        bytess[0] = bytess[4];
                        bytess[1] = bytess[5];
                        bytess[4] = bytess[3];
                        bytess[5] = bytess[2];
                        bytess[2] = bytess[1];
                        bytess[3] = bytess[0];
                        */
                        byte[] new0X19 = bytess.Skip(2).Take(4).ToArray();
                        uid.Text = ToHexString(new0X19);
                        break;
                    case 0x20:
                        if(bytess[2]==1)
                        {
                            radioButton1.Checked = true;
                            radioButton2.Checked = false;
                        }
                        else
                        {
                            radioButton1.Checked = false;
                            radioButton2.Checked = true;
                        }
                        if (bytess[3] > ages.Maximum)
                            bytess[3] = (byte)ages.Maximum;
                        else if (bytess[3] < 0)
                            bytess[3] = 0;
                        ages.Value=bytess[3];
                        byte[] new0X20 = bytess.Skip(4).Take(11).ToArray();
                        string ll = Encoding.Default.GetString(new0X20);
                        phones.Text = ll;
                        byte[] new0X201 = bytess.Skip(15).Take(15).ToArray();
                        string str = Encoding.UTF8.GetString(new0X201);
                        names.Text = str;
                        break;
                    case 0x21:     // 向从机发出握手信息
                        //握手成功
                        if (s == 4)
                        {
                            toolStripStatusLabel1.Text = DateTime.Now.ToString() + "握手成功!";
                        }
                        break;
                    case 0x30:      // 写命令0
                        //写命令0成功
                        if (s != 4)
                        {
                            //byte[] newA = bytess.Skip(2).Take(s - 4).ToArray();
                            //values.Text = ToHexString(newA);
                        }
                        else
                        {
                            toolStripStatusLabel1.Text = DateTime.Now.ToString() + "写命令成功!";
                        }
                        break;
                    case 0x40:      //BUS_RD0 0x40:   
                        //读命令0成功
                            byte[] newA = bytess.Skip(2).Take(s - 4).ToArray();
                            values.Text = ToHexString(newA);
                            toolStripStatusLabel1.Text = DateTime.Now.ToString() + "读命令成功!";
                        break; 






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    case 0x79:
                        tabControl1.SelectedIndex = 1;
                        /*
                        bytess[0] = bytess[4];
                        bytess[1] = bytess[5];
                        bytess[4] = bytess[3];
                        bytess[5] = bytess[2];
                        bytess[2] = bytess[1];
                        bytess[3] = bytess[0];
                        */
                        byte[] new0X79 = bytess.Skip(2).Take(4).ToArray();
                        mifareid.Text = ToHexString(new0X79);        
                        break;
                    case 0x90:      //写mifare one成功
                            toolStripStatusLabel1.Text = DateTime.Now.ToString() + "mifare one 写数据成功!";
                        break;
                    case 0xa0:      //读mifare one成功
                        byte[] new0xa0 = bytess.Skip(2).Take(16).ToArray();
                        mifaredata.Text = ToHexString(new0xa0);
                        toolStripStatusLabel1.Text = DateTime.Now.ToString() + "mifare one 读数据成功!";
                        break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    default:
                        break;
                }                
            }
        }

        private void OnDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            Thread thread = new Thread(new ThreadStart(DoWork));
            //bytess = System.Text.Encoding.ASCII.GetBytes(com.ReadExisting()); 
            thread.Start();
        }

        private void Buttons_Click(object sender, EventArgs e)
        {
            UInt16 CRC_Result=0,i,j;
            Button btn = sender as Button;
            if (btn.Name == "reset")
            {
                bytess1[0]=0x27;
                bytess1[1] = 0x20;                               // 通信初始化状态
                CRC_Result = CRC16(bytess1,2);
                bytess1[2] = (byte)(CRC_Result&0x00FF);        //CRC校验码的低字节
                bytess1[3] = (byte)((CRC_Result>>8)&0x00FF); //CRC校验码的高字节
                com.Write(bytess1,0,4);
            }
            else if (btn.Name == "cardinit")
            {
                bytess1[0] = 0x27;
                bytess1[1] = 0x19;                               // 通信初始化状态
                CRC_Result = CRC16(bytess1, 2);
                bytess1[2] = (byte)(CRC_Result & 0x00FF);        //CRC校验码的低字节
                bytess1[3] = (byte)((CRC_Result >> 8) & 0x00FF); //CRC校验码的高字节
                com.Write(bytess1, 0, 4);
                for (i = 0; i < 100; i++)
                {
                    Thread.Sleep(30);
                    progressBar1.Value = i;
                }
            }
            else if(btn.Name == "writes")
            {
                j = (UInt16)(values.TextLength / 2);
                addend.Value = j;
                bytess[0] = 0x27;
                bytess[1] = 0x30;                               // 写命令0
                bytess[2] = (byte)(((UInt16)(addstart.Value) & 0xff00) >> 8);
                bytess[3] = (byte)((UInt16)(addstart.Value) & 0x00ff);
                bytess[4] = (byte)(((UInt16)(addend.Value) & 0xff00) >> 8);
                bytess[5] = (byte)((UInt16)(addend.Value) & 0x00ff);
                
                for(i=0;i<j;i++)
                {
                    bytess[i+6]=Convert.ToByte(values.Text.Substring(i*2,2),16);
                }
                CRC_Result = CRC16(bytess,(byte)(i+6));
                bytess[i+6] = (byte)(CRC_Result & 0x00FF);        //CRC校验码的低字节
                bytess[i+7] = (byte)((CRC_Result >> 8) & 0x00FF); //CRC校验码的高字节
                bytess1[0] = 0x27;
                bytess1[1] = 0x20;                               // 通信初始化状态
                CRC_Result = CRC16(bytess1, 2);
                bytess1[2] = (byte)(CRC_Result & 0x00FF);        //CRC校验码的低字节
                bytess1[3] = (byte)((CRC_Result >> 8) & 0x00FF); //CRC校验码的高字节
                com.Write(bytess1, 0, 4);
                Thread.Sleep(800);
                com.Write(bytess, 0,i+8);
            }
            else if(btn.Name == "reads")
            {
                bytess[0] = 0x27;
                bytess[1] = 0x40;                               // 读命令0
                bytess[2] = (byte)(((UInt16)(addstart.Value)&0xff00)>>8);
                bytess[3] = (byte)((UInt16)(addstart.Value) & 0x00ff);
                bytess[4] = (byte)(((UInt16)(addend.Value) & 0xff00) >> 8);
                bytess[5] = (byte)((UInt16)(addend.Value) & 0x00ff);
                CRC_Result = CRC16(bytess,6);
                bytess[6] = (byte)(CRC_Result & 0x00FF);        //CRC校验码的低字节
                bytess[7] = (byte)((CRC_Result >> 8) & 0x00FF); //CRC校验码的高字节
                bytess1[0] = 0x27;
                bytess1[1] = 0x20;                               // 通信初始化状态
                CRC_Result = CRC16(bytess1, 2);
                bytess1[2] = (byte)(CRC_Result & 0x00FF);        //CRC校验码的低字节
                bytess1[3] = (byte)((CRC_Result >> 8) & 0x00FF); //CRC校验码的高字节
                com.Write(bytess1, 0, 4);
                Thread.Sleep(800);
                com.Write(bytess, 0, 8);
            }
            else if (btn.Name == "sure")
            {
                for (i = 0; i < 60; i++)
                    bytess[i] = 0;
                bytess[0] = 0x27;
                bytess[1] = 0x30;                               // 写命令0
                bytess[2] = 0;
                bytess[3] = 0;
                bytess[4] = 0;
                bytess[5] = 58;
                if (radioButton1.Checked)
                {
                    bytess[6] = 1;
                }
                else
                {
                    bytess[6] = 0;
                }
                bytess[7] =(byte)ages.Value;
                byte[] Temp = new ASCIIEncoding().GetBytes(phones.Text);
                for (i = 0; i < Temp.Length; i++)
                {
                    bytess[8 + i] = Temp[i];
                }
                byte[] Temp1 = Encoding.UTF8.GetBytes(names.Text);
               // string str = Encoding.UTF8.GetString(Temp1);
                for (i = 0; i <Temp1.Length; i++)
                {
                    bytess[19 + i] = Temp1[i];
                }

                byte[] Temp2 = Encoding.UTF8.GetBytes(adds.Text);
                // string str = Encoding.UTF8.GetString(Temp1);
                for (i = 0; i < Temp2.Length; i++)
                {
                    bytess[34 + i] = Temp2[i];
                }

                CRC_Result = CRC16(bytess,64);
                bytess[64] = (byte)(CRC_Result & 0x00FF);        //CRC校验码的低字节
                bytess[65] = (byte)((CRC_Result >> 8) & 0x00FF); //CRC校验码的高字节


                bytess1[0] = 0x27;
                bytess1[1] = 0x20;                               // 通信初始化状态
                CRC_Result = CRC16(bytess1, 2);
                bytess1[2] = (byte)(CRC_Result & 0x00FF);        //CRC校验码的低字节
                bytess1[3] = (byte)((CRC_Result >> 8) & 0x00FF); //CRC校验码的高字节
                com.Write(bytess1, 0, 4);
                Thread.Sleep(800);
                com.Write(bytess,0,66);
            }
        }

        private void mifareclicks(object sender, EventArgs e)
        {
            UInt16 CRC_Result=0,i=0;
            Button btn = sender as Button;
            if (btn.Name == "mifarereset")
            {
                bytess1[0] = 0x27;
                bytess1[1] = 0x80;                               // 通信初始化状态
                CRC_Result = CRC16(bytess1, 2);
                bytess1[2] = (byte)(CRC_Result & 0x00FF);        //CRC校验码的低字节
                bytess1[3] = (byte)((CRC_Result >> 8) & 0x00FF); //CRC校验码的高字节
                com.Write(bytess1, 0, 4);
            }
            else if (btn.Name == "mifareread")
            {
                mifaredata.Text = "";
                bytess[0] = 0x27;
                bytess[1] = 0xa0;                               // 写命令0
                bytess[2] = 0x60;               // 0x60是A密码;0x61是B密码
                if (mifarenum0.Checked)
                    i = 0;
                else if (mifarenum1.Checked)
                    i = 1;
                else if (mifarenum2.Checked)
                    i = 2;
                else if (mifarenum3.Checked)
                    i = 3;
                bytess[3] = (byte)(4 * mifaresanqu.SelectedIndex + i);
                for (i = 0; i < 6; i++)
                {
                    try
                    {
                        bytess[i + 4] = Convert.ToByte(mifarepassa.Text.Substring(i * 2, 2), 16);
                    }
                    catch
                    {
                        MessageBox.Show("密码A输入有误，正确为6字节16进制.");
                        return;
                    }
                }
                CRC_Result = CRC16(bytess,10);
                bytess[10] = (byte)(CRC_Result & 0x00FF);        //CRC校验码的低字节
                bytess[11] = (byte)((CRC_Result >> 8) & 0x00FF); //CRC校验码的高字节
                bytess1[0] = 0x27;
                bytess1[1] = 0x80;                               // 通信初始化状态
                CRC_Result = CRC16(bytess1, 2);
                bytess1[2] = (byte)(CRC_Result & 0x00FF);        //CRC校验码的低字节
                bytess1[3] = (byte)((CRC_Result >> 8) & 0x00FF); //CRC校验码的高字节
                com.Write(bytess1, 0, 4);
                Thread.Sleep(800);
                com.Write(bytess, 0, 12);
            }
            else if (btn.Name == "mifarewrite")
            {
                bytess[0] = 0x27;
                bytess[1] = 0x90;                               // 写命令0
                bytess[2] = 0x60;               // 0x60是A密码;0x61是B密码
                if (mifarenum0.Checked)
                    i = 0;
                else if (mifarenum1.Checked)
                    i = 1;
                else if (mifarenum2.Checked)
                    i = 2;
                else if (mifarenum3.Checked)
                    i = 3;
                bytess[3] = (byte)(4*mifaresanqu.SelectedIndex+i);
                try
                {

                    for (i = 0; i < 6; i++)
                    {
                        bytess[i + 4] = Convert.ToByte(mifarepassa.Text.Substring(i * 2, 2), 16);
                    }
                    for (i = 0; i < 16; i++)
                    {
                        bytess[i + 10] = Convert.ToByte(mifaredata.Text.Substring(i * 2, 2), 16);
                    }
                }
                catch 
                {
                    MessageBox.Show("输入有误，正确为16进制.");
                    return;
                }

                CRC_Result = CRC16(bytess,26);
                bytess[26] = (byte)(CRC_Result & 0x00FF);        //CRC校验码的低字节
                bytess[27] = (byte)((CRC_Result >> 8) & 0x00FF); //CRC校验码的高字节
                bytess1[0] = 0x27;
                bytess1[1] = 0x80;                               // 通信初始化状态
                CRC_Result = CRC16(bytess1, 2);
                bytess1[2] = (byte)(CRC_Result & 0x00FF);        //CRC校验码的低字节
                bytess1[3] = (byte)((CRC_Result >> 8) & 0x00FF); //CRC校验码的高字节
                com.Write(bytess1, 0, 4);
                Thread.Sleep(800);
                com.Write(bytess,0,28);
            }
        }

        private void mifarecheck(object sender, EventArgs e)
        {
            UInt16 i=0;
            string s="0";
            while(mifarepassa.TextLength < 12)
            {
                mifarepassa.AppendText(s);
            }
            while(mifarepassb.TextLength < 12)
            {
                mifarepassb.AppendText(s);
            }
            while(mifaredata.TextLength < 32)
            {
                mifaredata.AppendText(s);
            }
            for (i = 0; i < 6; i++)
            {
                try
                {
                    bytess[i + 4] = Convert.ToByte(mifarepassa.Text.Substring(i * 2, 2), 16);
                }
                catch
                {
                    MessageBox.Show("密码A输入有误，正确为6字节16进制.");
                    mifareread.Enabled = false;
                    mifarewrite.Enabled = false;
                    return;
                }
            }
            for (i = 0; i < 6; i++)
            {
                try
                {
                    bytess[i + 4] = Convert.ToByte(mifarepassb.Text.Substring(i * 2, 2), 16);
                }
                catch
                {
                    MessageBox.Show("密码B输入有误，正确为6字节16进制.");
                    mifareread.Enabled = false;
                    mifarewrite.Enabled = false;
                    return;
                }
            }


            try
            {

                for (i = 0; i < 6; i++)
                {
                    bytess[i + 4] = Convert.ToByte(mifarepassa.Text.Substring(i * 2, 2), 16);
                }
                for (i = 0; i < 16; i++)
                {
                    bytess[i + 10] = Convert.ToByte(mifaredata.Text.Substring(i * 2, 2), 16);
                }
            }
            catch
            {
                MessageBox.Show("数据输入有误，正确为16进制.");
                mifareread.Enabled = false;
                mifarewrite.Enabled = false;
                return;
            }

            mifareread.Enabled = true;
            mifarewrite.Enabled = true;
        }
        public bool bolNum(string temp)
        {
            for (int i = 0; i < temp.Length; i++)
            {
                byte tempByte = Convert.ToByte(temp[i]);
                if ((tempByte < 48) || (tempByte > 57))
                    return false;
            }
            return true;
        }


        public void Closecpu()
        {
            sure.Enabled = false;
            writes.Enabled = false;
            reads.Enabled = false;
            cardinit.Enabled = false;
            add.Enabled = false;
            del.Enabled = false;
            save.Enabled = false;
            write.Enabled = false;
        }
        public void Opencpu()
        {
            sure.Enabled = true;
            writes.Enabled = true;
            reads.Enabled = true;
            cardinit.Enabled = true;
            add.Enabled = true;
            del.Enabled = true;
            save.Enabled = true;
            write.Enabled = true;
        }
        private void cpucheck(object sender, EventArgs e)
        {
            UInt16 i = 0,j;
            string s = "0";
            string ss = phones.Text.Trim();
            if (!bolNum(ss))
            {
                MessageBox.Show("手机号码有误，请重新输入!");
                Closecpu();
                return;
            }
            

            while (phones.TextLength < 11)
            {
                phones.AppendText(s);
            }


            if (values.TextLength % 2 == 1)
                values.AppendText(s);
            j = (UInt16)(values.TextLength / 2);
            for (i = 0; i < j; i++)
            {
                try
                {
                    bytess[i + 4] = Convert.ToByte(values.Text.Substring(i * 2, 2), 16);
                }
                catch
                {
                    MessageBox.Show("数据输入有误，请输入16进制字符串.");
                    Closecpu();
                    return;
                }
            }
            Opencpu();
        }
    }
}
