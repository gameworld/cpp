#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

/*
 * 解决死锁
 */
using namespace std;


mutex m1;
mutex m2;

int i=0;

void f1()
{
	while(1)
	{
			//unique_lock<mutex> lck(m1);
			unique_lock<mutex> lck(m1,defer_lock);

			this_thread::sleep_for(chrono::seconds(1));
			//sleep(1); //故意休眠1秒
			//unique_lock<mutex> lck2(m2);
			unique_lock<mutex> lck2(m2,defer_lock);

			lock(lck2,lck);
			i++;
			this_thread::sleep_for(chrono::seconds(1));
			cout<<i<<endl;
	}
}


void f2()
{
	while(1)
	{
		//unique_lock<mutex> lck(m2);
		unique_lock<mutex> lck(m2,defer_lock);
		this_thread::sleep_for(chrono::seconds(1));;//故意休眠1秒
		//unique_lock<mutex> lck2(m1);
		unique_lock<mutex> lck2(m1,defer_lock);

		lock(lck2,lck);
		i++;
		this_thread::sleep_for(chrono::seconds(1));
		cout<<i<<endl;
	}
}

int main()
{

	thread t1(f1);
	thread t2(f2);

	t1.join();
	t2.join();
}

