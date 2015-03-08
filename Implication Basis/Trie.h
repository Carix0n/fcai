#include "datastructures.h"
#include <map>
#include <vector>
using namespace std;

class TrieNode
{
	size_t value;
	bool isEnd;
	TrieNode *prev;
	map <size_t, TrieNode *> next;

public:

	TrieNode(){ isEnd = false; prev = this; }
	TrieNode(TrieNode *parent, size_t new_value){ value = new_value; isEnd = false; prev = parent; }

	size_t getValue();

	TrieNode *getPrev();

	bool isEndOfBranch();

	void setEnd(bool val);
	
	void getKeys(vector <size_t> &keys);
	void getKeys(vector <size_t> &keys) const;

	TrieNode *getLink(size_t key);
	TrieNode *getLink(size_t key) const;

	TrieNode *findNext(size_t key);
	pair <TrieNode *, bool> getNext(size_t key);

	TrieNode *insert(size_t key);
};

class Trie
{
	TrieNode *root;

	void toDel(TrieNode *cur);

	void TrieStep(ostream &out, TrieNode *cur, BitSet &x, vector <string> &attrName);

public:
	Trie();
	~Trie();

	TrieNode *getRoot();

	void PrintTrie(ostream &out, vector <string> &attrName);

	void insert(const BitSet &object);
};