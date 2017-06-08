// SearchBinaryTree.cpp : 定义控制台应用程序的入口点。
//
#include"SearchBinaryTree.h"
void test1()
{
	int array[] = { 5, 3, 7, 1, 4, 6, 8, 0, 2, 9 };
	size_t size = sizeof(array) / sizeof(array[0]);
	SearchBinaryTree<int>sbt;
	for (size_t i = 0; i < size; i++)
	{
		sbt.Insert(array[i]);
	}
	sbt.InOrder();
	cout << "Find 4 ?" << sbt.Find(4) << endl;
	cout << "Find 6 ?" << sbt.Find(6) << endl;
	cout << "Find 10 ?" << sbt.Find(10) << endl;
	sbt.Remove(7);
	sbt.InOrder();   //0 1 2 3 4 5 6 8 9
	sbt.Remove(5);
	sbt.InOrder();   //0 1 2 3 4 6 8 9

	sbt.Remove(0);
	sbt.Remove(1);
	sbt.Remove(2);
	sbt.Remove(3);
	sbt.Remove(4);
	sbt.Remove(5);
	sbt.Remove(6);
	sbt.Remove(7);
	sbt.Remove(8);
	sbt.Remove(9);
	sbt.InOrder();    //空行
}
void test2()
{
	int array[] = { 5, 3, 7, 1, 4, 6, 8, 0, 2, 9 };
	size_t size = sizeof(array) / sizeof(array[0]);
	SearchBinaryTree<int>sbt;
	for (size_t i = 0; i < size; i++)
	{
		sbt.InsertR(array[i]);
	}
	sbt.InOrder();
	cout << "FindR 4 ?" << sbt.FindR(4) << endl;
	cout << "FindR 6 ?" << sbt.FindR(6) << endl;
	cout << "FindR 10 ?" << sbt.FindR(10) << endl;
	sbt.RemoveR(7);
	sbt.InOrder();   //0 1 2 3 4 5 6 8 9
	sbt.RemoveR(5);
	sbt.InOrder();   //0 1 2 3 4 6 8 9

	sbt.RemoveR(0);
	sbt.RemoveR(1);
	sbt.RemoveR(2);
	sbt.RemoveR(3);
	sbt.RemoveR(4);
	sbt.RemoveR(5);
	sbt.RemoveR(6);
	sbt.RemoveR(7);
	sbt.RemoveR(8);
	sbt.RemoveR(9);
	sbt.InOrder();    //空行

	SearchBinaryTree<int>bst1;
	for (size_t i = 0; i < size; i++)
	{
		bst1.InsertR(array[i]);
	}
	bst1.InOrder();
	SearchBinaryTree<int>bst2(bst1);
	bst2.InOrder();
	SearchBinaryTree<int>bst3;
	bst3 = bst1;
	bst3.InOrder();
}
int main()
{
	test1();
	//test2();
	system("pause");
}