#include <atomic>
#include <thread>
#include <memory>

template <typename T>
class lock_free_stack
{
private:
	struct  node
	{
		std::shared_ptr<T> data;
		node *next;
		node(T const &data_):data(std::make_shared<T>(data_)),next(nullptr){}
	};
	std::atomic<node *> head;
public:
	lock_free_stack():head(nullptr){}
	void push( T const &data)
	{
		node *const new_node=new node(data);
		new_node->next=head.load();
		while(!head.compare_exchange_weak(new_node->next,new_node));
	}

	std::shared_ptr<T> pop()
	{
		node *pn=head.load();
		while(!pn &&!head.compare_exchange_weak(pn,pn->next));
		std::shared_ptr<T> a= pn?pn->data:std::shared_ptr<T>();
		return a;
		//此处内存泄露，pn节点没有删除
	}


};



void th1()
{

}

void th2()
{

}

int main()
{

	std::thread t1(th1);
	std::thread t2(th2);
	t1.join();
	t2.join();

	return 0;
}



