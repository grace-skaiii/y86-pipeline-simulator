#pragma once
#include<string>
namespace Project1
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	public class INFO
	{
	public:
		string instr[13];
		string regist[16];
		string* regval= new string[16];
		static void ReadAsm() {
		}
		INFO()
		{
			instr[0] = "HALT"; instr[1] = "NOP"; instr[2] = "RRMOVQ"; instr[3] = "IRMOVQ"; instr[4] = "RMMOVQ";instr[5] = "MRMOVQ";
			instr[6] = "OPQ"; instr[7] = "JXX"; instr[8] = "CALL"; instr[9] = "RET"; instr[10] = "PUSHQ"; instr[11] = "POPQ";instr[12]="IADD";
			regist[0] = "rax"; regist[1] = "rcx"; regist[2] = "rdx"; regist[3] = "rbx"; regist[4] = "rsp"; regist[5] = "rbp";
			regist[6] = "rsi"; regist[7] = "rdi"; regist[8] = "r8"; regist[9] = "r9"; regist[10] = "r10"; regist[11] = "r11";
			regist[12] = "r12"; regist[13] = "r13"; regist[14] = "r14"; regist[15] = "NONE";
		}
	};
}