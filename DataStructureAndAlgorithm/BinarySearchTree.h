#pragma once
#include <assert.h>

enum class eNodeTypes
{
	PARENT,
	LCHILD,
	RCHILD,
	END
};

template<typename T1, typename T2>
struct t_Pair
{
	template<typename T1, typename T2>
	friend class BinarySearchTree;

	T1 first;
	T2 second;
};

template<typename T1, typename T2>
t_Pair<T1, T2> make_t_Pair(const T1& data1, const T2& data2)
{
	return t_Pair<T1, T2>{data1, data2};
}

template<typename T1, typename T2>
class tNode
{
	template<typename T1, typename T2>
		friend class BinarySearchTree;

	tNode<T1, T2>* mNodeArr[(int)eNodeTypes::END];
	t_Pair<T1, T2> mPair;

public:
	tNode(const t_Pair<T1,T2>& pair = t_Pair<T1,T2>())
		:mPair{pair},
		mNodeArr{nullptr,nullptr,nullptr}
	{}
};

template<typename T1, typename T2>
class BinarySearchTree
{

	tNode<T1, T2>* mRootNode;
	int mCount;

public:
	class iterator;

	BinarySearchTree()
		:mRootNode(nullptr),
		mCount(0)
	{}



	void Insert(const t_Pair<T1,T2>& data)
	{
		tNode<T1, T2>* newNode = new tNode<T1, T2>(data);

		if (mRootNode == nullptr)
		{
			mRootNode = newNode;
		}
		else
		{
			tNode<T1, T2>* rootNode = mRootNode;
			eNodeTypes types = eNodeTypes::END;
			while (true)
			{
				if (rootNode->mPair.first < newNode->mPair.first)
				{
					types = eNodeTypes::RCHILD;
				}
				else if (rootNode->mPair.first > newNode->mPair.first)
				{
					types = eNodeTypes::LCHILD;
				}
				else
				{
					return;
				}

				if (rootNode->mNodeArr[(int)types] == nullptr)
				{
					rootNode->mNodeArr[(int)types] = newNode;
					newNode->mNodeArr[(int)eNodeTypes::PARENT] = rootNode;
					break;
				}
				else
				{
					rootNode = rootNode->mNodeArr[(int)types];
				}
			}
		}
		++mCount;
	}

	iterator begin() 
	{
		tNode<T1, T2>* beginNode = mRootNode;
		while (beginNode->mNodeArr[(int)eNodeTypes::LCHILD])
		{
			beginNode = beginNode->mNodeArr[(int)eNodeTypes::LCHILD];
		}
		return iterator(this, beginNode);
	}

	iterator end()
	{
		return iterator(this, nullptr);
	}

	//find 는 iterator 값을 반환한다.

	iterator Find(const T1& data)
	{
		tNode<T1, T2>* rootNode = mRootNode;
		if (mRootNode == nullptr)
		{
			assert(false);
		}
		else
		{
	
			eNodeTypes types = eNodeTypes::END;
			while (true)
			{
				if (rootNode->mPair.first < data)
				{
					types = eNodeTypes::RCHILD;
				}
				else if (rootNode->mPair.first > data)
				{
					types = eNodeTypes::LCHILD;
				}
				else
				{
					break;
				}

				if (rootNode->mNodeArr[(int)types] == nullptr)
				{
					rootNode = nullptr;
					break;
				}
				else
				{
					rootNode = rootNode->mNodeArr[(int)types];
				}
			}
		}
		return iterator(this, rootNode);
	}

	tNode<T1, T2>* GetInOrdersuccessor( tNode<T1, T2>* _pNode)
	{
		tNode<T1, T2>* findNode = _pNode;
		if (findNode->mNodeArr[(int)eNodeTypes::RCHILD] != nullptr)
		{
			findNode = findNode->mNodeArr[(int)eNodeTypes::RCHILD];
			while (findNode->mNodeArr[(int)eNodeTypes::LCHILD])
			{
				findNode = findNode->mNodeArr[(int)eNodeTypes::LCHILD];
			}
		}
		else
		{
			while (true)
			{
				

				if (!findNode->mNodeArr[(int)eNodeTypes::PARENT])
				{
					break;
				}

				if (findNode->mNodeArr[(int)eNodeTypes::PARENT]->mNodeArr[(int)eNodeTypes::LCHILD] == this)
				{
					findNode = findNode->mNodeArr[(int)eNodeTypes::PARENT];
					break;
				}
				else
				{
					findNode = findNode->mNodeArr[(int)eNodeTypes::PARENT];
				}
			}
		}
		return findNode;

	
	}


	class iterator
	{
		BinarySearchTree<T1, T2>* mItBst;
		tNode<T1, T2>* mItNode;

	public:
		iterator( BinarySearchTree<T1,T2>* bst = nullptr,  tNode<T1,T2>* node = nullptr)
			:mItBst(bst),
			mItNode(node)
		{}

		const t_Pair<T1,T2>& operator*()
		{
			assert(mItNode);
			return mItNode->mPair;
		}

		const t_Pair<T1, T2>* operator->()
		{
			assert(mItNode);
			return &mItNode->mPair;
		}

		iterator& operator++()
		{
			mItNode = mItBst->GetInOrdersuccessor(mItNode);
			return *this;
		}

		iterator& operator++(int)
		{
			mItNode = mItBst->GetInOrdersuccessor(mItNode);
			return *this;
		}

		bool operator!=(const iterator& itr)
		{
			return !(*this == itr);
		}

		bool operator==(const iterator& itr)
		{
			return (this->mItBst == itr.mItBst && this->mItNode == itr.mItNode);
		}
	};
};

