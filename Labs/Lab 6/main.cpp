#include<iostream>
#include "log.hpp";

//Разработайте класс для логирования работы программы.
//Предусмотрите следующие возможности :
//1. Вывод в консоль и в файл
//2. Возможность отключения части логов
//3. Логи разного уровня(Info, Debug, Error и т.п.)
//4. Вывод времени записи лога


int main()
{
	Log::SetLogPath("log.txt");
	Log::SetLogLevel(LogLevel::DEBUG); // DEBUG: Debug и Trace; RELEASE: Info, Warn, Error, Fatal
	
	Log::Debug("Debug . . .");
	Log::Trace("Trace . . .");
	Log::Info("Info . . .");
	Log::Warn("Warn . . .");
	Log::Error("Error . . .");
	Log::Fatal("Fatal . . .");


}