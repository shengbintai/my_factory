#include "myFactory.h"

MyFactory::MyFactory() :
	m_isIntialized(false),
	m_isStarted(false)
{
}

MyFactory::~MyFactory()
{
}
int MyFactory::startProduct()
{
	if (m_isIntialized)
	{
		return -1;
	}
	m_dataList.clear();
	m_isIntialized = true;

	//生产者线程
	m_producerThread = thread([this]() {
		while (m_isIntialized)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::unique_lock <std::mutex> lck(m_mtx);

			//处理业务
			auto d = system_clock::now().time_since_epoch();
			auto sec = duration_cast<seconds>(d);
			m_dataList.push_back(sec.count());
			m_cv.notify_all();
			cout << "product thread notify all..." << endl;
		}
	});

	return 0;
}

int MyFactory::stopProduct()
{
	m_isIntialized = false;
	m_producerThread.join();
	return 0;
}

int MyFactory::startConsume(const NofityProc& proc)
{
	//消费者
	if (m_isStarted)
	{
		return -1;
	}
	m_isStarted = true;

	m_consumerThread = thread([this, &proc] {
		while (m_isStarted)
		{
			std::unique_lock <std::mutex> lck(m_mtx);
			while (m_dataList.empty())
			{
				m_cv.wait(lck);
			}
			//消费数据data
			auto data = m_dataList.front();
			m_dataList.pop_front();
			lck.unlock();
			//传出消费数据/通知消费结果
			if (proc)
			{
				proc(data);
			}
		}
	});

	return 0;
}

int MyFactory::stopConsume()
{
	m_isStarted = false;
	m_consumerThread.join();
	return 0;
}
