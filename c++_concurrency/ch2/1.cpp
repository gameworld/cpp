#include <thread>
#include <chrono>
#include <iostream>

void foo()
{

	int i=0;
	while(1)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));

		std::cout<<i++<<std::endl;
		if(i==20)
			break;
	}
}



int main()
{
		std::thread t(foo);
		t.detach();
}
