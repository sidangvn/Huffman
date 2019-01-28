#include "Huffman.hpp"

//Function to add L for leaf and B for branch
void HuffmanTree::postOrdered(HuffmanNode* root)
{
	if (root == nullptr)
	{
		//recursive to go to left and right
		postOrdered(root -> left);
		postOrdered(root -> right);

		if (root -> isLeaf()) //check for left node
		{
			//add L if it is leaf
			serialOut.push_back('L');
			serialOut.push_back(root -> getCharacter());
		}
		else
		{
			//add B if it is branch
			serialOut.push_back('B');
		}
	}
}

//function to add L + char if it is leaf and add B to branch
void HuffmanTree::encoded(HuffmanNode* root, std::string strIn, map<char, std::string> &map_str)
{
	if (root == nullptr)
	{	
		return;
	}

	if (root -> isLeaf()) 
	{
		map_str[root -> getCharacter()] = strIn;
	}

	//recursive to go to left and right
	encoded(root -> left, strIn + "0", map_str);
	encoded(root -> right, strIn + "1", map_str);

	if (root -> isLeaf())
	{
		serialOut.push_back('L'); //add L to leaf
		serialOut.push_back(root -> getCharacter());
	}
	else
	{
		serialOut.push_back('B');//add B to branch
	}
}

//compress function
string HuffmanTree::compress(const string inputStr) 
{
	string str_out = "";
	map<char, int> char_freq;

	for (char getChar : inputStr) 
	{
		char_freq[getChar]++;
	}

	for (auto temp : char_freq) 
	{
		myHeap.insert(new HuffmanNode(temp.first, temp.second));
	}

	while (myHeap.size() > 1) 
	{
		HuffmanNode *left = myHeap.min();
		myHeap.removeMin();

		HuffmanNode *right = myHeap.min();
		myHeap.removeMin();

		int sum = left -> getFrequency() + right -> getFrequency();
		myHeap.insert(new HuffmanNode('\0', sum, temp, left, right));
	}

	HuffmanNode *root = myHeap.min();

	map<char, string> map_endcoded;

	postOrdered(root);
	encoded(root, "", map_endcoded);

	
	for (char getChar : inputStr) 
	{
		str_out += map_endcoded[getChar];
	}

	return str_out;
}

//serialize Tree function
string HuffmanTree::serializeTree() const 
{
	return serialOut;
}

//decompress function
string HuffmanTree::decompress(const string inputCode, const string serializedTree) 
{
	bool flag = false;
	stack<HuffmanNode*> buff; //hold node

	for(unsigned int i = 0; i < serializedTree.length(); i++)
	{
		if(serializedTree[i] == 'L') //L case
		{
			i++;

			char ch = serializedTree[i];

			HuffmanNode* newNode = new HuffmanNode(ch, 0, nullptr, nullptr, nullptr);
			buff.push(newNode); 

			
		}
		else //B case
		{
			HuffmanNode *Right = buff.top();
			buff.pop();
			HuffmanNode *Left = buff.top();
			buff.pop();
			
			

			HuffmanNode* nNode = new HuffmanNode(0, 0, nullptr, Left, Right);

			buff.push(nNode);
		}
	}

	HuffmanNode* root = buff.top(); //set top is root
	HuffmanNode* pos; //position

	std::string decoded = "";

	int unsigned i = 0;
	while (i < inputCode.length())
	{
		if (!flag)
		{
			pos = root; //set current position to be root
			flag = true; //update 
		}
		else
		{
			if (pos -> isLeaf())
			{
				decoded.push_back(pos -> getCharacter());
				flag = false;

			}
			else
			{
				if(inputCode[i] == '1')
				{
					pos = pos -> right;
				}				
				else
				{
					pos = pos -> left;
				}

				i++;
			}
		}
	}

	decoded.push_back(pos -> getCharacter());
	
	return decoded;
}
