#include <iostream>
#include <stdlib.h>
#include <utility>


template<class  T >
void QuickSort(T  arr[],size_t  begin,size_t  end)
{

	if(begin>=end )
	{
		return ;
	}

	T key=arr[begin];
	size_t i=begin;
	size_t j=end;

	while(j>i)
	{
		while(arr[j]>=key and j>i)
			j--;

		arr[i]=arr[j];

		while(arr[i]<=key and j>i)
			i++;
		arr[j]=arr[i];

	}
	arr[i]=key;

	QuickSort(arr,begin,i-1);

	QuickSort(arr,i+1,end);

}


int main()
{

	int a[]={5,1,9,8,4,12,63,95,23};
	//4,1,9,8,5,12,63,95,23
	//4,1,5,8,9,12,63,95,23


	QuickSort(a,0,sizeof(a)/sizeof(a[0])-1);

	for(auto i:a)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;

}
