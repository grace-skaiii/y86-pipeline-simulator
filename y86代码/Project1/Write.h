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
	class Write
	{
	public:
		string* w_regval = new string[16];
		void Initialize() {
			for (int i = 0; i < 16; i++)
				w_regval[i] = "0x00000000";
		}
	};
}