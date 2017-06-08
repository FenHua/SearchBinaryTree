#define _CRT_SECURE_NO_WARNINGS
#include"iostream"
using namespace std;
template<class T>struct SearchBinaryTreeNode
{
	T _key;//�ؼ���
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
		//�ǵݹ�ʵ�ֲ������
		if (_root == NULL)
		{
			//����
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
				return false;//������ͬ�Ĺؼ���
		}
		//��������ͬ�Ĺؼ���
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
			//���ڸõ�
			if (cur->_left == NULL)
			{
				//��Ϊ��
				if (_root == cur)
				{
					//ɾ�����Ǹ��ڵ�����Ϊ��
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
				//��Ϊ��
				if (_root == cur)
				{
					//Ҫɾ���Ľ���Ǹ��������Ϊ��
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
				//���Ҷ���Ϊ��
				//�ҵ�ǰ�����������С���滻
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
				root = root->_right;//������Ϊ��
			else if (root->_right == NULL)
				root = root->_left;//������Ϊ��
			else
			{
				//������������Ϊ��
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
				return true;//�ҵ�
		}
		return false;//û����
	}
	bool FindR(const T&key)
	{
		return _FindR(_root, key);
	}
	bool _FindR(Node*root, const T&key)
	{
		if (root == NULL)
		{
			//��
			return false;
		}
		if (root->_key < key)
			return _FindR(root->_right, key);
		else if (root->_key>key)
			return _FindR(root->_left, key);
		else if (root->_key == key)
			return true;
		return false;//û���ҵ�
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