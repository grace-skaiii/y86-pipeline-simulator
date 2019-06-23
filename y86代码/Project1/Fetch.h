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
	class Fetch
	{
	public:
		string f_instruc,f_icode, f_ifun , f_ra , f_rb , f_valC, f_valP ;
		string f_A_reg, f_B_reg, f_predPC,d_predPC;
		bool F_stall, F_bubble;
		void Initialize() 
		{
			f_instruc = "NOP";
			f_icode = "0";
			f_ifun = "0";
			f_ra = "15";
			f_rb = "15";
			f_valC = "0x00000000";
			f_valP = "0x00000000";
			f_A_reg = "NONE";
			f_B_reg = "NONE";
			f_predPC = "0x00000000";
			d_predPC= "0x00000000";
		}
		void NOP() 
		{
			f_icode = "0";
			f_ifun = "0";
			//f_instruc = "NOP";
			f_ra = "15";
			f_rb = "15";
			f_valC = "0x00000000";
			f_valP = "0x00000000";
			f_A_reg = "NONE";
			f_B_reg = "NONE";
			f_predPC = "0x00000000";
		}
	};
}
