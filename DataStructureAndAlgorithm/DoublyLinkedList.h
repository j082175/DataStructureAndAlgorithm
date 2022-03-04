#pragma once
#include <initializer_list>

template<typename T>
class Node;

template<typename T>
class Reverse_Iterator
{
	template<typename T>
	friend class DoublyLinkedList;

	Node<T>* mNode;
public:
	T& operator*()
	{
		return mNode->mData;
	}

	void operator++()
	{
		mNode = mNode->mRear;
	}

	void operator++(int)
	{
		mNode = mNode->mRear;
	}

	void operator--()
	{
		mNode = mNode->mFront;
	}

	void operator--(int)
	{
		mNode = mNode->mFront;
	}

	bool operator!=(const Reverse_Iterator& iter)
	{
		return this->mNode != iter.mNode;
	}

	bool operator==(const Reverse_Iterator& iter)
	{
		return this->mNode == iter.mNode;
	}
};

template<typename T>
class Iterator
{
	template<typename T>
	friend class DoublyLinkedList;

	Node<T>* mNode;
public:
	T& operator*()
	{
		return mNode->mData;
	}

	void operator++()
	{
		mNode = mNode->mFront;
	}

	void operator++(int)
	{
		mNode = mNode->mFront;
	}

	void operator--()
	{
		mNode = mNode->mRear;
	}

	void operator--(int)
	{
		mNode = mNode->mRear;
	}

	bool operator!=(const Iterator& iter)
	{
		return this->mNode != iter.mNode;
	}

	bool operator==(const Iterator& iter)
	{
		return this->mNode == iter.mNode;
	}
};

template<typename T>
class Node
{
	template<typename T>
	friend class DoublyLinkedList;

	template<typename T>
	friend class Iterator;

	template<typename T>
	friend class Reverse_Iterator;

	T mData;
	Node<T>* mFront;
	Node<T>* mRear;

public:
	Node()
		:mData(),
		mFront(nullptr),
		mRear(nullptr)
	{}
};

template<typename T>
class DoublyLinkedList
{
	typedef Node<T>* PNODE;
	typedef Node<T> NODE;

	PNODE mBegin;
	PNODE mEnd;
	int mCount;
public:
	typedef Iterator<T> iterator;
	typedef Reverse_Iterator<T> reverse_iterator;

	//////////////////////////////

	DoublyLinkedList();

	DoublyLinkedList(const std::initializer_list<T>& list);

	~DoublyLinkedList();

	/////////////////////////////

	void Push_back(const T& data);

	T Pop_back();

	void Push_front(const T& data);

	T Pop_front();

	Iterator<T> begin()const;

	Iterator<T> end()const;

	Reverse_Iterator<T> rbegin()const;

	Reverse_Iterator<T> rend()const;

	void Sort()
	{
		for (PNODE i = mBegin->mFront; i != mEnd->mRear; i = i->mFront)
		{
			for (PNODE j = i->mFront; j != mEnd; j = j->mFront)
			{
				if (i->mData > j->mData)
				{
					T data = i->mData;
					i->mData = j->mData;
					j->mData = data;
				}
			}
		}
	}

};

template<typename T>
 DoublyLinkedList<T>::DoublyLinkedList()
	:mCount(0)
{
	mBegin = new NODE;
	mEnd = new NODE;
	mBegin->mFront = mEnd;
	mEnd->mRear = mBegin;
}

 template<typename T>
  DoublyLinkedList<T>::DoublyLinkedList(const std::initializer_list<T>& list)
	 :DoublyLinkedList()
 {
	 for (auto element : list)
	 {
		 Push_back(element);
		 ++mCount;
	 }
 }

template<typename T>
   DoublyLinkedList<T>::~DoublyLinkedList()
  {
	  delete mBegin;
	  delete mEnd;
  }

  template<typename T>
   void DoublyLinkedList<T>::Push_back(const T& data)
  {
	  PNODE newNode = new NODE;
	  PNODE exNode = mEnd->mRear;
	  exNode->mFront = newNode;
	  newNode->mFront = mEnd;
	  mEnd->mRear = newNode;
	  newNode->mRear = exNode;
	  newNode->mData = data;
	  ++mCount;
  }

  template<typename T>
   T DoublyLinkedList<T>::Pop_back()
  {
	  PNODE deleteNode = mEnd->mRear;
	  PNODE exNode = deleteNode->mRear;
	  exNode->mFront = mEnd;
	  mEnd->mRear = exNode;
	  T data = deleteNode->mData;
	  delete deleteNode;
	  --mCount;
	  return data;
  }

  template<typename T>
   void DoublyLinkedList<T>::Push_front(const T& data)
  {
	  PNODE newNode = new NODE;
	  PNODE exNode = mBegin->mFront;
	  mBegin->mFront = newNode;
	  newNode->mFront = exNode;
	  exNode->mRear = newNode;
	  newNode->mRear = mBegin;
	  ++mCount;
	  newNode->mData = data;
  }

  template<typename T>
   T DoublyLinkedList<T>::Pop_front()
  {
	  PNODE deleteNode = mBegin->mFront;
	  PNODE exNode = deleteNode->mFront;
	  T data = deleteNode->mData;
	  mBegin->mFront = exNode;
	  exNode->mRear = mBegin;
	  delete deleteNode;
	  --mCount;
	  return data;
  }

  template<typename T>
   Iterator<T> DoublyLinkedList<T>::begin() const
  {
	  Iterator<T> iter;
	  iter.mNode = mBegin->mFront;
	  return iter;
  }

  template<typename T>
   Iterator<T> DoublyLinkedList<T>::end() const
  {
	  Iterator<T> iter;
	  iter.mNode = mEnd;
	  return iter;
  }

   template<typename T>
   inline Reverse_Iterator<T> DoublyLinkedList<T>::rbegin() const
   {
	   Reverse_Iterator<T> iter;
	   iter.mNode = mEnd->mRear;
	   return iter;
   }

   template<typename T>
   inline Reverse_Iterator<T> DoublyLinkedList<T>::rend() const
   {
	   Reverse_Iterator<T> iter;
	   iter.mNode = mBegin;
	   return iter;
   }

