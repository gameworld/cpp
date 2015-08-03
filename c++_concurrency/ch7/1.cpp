#include <iostream>
#include <atomic>
#include <thread>


class spinlock_mutex
{
	std::atomic_flag  flag;
public:
	spinlock_mutex():flag(ATOMIC_FLAG_INIT){}

	void lock()
	{
		while(flag.test_and_set(std::memory_order_acquire));
	}

	void unlock()
	{
		flag.clear(std::memory_order_release);
	}
};


int i=0;
spinlock_mutex mut;
void th1()
{
	for(int i=0;i<10000;i++)
	{
		mut.lock();
		::i++;
		mut.unlock();
	}

}
void th2()
{
	for(int i=0;i<10000;i++)
	{
		mut.lock();
		::i++;
		mut.unlock();
	}

}

int main()
{
	std::thread t1(th1);
	std::thread t2(th2);

	t1.join();
	t2.join();

	std::cout<<i<<std::endl;


}
