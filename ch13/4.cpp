
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void f(const vector<double> & v,double *res  )
{
	std::cout<<"hello";
	for(auto i:v)
	{
		cout<<i<<" ";
	}
	cout<<endl;

	*res=8;
}

struct F
{
	const vector<double>& v;
	double *res;
	F(const vector<double> &v,double *res):v(v),res(res){}
	void operator( )()
	{
		std::cout<<" parallel world!\n";
		for(auto i:v)
		{
			cout<<i<<"  ";
		}
		cout<<endl;
		*res=10;
	}
};



void user()
{
	double res1;
	double res2;
	vector<double> some_vec{1,2,3,4,5};
	vector<double > vec2{10,11,12,13,14};

	//thread t1{f,cref(some_vec),&res1};
	thread t1(f,cref(some_vec),&res1);
	thread t2{F{vec2,&res2}};

	t1.join();
	t2.join();

    cout<<"res1: "<<res1<<endl;
	cout<<"res2 :"<<res2<<endl;
}

int main()
{
	user();
	return 0;
}
