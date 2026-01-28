#pragma once
#include <string>
#include <iostream>
class Log
{
public:
	static Log& instance()
	{
		static Log log;
		return log;
	}

	static void print(const std::string& text) {
		std::cout << text << "\n";
	}

private:
	Log() = default;
	Log(const Log&) = delete;
	Log& operator = (const Log&) = delete;
};

