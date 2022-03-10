#pragma once
#include <assert.h>

enum class NODE_TYPE
{
	PARENT,
	LCHILD,
	RCHILD,
	END
};

template<typename T1, typename T2>
struct tPair
{
	template<typename T1, typename T2>
	friend class CBST;

	T1 first;
	T2 second;

	//public:
	//	tPair(const T1& t1 = T1(), const T2& t2 = T2())
	//		:first(t1),
	//		second(t2)
	//	{}

};

template<typename T1, typename T2>
class tBSTNode
{
	template<typename T1, typename T2>
	friend class CBST;

	tPair<T1, T2> pair;

	tBSTNode* arrNode[(int)NODE_TYPE::END];
	//tBSTNode* pParent;
	//tBSTNode* pLeftChild;
	//tBSTNode* pRightChild;


public:
	/*tBSTNode()
		:pParent(nullptr),
		pLeftChild(nullptr),
		pRightChild(nullptr)
	{}*/
	tBSTNode(const tPair<T1, T2>& _pair = tPair<T1, T2>(),
		tBSTNode* _pParent = nullptr,
		tBSTNode* _pLChild = nullptr,
		tBSTNode* _pRChild = nullptr)
		:pair(_pair),
		arrNode{ _pParent,_pLChild,_pRChild }
	{}

	bool IsRoot()
	{
		if (arrNode[(int)NODE_TYPE::PARENT])
		{
			return true;
		}
		return false;
	}

	bool IsLeftChild()
	{
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == this)
		{
			return true;
		}
		return false;
	}

	bool IsRightChild()
	{
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] == this)
		{
			return true;
		}
		return false;
	}

	bool IsLeaf()
	{
		if (arrNode[(int)NODE_TYPE::LCHILD] == nullptr && arrNode[(int)NODE_TYPE::RCHILD] == nullptr)
		{
			return true;
		}
		return false;
	}

	bool IsFull()
	{
		if (arrNode[(int)NODE_TYPE::LCHILD] && arrNode[(int)NODE_TYPE::RCHILD])
		{
			return true;
		}
		return false;
	}
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

public:
	class iterator;
	iterator begin();
	iterator end();
	iterator find(const T1& _find);
	bool insert(const tPair<T1, T2>& _pair);
	iterator erase(const iterator& iter);
	tBSTNode<T1, T2>* GetInOrderSuccessor(tBSTNode<T1, T2>* _pNode);
	tBSTNode<T1, T2>* GetInOrderPredecessor(tBSTNode<T1, T2>* _pNode);
private:
	tBSTNode<T1, T2>* deleteNode(tBSTNode<T1, T2>* _pTargetNode);



public:
	class iterator
	{
		friend class CBST<T1, T2>;
	private:
		CBST<T1, T2>* m_pBST;
		tBSTNode<T1, T2>* m_pNode;
	public:
		iterator(CBST<T1, T2>* _pBST = nullptr, tBSTNode<T1, T2>* _pNode = nullptr)
			:m_pBST(_pBST),
			m_pNode(_pNode)
		{}

		bool operator==(const iterator& _other)
		{
			if (m_pBST == _other.m_pBST && m_pNode == _other.m_pNode)
			{
				return true;
			}
			return false;
		}

		bool operator!=(const iterator& _other)
		{
			return !(*this == _other);
		}

		const tPair<T1, T2>& operator*()
		{
			assert(m_pNode);
			return m_pNode->pair;
		}

		const tPair<T1, T2>* operator->()
		{
			assert(m_pNode);
			return &m_pNode->pair;
		}

		iterator& operator++()
		{
			m_pNode = m_pBST->GetInOrderSuccessor(m_pNode);
			return *this;
		}

		iterator& operator++(int)
		{
			m_pNode = m_pBST->GetInOrderSuccessor(m_pNode);
			return *this;
		}

		iterator& operator--()
		{
			m_pNode = m_pBST->GetInOrderPredecessor(m_pNode);
			return *this;
		}

		iterator& operator--(int)
		{
			m_pNode = m_pBST->GetInOrderPredecessor(m_pNode);
			return *this;
		}
	};
};

template<typename T1, typename T2>
typename CBST<T1, T2>::iterator CBST<T1, T2>::begin()
{
	tBSTNode<T1, T2>* pNode = m_pRoot;
	while (pNode->arrNode[(int)NODE_TYPE::LCHILD])
	{
		pNode = pNode->arrNode[(int)NODE_TYPE::LCHILD];
	}
	return iterator(this, pNode);
}

template<typename T1, typename T2>
typename CBST<T1, T2>::iterator CBST<T1, T2>::end()
{
	return iterator(this, nullptr);
}

template<typename T1, typename T2>
typename CBST<T1, T2>::iterator CBST<T1, T2>::find(const T1& _find)
{
	tBSTNode<T1, T2>* pNode = m_pRoot;
	NODE_TYPE node_type = NODE_TYPE::END;

	while (true)
	{
		if (pNode->pair.first < _find)
		{
			node_type = NODE_TYPE::RCHILD;
		}
		else if (pNode->pair.first > _find)
		{
			node_type = NODE_TYPE::LCHILD;
		}
		else
		{
			break;
		}

		if (pNode->arrNode[(int)node_type] == nullptr)
		{
			pNode = nullptr;
			break;
		}
		else
		{
			pNode = pNode->arrNode[(int)node_type];
			//pNewNode = pNewNode->pRightChild;
		}

	}

	return iterator(this, pNode);
}

template<typename T1, typename T2>
bool CBST<T1, T2>::insert(const tPair<T1, T2>& _pair)
{
	tBSTNode<T1, T2>* pNewNode = new tBSTNode<T1, T2>(_pair);

	if (m_pRoot == nullptr)
	{
		m_pRoot = pNewNode;
	}
	else
	{
		tBSTNode<T1, T2>* pNode_Root = m_pRoot;
		NODE_TYPE node_type = NODE_TYPE::END;

		while (true)
		{
			if (pNode_Root->pair.first < pNewNode->pair.first)
			{
				node_type = NODE_TYPE::RCHILD;
			}
			else if (pNode_Root->pair.first > pNewNode->pair.first)
			{
				node_type = NODE_TYPE::LCHILD;
			}
			else
			{
				return false;
			}

			if (pNode_Root->arrNode[(int)node_type] == nullptr)
			{
				pNode_Root->arrNode[(int)node_type] = pNewNode;
				pNewNode->arrNode[(int)NODE_TYPE::PARENT] = pNode_Root;
				break;
			}
			else
			{
				pNode_Root = pNode_Root->arrNode[(int)node_type];
				//pNewNode = pNewNode->pRightChild;
			}

		}
	}

	++m_iCount;
	return true;
}

template<typename T1, typename T2>
typename CBST<T1, T2>::iterator CBST<T1, T2>::erase(const iterator& iter)
{
	assert(this == iter.m_pBST);

	tBSTNode<T1, T2>* del = deleteNode(iter.m_pNode);


	return iterator(this, del);
}

template<typename T1, typename T2>
tBSTNode<T1, T2>* CBST<T1, T2>::GetInOrderSuccessor(tBSTNode<T1, T2>* _pNode)
{
	tBSTNode<T1, T2>* pSuccessor = nullptr;

	if (_pNode->arrNode[(int)NODE_TYPE::RCHILD] != nullptr)
	{
		pSuccessor = _pNode->arrNode[(int)NODE_TYPE::RCHILD];
		while (pSuccessor->arrNode[(int)NODE_TYPE::LCHILD])
		{
			pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::LCHILD];
		}
	}
	else
	{
		/* if (pSuccessor->arrNode[(int)NODE_TYPE::PARENT] == nullptr)
		 {
			 return nullptr;
		 }
		 pSuccessor->arrNode[(int)NODE_TYPE::PARENT]
			 ->arrNode[(int)NODE_TYPE::LCHILD] == pSuccessor;*/

		pSuccessor = _pNode;
		while (true)
		{
			if (pSuccessor->IsRoot())
			{
				return nullptr;
			}
			 if (pSuccessor->IsLeftChild())
			 {
				 pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
				 break;
			 }
		/*	if (pSuccessor->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == this)
			{
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
				break;
			}*/
			else
			{
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
			}
		}

	}
	return pSuccessor;
}

template<typename T1, typename T2>
tBSTNode<T1, T2>* CBST<T1, T2>::GetInOrderPredecessor(tBSTNode<T1, T2>* _pNode)
{
	tBSTNode<T1, T2>* pPredecessor = nullptr;

	if (_pNode->arrNode[(int)NODE_TYPE::LCHILD] != nullptr)
	{
		pPredecessor = _pNode->arrNode[(int)NODE_TYPE::LCHILD];
		while (pPredecessor->arrNode[(int)NODE_TYPE::RCHILD])
		{
			pPredecessor = pPredecessor->arrNode[(int)NODE_TYPE::RCHILD];
		}
	}
	else
	{
		pPredecessor = _pNode;
		while (true)
		{
			if (!pPredecessor->IsRoot())
			{
				break;
			}
			if (pPredecessor->IsRightChild())
			{
				pPredecessor = pPredecessor->arrNode[(int)NODE_TYPE::PARENT];
				break;
			}
			else
			{
				pPredecessor = pPredecessor->arrNode[(int)NODE_TYPE::PARENT];
			}
		}
	}



	return pPredecessor;
}

template<typename T1, typename T2>
tBSTNode<T1, T2>* CBST<T1, T2>::deleteNode(tBSTNode<T1, T2>* _pTargetNode)
{
	tBSTNode<T1, T2>* pSuccessor = nullptr;

	if (_pTargetNode->IsLeaf())
	{
		pSuccessor = GetInOrderSuccessor(_pTargetNode);

		if (_pTargetNode == m_pRoot)
		{
			m_pRoot = nullptr;
		}
		else
		{
			if (_pTargetNode->IsLeftChild())
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] = nullptr;
			}
			else
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] = nullptr;
			}

		}


		delete _pTargetNode;
	}
	else if (_pTargetNode->IsFull())
	{

	}
	else // 자식이 한개일 경우
	{
		pSuccessor = GetInOrderSuccessor(_pTargetNode);
		NODE_TYPE eChildType = NODE_TYPE::LCHILD;
		if (_pTargetNode->arrNode[(int)NODE_TYPE::RCHILD])
		{
			eChildType = NODE_TYPE::RCHILD;
		}

		if (_pTargetNode == m_pRoot)
		{
			m_pRoot = _pTargetNode->arrNode[(int)eChildType];

			_pTargetNode->arrNode[(int)eChildType]->arrNode[(int)NODE_TYPE::PARENT] = nullptr;
		}
		else
		{
			if (_pTargetNode->IsLeftChild())
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] = _pTargetNode->arrNode[(int)eChildType];
			}
			else
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] = _pTargetNode->arrNode[(int)eChildType];
			}

			_pTargetNode->arrNode[(int)eChildType]->arrNode[(int)NODE_TYPE::PARENT] = _pTargetNode->arrNode[(int)NODE_TYPE::PARENT];
		}

		delete _pTargetNode;
	}

	--m_iCount;
	return pSuccessor;
}

template<typename T1, typename T2>
tPair<T1, T2> make_tPair(const T1& t1, const T2& t2)
{
	return tPair<T1, T2>{t1, t2};
}