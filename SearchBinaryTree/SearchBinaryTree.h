#define _CRT_SECURE_NO_WARNINGS
#include"iostream"
using namespace std;
template<class T>struct SearchBinaryTreeNode
{
	T _key;//关键字
	SearchBinaryTreeNode<T>*_left;
	SearchBinaryTreeNode<T>*_right;
	SearchBinaryTreeNode(const T&key) :_key(key), _left(NULL), _right(NULL)
	{}
};
template<class T>class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<T> Node;
protected:
	Node*_root;
public:
	SearchBinaryTree() :_root(NULL)
	{}
	SearchBinaryTree(const SearchBinaryTree<T>& sbt)
	{
		_root = _Copy(sbt._root);
	}
	SearchBinaryTree<T>&operator=(const SearchBinaryTree<T>sbt)
	{
		if (this != &sbt)
		{
			SearchBinaryTree<T>tmp(sbt);
			std::swap(_root, tmp._root);
		}
		return *this;
	}
	~SearchBinaryTree()
	{
		_Destroy(_root);
	}
public:
	void InOrder()
	{

		_InOrder(_root);
		cout << endl;
	}
	bool Insert(const T&key)
	{
		//非递归实现插入操作
		if (_root == NULL)
		{
			//空树
			_root = new Node(key);
			return true;
		}
		Node*cur = _root;
		Node*parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;//存在相同的关键字
		}
		//不存在相同的关键字
		if (parent->_key < key)
		{
			parent->_right = new Node(key);
			return true;
		}
		else if (parent->_key>key)
		{
			parent->_left = new Node(key);
			return true;
		}
		else
			return false;
	}
	void InsertR(const T&key)
	{
		_InsertR(_root, key);
	}
	void _InsertR(Node* &root,const T&key)
	{
		if (root == NULL)
		{
			root = new Node(key);
			return;
		}
		if (root->_key < key)
			_InsertR(root->_right, key);
		else if (root->_key>key)
			_InsertR(root->_left, key);
	}
	bool Remove(const T&key)
	{
		if (_root == NULL)
		{
			return false;
		}
		Node*cur = _root;
		Node*parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				break;
			}
		}
		if (cur)
		{
			//存在该点
			if (cur->_left == NULL)
			{
				//左为空
				if (_root == cur)
				{
					//删除的是根节点且左为空
					_root = cur->_right;
				}
				else
				{
					if (parent->_right == cur)
						parent->_right = cur->_right;
					else if (parent->_left == cur)
						parent->_left = cur->_right;
				}
			}
			else if (cur->_right == NULL)
			{
				//右为空
				if (_root == cur)
				{
					//要删除的结点是根结点且右为空
					_root = cur->_left;
				}
				else
				{
					if (parent->_left == cur)
						parent->_left = cur->_left;
					else if (parent->_right == cur)
						parent->_right = cur->_left;
				}
			}
			else
			{
				//左右都不为空
				//找当前结点右树中最小点替换
				parent = cur;
				Node*tmp = cur->_right;
				while (tmp->_left)
				{
					parent = tmp;
					tmp = tmp->_left;
				}
				cur->_key = tmp->_key;
				if (parent->_left == tmp)
					parent->_left = tmp->_right;
				else
					parent->_right = tmp->_right;
				cur = tmp;
			}
			delete cur;
			cur = NULL;
		}
		return true;
	}
	bool RemoveR(const T&key)
	{
		return _RemoveR(_root, key);
	}
	bool _RemoveR(Node*&root, const T&key)
	{
		if (root ==NULL)
			return false;
		if (root->_key < key)
			return _RemoveR(root->_right, key);
		else if (root->_key>key)
			return _RemoveR(root->_left, key);
		else
		{
			Node*del = root;
			if (root->_left == NULL)
				root = root->_right;//左子树为空
			else if (root->_right == NULL)
				root = root->_left;//右子树为空
			else
			{
				//左右子树都不为空
				Node*parent = root;
				Node*tmp = root->_right;
				while (tmp->_left)
				{
					parent = tmp;
					tmp = tmp->_left;
				}
				del = tmp;
				root->_key = tmp->_key;
				if (parent->_left == tmp)
					parent->_left = tmp->_right;
				else
					parent->_right = tmp->_right;
			}
			delete del;
			del = NULL;
		}
		return true;
	}
	bool Find(const T&key)
	{
		Node*cur = _root;
		while (cur)
		{
			if (cur->_key < key)
				cur = cur->_right;
			else if (cur->_key>key)
				cur = cur->_left;
			else
				return true;//找到
		}
		return false;//没找着
	}
	bool FindR(const T&key)
	{
		return _FindR(_root, key);
	}
	bool _FindR(Node*root, const T&key)
	{
		if (root == NULL)
		{
			//空
			return false;
		}
		if (root->_key < key)
			return _FindR(root->_right, key);
		else if (root->_key>key)
			return _FindR(root->_left, key);
		else if (root->_key == key)
			return true;
		return false;//没有找到
	}
	void _Destroy(Node* root)
	{
		if (root == NULL)
			return;
		Node*cur = root;
		if (cur)
		{
			_Destroy(cur->_left);
			_Destroy(cur->_right);
			delete cur;
			cur = NULL;
		}
	}
	Node*_Copy(Node*root)
	{
		Node*cur = root;
		Node*proot = NULL;
		if (cur)
		{
			proot = new Node(cur->_key);
			proot->_left = _Copy(cur->_left);
			proot->_right = _Copy(cur->_right);
		}
		return proot;
	}
	void _InOrder(Node*root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
};