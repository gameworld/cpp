#include <iostream>
#include <thread>
#include <condition_variable>




int main()
{
	std::cout<<std::thread::hardware_concurrency()<<std::endl;
}
