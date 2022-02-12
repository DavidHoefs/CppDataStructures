#include <iostream>
#include "stack.h"
#include "queue.h"
#include "linkedlist.h"
using namespace algo;

int main()
{
    std::cout << "STACK" << std::endl;
    algo::Stack<double> st{ 10 };
	for (int i = 0; i < 10; i++)
	{
		st.push(i);
	}
	st.print();
	std::cout << "NEXT" << std::endl;
	while (!st.empty()) {
		std::cout << st.top() << " ";
		st.pop();
	}

	while (st.size() > 0) {
		std::cout << st.top() << " ";
		st.pop();
	}

	std::cout << std::endl;

	std::cout << "----------------------------" << std::endl;
	std::cout << "QUEUE" << std::endl;
	const int QUEUE_SIZE = 10;
	algo::Queue<int> Q(QUEUE_SIZE);
	std::cout << "PUSH TO QUEUE" << std::endl;

	for (int j = 0; j < QUEUE_SIZE; j++)
	{
		Q.push(j);
	}

	std::cout << "Size of QUEUE is: " << Q.count() << std::endl;
	while (!Q.empty()) {
		std::cout << Q.front() << " ";
		Q.pop();
	}
	std::cout << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "LINKED LIST" << std::endl;

	const int N = 20;
	List<int> lst;

	for (int l = N - 1; l > 0; l--)
	{
		lst.pushFront(l);

	}

	lst.print(lst);


	std::cout << "TESTING LIST ----------------------" << std::endl;
	algo::List<char> nodeList;

	nodeList.pushBack('t');
	nodeList.pushBack('o');
	nodeList.pushBack('t');
	nodeList.pushBack('t');
	nodeList.pushBack('o');



	
	nodeList.printList(nodeList);
	std::string output = nodeList.isPalindrome() == 1 ? "TRUE" : "FALSE";
	std::cout << "Palindrome?: " << output << std::endl;
	
	

	return 0;

}

