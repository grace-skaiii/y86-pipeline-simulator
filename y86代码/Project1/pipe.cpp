#include "Entrance.h"
#include"mm.h"
#include<string>
#include <sstream>
using namespace Project1;//ʹ��MyForm.h�ж��������ռ�
using namespace std;
[STAThread]//���߳����ԣ���Щ���Ҫ���߳�

int main(cli::array<System::String^>^args)
{
	Application::EnableVisualStyles();//���ÿ��ӻ����棬��Ȼ����ѿ�
	//Application::Run(gcnew MyForm());//����һ�����壬��������Ϣѭ��
	MyForm1^ f1 = gcnew MyForm1();
	f1->ShowDialog();
	return 0;
}



