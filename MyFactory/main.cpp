#pragma once
#pragma execution_character_set("utf-8")

#include <iostream>
#include "myFactory.h"

using namespace std;

int main()
{
	cout << "Hello world!" << endl;


	MyFactory mf;
	auto ret = mf.startProduct();
	if (0 != ret)
	{
		return -1;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	NofityProc proc = [](const int& data) {
		cout << "data:" << data << endl;
	};
	ret = mf.startConsume(proc);
	if (0 != ret)
	{
		return -1;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	ret = mf.stopConsume();
	if (0 != ret)
	{
		return -1;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	ret = mf.stopProduct();
	if (0 != ret)
	{
		return -1;
	}

	cout << "return from main()" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	return 0;
}