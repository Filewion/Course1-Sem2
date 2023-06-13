#pragma once
#include <fstream>
#include <iostream>
#include <time.h>

enum class LogLevel
{
	DEBUG,
	RELEASE
};
class Log
{
private:
	static std::ofstream m_out; 
	static LogLevel m_logLevel;
	static std::time_t now;
public:
	Log() = default;

	static void SetLogLevel(LogLevel logLevel) 
	{
		m_logLevel = logLevel;
	}
	static void SetLogPath(const std::string& path)
	{
		m_out.open(path);
	}

	static void Debug(const std::string& msg) // ���������� ���������
	{
		if (m_logLevel == LogLevel::DEBUG)
		{
			now = time(nullptr);
			std::cerr << ctime(&now)<< msg << std::endl;
			m_out << ctime(&now) << msg << std::endl;
			m_out.flush();
		}

	}
	static void Trace(const std::string& msg) // ����� ��������, ������ Debug
	{
		if (m_logLevel == LogLevel::DEBUG)
		{
			now = time(nullptr);
			std::cerr << ctime(&now) << msg << std::endl;
			m_out << ctime(&now) << msg << std::endl;
			m_out.flush();
		}

	}
	static void Info(const std::string& msg) // �������������� ��������� 
	{
		now = time(nullptr);
		if (m_logLevel == LogLevel::RELEASE)
		{
			now = time(nullptr);
			std::cerr << ctime(&now) << msg << std::endl;
			m_out << ctime(&now) << msg << std::endl;
			m_out.flush();
		}
	}
	static void Warn(const std::string& msg) // �������������� � ������������� ��������
	{
		if (m_logLevel == LogLevel::RELEASE)
		{
			now = time(nullptr);
			std::cerr << ctime(&now) << msg << std::endl;
			m_out << ctime(&now) << msg << std::endl;
			m_out.flush();
		}
	}
	static void Error(const std::string& msg) // ������, �� ���������� � ����� ���������� 
	{
		if (m_logLevel == LogLevel::RELEASE)
		{
			now = time(nullptr);
			std::cerr << ctime(&now) << msg << std::endl;
			m_out << ctime(&now) << msg << std::endl;
			m_out.flush();
		}
	}
	static void Fatal(const std::string& msg) // ������, ���������� � ����� ���������� / ������ ������ 
	{
		if (m_logLevel == LogLevel::RELEASE)
		{
			now = time(nullptr);
			std::cerr << ctime(&now) << msg << std::endl;
			m_out << ctime(&now) << msg << std::endl;
			m_out.flush();
		}
	}
	~Log() = default;
};
