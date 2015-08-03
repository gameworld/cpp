#include <thread>
#include <future>
#include <iostream>
#include <exception>
#include <chrono>

using namespace std;

int foo(std::shared_future<int> &fu)
{
	std::cout<<fu.get()<<std::endl;
	return 0;
}

int foo2(std::shared_future<int> &fu)
{
	std::cout<<fu.get()<<std::endl;
	return 0;
}


int main()
{

	std::promise<int> a;
	auto sf1=std::shared_future<int>(std::move(a.get_future()));
	auto sf2=std::shared_future<int>(sf1);
	std::thread t(foo,std::ref(sf1));
	std::thread t2(foo2,std::ref(sf2));

	a.set_value(5);

	t.join();
	t2.join();

	std::chrono::hours  ha(5);
	std::chrono::seconds sa(80);
	std::chrono::minutes fa=ha-sa;
	cout<<fa.count();

//	cout<<chrono::system_clock::now();
}


