#include<iostream>
#include "log.hpp";

//������������ ����� ��� ����������� ������ ���������.
//������������� ��������� ����������� :
//1. ����� � ������� � � ����
//2. ����������� ���������� ����� �����
//3. ���� ������� ������(Info, Debug, Error � �.�.)
//4. ����� ������� ������ ����


int main()
{
	Log::SetLogPath("log.txt");
	Log::SetLogLevel(LogLevel::DEBUG); // DEBUG: Debug � Trace; RELEASE: Info, Warn, Error, Fatal
	
	Log::Debug("Debug . . .");
	Log::Trace("Trace . . .");
	Log::Info("Info . . .");
	Log::Warn("Warn . . .");
	Log::Error("Error . . .");
	Log::Fatal("Fatal . . .");


}