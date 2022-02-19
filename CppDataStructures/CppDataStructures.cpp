
#include <iostream>
#include "stack.h"
#include "queue.h"
#include "linkedlist.h"
#include "BinarySearchTree.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <math.h>
#include <algorithm>
#include <map>
#include "HeapSort.h"


using namespace algo;

struct CoordinateNode {
	std::pair<int, int> coordinates;
	int value;

	bool operator<(const CoordinateNode& comp) const {
		if (this->coordinates.first < comp.coordinates.first) {
			return true;
		}
		else if ((this->coordinates.first == comp.coordinates.first) && (this->coordinates.second < comp.coordinates.second)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator>(const CoordinateNode& comp) const {
		if (this->coordinates.first > comp.coordinates.first) {
			return true;
		}
		else if ((this->coordinates.first == comp.coordinates.first) && (this->coordinates.second > comp.coordinates.second)) {
			return true;
		}
		else {
			return false;
		}
	}
};

void gameOfLife();
algo::BinarySearchTree<CoordinateNode> readToTree(std::string& fileName);

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

	std::cout << "TESTING BST ----------------------" << std::endl;

	algo::BinarySearchTree<CoordinateNode> tree;
	for (int l = 0; l < 100; l++)
	{
		CoordinateNode tempNode;
		
		std::pair<int, int> temp;
		temp.first = l;
		temp.second = l + 5;
		tempNode.coordinates = temp;
		tempNode.value = l % 2 == 0 ? 1 : 0;
		tree.insert(tempNode);
		//tree.insert(random_range(1,250));
	}

	CoordinateNode node;
	node.coordinates = std::pair<int, int>(0, 1);
	node.value = 0;
	bool contained = tree.contains(node);
	gameOfLife();

	//tree.printTree();

	std::cout << "TESTING HEAP SORT ----------------------" << std::endl;
	int arr[] = { 4,2,3,1,5,6,8, };
	for (int a = 0; a < 7; ++a) {
		std::cout << arr[a] << " ";
	}
	std::cout << std::endl;
	std::cout << "SORTED:" << std::endl;

	algo::heap_sort(arr, 7);
	for (int d = 0; d < 7; d++) {
		std::cout << arr[d] << " ";
	}
	std::cout << std::endl;

	return 0;
}


void gameOfLife() {
	std::string fileName = "C:\\Users\\David Hoefs\\source\\repos\\GameOfLifeConsole\\GameOfLifeConsole\\6x6step.dat";
	algo::BinarySearchTree<CoordinateNode> gameTree = readToTree(fileName);

}

algo::BinarySearchTree<CoordinateNode> readToTree(std::string& fileName) {
	std::fstream in = std::fstream(fileName);
	
	char c;
	int x = 0, y = 0;
	algo::BinarySearchTree<CoordinateNode> output;
	if (in.is_open()) {
		while (in.good()) {
			if (x == 99 && y == 100)
				break;
			CoordinateNode node;
			if (y == 100) {
				y = 0;
				x++;
			}

			node.coordinates.first = x;
			node.coordinates.second = y;
			in.get(c);
			if (c == 'O') {
				node.value = 1;
				output.insert(node);
				y++;
			}
			else if (c == '.') {
				node.value = 0;
				output.insert(node);
				y++;
			}
		}
	}

	in.close();

	return output;
}