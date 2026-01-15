#pragma once
#include <string>
#include <iostream>
class Log
{
public:
	static void print(const std::string& text) {
		std::cout << text << "\n";
	}
};

