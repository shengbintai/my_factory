#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <chrono>

using namespace std;
using namespace chrono;

typedef std::function<void(const int&)> NofityProc;

class MyFactory
{
public:
	MyFactory();
	virtual ~MyFactory();
	int startProduct();
	int stopProduct();

	int startConsume(const NofityProc& proc);
	int stopConsume();

private:
	thread m_producerThread;				//�������߳�
	thread m_consumerThread;				//�������߳�
	bool m_isIntialized;
	bool m_isStarted;
	mutex m_mtx;							// ȫ�ֻ�����.
	condition_variable m_cv;				// ȫ����������.

	list<int> m_dataList;
};