#pragma once


template < typename T>
class PNode
{
private:
	T item; // A data item
	float Priority;
	PNode<T>* next; // Pointer to next node
public:
	PNode();
	PNode(const T& r_Item);	//passing by const ref.
	PNode(const T& r_Item, PNode<T>* nextNodePtr, float Pr);
	void setItem(const T& r_Item);
	void setNext(PNode<T>* nextNodePtr);
	T getItem() const;
	PNode<T>* getNext() const;
	float GetPriority() const;
	void SetPriority(float P);
}; // end Node


template < typename T>
PNode<T>::PNode()
{
	next = nullptr;
}

template < typename T>
PNode<T>::PNode(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
PNode<T>::PNode(const T& r_Item, PNode<T>* nextNodePtr, float Pr)
{
	item = r_Item;
	next = nextNodePtr;
	Priority = Pr;
}
template < typename T>
void PNode<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void PNode<T>::setNext(PNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T PNode<T>::getItem() const
{
	return item;
}

template < typename T>
PNode<T>* PNode<T>::getNext() const
{
	return next;
}

template<typename T>
inline float PNode<T>::GetPriority() const
{
	return Priority;
}

template<typename T>
inline void PNode<T>::SetPriority(float P)
{
	Priority = P;
}

template<class T>
class PriorityQueue
{
	PNode<T>* frontptr;
	int count;
public:
	PriorityQueue<T>(PNode<T>* ptr = nullptr)
	{
		count = 0;
		frontptr = ptr;
	}
	int getSize() const
	{
		return count;
	}
	bool enqueue(const T& item, float P)
	{
		count++;

		PNode<T>* newNode = new PNode<T>(item);
		newNode->SetPriority(P);
		if (!newNode)
			return 0;

		if (!frontptr || frontptr->GetPriority() < P)
		{
			newNode->setNext(frontptr);
			frontptr = newNode;
			return 1;
		}
		else
		{
			PNode<T>* prev = frontptr;
			PNode<T>* after = frontptr->getNext();
			while (after)
			{
				if (after->GetPriority() < P)
				{
					prev->setNext(newNode);
					newNode->setNext(after);
					return 1;
				}
				prev = after;
				after = after->getNext();
			}
			prev->setNext(newNode);
			newNode->setNext(nullptr);
		}
	}

	bool isEmpty()
	{
		if (!frontptr)
			return true;

		return false;
	}

	bool peek(T& item)
	{
		if (!frontptr)
			return false;
		item = frontptr->getItem();
		return true;
	}

	bool dequeue(T& item)
	{
		if (!frontptr)
			return false;

		item = frontptr->getItem();
		PNode<T>* temp = frontptr;
		
		frontptr = frontptr->getNext();
		delete temp;
		count--;
		return true;
	}

	~PriorityQueue<T>()
	{
		T item;
		float P;
		while (dequeue(item));
	}

};




/*#include"../Generic_DS/Node.h"

template<class T>
class PriorityQueue
{
	Node<T>* frontptr;
	int count ;
public:
	PriorityQueue<T>(Node<T>*ptr = nullptr)
	{
		count = 0;
		frontptr = ptr;
	}
	int getSize() const
	{
		return count;
	}
	void enqueueSort(const T& item)
	{
		count++;
		Node<T>* newNode = new Node<T>(item);
		if (!frontptr || frontptr->getItem() <= item)
		{
			newNode->setNext(frontptr);
			frontptr = newNode;

			return;
		}
		else
		{
			Node<T>* prev = frontptr;
			Node<T>* after = frontptr->getNext();
			while (after)
			{
				if (after->getItem() <= item)
				{
					prev->setNext(newNode);
					newNode->setNext(after);
					return;
				}
				prev = after;
				after = after->getNext();
			}
			prev->setNext(newNode);
			newNode->setNext(nullptr);
		}
	}

	bool isEmpty()
	{
		if (!frontptr)
			return true;

		return false;
	}

	bool peek(T& item)
	{
		if (!frontptr)
			return false;
		item = frontptr->getItem();
		return true;
	}

	bool dequeue(T& item)
	{
		if (!frontptr)
			return false;

		item = frontptr->getItem();
		Node<T>* temp = frontptr;
		frontptr = frontptr->getNext();
		delete temp;
		count--;
		return true;
	}

	

	T* toArray(int& count)
	{
		count = 0;
		if (!frontptr)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = frontptr;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr = new T[count];
		p = frontptr;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}
	~PriorityQueue<T>()
	{
		T item;
		while (dequeue(item));
	}

};*/
