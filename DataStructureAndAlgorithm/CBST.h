#pragma once

template<typename T1, typename T2>
class tPair
{
	template<typename T1, typename T2>
	friend class CBST;

	T1 first;
	T2 second;

public:
	tPair(const T1& t1 = T1(), const T2& t2 = T2())
		:first(t1),
		second(t2)
	{}

};

template<typename T1, typename T2>
class tBSTNode
{
	template<typename T1, typename T2>
	friend class CBST;

	tPair<T1, T2> pair;
	tBSTNode* pParent;
	tBSTNode* pLeftChild;
	tBSTNode* pRightChild;

public:
	tBSTNode()
		:pParent(nullptr),
		pLeftChild(nullptr),
		pRightChild(nullptr)
	{}
};

template<typename T1, typename T2>
class CBST
{
	tBSTNode<T1, T2>* m_pRoot;
	int m_iCount;
public:
	CBST()
		:m_pRoot(nullptr),
		m_iCount(0)
	{}

	bool insert(const tPair<T1, T2>& _pair);
};

template<typename T1, typename T2>
bool CBST<T1, T2>::insert(const tPair<T1, T2>& _pair)
{
	tBSTNode<T1, T2>* pNewNode = new tBSTNode<T1,T2>();
	pNewNode->pair = _pair;
	pNewNode->pLeftChild = nullptr;
	pNewNode->pParent = nullptr;
	pNewNode->pRightChild = nullptr;

	if (m_pRoot == nullptr)
	{
		m_pRoot = pNewNode;
	}
	else
	{
		tBSTNode<T1, T2>* pNode = m_pRoot;

		while (true)
		{

			if (pNode->pair.first < pNewNode->pair.first)
			{
				if (pNode->pRightChild == nullptr)
				{
					pNode->pRightChild = pNewNode;
					pNewNode->pParent = pNode;
					break;
				}
				else
				{
					pNode = pNode->pRightChild;
					//pNewNode = pNewNode->pRightChild;

				}
			}
			else if (pNode->pair.first > pNewNode->pair.first)
			{
				if (pNode->pLeftChild == nullptr)
				{
					pNode->pLeftChild = pNewNode;
					pNewNode->pParent = pNode;
					break;
				}
				else
				{
					pNode = pNode->pLeftChild;
					//pNewNode = pNewNode->pLeftChild;

				}
			}
			else
			{
				return false;
			}
		}
	}

	++m_iCount;
	return true;
}
