#include "HeapQueue.hpp"


template <typename E, typename C>
int HeapQueue<E, C>::size() const
{
	return T.size();
}

template <typename E, typename C>
bool HeapQueue<E, C>::empty() const
{
	return size() == 0;
}

template <typename E, typename C>
const E &HeapQueue<E, C>::min()
{
	return *(T.root());
}

template <typename E, typename C>
void HeapQueue<E, C>::removeMin()
{
	if(size() == 1)
	{
		T.removeLast();
	}
	else
	{
		Position u = T.root();
		T.swap(u, T.last());
		T.removeLast();

		while(T.hasLeft(u))
		{
			Position v = T.left(u);
			if(T.hasRight(u) && isLess(*(T.right(u)), *v))
			{
				v = T.right(u);
			}
			
			if (isLess(*v, *u))
			{
				T.swap(u, v);
				u = v;
			}
			else
			{
				break;
			}
		}
	}
}

template <typename E, typename C>
void HeapQueue<E, C>::insert(const E &e)
{
	T.addLast(e);
	Position v = T.last();
	while(!T.isRoot(v))
	{
		Position u = T.parent(v);
		if(!isLess(*v, *u)) break;
		T.swap(v, u);
		v = u;
	}
}
