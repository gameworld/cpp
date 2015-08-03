
#include <iostream>
#include <future>
#include <thread>

using namespace std;

using X=int;

void f1(promise<X> &px)
{
	try
	{


			X res=8;
			this_thread::sleep_for(chrono::seconds(2));
			px.set_value(res);


	}
	catch(...)
	{

	}

}

void f2(future<X> &fx)
{


	X a=fx.get();
	cout<<a<<endl;

}


int main()
{

	promise<X> a;

	future<X> fu=a.get_future();
	thread t1(f1,ref(a));

	thread t2(f2,ref(fu));


	t1.join();
	t2.join();

}
