#include "Entrance.h"
#include"mm.h"
#include<string>
#include <sstream>
using namespace Project1;//使用MyForm.h中定义的命令空间
using namespace std;
[STAThread]//单线程特性，有些组件要求单线程

int main(cli::array<System::String^>^args)
{
	Application::EnableVisualStyles();//启用可视化界面，不然会很难看
	//Application::Run(gcnew MyForm());//创建一个窗体，并进入消息循环
	MyForm1^ f1 = gcnew MyForm1();
	f1->ShowDialog();
	return 0;
}



