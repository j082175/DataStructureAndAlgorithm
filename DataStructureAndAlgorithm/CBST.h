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

	class iterator;
	iterator begin();
	iterator end();

	iterator find(const T1& _find);
	bool insert(const tPair<T1, T2>& _pair);

	tBSTNode<T1, T2>* GetInOrderSuccessor(tBSTNode<T1, T2>* _pNode);
	tBSTNode<T1, T2>* GetInOrderPredecessor(tBSTNode<T1, T2>* _pNode);


	class iterator
	{
	private:
		CBST<T1, T2>* m_pBST;
		tBSTNode<T1, T2>* m_pNode;
	public:
		iterator( CBST<T1,T2>* _pBST,  tBSTNode<T1,T2>* _pNode)
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

	private:
		const tPair<T1, T2>& operator*()
		{
			assert(m_pNode);
			return m_pNode->pair;
		}

	public:
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
	};
};

template<typename T1, typename T2>
 typename CBST<T1,T2>::iterator CBST<T1, T2>::begin()
{
	 tBSTNode<T1, T2>* pNode = m_pRoot;
	 while (pNode->arrNode[(int)NODE_TYPE::LCHILD])
	 {
		 pNode = pNode->arrNode[(int)NODE_TYPE::LCHILD];
	 }
	return iterator(this,pNode);
}

 template<typename T1, typename T2>
 typename CBST<T1,T2>::iterator CBST<T1, T2>::end()
 {
	 return iterator(this, nullptr);
 }

 template<typename T1, typename T2>
  typename CBST<T1,T2>::iterator CBST<T1, T2>::find(const T1& _find)
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

	 return iterator(this,pNode);
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
		tBSTNode<T1, T2>* pNode = m_pRoot;
		NODE_TYPE node_type = NODE_TYPE::END;

		while (true)
		{
			if (pNode->pair.first < pNewNode->pair.first)
			{
				node_type = NODE_TYPE::RCHILD;
			}
			else if (pNode->pair.first > pNewNode->pair.first)
			{
				node_type = NODE_TYPE::LCHILD;
			}
			else
			{
				return false;
			}

			if (pNode->arrNode[(int)node_type] == nullptr)
			{
				pNode->arrNode[(int)node_type] = pNewNode;
				pNewNode->arrNode[(int)NODE_TYPE::PARENT] = pNode;
				break;
			}
			else
			{
				pNode = pNode->arrNode[(int)node_type];
				//pNewNode = pNewNode->pRightChild;
			}

		}
	}

	++m_iCount;
	return true;
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

	return nullptr;
}

template<typename T1, typename T2>
 tPair<T1, T2> make_tPair(const T1& t1, const T2& t2)
{
	 return tPair<T1, T2>{t1, t2};
}