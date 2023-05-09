#pragma once
#include<iostream>
#include<vector>
#include<time.h>
using namespace std;
enum Color
{
	RED,
	BLACK
};
template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _pLeft;
	RBTreeNode<T>* _pRight;
	RBTreeNode<T>* _pParent;
	T _data;

	Color _col;

	RBTreeNode(const T& data)
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _data(data)
		, _col(RED)
	{}
};
template<class T, class Ref, class Ptr>
class __RBTreeIterator
{
public:
	typedef RBTreeNode<T> Node;
	typedef __RBTreeIterator<T, Ref, Ptr> Self;

	Node* _node;
	__RBTreeIterator(Node* node)
		:_node(node)
	{}
	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &(_node->_data);
	}
	Self& operator++()
	{
		if (_node->_pRight)
		{
			Node* min = _node->_pRight;
			while (min->_pLeft)
			{
				min = min->_pLeft;
			}

			_node = min;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_pParent;
			while (parent && cur == parent->_pRight)
			{
				cur = parent;
				parent = parent->_pParent;
			}

			_node = parent;
		}
		return *this;
	}
	Self& operator--()
	{
		if (_node->_pLeft)
		{
			Node* max = _node->_pLeft;
			while (max->_pRight)
			{
				max = max->_pRight;
			}

			_node = max;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_pParent;
			while (parent && cur == parent->_pLeft)
			{
				cur = parent;
				parent = cur->_pParent;
			}

			_node = parent;
		}
		return *this;
	}
	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}
	bool operator==(const Self& s) const
	{
		return _node == s._node;
	}
};
template<class K, class T, class KeyOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef __RBTreeIterator<T, T&, T*> _iterator;
	typedef __RBTreeIterator<T, const T&,const T*> const_iterator;
	_iterator begin()
	{
		Node* left = _root;
		while (left && left->_pLeft)
		{
			left = left->_pLeft;
		}
		return _iterator(left);
	}
	_iterator end()
	{
		return _iterator(nullptr);
	}

	RBTree()
		:_root(nullptr)
	{}
	RBTree(RBTree<K, T, KeyOfT>& t)
	{
		_root = Copy(t._root);
	}
	RBTree<K, T, KeyOfT>& operator=(RBTree<K, T, KeyOfT> t)
	{
		swap(_root, t._root);
		return *this;
	}
	~RBTree()
	{
		Destory(_root);
		_root = nullptr;
	}
	_iterator Find(const K& key)
	{
		KeyOfT kot;
		Node* cur = _root;
		while (cur)
		{
			if (key < kot(cur->_data))
			{
				cur = cur->_pLeft;
			}
			else if (key > kot(cur->_data))
			{
				cur = cur->_pRight;
			}
			else
			{
				return _iterator(cur);
			}
		}
		return end();
	}
	pair<_iterator, bool> Insert(const T& data)
	{
		//1.判断根节点是否为空
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(_iterator(_root), true);
		}

		//2.遍历二叉树寻找插入的位置
		KeyOfT kot;
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (kot(data) < kot(cur->_data))
			{
				parent = cur;
				cur = cur->_pLeft;
			}
			else if (kot(data) > kot(cur->_data))
			{
				parent = cur;
				cur = cur->_pRight;
			}
			else
			{
				return make_pair(_iterator(cur), false);
			}
		}

		//3.插入节点
		cur = new Node(data);
		Node* newNode = cur;
		cur->_col = RED;
		if (kot(data) < kot(parent->_data))
		{
			parent->_pLeft = cur;
			cur->_pParent = parent;
		}
		else
		{
			parent->_pRight = cur;
			cur->_pParent = parent;
		}

		//4.控制平衡
		//父亲存在且为红
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_pParent;
			//     g
			//  p     u
			//c 
			//     g
			//  p     u
			//    c 
			if (parent == grandfather->_pLeft)
			{
				Node* uncle = grandfather->_pRight;
				//叔叔存在且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_pParent;
				}
				//叔叔不存在或者存在且为黑
				else
				{
					if (cur == parent->_pLeft)
					{
						//单旋
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//双旋
						RotateLR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_pLeft;
				//叔叔存在且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_pParent;
				}
				//叔叔不存在或者存在且为黑
				else
				{
					if (cur == parent->_pRight)
					{
						//单旋
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//双旋
						RotateRL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					break;
				}
			}
		}

		_root->_col = BLACK;

		return make_pair(_iterator(newNode), true);
	}

	//打印红黑树
	void InOrder()
	{
		_InOrder(_root);
	}
	//判断红黑树是否平衡
	bool IsBalance()
	{
		//判断根节点颜色
		if (_root && _root->_col == RED)
		{
			cout << "根节点为红色" << endl;
			return false;
		}
		//判断各路径黑色节点是否一致
		Node* left = _root;
		int BaseValue = 0;
		int BlackNum = 0;
		while (left)
		{
			if (left->_col == BLACK)
			{
				BaseValue++;
			}
			left = left->_pLeft;
		}
		return _IsBalance(_root, BaseValue, BlackNum);
	}
private:
	Node* Copy(Node* root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		Node* newRoot = new Node(root->_data);
		newRoot->_col = root->_col;

		newRoot->_pLeft = Copy(root->_pLeft);
		newRoot->_pRight = Copy(root->_pRight);

		if (newRoot->_pLeft)
		{
			newRoot->_pLeft->_pParent = newRoot;
		}
		if (newRoot->_pRight)
		{
			newRoot->_pRight->_pParent = newRoot;
		}
		return newRoot;
	}
	void Destory(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		Destory(root->_pLeft);
		Destory(root->_pRight);
		delete root;
	}

	//右旋
	void RotateR(Node* parent)
	{
		Node* subL = parent->_pLeft;
		Node* subLR = subL->_pRight;
		Node* parentParent = parent->_pParent;

		//链接左右节点和父亲
		parent->_pLeft = subLR;
		parent->_pParent = subL;
		if (subLR)
		{
			subLR->_pParent = parent;
		}
		subL->_pRight = parent;
		if (_root == parent)
		{
			_root = subL;
			subL->_pParent = nullptr;
		}
		else
		{
			if (parentParent->_pLeft == parent)
			{
				parentParent->_pLeft = subL;
			}
			else
			{
				parentParent->_pRight = subL;
			}
			subL->_pParent = parentParent;
		}
	}

	//左旋
	void RotateL(Node* parent)
	{
		Node* subR = parent->_pRight;
		Node* subRL = subR->_pLeft;
		Node* parentParent = parent->_pParent;
		//链接左右节点和父亲
		parent->_pRight = subRL;
		subR->_pLeft = parent;
		if (subRL)
		{
			subRL->_pParent = parent;
		}
		parent->_pParent = subR;

		if (parent == _root)
		{
			_root = subR;
			subR->_pParent = nullptr;
		}
		else
		{
			if (parentParent->_pLeft == parent)
			{
				parentParent->_pLeft = subR;
			}
			else
			{
				parentParent->_pRight = subR;
			}
			subR->_pParent = parentParent;
		}
	}

	//右左双旋
	void RotateRL(Node* parent)
	{
		RotateR(parent->_pRight);
		RotateL(parent);
	}

	//左右双旋
	void RotateLR(Node* parent)
	{
		RotateL(parent->_pLeft);
		RotateR(parent);
	}
private:
	Node* _root;
};
