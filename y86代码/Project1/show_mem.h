#pragma once

#include"mm.h"
#include<string>
#include <sstream>
namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Text;
	using namespace std;
	/// <summary>
	/// MyForm2 摘要
	/// </summary>
	extern ul stack_top;
	public ref class MyForm2 : public System::Windows::Forms::Form
	{
	public:
		MyForm2(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MyForm2()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  memory;
	protected:

	private: System::Windows::Forms::Button^  show;
	private: System::Windows::Forms::TextBox^  num;

	protected:

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->memory = (gcnew System::Windows::Forms::TextBox());
			this->show = (gcnew System::Windows::Forms::Button());
			this->num = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// memory
			// 
			this->memory->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->memory->Location = System::Drawing::Point(101, 52);
			this->memory->Multiline = true;
			this->memory->Name = L"memory";
			this->memory->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->memory->Size = System::Drawing::Size(410, 360);
			this->memory->TabIndex = 0;
			// 
			// show
			// 
			this->show->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->show->Location = System::Drawing::Point(297, 443);
			this->show->Name = L"show";
			this->show->Size = System::Drawing::Size(94, 42);
			this->show->TabIndex = 1;
			this->show->Text = L"show ";
			this->show->UseVisualStyleBackColor = true;
			this->show->Click += gcnew System::EventHandler(this, &MyForm2::show_Click);
			// 
			// num
			// 
			this->num->Font = (gcnew System::Drawing::Font(L"宋体", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->num->Location = System::Drawing::Point(174, 443);
			this->num->Multiline = true;
			this->num->Name = L"num";
			this->num->Size = System::Drawing::Size(101, 42);
			this->num->TabIndex = 2;
			// 
			// MyForm2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->ClientSize = System::Drawing::Size(702, 520);
			this->Controls->Add(this->num);
			this->Controls->Add(this->show);
			this->Controls->Add(this->memory);
			this->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Name = L"MyForm2";
			this->Text = L"Memory";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		String^ str;
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
			s << hex << temp;
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
			string s = in_to_hex_str(num);
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
			for (int i = 2; i < len; i++)
			{
				res = res * 16 + transform(s[i]);
			}
			return res;
		}
		int str_to_in(String^ s)
		{
			int num;
			char* c = str_to_ch(s);
			return atoi(c);
		}
	private: 
		System::Void show_Click(System::Object^  sender, System::EventArgs^  e) {
		int n = str_to_in(num->Text);
		int dis = stack_top;
		int i= 1;
		while(i <=n&&i*8+dis<=0x200)
		{
			String^ s = "0x"+in_to_str((i-1)*8 + dis) + ":	0x";
			for (int j = 1; j<=8; j++)
			{
				ul ull = print_mem(i * 8 + dis-j);
				string t = ll_to_str1(ull);
				string tt = t;//t.substr(2,2);
				s+= str1_to_str2(tt);
			}
			memory->Text += s + "\r\n";
			i++;
		}
	}

};
}
