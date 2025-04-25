#include "MyForm.h"
//пр им
using namespace PressureApp;
using namespace System;
using namespace System::Windows::Forms;
//копирует, отк файл
//Возвращает количество предоставляемых объектом интерфейсов для доступа к сведениям о типе
[STAThreadAttribute]
int main()
{
    //стиль отображения для эл
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    //gcnew  создаёт объект
    Application::Run(gcnew MyForm());
    return 0;
}
