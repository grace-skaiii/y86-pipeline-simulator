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
	class Decode
	{
	public: 
		string d_icode,d_ifun,d_instruc,d_valC,d_valA,d_valB,d_dstE,d_dstM;
		string d_srcA,d_srcB,d_E_reg,d_M_reg,d_A_reg,d_B_reg,d_predPC;
		bool D_stall, D_bubble;
		void Initialize() 
		{
			d_icode = "0";
			d_ifun = "0";
			d_instruc = "NOP";
			d_valC = "0x00000000";
			d_valA = "0x00000000";
			d_valB = "0x00000000";
			d_dstE = "15";
			d_dstM = "15";
			d_srcA = "15";
			d_srcB = "15";
			d_E_reg = "NONE";
			d_M_reg = "NONE";
			d_A_reg = "NONE";
			d_B_reg = "NONE";
		}
		void NOP() 
		{
			//d_instruc = "NOP";
			d_valC = "0x00000000";
			d_valA = "0x00000000";
			d_valB = "0x00000000";
			d_dstE = "15";
			d_dstM = "15";
			d_srcA = "15";
			d_srcB = "15";
			d_E_reg = "NONE";
			d_M_reg = "NONE";
			d_A_reg = "NONE";
			d_B_reg = "NONE";
		}
	};
}
