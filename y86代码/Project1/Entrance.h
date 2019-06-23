#pragma once
#ifndef _ENTRANCE_H
#define _ENTRANCE_H
#include"pipe.h"
namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	/// <summary>
	/// MyForm1 摘要
	/// </summary>
	public ref class MyForm1 : public System::Windows::Forms::Form
	{
	public:
		MyForm1(void)
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
		~MyForm1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  show_yo;
	protected:

	private: System::Windows::Forms::TextBox^  yo;

	private: System::Windows::Forms::TextBox^  file_content;
	private: System::Windows::Forms::Button^  run_yo;
	protected:

	protected:



	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::TextBox^  ys;
	private: System::Windows::Forms::Button^  show_ys;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  run_ys;


	private: System::ComponentModel::IContainer^  components;


	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->show_yo = (gcnew System::Windows::Forms::Button());
			this->yo = (gcnew System::Windows::Forms::TextBox());
			this->file_content = (gcnew System::Windows::Forms::TextBox());
			this->run_yo = (gcnew System::Windows::Forms::Button());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->ys = (gcnew System::Windows::Forms::TextBox());
			this->show_ys = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->run_ys = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// show_yo
			// 
			this->show_yo->Font = (gcnew System::Drawing::Font(L"幼圆", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->show_yo->Location = System::Drawing::Point(409, 483);
			this->show_yo->Name = L"show_yo";
			this->show_yo->Size = System::Drawing::Size(178, 41);
			this->show_yo->TabIndex = 0;
			this->show_yo->Text = L".yo-show";
			this->show_yo->UseVisualStyleBackColor = true;
			this->show_yo->Click += gcnew System::EventHandler(this, &MyForm1::show_yo_Click_1);
			// 
			// yo
			// 
			this->yo->Location = System::Drawing::Point(146, 494);
			this->yo->Name = L"yo";
			this->yo->Size = System::Drawing::Size(210, 28);
			this->yo->TabIndex = 1;
			// 
			// file_content
			// 
			this->file_content->Font = (gcnew System::Drawing::Font(L"宋体", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->file_content->Location = System::Drawing::Point(86, 30);
			this->file_content->Multiline = true;
			this->file_content->Name = L"file_content";
			this->file_content->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->file_content->Size = System::Drawing::Size(928, 430);
			this->file_content->TabIndex = 2;
			// 
			// run_yo
			// 
			this->run_yo->Font = (gcnew System::Drawing::Font(L"宋体", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->run_yo->Location = System::Drawing::Point(667, 483);
			this->run_yo->Name = L"run_yo";
			this->run_yo->Size = System::Drawing::Size(163, 39);
			this->run_yo->TabIndex = 3;
			this->run_yo->Text = L".yo-run";
			this->run_yo->UseVisualStyleBackColor = true;
			this->run_yo->Click += gcnew System::EventHandler(this, &MyForm1::run_Click);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// ys
			// 
			this->ys->Location = System::Drawing::Point(146, 549);
			this->ys->Name = L"ys";
			this->ys->Size = System::Drawing::Size(210, 28);
			this->ys->TabIndex = 5;
			// 
			// show_ys
			// 
			this->show_ys->Font = (gcnew System::Drawing::Font(L"幼圆", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->show_ys->Location = System::Drawing::Point(409, 547);
			this->show_ys->Name = L"show_ys";
			this->show_ys->Size = System::Drawing::Size(178, 38);
			this->show_ys->TabIndex = 6;
			this->show_ys->Text = L".ys-show";
			this->show_ys->UseVisualStyleBackColor = true;
			this->show_ys->Click += gcnew System::EventHandler(this, &MyForm1::show_ys_Click_1);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(72, 494);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 24);
			this->label1->TabIndex = 7;
			this->label1->Text = L".yo:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label2->Location = System::Drawing::Point(72, 547);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(58, 24);
			this->label2->TabIndex = 8;
			this->label2->Text = L".ys:";
			// 
			// run_ys
			// 
			this->run_ys->Font = (gcnew System::Drawing::Font(L"宋体", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->run_ys->Location = System::Drawing::Point(667, 547);
			this->run_ys->Name = L"run_ys";
			this->run_ys->Size = System::Drawing::Size(163, 38);
			this->run_ys->TabIndex = 9;
			this->run_ys->Text = L".ys-run";
			this->run_ys->UseVisualStyleBackColor = true;
			this->run_ys->Click += gcnew System::EventHandler(this, &MyForm1::run_ys_Click_1);
			// 
			// MyForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->ClientSize = System::Drawing::Size(1378, 687);
			this->Controls->Add(this->run_ys);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->show_ys);
			this->Controls->Add(this->ys);
			this->Controls->Add(this->run_yo);
			this->Controls->Add(this->file_content);
			this->Controls->Add(this->yo);
			this->Controls->Add(this->show_yo);
			this->Name = L"MyForm1";
			this->Text = L"Entrance";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		char * str_to_ch(String^ s)
		{
			return (char*)(void*)Marshal::StringToHGlobalAnsi(s);
		}
		String^ ch_to_str(char *c)
		{
			return  Marshal::PtrToStringAnsi((IntPtr)(char *)c);
		}
		/*String^ ll_to_str(ul ull)
		{
			uc * c = long2charArr(ull);
			String^ str;
			str = ch_to_str(c);
			return str;
		}*/
		String^ in_to_str(int num)
		{
			char s[25];
			_itoa_s(num, s, 16);
			return ch_to_str(s);
		}
		int str_to_in(String^ s)
		{
			int num;
			char* c = str_to_ch(s);
			return atoi(c);
		}
		void load_file(char* file_name)
		{
			FILE* fp = fopen(file_name, "r");
			char line[1024];
			while (fgets(line, sizeof(line), fp) != NULL)
			{
				String^ s = ch_to_str(line);
				file_content->Text += s + "\r\n";
			}
		}
		/*fopen_s(&object_file, file_name, "r");
			char *pchBuf;
			int nLen;
			FILE* fp = object_file;
			fseek(fp, 0, SEEK_END);//文件指针移到文件尾
			nLen = ftell(fp); //得到当前指针位置, 即是文件的长度
			fseek(fp, 0, SEEK_SET);//文件指针恢复到文件头位置
			//rewind(fp); 
			pchBuf = (char*)malloc(sizeof(char)*nLen + 1);
			nLen = fread(pchBuf, sizeof(char), nLen, fp);
			fclose(fp);
			pchBuf[nLen] = '\0'; //添加字符串结尾标志
			return pchBuf;*/
private: System::Void show_yo_Click_1(System::Object^  sender, System::EventArgs^  e) {
	file_content->Text = "";
	char* str = str_to_ch(yo->Text);//String 转 char*
	load_file(str);//加载文件
}
private: System::Void show_ys_Click_1(System::Object^  sender, System::EventArgs^  e) {
	file_content->Text = "";
	char* str = str_to_ch(ys->Text);//String 转 char*
	load_file(str);//加载文件
}
private: System::Void run_Click(System::Object^  sender, System::EventArgs^  e) {
	MyForm^ f2 = gcnew MyForm();
	f2->str = yo->Text;
	char* s = str_to_ch(f2->str);
	load_yo(s);
	f2->cyclenum = 0;
	f2->ShowDialog();
}
private: System::Void run_ys_Click_1(System::Object^  sender, System::EventArgs^  e) {
	MyForm^ f2 = gcnew MyForm();
	f2->str = ys->Text;
	char* s = str_to_ch(f2->str);
	load_ys(s);
	f2->cyclenum = 0;
	f2->ShowDialog();
}
};
}
#endif
