#include "MyForm.h"
//�� ��
using namespace PressureApp;
using namespace System;
using namespace System::Windows::Forms;
//��������, ��� ����
//���������� ���������� ��������������� �������� ����������� ��� ������� � ��������� � ����
[STAThreadAttribute]
int main()
{
    //����� ����������� ��� ��
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    //gcnew  ������ ������
    Application::Run(gcnew MyForm());
    return 0;
}
