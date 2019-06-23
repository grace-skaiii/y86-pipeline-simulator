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
	class Execute
	{
	public:
		string e_icode, e_instruc, zf, of, sf,e_cnd,e_valE, e_valA, e_dstE, e_dstM, e_E_reg, e_M_reg;
		bool E_bubble, E_stall;
		void Initialize() 
		{
			e_icode = "0";
			e_instruc = "NOP";
			zf = "0";
			of = "0";
			sf = "0";
			e_cnd = "0";
			e_valE = "0x00000000";
			e_valA = "0x00000000";
			e_dstE = "15";
			e_dstM = "15";
			e_E_reg = "NONE";
			e_M_reg = "NONE";
		}
		void NOP() 
		{
			//e_instruc = "NOP";
			e_cnd = "0";
			zf = "0";
			of = "0";
			sf = "0";
			e_valE = "0x00000000";
			e_valA = "0x00000000";
			e_dstE = "15";
			e_dstM = "15";
			e_E_reg = "NONE";
			e_M_reg = "NONE";
		}
	};
}
