#include <string>
#include <iostream>

struct pass
{
	template <typename ... args>
	pass(args...){}
};





void _print(int a)
{
	std::cout<<a<<std::endl;
}

void _print(std::string a)
{
	std::cout<<a<<std::endl;
}
void _print(const char *a)
{
	std::cout<<a<<std::endl;
}

template <typename ... args>
void print(args  ... arg)
{
	pass{(_print(arg),1)...};
}

int main()
{
	print("hello",2,2,3);

}

