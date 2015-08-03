#include <future>
#include <iostream>
#include <chrono>


struct  A
{
	A(){}
	A & operator =(const A&a){std::cout<<"="<<std::endl;return *this;}
	A(const A&a){std::cout<<"copy"<<std::endl;}
	A(const A&&a){std::cout<<"move"<<std::endl;}

};

int find_the_answer_of_ltuae(int a,int b)
{

	A *p=new A;
	std::cout<<p<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(4));
	throw p;
	return a+b;
}


void do_other_stuff()
{

}

int main()
{

	std::future<int> the_answer=std::async(find_the_answer_of_ltuae,6,7);
	do_other_stuff();
	try
	{
		std::cout<<the_answer.get()<<std::endl;
	}
	catch(A *e)
	{
		std::cout<<e<<std::endl;
		std::current_exception();

	}


}
