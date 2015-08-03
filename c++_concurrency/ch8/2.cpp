#include <thread>
#include <list>
#include <stack>
#include <memory>
#include <mutex>
#include <atomic>
#include <vector>
#include <future>
#include <iostream>
#include <algorithm>
#include <exception>
#include <fstream>
#include <string>
//#include "thread_safe_stack.h"


struct empty_stack: std::exception
{
    const char* what() const throw()
    {
        return "empty stack";
    }
};

template<typename T>
class thread_safe_stack
{
private:
	std::stack< std::shared_ptr<T> > data;
	std::mutex m_;
public:
	thread_safe_stack(){}
//    thread_safe_stack(const thread_safe_stack& other)
//    {
//        std::lock_guard<std::mutex> lock(other.m_);
//        data=other.data;
//    }
//    thread_safe_stack& operator=(const thread_safe_stack&) = delete;
	void push(T data )
	{
		std::lock_guard<std::mutex> lk(m_);
		this->data.push(std::make_shared<T>(std::move(data)));
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lk(m_);
		if(data.empty())
		{
			return std::shared_ptr<T>();
		}
		else
		{
	        std::shared_ptr<T>  res=data.top();
			data.pop();
			return res;
		}

	}

//    void pop(T& value)
//    {
//        std::lock_guard<std::mutex> lock(m_);
//        if(data.empty()) throw empty_stack();
//        value=std::move(data.top());
//        data.pop();
//    }
};


/*
template<typename T>
struct sorter
{
	struct chunk_to_sort
	{
		std::list<T> data;
		std::promise<std::list<T> > promise;
	};

	thread_safe_stack<chunk_to_sort> chunks;
	std::vector<std::thread> threads;
	unsigned const max_thread_count;
	std::atomic<bool> end_of_data;

	sorter():max_thread_count(std::thread::hardware_concurrency()-1),end_of_data(false){}

	~sorter()
	{
		end_of_data=true;
		for(unsigned i=0;i<threads.size();i++)
		{
			threads[i].join();
		}
	}

	void try_sort_chunk()
	{
		std::shared_ptr<chunk_to_sort> chunk=chunks.pop();
		if(chunk)
		{
			sort_chunk(chunk);
		}
	}

	std::list<T> do_sort(std::list<T> &chunk_data)
	{
		if(chunk_data.empty())
		{
			return chunk_data;
		}

		std::list<T>  result;
		result.splice(result.begin(),chunk_data,chunk_data.begin());
		T const &partition_val=*result.begin();

		typename std::list<T>::iterator divide_point=std::partition(chunk_data.begin(),chunk_data.end(),[&](T const &val ){return val < partition_val;});

		chunk_to_sort new_lower_chunk;
		new_lower_chunk.data.splice(new_lower_chunk.data.end(),chunk_data,chunk_data.begin(),divide_point);

		std::future<std::list<T> > new_lower=new_lower_chunk.promise.get_future();
		chunks.push(std::move(new_lower_chunk));

		if(threads.size()<max_thread_count)
		{
			threads.push_back(std::thread(&sorter<T>::sort_thread,this));
		}

		std::list<T> new_higher(do_sort(chunk_data));

		result.splice(result.end(),new_higher);
		while(new_lower.wait_for(std::chrono::seconds(0))!=std::future_status::ready)
		{
			try_sort_chunk();
		}
		result.splice(result.begin(),new_lower.get());
		return result;
	}

	void sort_chunk(std::shared_ptr<chunk_to_sort> const &chunk)
	{
		chunk->promise.set_value(chunk->data);
	}
	void sort_thread()
	{
		while(!end_of_data)
		{
			try_sort_chunk();
			std::this_thread::yield();
		}
	}
};

template<typename T>
std::list<T> parallel_quick_sort( std::list<T>  input)
{
	if(input.empty())
	{
		return input;
	}

	sorter<T> a;
	return a.do_sort(input);
}

*/

#include <iostream>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <cassert>


template<class  T >
void QuickSort(std:: vector<T>  &arr,size_t  begin,size_t  end)
{
	assert(begin>=0);
	assert(end<=arr.size());

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

	if(i>1)
		QuickSort(arr,begin,i-1);

	QuickSort(arr,i+1,end);

}


template<typename T>
struct sorter
{
    struct chunk_to_sort
    {
        std::list<T> data;
        std::promise<std::list<T> > promise;
    };

    thread_safe_stack<chunk_to_sort> chunks;
    std::vector<std::thread> threads;
    unsigned const max_thread_count;
    std::atomic<bool> end_of_data;

    sorter():
        max_thread_count(std::thread::hardware_concurrency()),
        end_of_data(false)
    {}

    ~sorter()
    {
        end_of_data=true;
        for(unsigned i=0;i<threads.size();++i)
        {
            threads[i].join();
        }
    }

    void try_sort_chunk()
    {
       std::shared_ptr<chunk_to_sort > chunk=chunks.pop();
        if(chunk)
        {
            sort_chunk(chunk);
        }
    }

    std::list<T> do_sort(std::list<T>& chunk_data)
    {
        if(chunk_data.empty())
        {
            return chunk_data;
        }

        std::list<T> result;
        result.splice(result.begin(),chunk_data,chunk_data.begin());
        T const& partition_val=*result.begin();

        typename std::list<T>::iterator divide_point=
            std::partition(chunk_data.begin(),chunk_data.end(),
                           [&](T const& val){return val<partition_val;});
        chunk_to_sort new_lower_chunk;
        new_lower_chunk.data.splice(new_lower_chunk.data.end(),
                                    chunk_data,chunk_data.begin(),
                                    divide_point);

        std::future<std::list<T> > new_lower=
            new_lower_chunk.promise.get_future();
        chunks.push(std::move(new_lower_chunk));
        if(threads.size()<max_thread_count)
        {
            threads.push_back(std::thread(&sorter<T>::sort_thread,this));
        }

        std::list<T> new_higher(do_sort(chunk_data));

        result.splice(result.end(),new_higher);
        while(new_lower.wait_for(std::chrono::seconds(0)) !=
              std::future_status::ready)
        {
            try_sort_chunk();
        }

        result.splice(result.begin(),new_lower.get());
        return result;
    }

    void sort_chunk(std::shared_ptr<chunk_to_sort > const& chunk)
    {
        chunk->promise.set_value(do_sort(chunk->data));
    }

    void sort_thread()
    {
        while(!end_of_data)
        {
            try_sort_chunk();
            std::this_thread::yield();
        }
    }
};

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
    if(input.empty())
    {
        return input;
    }
    sorter<T> s;
    return s.do_sort(input);
}


int main()
{
	std::fstream in("number.txt");

	std::vector<uint64_t>  a;
	std::string str;
	while(std::getline(in,str))
	{
		a.push_back(atoll(str.c_str()));
	}

	std::ofstream out("sorted_number.txt");
	std::cout<<a.size()<<std::endl;

	QuickSort(a,0,a.size());

	for(auto i:a)
	{
		out<<i<<std::endl;
	}
}
