
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void f(vector<double> & v  )
{
	std::cout<<"hello";
	for(auto i:v)
	{
		cout<<i<<" ";
	}
	cout<<endl;
}

struct F
{
	vector<double>& v;
	F(vector<double> &v):v(v){}
	void operator( )()
	{
		std::cout<<" parallel world!\n";
		for(auto i:v)
		{
			cout<<i<<"  ";
		}
		cout<<endl;
	}
};



void user()
{

	vector<double> some_vec{1,2,3,4,5};
	vector<double > vec2{10,11,12,13,14};

	thread t1{f,ref(some_vec)};
	thread t2{F(vec2)};

	t1.join();
	t2.join();
}

int main()
{
	user();
	return 0;
}
