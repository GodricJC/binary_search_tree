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
	bst.inorder_nr(cout);
	cout << endl;
	bst.preorder_r(cout);
	cout << endl;
	bst.preorder_nr(cout);
	cout << endl;
	bst.postorder_r(cout);
	cout << endl;
	system("pause");
	return 0;
}

