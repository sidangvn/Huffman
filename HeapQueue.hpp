#ifndef HEAPQUEUE_H
#define HEAPQUEUE_H

#include <vector>

using namespace std;

template <typename E>
class VectorCompleteTree
{
	public:
		typedef typename vector<E>::iterator Position;
		VectorCompleteTree() : V(1) {}
		
		int size() const 
		{
			return V.size() - 1; 
		}
		 
		Position left(const Position &p) 
		{ 
			return pos(2 * idx(p)); 
		}
		
		Position right(const Position &p) 
		{ 
			return pos(2 * idx(p) + 1); 
		}
		
		Position parent(const Position &p)
		{ 
			return pos(idx(p) / 2);
		}
		  
		bool hasLeft(const Position &p) const
		{ 
			return 2 * idx(p) <= size();
		}
		  
		bool hasRight(const Position &p) const
		{
			return 2 * idx(p) + 1 <= size(); 
		}
		  
		bool isRoot(const Position &p) const 
		{
			return idx(p) == 1;
		}
		  
		Position root()
		{ 
			return pos(1);
		}
		  
		Position last()
		{ 
			return pos(size());
		}
		  
		void addLast(const E &e) 
		{
			V.push_back(e);
		}
		  
		void removeLast() 
		{ 
			V.pop_back(); 
		}
		
		void swap(const Position &p, const Position &q)
		{
			E e = *q;
			*q = *p;
			*p = e;
		}

	private:
		vector<E> V;

	protected:
		Position pos(int i)
		{
			return V.begin() + i;
		}

		int idx(const Position &p) const
		{
			return p - V.begin();
		}
};

template <typename E, typename C>
class HeapQueue
{
	public:
		int size() const;
		bool empty() const;
		void insert(const E &e);
		const E &min();
		void removeMin();

	private:
		VectorCompleteTree<E> T;
		C isLess;
		typedef typename VectorCompleteTree<E>::Position Position;
};
#endif
