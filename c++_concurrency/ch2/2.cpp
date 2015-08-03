#include <thread>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;
struct A
{

};


void f(const int i, std::string  &str,A a)
{
	cout<<str<<endl;
	str="result";
}

int main()
{
	string s="fwfe";
	{
			thread t(f,1,std::ref(s),A());

			t.detach();
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));

	cout<<s<<endl;

}
