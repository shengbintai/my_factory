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
	thread m_producerThread;				//生产者线程
	thread m_consumerThread;				//消费者线程
	bool m_isIntialized;
	bool m_isStarted;
	mutex m_mtx;							// 全局互斥锁.
	condition_variable m_cv;				// 全局条件变量.

	list<int> m_dataList;
};