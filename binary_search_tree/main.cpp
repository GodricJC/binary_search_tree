// binary_search_tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "binary_search_tree.h"
#include <iostream>

using namespace std;

class R
{
public:
	shared_ptr<R> p_;
	~R()
	{}
};

int _tmain(int argc, _TCHAR* argv[])
{
	BinarySearchTree<int> bst;
	for (int i = 5; i < 10; i++)
	{
		bst.insert(i);
		bst.insert(10 - i);
	}

	// tree walk test
	bst.inorder_r(cout);
	cout << endl;
	bst.inorder_nr(cout);
	cout << endl;
	bst.preorder_r(cout);
	cout << endl;
	bst.preorder_nr(cout);
	cout << endl;
	bst.postorder_r(cout);
	cout << endl;
	bst.postorder_nr(cout);
	cout << endl;

	// search test
	auto n1 = bst.search_r(11);
	auto n2 = bst.search_nr(11);
	if (n1)
		cout << *n1 << endl;
	if (n2)
		cout << *n2 << endl;

	// min/max test
	cout << bst.maxV() << endl;
	cout << bst.minV() << endl;

	// successor
	for (int i = 1; i < 10; i++)
		cout << bst.successor(i) << " ";
	cout << endl;

	// predecessor
	for (int i = 2; i < 9; i++)
		cout << bst.predecessor(i) << " ";
	cout << endl;

	system("pause");	
	return 0;
}

