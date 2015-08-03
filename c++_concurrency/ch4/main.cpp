
#include "threadsafequeue.h"
#include <thread>
#include <iostream>
#include <chrono>


void push_func(threadsafe_queue<int> &c)
{
	int i=0;
	while(1)
	{
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		c.push(i++);
	}

}

int main()
{


	threadsafe_queue<int>  tqueue;

	std::thread t(push_func,std::ref(tqueue));
	std::thread t2(push_func,std::ref(tqueue));
	std::thread t3(push_func,std::ref(tqueue));
	std::thread t4(push_func,std::ref(tqueue));

	while(1)
	{
		int c;
		tqueue.wait_and_pop(c) ;
		std::cout<<c<<std::endl;

	}


	t.join();
	t2.join();
	t3.join();
	t4.join();
}
