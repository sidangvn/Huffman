#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>

#include "HeapQueue.hpp"
#include "HeapQueue.cpp"
#include "HuffmanBase.hpp"

using namespace std;

class HuffmanTree : public HuffmanTreeBase 
{
	public:
		void postOrdered(HuffmanNode* root);	
		void encoded(HuffmanNode* root, std::string strIn, map<char, string> &map_str);
		string compress(const std::string inputStr);
		string serializeTree() const;
		string decompress(const string inputCode, const string serializedTree);

	private:
		HuffmanNode *node;
		HuffmanNode *temp;
		
		HeapQueue<HuffmanNode*, HuffmanNode::Compare> myHeap;
		std::string serialOut = "";
};
