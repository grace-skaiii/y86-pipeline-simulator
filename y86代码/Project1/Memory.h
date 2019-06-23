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
	public class Memory
	{
	public:
		string m_icode = "0", m_instruc, m_valE = "0x00000000", m_valM = "0x00000000", m_dstE = "16", m_dstM = "16", m_E_reg = "NONE", m_M_reg = "NONE";
		void Initialize()
		{
			m_icode = "0";
			m_instruc = "NOP";
			m_valE = "0x00000000";
			m_valM = "0x00000000";
			m_dstE = "15";
			m_dstM = "15";
			m_E_reg = "NONE";
			m_M_reg = "NONE";
		}
		void NOP() 
		{
			//m_instruc = "NOP";
			m_valE = "0x00000000";
			m_valM = "0x00000000";
			m_dstE = "15";
			m_dstM = "15";
			m_E_reg = "NONE";
			m_M_reg = "NONE";
		}
	};
}
