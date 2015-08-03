#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

/*
 * 要死锁
 */
using namespace std;


mutex m1;
mutex m2;

int i=0;

void f1()
{
	while(1)
	{
			unique_lock<mutex> lck(m1);
			sleep(1); //故意休眠1秒
			unique_lock<mutex> lck2(m2);
			i++;
			sleep(1);
			cout<<i<<endl;
	}
}


void f2()
{
	while(1)
	{
		unique_lock<mutex> lck(m2);
		sleep(1);//故意休眠1秒
		unique_lock<mutex> lck2(m1);
		i++;
		sleep(1);
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

