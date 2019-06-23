#pragma once
#ifndef _PIPE_H
#define _PIPE_H
#include"mm.h"
#include"Memory.h"
#include"Execute.h"
#include"Decode.h"
#include"Write.h"
#include"Fetch.h"
#include"INFO.h"
#include"show_mem.h"
#include"Vcache.h"
#include<stdio.h>
namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Threading;
	using namespace std;
	/// <summary>
	/// MyForm 摘要
	/// </summary>
	string W_now_dstE, W_now_dstM, W_next_dstE, W_next_dstM, M_now_dstE, M_now_dstM, M_next_dstE, M_next_dstM;
	string E_now_dstE, E_now_dstM, E_next_dstE, E_next_dstM, E_now_srcA, E_now_srcB, E_next_srcA, E_next_srcB;
	string D_now_ra, D_now_rb, D_next_ra, D_next_rb;
	ul stack_top=0;
	bool valE=false, valA=false, valM=false,srcA=false,srcB=false,cnd=false;
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:System::Windows::Forms::Timer^ tm = gcnew System::Windows::Forms::Timer();  

	private: System::Windows::Forms::Button^  memory;

	private: System::Windows::Forms::Button^  change;
	public:
		   static int cyclenum;
		   int s, o, z;
		   ul m_addr,pc;
		   ul aluA, aluB, aluE;
		   Fetch* fe = new Fetch();
		   Decode* de = new Decode();
		   Execute* exe = new Execute();
		   Memory* mem = new Memory();
		   Write* wri = new Write();
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::TextBox^  policy;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  byte;
	private: System::Windows::Forms::Label^  line;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  set;
	private: System::Windows::Forms::TextBox^  textBox5;
	public:
		INFO* info = new INFO();
	public:
		MyForm(void)
		{
			tm->Interval =1000;
			//tm->Tick += gcnew EventHandler(this,&MyForm::DoWork);
			tm->Tick += gcnew EventHandler(this, &MyForm::tm_Tick);
			tm->Enabled =false;
			InitializeComponent();
		}
	private: 
		void Initialize() 
	    {
		    W_now_instruc->Text = "AOK";
			W_now_icode->Text = "0";
			//W_instruc.Text = "NOP";
			W_now_valE->Text = "0x00000000";
			W_now_valM->Text = "0x00000000";
			W_now_dstE = "15";
			W_now_dstM= "15";
			W_now_E_reg->Text = "NONE";
			W_now_M_reg->Text = "NONE";
			//M
			M_now_icode->Text = "0";
			// M_instruc.Text = "NOP";
			zf->Text = "15";
			of->Text = "15";
			sf->Text = "15";
			M_now_cnd->Text = "0";
			M_now_valE->Text = "0x00000000";
			M_now_valA->Text = "0x00000000";
			M_now_dstE = "15";
			M_now_dstM = "15";
			M_now_E_reg->Text = "NONE";
			M_now_M_reg->Text = "NONE";
			//E
			E_now_icode->Text = "0";
			E_now_ifun->Text = "0";
			// E_instruc.Text = "NOP";
			E_now_valC->Text = "0x00000000";
			E_now_valA->Text = "0x00000000";
			E_now_valB->Text = "0x00000000";
			E_now_dstE = "15";
			E_now_dstM = "15";
			E_now_srcA = "15";
			E_now_srcB = "15";
			E_now_E_reg->Text = "NONE";
			E_now_M_reg->Text = "NONE";
			E_now_A_reg->Text = "NONE";
			E_now_B_reg->Text = "NONE";
			//D
			D_now_icode->Text = "0";
			//D_instruc.Text = "NOP";
			D_now_ifun->Text = "0";
			D_now_ra= "15";
			D_now_rb= "15";
			D_now_valC->Text = "0x00000000";
			D_now_valP->Text = "0x00000000";
			D_now_A_reg->Text = "NONE";
			D_now_B_reg->Text = "NONE";
			//F
			F_now_predPC->Text = "0x00000000";
			//REGIST
			rax->Text = "0x00000000";
			rcx->Text = "0x00000000";
			rdx->Text = "0x00000000";
			rbx->Text = "0x00000000";
			rsp->Text = "0x00000000";
			rbp->Text = "0x00000000";
			rsi->Text = "0x00000000";
			rdi->Text = "0x00000000";
			r8->Text= "0x00000000";
			r9->Text= "0x00000000";
			r10->Text= "0x00000000";
			r11->Text="0x00000000";
			cycle->Text = "0";

		}
	public:String^ str;
		   char * str_to_ch(String^ s)
		   {
			   return (char*)(void*)Marshal::StringToHGlobalAnsi(s);
		   }
		   String^ ch_to_str(uc *c)
		   {
			   return  Marshal::PtrToStringAnsi((IntPtr)(uc *)c);
		   }
		   string ll_to_str1(ul ull)
		   {
			   ul temp = ull;
			   stringstream s;
			   s <<hex<< temp;
			   return s.str();
		   }
		   string in_to_hex_str(int i)
		   {
			   int num = i;
			   stringstream s;
			   s << hex << num;
			   return s.str();
		   }
		   String^ str1_to_str2(string s)
		   {
			   const char* cw = s.data();
			   return String(cw).ToString();
		   }
		   /*string str2_to_str1(String^ s)
		   {
			   return marshal_as<std::string>(str->ToString());
		   }*/
		   String^ ll_to_str(ul ull)
		   {
			   string temp = ll_to_str1(ull);
			   return str1_to_str2(temp);
		   }
		   String^ in_to_str(int num)
		   {
			   string s = to_string(num);
			   return str1_to_str2(s);
		   }
		   int str_to_int(String^ s)
		   {
			   int num;
			   char* c = str_to_ch(s);
			   return atoi(c);
		   }
		   ul str_to_ll(String^ s)
		   {
			   return atoi64_t((uc*)str_to_ch(s));
		   }
		   ul hex_str_to_ll(string s)
		   {
			   int len = s.size();
			   ul res = 0;
			   for (int i = 2; i <len; i++)
			   {
				   res= res * 16 + transform(s[i]);
			   }
			   return res;
		   }
	public:
		System::Void Fe()
		{
			if (D_now_instruc->Text == "HALT")//如果Decode阶段的代码为结束，则F阶段无需再读入指令
			{
				fe->f_instruc = str_to_ch(D_now_instruc->Text);
				fe->NOP();
			}
			else
			{
				uc *val = new(uc)(1 * sizeof(uc));
				if (read_mem(pc, val, 1) < 0)
				{
					fe->f_instruc = "ADR";
					fe->NOP();
				}
				else
				{
					unsigned int temp1 = (*val) & 0xf0, temp2 = (*val) & 0x0f;
					temp1 = temp1 >> 4;
					if (temp1 >= 0 && temp1 <= 0xc)
					{
						if ((temp1 == 0x2 || temp1 == 0x7) && temp2 >= 0x0 && temp2 <= 0x6 || temp1 == 0x6 && temp2 >= 0x0 && temp2 <= 0x3)
						{
							fe->f_icode = to_string(temp1);
							fe->f_ifun = to_string(temp2);
							pc++;
						}
						else if ((!(temp2 == 0x2 || temp2 == 0x7 || temp2 == 0x6)) && temp2 == 0x0)//!和&&
						{
							fe->f_icode = to_string(temp1);
							fe->f_ifun = to_string(temp2);
							pc++;
						}
						else
						{
							tm->Enabled = false;
							MessageBox::Show("机器码错误!", "提示对话框", MessageBoxButtons::OK);

						}
					}
					//存储指令类型
					fe->f_instruc = info->instr[atoi(fe->f_icode.c_str())];//others
					//f_rA,f_rB
					if (fe->f_icode == "0" || fe->f_icode == "1" || fe->f_icode == "7" || fe->f_icode == "8" || fe->f_icode == "9")
					{
						fe->f_ra = "15";
						fe->f_rb = "15";
					}
					else
					{
						uc* val = new(uc)(1 * sizeof(uc));
						read_mem(pc, val, 1);
						unsigned int temp1 = (*val) & 0xf0, temp2 = (*val) & 0x0f;
						temp1 = temp1 >> 4;
						fe->f_ra = to_string(temp1);
						fe->f_rb = to_string(temp2);
						pc++;
					}
					fe->f_A_reg = info->regist[atoi(fe->f_ra.c_str())];//用寄存器的名称表示出来
					fe->f_B_reg = info->regist[atoi(fe->f_rb.c_str())];
					//f_valC
					if (atoi(fe->f_icode.c_str()) > 0x2 && atoi(fe->f_icode.c_str()) < 0x9 && fe->f_icode != "6" || fe->f_icode == "12")
					{
						ul* temp = new(ul)(8 * sizeof(uc));
						read8Bytes(pc, temp);
						fe->f_valC = "0x" + ll_to_str1(*temp);
						pc += 8;
					}
					else fe->f_valC = "0x00000000";
					//f_valP
					fe->f_valP = "0x" + ll_to_str1(pc);
					//F_stall
					while (!(srcA&&srcB));
					if ((E_now_icode->Text == "5" || E_now_icode->Text == "11") && (E_now_dstM == de->d_srcA || E_now_dstM == de->d_srcB) || (D_now_icode->Text == "9"
						|| E_now_icode->Text == "9" || M_now_icode->Text == "9"))
						fe->F_stall = true;
					else fe->F_stall = false;
					//f_predPC
					//d_predPC：预测地址字符串；
					if (fe->f_icode == "7" || fe->f_icode == "8")
						de->d_predPC = fe->f_valC;//jxx,call
					else
						de->d_predPC = fe->f_valP;
					if (M_now_icode->Text == "7" && M_now_cnd->Text == "0") fe->f_predPC = str_to_ch(M_now_valA->Text);
					else
					{
						if (W_now_icode->Text == "9") fe->f_predPC = str_to_ch(W_now_valM->Text);
						else fe->f_predPC = de->d_predPC;
					}
					while (!(cnd&&valA&&valM));//在全部更新前一直循环
					if (E_now_icode->Text == "7" && exe->e_cnd == "0")
						fe->f_predPC = exe->e_valA;
					else
					{
						if (M_now_icode->Text == "9") fe->f_predPC = mem->m_valM;
						else fe->f_predPC = de->d_predPC;//16进制
					}
				}
			}
			while (!(cnd&&srcA&&srcB));
			//D_bubble
			if ((E_now_icode->Text == "7" && exe->e_cnd == "0") || !((E_now_icode->Text == "5" || E_now_icode->Text == "11") && (E_now_dstM == de->d_srcA
				|| E_now_dstM == de->d_srcB)) && (D_now_icode->Text == "9" || E_now_icode->Text == "9" || M_now_icode->Text == "9"))
			{
				de->D_bubble = true;
				fe->f_instruc = "NOP";
				fe->f_icode = "0";
				fe->f_ifun = "0";
				fe->f_ra = "15";
				fe->f_rb = "15";
				fe->f_valC = "0x00000000";
				fe->f_valP = "0x00000000";
				fe->f_A_reg = "NONE";
				fe->f_B_reg = "NONE";
			}
			else
				de->D_bubble = false;
		}

		System::Void De()
		{
			if (D_now_instruc->Text == "NOP" || D_now_instruc->Text == "HALT")//如果没有指令内容
			{
				de->d_icode = str_to_ch(D_now_icode->Text);
				de->d_ifun = "0";
				de->d_instruc = str_to_ch(D_now_instruc->Text);
				de->NOP();
				srcA = srcB = true;
			}
			else
			{
				de->d_icode = str_to_ch(D_now_icode->Text);
				de->d_ifun = str_to_ch(D_now_ifun->Text);
				de->d_instruc = str_to_ch(D_now_instruc->Text);
				de->d_valC = str_to_ch(D_now_valC->Text);//16进制
				//d_srcA

				if (D_now_icode->Text == "2" || D_now_icode->Text == "4" || D_now_icode->Text == "6" || D_now_icode->Text == "10")
					de->d_srcA = D_now_ra;//rrmovl,rmmovl,opl,pushl
				else
				{
					if (D_now_icode->Text == "9" || D_now_icode->Text == "11")
						de->d_srcA = "4"; //ret,pop,rmmovl
					else de->d_srcA = "15";
				}
				srcA = true;
				de->d_A_reg = info->regist[atoi(de->d_srcA.c_str())];
				
				//d_srcB
				if (D_now_icode->Text == "4" || D_now_icode->Text == "5" || D_now_icode->Text == "6" || D_now_icode->Text == "12")
					de->d_srcB = D_now_rb;//rmmovl,mrmobl,opl
				else
				{
					if (D_now_icode->Text == "8" || D_now_icode->Text == "9" || D_now_icode->Text == "10" || D_now_icode->Text == "11")
						de->d_srcB = "4";//call,ret,pop,push
					else de->d_srcB = "15";
				}
				srcB = true;
				de->d_B_reg = info->regist[atoi(de->d_srcB.c_str())];//获取寄存器名称


				//d_dstE
				if (D_now_icode->Text == "2" || D_now_icode->Text == "3" || D_now_icode->Text == "6" || D_now_icode->Text == "12")
					de->d_dstE = D_now_rb;//rrmovl,irmovl,opl
				else
				{
					if (D_now_icode->Text == "8" || D_now_icode->Text == "9" || D_now_icode->Text == "10" || D_now_icode->Text == "11")
						de->d_dstE = "4";//call,ret,push,pop为esp
					else de->d_dstE = "15";
				}
				de->d_E_reg = info->regist[atoi(de->d_dstE.c_str())];//获取寄存器名称

				//d_dstM
				if (D_now_icode->Text == "5" || D_now_icode->Text == "11")
					de->d_dstM = D_now_ra;//mrmovl,opl
				else de->d_dstM = "15";
				de->d_M_reg = info->regist[atoi(de->d_dstM.c_str())];//获取寄存器名称
				if ((E_now_icode->Text == "5" || E_now_icode->Text == "11") && (E_now_dstM == de->d_srcA || E_now_dstM == de->d_srcB))
					de->D_stall = true;
				else de->D_stall = false;
				while (!(cnd&&valE&&valM));
				if (D_now_icode->Text == "7" || D_now_icode->Text == "8") de->d_valA = str_to_ch(D_now_valP->Text);
				else
				{
					if (de->d_srcA == "15") de->d_valA = "0x00000000";
					else
					{
						if ((de->d_srcA == E_now_dstE)&&!(E_now_icode->Text =="2"&&!cnd))
						{
								de->d_valA = exe->e_valE;
						}
						else if (de->d_srcA == M_now_dstM) de->d_valA = mem->m_valM;
						else if (de->d_srcA == M_now_dstE) de->d_valA = str_to_ch(M_now_valE->Text);
						else if (de->d_srcA == W_now_dstM) de->d_valA = str_to_ch(W_now_valM->Text);
						else if (de->d_srcA == W_now_dstE) de->d_valA = str_to_ch(W_now_valE->Text);
						else de->d_valA = info->regval[atoi(de->d_srcA.c_str())];
					}
				}
				if (de->d_srcB == "15")de->d_valB = "0x00000000";
				else//forwarding
				{
					if ((de->d_srcB == E_now_dstE) && !(E_now_icode->Text == "2" && !cnd))
					{
						de->d_valB = exe->e_valE;
					}
					else if (de->d_srcB == M_now_dstM) de->d_valB = mem->m_valM;
					else if (de->d_srcB == M_now_dstE) de->d_valB = str_to_ch(M_now_valE->Text);
					else if (de->d_srcB == W_now_dstM) de->d_valB = str_to_ch(W_now_valM->Text);
					else if (de->d_srcB == W_now_dstE) de->d_valB = str_to_ch(W_now_valE->Text);
					else  de->d_valB = info->regval[atoi(de->d_srcB.c_str())];
				}
			}
			while (!(cnd&&srcA&&srcB));
			//E_bubble
			if ((E_now_icode->Text == "7" && exe->e_cnd == "0") || ((E_now_icode->Text == "5" || E_now_icode->Text == "11") && (E_now_dstM == de->d_srcA
				|| E_now_dstM == de->d_srcB)))
			{
				exe->E_bubble = true;
				de->d_icode = "0";
				de->d_ifun = "0";
				de->d_instruc = "NOP";
				de->d_valC = "0x00000000";
				de->d_valA = "0x00000000";
				de->d_valB = "0x00000000";
				de->d_dstE = "15";
				de->d_dstM = "15";
				de->d_srcA = "15";
				de->d_srcB = "15";
				de->d_E_reg = "NONE";
				de->d_M_reg = "NONE";
				de->d_A_reg = "NONE";
				de->d_B_reg = "NONE";
			}
			else
				exe->E_bubble = false;
		}

		System::Void Ex()
		{
			if (E_now_instruc->Text == "NOP" || E_now_instruc->Text == "HALT")//没有代码的情况
			{
				exe->e_icode = str_to_ch(E_now_icode->Text);
				exe->e_instruc = str_to_ch(E_now_instruc->Text);
				exe->NOP();
				cnd = valE = valA = true;
			}
			else
			{
				exe->e_icode = str_to_ch(E_now_icode->Text);
				exe->e_instruc = str_to_ch(E_now_instruc->Text);
				exe->e_dstE = E_now_dstE;
				exe->e_dstM = E_now_dstM;
				exe->e_dstE = E_now_dstE;
				exe->e_E_reg = info->regist[atoi(exe->e_dstE.c_str())];
				exe->e_M_reg = info->regist[atoi(exe->e_dstM.c_str())];
				exe->e_valA = str_to_ch(E_now_valA->Text);
				valA = true;
				//计算aluA及aluB
				if (E_now_icode->Text != "7")
				{
					//aluA
					if (E_now_icode->Text == "2" || E_now_icode->Text == "6")
						aluA = hex_str_to_ll(str_to_ch(E_now_valA->Text));
					else if (E_now_icode->Text == "3" || E_now_icode->Text == "4" || E_now_icode->Text == "5" || E_now_icode->Text == "12")
						aluA = hex_str_to_ll(str_to_ch(E_now_valC->Text));
					else if (E_now_icode->Text == "8" || E_now_icode->Text == "10")
						aluA = -8;
					else aluA = 8;
					//aluB
					if (E_now_icode->Text == "2" || E_now_icode->Text == "3")
						aluB = 0;
					else
						aluB = hex_str_to_ll(str_to_ch(E_now_valB->Text));
				}

				//根据指令的内容计算valE
				if (E_now_icode->Text == "6" || E_now_icode->Text == "12")//opl
				{
					if (E_now_ifun->Text == "0") aluE = aluB + aluA;//+
					else if (E_now_ifun->Text == "1") aluE = aluB - aluA;//-
					else if (E_now_ifun->Text == "2") aluE = aluB & aluA;//&
					else aluE = aluB ^ aluA;//^
					//set CC
					if (aluE == 0) exe->zf = "1";
					else exe->zf = "0";//yield 0
					if (aluE < 0)exe->sf = "1";
					else exe->sf = "0";//yield negitive
					exe->of = "0";
					if (E_now_ifun->Text == "0")
						if ((aluA < 0 == aluB < 0) && (aluE < 0 != aluA < 0)) exe->of = "1";//加法溢出
						else exe->of = "0";
					if (E_now_ifun->Text == "1")
						if (((-aluA) < 0 == aluB < 0) && (aluE < 0 != (-aluA) < 0)) exe->of = "1";//减法溢出
						else exe->of = "0";
				}
				else aluE = aluB + aluA;//其余指令都是采用加法
				exe->e_valE = ll_to_str1(aluE);
				for (int i = exe->e_valE.size(); i < 8; i++)
					exe->e_valE = "0" + exe->e_valE;//补齐8位
				exe->e_valE = "0x" + exe->e_valE;
				valE = true;
				//e_Bch
				if (E_now_icode->Text == "7" || E_now_icode->Text == "2")//jxx的情况判断bch
				{
					if (sf->Text == "1") s = 1;
					else s = 0;
					if (of->Text == "1") o = 1;
					else o = 0;
					if (zf->Text == "1") z = 1;
					else z = 0;
					if (E_now_ifun->Text == "0" || (E_now_ifun->Text == "1" && ((s ^ o) | z)) || (E_now_ifun->Text == "2" && (s ^ o))
						|| (E_now_ifun->Text == "3" && z) || (E_now_ifun->Text == "4" && !z) || (E_now_ifun->Text == "5" && !(s ^ o))
						|| (E_now_ifun->Text == "6" && (!(s ^ o) & !z)))
						exe->e_cnd = "1";
					else exe->e_cnd = "0";
					if (E_now_icode->Text == "2" && E_now_ifun->Text != "0")
					{
						if (exe->e_cnd == "0")//不走
						{
							exe->e_valE = info->regval[atoi(exe->e_dstE.c_str())];
							exe->e_E_reg = info->regist[atoi(exe->e_dstE.c_str())];
							/*exe->e_icode = '1';
							exe->e_instruc = "NOP";
							exe->e_valE = "0x00000000";
							exe->e_valA = "0x00000000";
							exe->e_dstE = "15";
							exe->e_dstM = "15";
							exe->e_E_reg = "NONE";
							exe->e_M_reg = "NONE";*/
						}
					}
				}
				cnd = true;
			}
		}
		System::Void Me()
		{
			if (M_now_instruc->Text == "NOP" || M_now_instruc->Text == "HALT")//指令不存在的情况
			{
				mem->m_icode = str_to_ch(M_now_icode->Text);
				mem->m_instruc = str_to_ch(M_now_instruc->Text);
				mem->NOP();
				valM = true;
			}
			else
			{
				mem->m_icode = str_to_ch(M_now_icode->Text);
				mem->m_instruc = str_to_ch(M_now_instruc->Text);
				mem->m_dstE = M_now_dstE;
				mem->m_dstM = M_now_dstM;
				mem->m_E_reg = info->regist[atoi(mem->m_dstE.c_str())];
				mem->m_M_reg = info->regist[atoi(mem->m_dstM.c_str())];
				mem->m_valE = str_to_ch(M_now_valE->Text);
				//m_valM
				if (M_now_icode->Text == "4" || M_now_icode->Text == "10" || M_now_icode->Text == "8" || M_now_icode->Text == "5")
					m_addr = hex_str_to_ll(str_to_ch(M_now_valE->Text));
				else if (M_now_icode->Text == "9" || M_now_icode->Text == "11")
					m_addr = hex_str_to_ll(str_to_ch(M_now_valA->Text));
				if (M_now_icode->Text == "5" || M_now_icode->Text == "11" || M_now_icode->Text == "9")//Read from Memory
				{
					ul temp = 0x8;
					int r = read8Bytes(m_addr, &temp);
					if (r < 0)
					{
						tm->Enabled = false;
						MessageBox::Show("读取内存错误!", "提示对话框", MessageBoxButtons::OK);
					}
					mem->m_valM = "0x" + ll_to_str1(temp);
				}
				else if (M_now_icode->Text == "4" || M_now_icode->Text == "10" || M_now_icode->Text == "8")//Write to Memory
				{
					ul temp = hex_str_to_ll(str_to_ch(M_now_valA->Text));
					int r = write_mem(m_addr, temp, 8);
					if (r < 0)
					{
						tm->Enabled = false;
						MessageBox::Show("写入内存错误!", "提示对话框", MessageBoxButtons::OK);
					}
				}
				valM = true;
			}
		}

		System::Void Wr()
		{
			if (W_now_icode->Text == "6" || W_now_icode->Text == "2" || W_now_icode->Text == "3" || W_now_icode->Text == "10" || W_now_icode->Text == "11"
				|| W_now_icode->Text == "8" || W_now_icode->Text == "9" || W_now_icode->Text == "12")
				wri->w_regval[atoi(W_now_dstE.c_str())] = str_to_ch(W_now_valE->Text);
			if (W_now_icode->Text == "5" || W_now_icode->Text == "11" || W_now_icode->Text == "3")
				wri->w_regval[atoi(W_now_dstM.c_str())] = str_to_ch(W_now_valM->Text);
		}
		public:
			Thread ^f;
			Thread^ d;
			Thread^ e;
			Thread^ m;
			Thread^ w;
		System::Void DoWork()
		{
			pc = hex_str_to_ll(str_to_ch(F_now_predPC->Text));
			f = gcnew Thread(gcnew ThreadStart(this, &MyForm::Fe));
			d = gcnew Thread(gcnew ThreadStart(this, &MyForm::De));
			e = gcnew Thread(gcnew ThreadStart(this, &MyForm::Ex));
			m = gcnew Thread(gcnew ThreadStart(this, &MyForm::Me));
			w = gcnew Thread(gcnew ThreadStart(this, &MyForm::Wr));
			f->Start(); d->Start(); e->Start(); m->Start(); w->Start();
			f->Join(); d->Join(); e->Join(); m->Join(); w->Join();
			//更新界面上的next系列
			W_next_icode->Text = str1_to_str2(mem->m_icode);
			W_next_instruc->Text = str1_to_str2(mem->m_instruc);
			W_next_valE->Text = str1_to_str2(mem->m_valE);
			W_next_valM->Text = str1_to_str2(mem->m_valM);
			W_next_dstE = mem->m_dstE;
			W_next_dstM = mem->m_dstM;
			W_next_E_reg->Text = str1_to_str2(mem->m_E_reg);
			W_next_M_reg->Text = str1_to_str2(mem->m_M_reg);

			//M
			M_next_icode->Text = str1_to_str2(exe->e_icode);
			M_next_instruc->Text = str1_to_str2(exe->e_instruc);
			M_next_cnd->Text = str1_to_str2(exe->e_cnd);
			M_next_valE->Text = str1_to_str2(exe->e_valE);
			M_next_valA->Text = str1_to_str2(exe->e_valA);
			M_next_dstE = exe->e_dstE;
			M_next_dstM = exe->e_dstM;
			M_next_E_reg->Text = str1_to_str2(exe->e_E_reg);
			M_next_M_reg->Text = str1_to_str2(exe->e_M_reg);
			//E
			E_next_icode->Text = str1_to_str2(de->d_icode);
			E_next_ifun->Text = str1_to_str2(de->d_ifun);
			E_next_instruc->Text = str1_to_str2(de->d_instruc);
			E_next_valC->Text = str1_to_str2(de->d_valC);
			E_next_valA->Text = str1_to_str2(de->d_valA);
			E_next_valB->Text = str1_to_str2(de->d_valB);
			E_next_dstE = de->d_dstE;
			E_next_dstM = de->d_dstM;
			E_next_srcA = de->d_srcA;
			E_next_srcB = de->d_srcB;
			E_next_E_reg->Text = str1_to_str2(de->d_E_reg);
			E_next_M_reg->Text = str1_to_str2(de->d_M_reg);
			E_next_A_reg->Text = str1_to_str2(de->d_A_reg);
			E_next_B_reg->Text = str1_to_str2(de->d_B_reg);
			if (!de->D_stall)
			{
				D_next_icode->Text = str1_to_str2(fe->f_icode);
				D_next_instruc->Text = str1_to_str2(fe->f_instruc);
				D_next_ifun->Text = str1_to_str2(fe->f_ifun);
				D_next_ra = fe->f_ra;
				D_next_rb = fe->f_rb;
				D_next_valC->Text = str1_to_str2(fe->f_valC);
				D_next_valP->Text = str1_to_str2(fe->f_valP);
				D_next_A_reg->Text = str1_to_str2(fe->f_A_reg);
				D_next_B_reg->Text = str1_to_str2(fe->f_B_reg);
			}
			//F
			if (!(fe->F_stall) || W_now_icode->Text == "9")
				F_next_predPC->Text = str1_to_str2(fe->f_predPC);
			stack_top= hex_str_to_ll(info->regval[4]);
			cnd = valA = valM = srcA = srcB = valE = false;
		}
		System::Void Once()
		{
			cyclenum++;
			cycle->Text = in_to_str(cyclenum);
			//先更新now的寄存器
			W_now_icode->Text = str1_to_str2(mem->m_icode);
			W_now_instruc->Text = str1_to_str2(mem->m_instruc);
			W_now_valE->Text = str1_to_str2(mem->m_valE);
			W_now_valM->Text = str1_to_str2(mem->m_valM);
			W_now_dstE = mem->m_dstE;
			W_now_dstM = mem->m_dstM;
			W_now_E_reg->Text = str1_to_str2(mem->m_E_reg);
			W_now_M_reg->Text = str1_to_str2(mem->m_M_reg);

			//M
			M_now_icode->Text = str1_to_str2(exe->e_icode);
			M_now_instruc->Text = str1_to_str2(exe->e_instruc);
			M_now_cnd->Text = str1_to_str2(exe->e_cnd);
			zf->Text = str1_to_str2(exe->zf);
			of->Text = str1_to_str2(exe->of);
			sf->Text = str1_to_str2(exe->sf);
			M_now_valE->Text = str1_to_str2(exe->e_valE);
			M_now_valA->Text = str1_to_str2(exe->e_valA);
			M_now_dstE = exe->e_dstE;
			M_now_dstM = exe->e_dstM;
			M_now_E_reg->Text = str1_to_str2(exe->e_E_reg);
			M_now_M_reg->Text = str1_to_str2(exe->e_M_reg);
			//E
			E_now_icode->Text = str1_to_str2(de->d_icode);
			E_now_ifun->Text = str1_to_str2(de->d_ifun);
			E_now_instruc->Text = str1_to_str2(de->d_instruc);
			E_now_valC->Text = str1_to_str2(de->d_valC);
			E_now_valA->Text = str1_to_str2(de->d_valA);
			E_now_valB->Text = str1_to_str2(de->d_valB);
			E_now_dstE = de->d_dstE;
			E_now_dstM = de->d_dstM;
			E_now_srcA = de->d_srcA;
			E_now_srcB = de->d_srcB;
			E_now_E_reg->Text = str1_to_str2(de->d_E_reg);
			E_now_M_reg->Text = str1_to_str2(de->d_M_reg);
			E_now_A_reg->Text = str1_to_str2(de->d_A_reg);
			E_now_B_reg->Text = str1_to_str2(de->d_B_reg);
			if (!de->D_stall)
			{
				D_now_icode->Text = str1_to_str2(fe->f_icode);
				D_now_instruc->Text = str1_to_str2(fe->f_instruc);
				D_now_ifun->Text = str1_to_str2(fe->f_ifun);
				D_now_ra = fe->f_ra;
				D_now_rb = fe->f_rb;
				D_now_valC->Text = str1_to_str2(fe->f_valC);
				D_now_valP->Text = str1_to_str2(fe->f_valP);
				D_now_A_reg->Text = str1_to_str2(fe->f_A_reg);
				D_now_B_reg->Text = str1_to_str2(fe->f_B_reg);
			}
			//F
			if (!fe->F_stall || W_now_icode->Text == "9")
				F_now_predPC->Text = str1_to_str2(fe->f_predPC);

			rax->Text = str1_to_str2(wri->w_regval[0]);
			rcx->Text = str1_to_str2(wri->w_regval[1]);
			rdx->Text = str1_to_str2(wri->w_regval[2]);
			rbx->Text = str1_to_str2(wri->w_regval[3]);
			rsp->Text = str1_to_str2(wri->w_regval[4]);
			rbp->Text = str1_to_str2(wri->w_regval[5]);
			rsi->Text = str1_to_str2(wri->w_regval[6]);
			rdi->Text = str1_to_str2(wri->w_regval[7]);
			r8->Text = str1_to_str2(wri->w_regval[8]);
			r9->Text = str1_to_str2(wri->w_regval[9]);
			r10->Text = str1_to_str2(wri->w_regval[10]);
			r11->Text = str1_to_str2(wri->w_regval[11]);
			//更新寄存器的值
			info->regval[0] = wri->w_regval[0];
			info->regval[1] = wri->w_regval[1];
			info->regval[2] = wri->w_regval[2];
			info->regval[3] = wri->w_regval[3];
			info->regval[4] = wri->w_regval[4];
			info->regval[5] = wri->w_regval[5];
			info->regval[6] = wri->w_regval[6];
			info->regval[7] = wri->w_regval[7];
			info->regval[8] = wri->w_regval[8];
			info->regval[9] = wri->w_regval[9];
			info->regval[10] = wri->w_regval[10];
			info->regval[11] = wri->w_regval[11];
			if (W_now_instruc->Text == "HALT") //执行完毕
			{
				tm->Enabled = false;
				MessageBox::Show("运行完毕!", "提示对话框", MessageBoxButtons::OK);

			}
			else
				DoWork();
		}
	private:
		Void tm_Tick(System::Object^  sender, System::EventArgs^  e)
		{
			Once();
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  sf;
	private: System::Windows::Forms::TextBox^  cycle;
	private: System::Windows::Forms::TextBox^  of;
	private: System::Windows::Forms::TextBox^  zf;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::Button^  resume;
	private: System::Windows::Forms::Button^  start;
	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  pause;
	private: System::Windows::Forms::TextBox^  rax;
	private: System::Windows::Forms::TextBox^  rcx;
	private: System::Windows::Forms::TextBox^  rdx;
	private: System::Windows::Forms::TextBox^  rbx;
	private: System::Windows::Forms::TextBox^  rsp;
	private: System::Windows::Forms::TextBox^  rbp;
	private: System::Windows::Forms::TextBox^  rsi;
	private: System::Windows::Forms::TextBox^  rdi;
	private: System::Windows::Forms::TextBox^  r8;
	private: System::Windows::Forms::TextBox^  r9;
	private: System::Windows::Forms::TextBox^  r10;
	private: System::Windows::Forms::TextBox^  r11;
private: System::Windows::Forms::TextBox^  W_now_instruc;

	private: System::Windows::Forms::TextBox^  W_now_icode;
	private: System::Windows::Forms::TextBox^  M_now_icode;
	private: System::Windows::Forms::TextBox^  W_now_valM;
private: System::Windows::Forms::TextBox^  W_now_E_reg;
private: System::Windows::Forms::TextBox^  W_now_M_reg;
private: System::Windows::Forms::TextBox^  M_now_instruc;



	private: System::Windows::Forms::TextBox^  W_now_valE;
	private: System::Windows::Forms::TextBox^  M_now_cnd;

	private: System::Windows::Forms::TextBox^  M_now_valE;
	private: System::Windows::Forms::TextBox^  M_now_valA;
private: System::Windows::Forms::TextBox^  M_now_E_reg;
private: System::Windows::Forms::TextBox^  M_now_M_reg;
private: System::Windows::Forms::TextBox^  W_next_instruc;




	private: System::Windows::Forms::TextBox^  W_next_icode;
	private: System::Windows::Forms::TextBox^  W_next_valE;
	private: System::Windows::Forms::TextBox^  W_next_valM;
private: System::Windows::Forms::TextBox^  W_next_E_reg;
private: System::Windows::Forms::TextBox^  W_next_M_reg;
private: System::Windows::Forms::TextBox^  M_next_instruc;



	private: System::Windows::Forms::TextBox^  M_next_icode;

	private: System::Windows::Forms::TextBox^  M_next_cnd;

	private: System::Windows::Forms::TextBox^  M_next_valE;

	private: System::Windows::Forms::TextBox^  M_next_valA;
private: System::Windows::Forms::TextBox^  M_next_E_reg;
private: System::Windows::Forms::TextBox^  M_next_M_reg;
private: System::Windows::Forms::TextBox^  E_now_instruc;
private: System::Windows::Forms::TextBox^  E_next_instruc;






	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::TextBox^  filename;
private: System::Windows::Forms::TextBox^  E_now_icode;
private: System::Windows::Forms::TextBox^  E_next_icode;
private: System::Windows::Forms::TextBox^  E_now_ifun;
private: System::Windows::Forms::TextBox^  E_next_ifun;
private: System::Windows::Forms::TextBox^  E_now_valA;
private: System::Windows::Forms::TextBox^  E_next_valC;
private: System::Windows::Forms::TextBox^  E_now_valB;


private: System::Windows::Forms::TextBox^  E_next_valA;
private: System::Windows::Forms::TextBox^  E_now_E_reg;



private: System::Windows::Forms::TextBox^  E_next_valB;
private: System::Windows::Forms::TextBox^  E_now_M_reg;
private: System::Windows::Forms::TextBox^  E_next_M_reg;
private: System::Windows::Forms::TextBox^  E_now_A_reg;
private: System::Windows::Forms::TextBox^  E_now_B_reg;




private: System::Windows::Forms::TextBox^  E_now_valC;
private: System::Windows::Forms::TextBox^  E_next_A_reg;
private: System::Windows::Forms::TextBox^  E_next_B_reg;




private: System::Windows::Forms::TextBox^  E_next_E_reg;


private: System::Windows::Forms::TextBox^  D_now_icode;
private: System::Windows::Forms::TextBox^  D_now_instruc;


private: System::Windows::Forms::TextBox^  D_now_B_reg;

private: System::Windows::Forms::TextBox^  D_now_A_reg;




private: System::Windows::Forms::TextBox^  D_now_ifun;
private: System::Windows::Forms::TextBox^  D_now_valC;
private: System::Windows::Forms::TextBox^  D_now_valP;
private: System::Windows::Forms::TextBox^  D_next_instruc;

private: System::Windows::Forms::TextBox^  D_next_icode;
private: System::Windows::Forms::TextBox^  D_next_ifun;
private: System::Windows::Forms::TextBox^  D_next_A_reg;
private: System::Windows::Forms::TextBox^  D_next_B_reg;


private: System::Windows::Forms::TextBox^  D_next_valC;
private: System::Windows::Forms::TextBox^  D_next_valP;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::TextBox^  F_now_predPC;
private: System::Windows::Forms::TextBox^  F_next_predPC;
	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pause = (gcnew System::Windows::Forms::Button());
			this->rax = (gcnew System::Windows::Forms::TextBox());
			this->rcx = (gcnew System::Windows::Forms::TextBox());
			this->rdx = (gcnew System::Windows::Forms::TextBox());
			this->rbx = (gcnew System::Windows::Forms::TextBox());
			this->rsp = (gcnew System::Windows::Forms::TextBox());
			this->rbp = (gcnew System::Windows::Forms::TextBox());
			this->rsi = (gcnew System::Windows::Forms::TextBox());
			this->rdi = (gcnew System::Windows::Forms::TextBox());
			this->r8 = (gcnew System::Windows::Forms::TextBox());
			this->r9 = (gcnew System::Windows::Forms::TextBox());
			this->r10 = (gcnew System::Windows::Forms::TextBox());
			this->r11 = (gcnew System::Windows::Forms::TextBox());
			this->W_now_instruc = (gcnew System::Windows::Forms::TextBox());
			this->W_now_icode = (gcnew System::Windows::Forms::TextBox());
			this->M_now_icode = (gcnew System::Windows::Forms::TextBox());
			this->W_now_valM = (gcnew System::Windows::Forms::TextBox());
			this->W_now_E_reg = (gcnew System::Windows::Forms::TextBox());
			this->W_now_M_reg = (gcnew System::Windows::Forms::TextBox());
			this->M_now_instruc = (gcnew System::Windows::Forms::TextBox());
			this->W_now_valE = (gcnew System::Windows::Forms::TextBox());
			this->M_now_cnd = (gcnew System::Windows::Forms::TextBox());
			this->M_now_valE = (gcnew System::Windows::Forms::TextBox());
			this->M_now_valA = (gcnew System::Windows::Forms::TextBox());
			this->M_now_E_reg = (gcnew System::Windows::Forms::TextBox());
			this->M_now_M_reg = (gcnew System::Windows::Forms::TextBox());
			this->W_next_instruc = (gcnew System::Windows::Forms::TextBox());
			this->W_next_icode = (gcnew System::Windows::Forms::TextBox());
			this->W_next_valE = (gcnew System::Windows::Forms::TextBox());
			this->W_next_valM = (gcnew System::Windows::Forms::TextBox());
			this->W_next_E_reg = (gcnew System::Windows::Forms::TextBox());
			this->W_next_M_reg = (gcnew System::Windows::Forms::TextBox());
			this->M_next_instruc = (gcnew System::Windows::Forms::TextBox());
			this->M_next_icode = (gcnew System::Windows::Forms::TextBox());
			this->M_next_cnd = (gcnew System::Windows::Forms::TextBox());
			this->M_next_valE = (gcnew System::Windows::Forms::TextBox());
			this->M_next_valA = (gcnew System::Windows::Forms::TextBox());
			this->M_next_E_reg = (gcnew System::Windows::Forms::TextBox());
			this->M_next_M_reg = (gcnew System::Windows::Forms::TextBox());
			this->E_now_instruc = (gcnew System::Windows::Forms::TextBox());
			this->E_next_instruc = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->filename = (gcnew System::Windows::Forms::TextBox());
			this->E_now_icode = (gcnew System::Windows::Forms::TextBox());
			this->E_next_icode = (gcnew System::Windows::Forms::TextBox());
			this->E_now_ifun = (gcnew System::Windows::Forms::TextBox());
			this->E_next_ifun = (gcnew System::Windows::Forms::TextBox());
			this->E_now_valA = (gcnew System::Windows::Forms::TextBox());
			this->E_next_valC = (gcnew System::Windows::Forms::TextBox());
			this->E_now_valB = (gcnew System::Windows::Forms::TextBox());
			this->E_next_valA = (gcnew System::Windows::Forms::TextBox());
			this->E_now_E_reg = (gcnew System::Windows::Forms::TextBox());
			this->E_next_valB = (gcnew System::Windows::Forms::TextBox());
			this->E_now_M_reg = (gcnew System::Windows::Forms::TextBox());
			this->E_next_M_reg = (gcnew System::Windows::Forms::TextBox());
			this->E_now_A_reg = (gcnew System::Windows::Forms::TextBox());
			this->E_now_B_reg = (gcnew System::Windows::Forms::TextBox());
			this->E_now_valC = (gcnew System::Windows::Forms::TextBox());
			this->E_next_A_reg = (gcnew System::Windows::Forms::TextBox());
			this->E_next_B_reg = (gcnew System::Windows::Forms::TextBox());
			this->E_next_E_reg = (gcnew System::Windows::Forms::TextBox());
			this->D_now_icode = (gcnew System::Windows::Forms::TextBox());
			this->D_now_instruc = (gcnew System::Windows::Forms::TextBox());
			this->D_now_B_reg = (gcnew System::Windows::Forms::TextBox());
			this->D_now_A_reg = (gcnew System::Windows::Forms::TextBox());
			this->D_now_ifun = (gcnew System::Windows::Forms::TextBox());
			this->D_now_valC = (gcnew System::Windows::Forms::TextBox());
			this->D_now_valP = (gcnew System::Windows::Forms::TextBox());
			this->D_next_instruc = (gcnew System::Windows::Forms::TextBox());
			this->D_next_icode = (gcnew System::Windows::Forms::TextBox());
			this->D_next_ifun = (gcnew System::Windows::Forms::TextBox());
			this->D_next_A_reg = (gcnew System::Windows::Forms::TextBox());
			this->D_next_B_reg = (gcnew System::Windows::Forms::TextBox());
			this->D_next_valC = (gcnew System::Windows::Forms::TextBox());
			this->D_next_valP = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->F_now_predPC = (gcnew System::Windows::Forms::TextBox());
			this->F_next_predPC = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->sf = (gcnew System::Windows::Forms::TextBox());
			this->cycle = (gcnew System::Windows::Forms::TextBox());
			this->of = (gcnew System::Windows::Forms::TextBox());
			this->zf = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->resume = (gcnew System::Windows::Forms::Button());
			this->start = (gcnew System::Windows::Forms::Button());
			this->memory = (gcnew System::Windows::Forms::Button());
			this->change = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->policy = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->byte = (gcnew System::Windows::Forms::Label());
			this->line = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->set = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// pause
			// 
			this->pause->Font = (gcnew System::Drawing::Font(L"幼圆", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->pause->Location = System::Drawing::Point(87, 53);
			this->pause->Name = L"pause";
			this->pause->Size = System::Drawing::Size(77, 29);
			this->pause->TabIndex = 0;
			this->pause->Text = L"pause";
			this->pause->UseVisualStyleBackColor = true;
			this->pause->Click += gcnew System::EventHandler(this, &MyForm::pause_Click);
			// 
			// rax
			// 
			this->rax->Location = System::Drawing::Point(1264, 12);
			this->rax->Name = L"rax";
			this->rax->Size = System::Drawing::Size(174, 28);
			this->rax->TabIndex = 1;
			// 
			// rcx
			// 
			this->rcx->Location = System::Drawing::Point(1264, 53);
			this->rcx->Name = L"rcx";
			this->rcx->Size = System::Drawing::Size(174, 28);
			this->rcx->TabIndex = 2;
			// 
			// rdx
			// 
			this->rdx->Location = System::Drawing::Point(1264, 107);
			this->rdx->Name = L"rdx";
			this->rdx->Size = System::Drawing::Size(174, 28);
			this->rdx->TabIndex = 3;
			// 
			// rbx
			// 
			this->rbx->Location = System::Drawing::Point(1264, 150);
			this->rbx->Name = L"rbx";
			this->rbx->Size = System::Drawing::Size(174, 28);
			this->rbx->TabIndex = 4;
			// 
			// rsp
			// 
			this->rsp->Location = System::Drawing::Point(1264, 201);
			this->rsp->Name = L"rsp";
			this->rsp->Size = System::Drawing::Size(174, 28);
			this->rsp->TabIndex = 5;
			// 
			// rbp
			// 
			this->rbp->Location = System::Drawing::Point(1264, 249);
			this->rbp->Name = L"rbp";
			this->rbp->Size = System::Drawing::Size(174, 28);
			this->rbp->TabIndex = 6;
			// 
			// rsi
			// 
			this->rsi->Location = System::Drawing::Point(1264, 295);
			this->rsi->Name = L"rsi";
			this->rsi->Size = System::Drawing::Size(174, 28);
			this->rsi->TabIndex = 7;
			// 
			// rdi
			// 
			this->rdi->Location = System::Drawing::Point(1264, 338);
			this->rdi->Name = L"rdi";
			this->rdi->Size = System::Drawing::Size(174, 28);
			this->rdi->TabIndex = 8;
			// 
			// r8
			// 
			this->r8->Location = System::Drawing::Point(1264, 391);
			this->r8->Name = L"r8";
			this->r8->Size = System::Drawing::Size(174, 28);
			this->r8->TabIndex = 9;
			// 
			// r9
			// 
			this->r9->Location = System::Drawing::Point(1264, 428);
			this->r9->Name = L"r9";
			this->r9->Size = System::Drawing::Size(174, 28);
			this->r9->TabIndex = 10;
			// 
			// r10
			// 
			this->r10->Location = System::Drawing::Point(1264, 474);
			this->r10->Name = L"r10";
			this->r10->Size = System::Drawing::Size(174, 28);
			this->r10->TabIndex = 11;
			// 
			// r11
			// 
			this->r11->Location = System::Drawing::Point(1264, 519);
			this->r11->Name = L"r11";
			this->r11->Size = System::Drawing::Size(174, 28);
			this->r11->TabIndex = 12;
			// 
			// W_now_instruc
			// 
			this->W_now_instruc->Location = System::Drawing::Point(305, 88);
			this->W_now_instruc->Name = L"W_now_instruc";
			this->W_now_instruc->Size = System::Drawing::Size(72, 28);
			this->W_now_instruc->TabIndex = 13;
			// 
			// W_now_icode
			// 
			this->W_now_icode->Location = System::Drawing::Point(396, 88);
			this->W_now_icode->Name = L"W_now_icode";
			this->W_now_icode->Size = System::Drawing::Size(56, 28);
			this->W_now_icode->TabIndex = 14;
			// 
			// M_now_icode
			// 
			this->M_now_icode->Location = System::Drawing::Point(396, 186);
			this->M_now_icode->Name = L"M_now_icode";
			this->M_now_icode->Size = System::Drawing::Size(52, 28);
			this->M_now_icode->TabIndex = 15;
			// 
			// W_now_valM
			// 
			this->W_now_valM->Location = System::Drawing::Point(815, 91);
			this->W_now_valM->Name = L"W_now_valM";
			this->W_now_valM->Size = System::Drawing::Size(157, 28);
			this->W_now_valM->TabIndex = 16;
			// 
			// W_now_E_reg
			// 
			this->W_now_E_reg->Location = System::Drawing::Point(988, 91);
			this->W_now_E_reg->Name = L"W_now_E_reg";
			this->W_now_E_reg->Size = System::Drawing::Size(50, 28);
			this->W_now_E_reg->TabIndex = 17;
			// 
			// W_now_M_reg
			// 
			this->W_now_M_reg->Location = System::Drawing::Point(1044, 91);
			this->W_now_M_reg->Name = L"W_now_M_reg";
			this->W_now_M_reg->Size = System::Drawing::Size(44, 28);
			this->W_now_M_reg->TabIndex = 18;
			// 
			// M_now_instruc
			// 
			this->M_now_instruc->Location = System::Drawing::Point(305, 186);
			this->M_now_instruc->Name = L"M_now_instruc";
			this->M_now_instruc->Size = System::Drawing::Size(72, 28);
			this->M_now_instruc->TabIndex = 19;
			// 
			// W_now_valE
			// 
			this->W_now_valE->Location = System::Drawing::Point(681, 88);
			this->W_now_valE->Name = L"W_now_valE";
			this->W_now_valE->Size = System::Drawing::Size(128, 28);
			this->W_now_valE->TabIndex = 20;
			// 
			// M_now_cnd
			// 
			this->M_now_cnd->Location = System::Drawing::Point(548, 185);
			this->M_now_cnd->Name = L"M_now_cnd";
			this->M_now_cnd->Size = System::Drawing::Size(45, 28);
			this->M_now_cnd->TabIndex = 21;
			// 
			// M_now_valE
			// 
			this->M_now_valE->Location = System::Drawing::Point(681, 186);
			this->M_now_valE->Name = L"M_now_valE";
			this->M_now_valE->Size = System::Drawing::Size(129, 28);
			this->M_now_valE->TabIndex = 22;
			// 
			// M_now_valA
			// 
			this->M_now_valA->Location = System::Drawing::Point(815, 186);
			this->M_now_valA->Name = L"M_now_valA";
			this->M_now_valA->Size = System::Drawing::Size(157, 28);
			this->M_now_valA->TabIndex = 23;
			// 
			// M_now_E_reg
			// 
			this->M_now_E_reg->Location = System::Drawing::Point(992, 186);
			this->M_now_E_reg->Name = L"M_now_E_reg";
			this->M_now_E_reg->Size = System::Drawing::Size(46, 28);
			this->M_now_E_reg->TabIndex = 24;
			// 
			// M_now_M_reg
			// 
			this->M_now_M_reg->Location = System::Drawing::Point(1044, 186);
			this->M_now_M_reg->Name = L"M_now_M_reg";
			this->M_now_M_reg->Size = System::Drawing::Size(44, 28);
			this->M_now_M_reg->TabIndex = 25;
			// 
			// W_next_instruc
			// 
			this->W_next_instruc->Location = System::Drawing::Point(305, 122);
			this->W_next_instruc->Name = L"W_next_instruc";
			this->W_next_instruc->Size = System::Drawing::Size(72, 28);
			this->W_next_instruc->TabIndex = 26;
			// 
			// W_next_icode
			// 
			this->W_next_icode->Location = System::Drawing::Point(396, 122);
			this->W_next_icode->Name = L"W_next_icode";
			this->W_next_icode->Size = System::Drawing::Size(56, 28);
			this->W_next_icode->TabIndex = 27;
			// 
			// W_next_valE
			// 
			this->W_next_valE->Location = System::Drawing::Point(681, 122);
			this->W_next_valE->Name = L"W_next_valE";
			this->W_next_valE->Size = System::Drawing::Size(129, 28);
			this->W_next_valE->TabIndex = 28;
			// 
			// W_next_valM
			// 
			this->W_next_valM->Location = System::Drawing::Point(815, 122);
			this->W_next_valM->Name = L"W_next_valM";
			this->W_next_valM->Size = System::Drawing::Size(157, 28);
			this->W_next_valM->TabIndex = 29;
			// 
			// W_next_E_reg
			// 
			this->W_next_E_reg->Location = System::Drawing::Point(988, 122);
			this->W_next_E_reg->Name = L"W_next_E_reg";
			this->W_next_E_reg->Size = System::Drawing::Size(50, 28);
			this->W_next_E_reg->TabIndex = 30;
			// 
			// W_next_M_reg
			// 
			this->W_next_M_reg->Location = System::Drawing::Point(1044, 122);
			this->W_next_M_reg->Name = L"W_next_M_reg";
			this->W_next_M_reg->Size = System::Drawing::Size(44, 28);
			this->W_next_M_reg->TabIndex = 31;
			// 
			// M_next_instruc
			// 
			this->M_next_instruc->Location = System::Drawing::Point(305, 228);
			this->M_next_instruc->Name = L"M_next_instruc";
			this->M_next_instruc->Size = System::Drawing::Size(72, 28);
			this->M_next_instruc->TabIndex = 32;
			// 
			// M_next_icode
			// 
			this->M_next_icode->Location = System::Drawing::Point(396, 228);
			this->M_next_icode->Name = L"M_next_icode";
			this->M_next_icode->Size = System::Drawing::Size(52, 28);
			this->M_next_icode->TabIndex = 33;
			// 
			// M_next_cnd
			// 
			this->M_next_cnd->Location = System::Drawing::Point(548, 228);
			this->M_next_cnd->Name = L"M_next_cnd";
			this->M_next_cnd->Size = System::Drawing::Size(45, 28);
			this->M_next_cnd->TabIndex = 34;
			// 
			// M_next_valE
			// 
			this->M_next_valE->Location = System::Drawing::Point(681, 228);
			this->M_next_valE->Name = L"M_next_valE";
			this->M_next_valE->Size = System::Drawing::Size(128, 28);
			this->M_next_valE->TabIndex = 35;
			// 
			// M_next_valA
			// 
			this->M_next_valA->Location = System::Drawing::Point(815, 228);
			this->M_next_valA->Name = L"M_next_valA";
			this->M_next_valA->Size = System::Drawing::Size(157, 28);
			this->M_next_valA->TabIndex = 36;
			// 
			// M_next_E_reg
			// 
			this->M_next_E_reg->Location = System::Drawing::Point(992, 228);
			this->M_next_E_reg->Name = L"M_next_E_reg";
			this->M_next_E_reg->Size = System::Drawing::Size(46, 28);
			this->M_next_E_reg->TabIndex = 37;
			// 
			// M_next_M_reg
			// 
			this->M_next_M_reg->Location = System::Drawing::Point(1044, 228);
			this->M_next_M_reg->Name = L"M_next_M_reg";
			this->M_next_M_reg->Size = System::Drawing::Size(44, 28);
			this->M_next_M_reg->TabIndex = 38;
			// 
			// E_now_instruc
			// 
			this->E_now_instruc->Location = System::Drawing::Point(305, 292);
			this->E_now_instruc->Name = L"E_now_instruc";
			this->E_now_instruc->Size = System::Drawing::Size(72, 28);
			this->E_now_instruc->TabIndex = 39;
			// 
			// E_next_instruc
			// 
			this->E_next_instruc->Location = System::Drawing::Point(305, 335);
			this->E_next_instruc->Name = L"E_next_instruc";
			this->E_next_instruc->Size = System::Drawing::Size(72, 28);
			this->E_next_instruc->TabIndex = 40;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"幼圆", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(220, 91);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 24);
			this->label1->TabIndex = 41;
			this->label1->Text = L"W_now";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"幼圆", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label2->Location = System::Drawing::Point(220, 126);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(82, 24);
			this->label2->TabIndex = 42;
			this->label2->Text = L"W_next";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"幼圆", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label3->Location = System::Drawing::Point(220, 189);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(70, 24);
			this->label3->TabIndex = 43;
			this->label3->Text = L"M_now";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"幼圆", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label4->Location = System::Drawing::Point(220, 228);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(82, 24);
			this->label4->TabIndex = 44;
			this->label4->Text = L"M_next";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"幼圆", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label5->Location = System::Drawing::Point(220, 295);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(70, 24);
			this->label5->TabIndex = 45;
			this->label5->Text = L"E_now";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"幼圆", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label6->Location = System::Drawing::Point(220, 338);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(82, 24);
			this->label6->TabIndex = 46;
			this->label6->Text = L"E_next";
			// 
			// filename
			// 
			this->filename->Location = System::Drawing::Point(12, 12);
			this->filename->Name = L"filename";
			this->filename->Size = System::Drawing::Size(354, 28);
			this->filename->TabIndex = 47;
			// 
			// E_now_icode
			// 
			this->E_now_icode->Location = System::Drawing::Point(396, 292);
			this->E_now_icode->Name = L"E_now_icode";
			this->E_now_icode->Size = System::Drawing::Size(52, 28);
			this->E_now_icode->TabIndex = 49;
			// 
			// E_next_icode
			// 
			this->E_next_icode->Location = System::Drawing::Point(396, 338);
			this->E_next_icode->Name = L"E_next_icode";
			this->E_next_icode->Size = System::Drawing::Size(52, 28);
			this->E_next_icode->TabIndex = 50;
			// 
			// E_now_ifun
			// 
			this->E_now_ifun->Location = System::Drawing::Point(472, 292);
			this->E_now_ifun->Name = L"E_now_ifun";
			this->E_now_ifun->Size = System::Drawing::Size(45, 28);
			this->E_now_ifun->TabIndex = 51;
			// 
			// E_next_ifun
			// 
			this->E_next_ifun->Location = System::Drawing::Point(472, 338);
			this->E_next_ifun->Name = L"E_next_ifun";
			this->E_next_ifun->Size = System::Drawing::Size(45, 28);
			this->E_next_ifun->TabIndex = 52;
			// 
			// E_now_valA
			// 
			this->E_now_valA->Location = System::Drawing::Point(681, 294);
			this->E_now_valA->Name = L"E_now_valA";
			this->E_now_valA->Size = System::Drawing::Size(138, 28);
			this->E_now_valA->TabIndex = 53;
			// 
			// E_next_valC
			// 
			this->E_next_valC->Location = System::Drawing::Point(548, 338);
			this->E_next_valC->Name = L"E_next_valC";
			this->E_next_valC->Size = System::Drawing::Size(127, 28);
			this->E_next_valC->TabIndex = 54;
			// 
			// E_now_valB
			// 
			this->E_now_valB->Location = System::Drawing::Point(825, 292);
			this->E_now_valB->Name = L"E_now_valB";
			this->E_now_valB->Size = System::Drawing::Size(147, 28);
			this->E_now_valB->TabIndex = 55;
			// 
			// E_next_valA
			// 
			this->E_next_valA->Location = System::Drawing::Point(681, 338);
			this->E_next_valA->Name = L"E_next_valA";
			this->E_next_valA->Size = System::Drawing::Size(138, 28);
			this->E_next_valA->TabIndex = 56;
			// 
			// E_now_E_reg
			// 
			this->E_now_E_reg->Location = System::Drawing::Point(992, 292);
			this->E_now_E_reg->Name = L"E_now_E_reg";
			this->E_now_E_reg->Size = System::Drawing::Size(46, 28);
			this->E_now_E_reg->TabIndex = 57;
			// 
			// E_next_valB
			// 
			this->E_next_valB->Location = System::Drawing::Point(825, 338);
			this->E_next_valB->Name = L"E_next_valB";
			this->E_next_valB->Size = System::Drawing::Size(147, 28);
			this->E_next_valB->TabIndex = 58;
			// 
			// E_now_M_reg
			// 
			this->E_now_M_reg->Location = System::Drawing::Point(1044, 294);
			this->E_now_M_reg->Name = L"E_now_M_reg";
			this->E_now_M_reg->Size = System::Drawing::Size(44, 28);
			this->E_now_M_reg->TabIndex = 59;
			// 
			// E_next_M_reg
			// 
			this->E_next_M_reg->Location = System::Drawing::Point(1044, 338);
			this->E_next_M_reg->Name = L"E_next_M_reg";
			this->E_next_M_reg->Size = System::Drawing::Size(44, 28);
			this->E_next_M_reg->TabIndex = 60;
			// 
			// E_now_A_reg
			// 
			this->E_now_A_reg->Location = System::Drawing::Point(1098, 294);
			this->E_now_A_reg->Name = L"E_now_A_reg";
			this->E_now_A_reg->Size = System::Drawing::Size(45, 28);
			this->E_now_A_reg->TabIndex = 61;
			// 
			// E_now_B_reg
			// 
			this->E_now_B_reg->Location = System::Drawing::Point(1149, 294);
			this->E_now_B_reg->Name = L"E_now_B_reg";
			this->E_now_B_reg->Size = System::Drawing::Size(40, 28);
			this->E_now_B_reg->TabIndex = 62;
			// 
			// E_now_valC
			// 
			this->E_now_valC->Location = System::Drawing::Point(548, 292);
			this->E_now_valC->Name = L"E_now_valC";
			this->E_now_valC->Size = System::Drawing::Size(127, 28);
			this->E_now_valC->TabIndex = 63;
			// 
			// E_next_A_reg
			// 
			this->E_next_A_reg->Location = System::Drawing::Point(1098, 338);
			this->E_next_A_reg->Name = L"E_next_A_reg";
			this->E_next_A_reg->Size = System::Drawing::Size(45, 28);
			this->E_next_A_reg->TabIndex = 64;
			// 
			// E_next_B_reg
			// 
			this->E_next_B_reg->Location = System::Drawing::Point(1149, 338);
			this->E_next_B_reg->Name = L"E_next_B_reg";
			this->E_next_B_reg->Size = System::Drawing::Size(40, 28);
			this->E_next_B_reg->TabIndex = 65;
			// 
			// E_next_E_reg
			// 
			this->E_next_E_reg->Location = System::Drawing::Point(992, 338);
			this->E_next_E_reg->Name = L"E_next_E_reg";
			this->E_next_E_reg->Size = System::Drawing::Size(46, 28);
			this->E_next_E_reg->TabIndex = 66;
			// 
			// D_now_icode
			// 
			this->D_now_icode->Location = System::Drawing::Point(394, 391);
			this->D_now_icode->Name = L"D_now_icode";
			this->D_now_icode->Size = System::Drawing::Size(54, 28);
			this->D_now_icode->TabIndex = 67;
			// 
			// D_now_instruc
			// 
			this->D_now_instruc->Location = System::Drawing::Point(305, 391);
			this->D_now_instruc->Name = L"D_now_instruc";
			this->D_now_instruc->Size = System::Drawing::Size(72, 28);
			this->D_now_instruc->TabIndex = 68;
			// 
			// D_now_B_reg
			// 
			this->D_now_B_reg->Location = System::Drawing::Point(596, 390);
			this->D_now_B_reg->Name = L"D_now_B_reg";
			this->D_now_B_reg->Size = System::Drawing::Size(45, 28);
			this->D_now_B_reg->TabIndex = 69;
			// 
			// D_now_A_reg
			// 
			this->D_now_A_reg->Location = System::Drawing::Point(548, 390);
			this->D_now_A_reg->Name = L"D_now_A_reg";
			this->D_now_A_reg->Size = System::Drawing::Size(42, 28);
			this->D_now_A_reg->TabIndex = 70;
			// 
			// D_now_ifun
			// 
			this->D_now_ifun->Location = System::Drawing::Point(472, 391);
			this->D_now_ifun->Name = L"D_now_ifun";
			this->D_now_ifun->Size = System::Drawing::Size(43, 28);
			this->D_now_ifun->TabIndex = 71;
			// 
			// D_now_valC
			// 
			this->D_now_valC->Location = System::Drawing::Point(681, 391);
			this->D_now_valC->Name = L"D_now_valC";
			this->D_now_valC->Size = System::Drawing::Size(138, 28);
			this->D_now_valC->TabIndex = 72;
			// 
			// D_now_valP
			// 
			this->D_now_valP->Location = System::Drawing::Point(825, 391);
			this->D_now_valP->Name = L"D_now_valP";
			this->D_now_valP->Size = System::Drawing::Size(147, 28);
			this->D_now_valP->TabIndex = 73;
			// 
			// D_next_instruc
			// 
			this->D_next_instruc->Location = System::Drawing::Point(305, 435);
			this->D_next_instruc->Name = L"D_next_instruc";
			this->D_next_instruc->Size = System::Drawing::Size(72, 28);
			this->D_next_instruc->TabIndex = 74;
			// 
			// D_next_icode
			// 
			this->D_next_icode->Location = System::Drawing::Point(396, 435);
			this->D_next_icode->Name = L"D_next_icode";
			this->D_next_icode->Size = System::Drawing::Size(52, 28);
			this->D_next_icode->TabIndex = 75;
			// 
			// D_next_ifun
			// 
			this->D_next_ifun->Location = System::Drawing::Point(472, 435);
			this->D_next_ifun->Name = L"D_next_ifun";
			this->D_next_ifun->Size = System::Drawing::Size(43, 28);
			this->D_next_ifun->TabIndex = 76;
			// 
			// D_next_A_reg
			// 
			this->D_next_A_reg->Location = System::Drawing::Point(548, 435);
			this->D_next_A_reg->Name = L"D_next_A_reg";
			this->D_next_A_reg->Size = System::Drawing::Size(42, 28);
			this->D_next_A_reg->TabIndex = 77;
			// 
			// D_next_B_reg
			// 
			this->D_next_B_reg->Location = System::Drawing::Point(596, 435);
			this->D_next_B_reg->Name = L"D_next_B_reg";
			this->D_next_B_reg->Size = System::Drawing::Size(45, 28);
			this->D_next_B_reg->TabIndex = 78;
			// 
			// D_next_valC
			// 
			this->D_next_valC->Location = System::Drawing::Point(681, 438);
			this->D_next_valC->Name = L"D_next_valC";
			this->D_next_valC->Size = System::Drawing::Size(138, 28);
			this->D_next_valC->TabIndex = 79;
			// 
			// D_next_valP
			// 
			this->D_next_valP->Location = System::Drawing::Point(825, 435);
			this->D_next_valP->Name = L"D_next_valP";
			this->D_next_valP->Size = System::Drawing::Size(147, 28);
			this->D_next_valP->TabIndex = 80;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label8->Location = System::Drawing::Point(223, 394);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(70, 24);
			this->label8->TabIndex = 82;
			this->label8->Text = L"D_now";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label9->Location = System::Drawing::Point(223, 439);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(82, 24);
			this->label9->TabIndex = 83;
			this->label9->Text = L"D_next";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label10->Location = System::Drawing::Point(223, 523);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(82, 24);
			this->label10->TabIndex = 84;
			this->label10->Text = L"F_next";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label11->Location = System::Drawing::Point(229, 485);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(70, 24);
			this->label11->TabIndex = 85;
			this->label11->Text = L"F_now";
			// 
			// F_now_predPC
			// 
			this->F_now_predPC->Location = System::Drawing::Point(305, 481);
			this->F_now_predPC->Name = L"F_now_predPC";
			this->F_now_predPC->Size = System::Drawing::Size(143, 28);
			this->F_now_predPC->TabIndex = 86;
			// 
			// F_next_predPC
			// 
			this->F_next_predPC->Location = System::Drawing::Point(305, 519);
			this->F_next_predPC->Name = L"F_next_predPC";
			this->F_next_predPC->Size = System::Drawing::Size(143, 28);
			this->F_next_predPC->TabIndex = 87;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(77, 459);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(59, 28);
			this->textBox1->TabIndex = 88;
			// 
			// sf
			// 
			this->sf->Location = System::Drawing::Point(77, 328);
			this->sf->Name = L"sf";
			this->sf->Size = System::Drawing::Size(59, 28);
			this->sf->TabIndex = 89;
			// 
			// cycle
			// 
			this->cycle->Location = System::Drawing::Point(77, 391);
			this->cycle->Name = L"cycle";
			this->cycle->Size = System::Drawing::Size(59, 28);
			this->cycle->TabIndex = 90;
			// 
			// of
			// 
			this->of->Location = System::Drawing::Point(77, 277);
			this->of->Name = L"of";
			this->of->Size = System::Drawing::Size(59, 28);
			this->of->TabIndex = 91;
			// 
			// zf
			// 
			this->zf->Location = System::Drawing::Point(77, 218);
			this->zf->Name = L"zf";
			this->zf->Size = System::Drawing::Size(59, 28);
			this->zf->TabIndex = 92;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label7->Location = System::Drawing::Point(1200, 16);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(58, 24);
			this->label7->TabIndex = 93;
			this->label7->Text = L"%rax";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label12->Location = System::Drawing::Point(1200, 57);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(58, 24);
			this->label12->TabIndex = 94;
			this->label12->Text = L"%rcx";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label13->Location = System::Drawing::Point(1200, 111);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(58, 24);
			this->label13->TabIndex = 95;
			this->label13->Text = L"%rdx";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label14->Location = System::Drawing::Point(1200, 154);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(58, 24);
			this->label14->TabIndex = 96;
			this->label14->Text = L"%rbx";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label15->Location = System::Drawing::Point(1200, 205);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(58, 24);
			this->label15->TabIndex = 97;
			this->label15->Text = L"%rsp";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label16->Location = System::Drawing::Point(1200, 253);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(58, 24);
			this->label16->TabIndex = 98;
			this->label16->Text = L"%rbp";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label17->Location = System::Drawing::Point(1200, 299);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(58, 24);
			this->label17->TabIndex = 99;
			this->label17->Text = L"%rsi";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label18->Location = System::Drawing::Point(1203, 342);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(58, 24);
			this->label18->TabIndex = 100;
			this->label18->Text = L"%rdi";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label19->Location = System::Drawing::Point(1215, 432);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(46, 24);
			this->label19->TabIndex = 101;
			this->label19->Text = L"%r9";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label20->Location = System::Drawing::Point(1215, 395);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(46, 24);
			this->label20->TabIndex = 102;
			this->label20->Text = L"%r8";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label21->Location = System::Drawing::Point(1203, 523);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(58, 24);
			this->label21->TabIndex = 103;
			this->label21->Text = L"%r11";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label22->Location = System::Drawing::Point(1203, 478);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(58, 24);
			this->label22->TabIndex = 104;
			this->label22->Text = L"%r10";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"幼圆", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label23->Location = System::Drawing::Point(9, 221);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(34, 24);
			this->label23->TabIndex = 105;
			this->label23->Text = L"zf";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label24->Location = System::Drawing::Point(9, 281);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(34, 24);
			this->label24->TabIndex = 106;
			this->label24->Text = L"of";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"幼圆", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label25->Location = System::Drawing::Point(9, 332);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(34, 24);
			this->label25->TabIndex = 107;
			this->label25->Text = L"sf";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label26->Location = System::Drawing::Point(0, 390);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(70, 24);
			this->label26->TabIndex = 108;
			this->label26->Text = L"cycle";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"幼圆", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label27->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label27->Location = System::Drawing::Point(0, 459);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(58, 24);
			this->label27->TabIndex = 109;
			this->label27->Text = L"rate";
			// 
			// resume
			// 
			this->resume->Font = (gcnew System::Drawing::Font(L"幼圆", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->resume->Location = System::Drawing::Point(263, 52);
			this->resume->Name = L"resume";
			this->resume->Size = System::Drawing::Size(103, 29);
			this->resume->TabIndex = 111;
			this->resume->Text = L"resume";
			this->resume->UseVisualStyleBackColor = true;
			this->resume->Click += gcnew System::EventHandler(this, &MyForm::resume_Click);
			// 
			// start
			// 
			this->start->Font = (gcnew System::Drawing::Font(L"幼圆", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->start->Location = System::Drawing::Point(3, 53);
			this->start->Name = L"start";
			this->start->Size = System::Drawing::Size(73, 29);
			this->start->TabIndex = 113;
			this->start->Text = L"start";
			this->start->UseVisualStyleBackColor = true;
			this->start->Click += gcnew System::EventHandler(this, &MyForm::start_Click);
			// 
			// memory
			// 
			this->memory->Font = (gcnew System::Drawing::Font(L"幼圆", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->memory->Location = System::Drawing::Point(3, 122);
			this->memory->Name = L"memory";
			this->memory->Size = System::Drawing::Size(124, 52);
			this->memory->TabIndex = 116;
			this->memory->Text = L"memory";
			this->memory->UseVisualStyleBackColor = true;
			this->memory->Click += gcnew System::EventHandler(this, &MyForm::memory_Click);
			// 
			// change
			// 
			this->change->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->change->Location = System::Drawing::Point(65, 493);
			this->change->Name = L"change";
			this->change->Size = System::Drawing::Size(84, 28);
			this->change->TabIndex = 118;
			this->change->Text = L"change";
			this->change->UseVisualStyleBackColor = true;
			this->change->Click += gcnew System::EventHandler(this, &MyForm::change_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->button2->Location = System::Drawing::Point(172, 54);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(85, 27);
			this->button2->TabIndex = 120;
			this->button2->Text = L"step";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label29->Location = System::Drawing::Point(32, 616);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(214, 24);
			this->label29->TabIndex = 122;
			this->label29->Text = L"replace policy ：";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label30->Location = System::Drawing::Point(32, 657);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(75, 21);
			this->label30->TabIndex = 124;
			this->label30->Text = L"0：LRU";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label31->Location = System::Drawing::Point(130, 657);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(75, 21);
			this->label31->TabIndex = 125;
			this->label31->Text = L"1：LFU";
			// 
			// policy
			// 
			this->policy->Location = System::Drawing::Point(254, 619);
			this->policy->Name = L"policy";
			this->policy->Size = System::Drawing::Size(82, 28);
			this->policy->TabIndex = 126;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->button1->Location = System::Drawing::Point(252, 666);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(84, 28);
			this->button1->TabIndex = 127;
			this->button1->Text = L"change";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// byte
			// 
			this->byte->AutoSize = true;
			this->byte->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->byte->Location = System::Drawing::Point(392, 679);
			this->byte->Name = L"byte";
			this->byte->Size = System::Drawing::Size(130, 24);
			this->byte->TabIndex = 128;
			this->byte->Text = L"byte_num :";
			// 
			// line
			// 
			this->line->AutoSize = true;
			this->line->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->line->Location = System::Drawing::Point(392, 645);
			this->line->Name = L"line";
			this->line->Size = System::Drawing::Size(130, 24);
			this->line->TabIndex = 129;
			this->line->Text = L"line_num :";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label33->Location = System::Drawing::Point(392, 607);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(118, 24);
			this->label33->TabIndex = 130;
			this->label33->Text = L"set_num :";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(539, 644);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(82, 28);
			this->textBox3->TabIndex = 132;
			// 
			// set
			// 
			this->set->Location = System::Drawing::Point(539, 610);
			this->set->Name = L"set";
			this->set->Size = System::Drawing::Size(82, 28);
			this->set->TabIndex = 133;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(539, 682);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(82, 28);
			this->textBox5->TabIndex = 134;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->ClientSize = System::Drawing::Size(1490, 744);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->set);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label33);
			this->Controls->Add(this->line);
			this->Controls->Add(this->byte);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->policy);
			this->Controls->Add(this->label31);
			this->Controls->Add(this->label30);
			this->Controls->Add(this->label29);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->change);
			this->Controls->Add(this->memory);
			this->Controls->Add(this->start);
			this->Controls->Add(this->resume);
			this->Controls->Add(this->label27);
			this->Controls->Add(this->label26);
			this->Controls->Add(this->label25);
			this->Controls->Add(this->label24);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->zf);
			this->Controls->Add(this->of);
			this->Controls->Add(this->cycle);
			this->Controls->Add(this->sf);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->F_next_predPC);
			this->Controls->Add(this->F_now_predPC);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->D_next_valP);
			this->Controls->Add(this->D_next_valC);
			this->Controls->Add(this->D_next_B_reg);
			this->Controls->Add(this->D_next_A_reg);
			this->Controls->Add(this->D_next_ifun);
			this->Controls->Add(this->D_next_icode);
			this->Controls->Add(this->D_next_instruc);
			this->Controls->Add(this->D_now_valP);
			this->Controls->Add(this->D_now_valC);
			this->Controls->Add(this->D_now_ifun);
			this->Controls->Add(this->D_now_A_reg);
			this->Controls->Add(this->D_now_B_reg);
			this->Controls->Add(this->D_now_instruc);
			this->Controls->Add(this->D_now_icode);
			this->Controls->Add(this->E_next_E_reg);
			this->Controls->Add(this->E_next_B_reg);
			this->Controls->Add(this->E_next_A_reg);
			this->Controls->Add(this->E_now_valC);
			this->Controls->Add(this->E_now_B_reg);
			this->Controls->Add(this->E_now_A_reg);
			this->Controls->Add(this->E_next_M_reg);
			this->Controls->Add(this->E_now_M_reg);
			this->Controls->Add(this->E_next_valB);
			this->Controls->Add(this->E_now_E_reg);
			this->Controls->Add(this->E_next_valA);
			this->Controls->Add(this->E_now_valB);
			this->Controls->Add(this->E_next_valC);
			this->Controls->Add(this->E_now_valA);
			this->Controls->Add(this->E_next_ifun);
			this->Controls->Add(this->E_now_ifun);
			this->Controls->Add(this->E_next_icode);
			this->Controls->Add(this->E_now_icode);
			this->Controls->Add(this->filename);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->E_next_instruc);
			this->Controls->Add(this->E_now_instruc);
			this->Controls->Add(this->M_next_M_reg);
			this->Controls->Add(this->M_next_E_reg);
			this->Controls->Add(this->M_next_valA);
			this->Controls->Add(this->M_next_valE);
			this->Controls->Add(this->M_next_cnd);
			this->Controls->Add(this->M_next_icode);
			this->Controls->Add(this->M_next_instruc);
			this->Controls->Add(this->W_next_M_reg);
			this->Controls->Add(this->W_next_E_reg);
			this->Controls->Add(this->W_next_valM);
			this->Controls->Add(this->W_next_valE);
			this->Controls->Add(this->W_next_icode);
			this->Controls->Add(this->W_next_instruc);
			this->Controls->Add(this->M_now_M_reg);
			this->Controls->Add(this->M_now_E_reg);
			this->Controls->Add(this->M_now_valA);
			this->Controls->Add(this->M_now_valE);
			this->Controls->Add(this->M_now_cnd);
			this->Controls->Add(this->W_now_valE);
			this->Controls->Add(this->M_now_instruc);
			this->Controls->Add(this->W_now_M_reg);
			this->Controls->Add(this->W_now_E_reg);
			this->Controls->Add(this->W_now_valM);
			this->Controls->Add(this->M_now_icode);
			this->Controls->Add(this->W_now_icode);
			this->Controls->Add(this->W_now_instruc);
			this->Controls->Add(this->r11);
			this->Controls->Add(this->r10);
			this->Controls->Add(this->r9);
			this->Controls->Add(this->r8);
			this->Controls->Add(this->rdi);
			this->Controls->Add(this->rsi);
			this->Controls->Add(this->rbp);
			this->Controls->Add(this->rsp);
			this->Controls->Add(this->rbx);
			this->Controls->Add(this->rdx);
			this->Controls->Add(this->rcx);
			this->Controls->Add(this->rax);
			this->Controls->Add(this->pause);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximumSize = System::Drawing::Size(2500, 800);
			this->Name = L"MyForm";
			this->Text = L"y86-64";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	filename->Text = str;
}

private: System::Void change_Click(System::Object^  sender, System::EventArgs^  e) {
	tm->Interval = str_to_int(textBox1->Text);
}
private: System::Void memory_Click(System::Object^  sender, System::EventArgs^  e) {
	MyForm2^ f3 = gcnew MyForm2;
	f3->ShowDialog();
}

private: System::Void start_Click(System::Object^  sender, System::EventArgs^  e) 
{
	delete cache;
	cache = new Cache();
	initCache();
	//char* s = str_to_ch(str);
	//load_instr(s);
	fe->Initialize();
	fe->f_predPC = "0x0";
	de->Initialize();
	exe->Initialize();
	mem->Initialize();
	wri->Initialize();
	for (int i = 0; i < 9; i++)
		info->regval[i] = "0x00000000";
	rax->Text =str1_to_str2( wri->w_regval[0]);
	rcx->Text = str1_to_str2(wri->w_regval[1]);
	rdx->Text = str1_to_str2(wri->w_regval[2]);
	rbx->Text = str1_to_str2(wri->w_regval[3]);
	rsp->Text = str1_to_str2(wri->w_regval[4]);
	rbp->Text = str1_to_str2(wri->w_regval[5]);
	rsi->Text = str1_to_str2(wri->w_regval[6]);
	rdi->Text = str1_to_str2(wri->w_regval[7]);
	r8->Text= str1_to_str2(wri->w_regval[8]);
	r9->Text= str1_to_str2(wri->w_regval[9]);
	r10->Text= str1_to_str2(wri->w_regval[10]);
	r11->Text= str1_to_str2(wri->w_regval[11]);
	tm->Enabled = true;
}

private: System::Void pause_Click(System::Object^  sender, System::EventArgs^  e) {
	tm->Enabled = false;
}
private: System::Void resume_Click(System::Object^  sender, System::EventArgs^  e) {
	tm->Enabled = true;
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
{
	Once();
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	replace = str_to_int(policy->Text);
	s = str_to_int(set->Text);
	E = str_to_int(line->Text);
	b = str_to_int(byte->Text);
	initCache();
}
};
}
#endif
