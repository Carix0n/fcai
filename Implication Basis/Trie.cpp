#include "definitions.h"
using namespace std;

TrieNode::TrieNode(){ isEnd = false; prev = this; }
TrieNode::TrieNode(TrieNode *parent, size_t new_value){ value = new_value; isEnd = false; prev = parent; }

size_t TrieNode::getValue(){ return this->value; }

TrieNode* TrieNode::getPrev(){ return this->prev; }

bool TrieNode::isEndOfBranch(){ return this->isEnd; }

void TrieNode::setEnd(bool val){ this->isEnd = val; }

void TrieNode::getKeys(vector <size_t> &keys)
{
	keys.clear();
	for(map <size_t, TrieNode *>::iterator it = this->next.begin(); it != this->next.end(); it++)
		keys.push_back(it->first);
}

void TrieNode::getKeys(vector <size_t> &keys) const
{
	keys.clear();
	for(map <size_t, TrieNode *>::const_iterator it = this->next.begin(); it != this->next.end(); it++)
		keys.push_back(it->first);
}

TrieNode* TrieNode::getLink(size_t key){ return this->next.at(key); }

TrieNode* TrieNode::getLink(size_t key) const { return this->next.at(key); }

TrieNode* TrieNode::findNext(size_t key)
{
	map <size_t, TrieNode *>::iterator it = this->next.find(key);
	return it == this->next.end() ? NULL : it->second;
}
pair <TrieNode *, bool> TrieNode::getNext(size_t key)
{
	TrieNode *next = this->findNext(key);
	return make_pair(next, next == NULL ? false : true);
}

TrieNode* TrieNode::insert(size_t key)
{
	TrieNode *res = findNext(key);
	if(res == NULL)
	{
		res = new TrieNode(this, key);
		this->next.insert(make_pair(key, res));
	}
	return res;
}

//----------------------------------------

void Trie::toDel(TrieNode *cur)
{
	vector <size_t> keys;
	cur->getKeys(keys);
	for(vector <size_t>::iterator it = keys.begin(); it != keys.end(); it++)
		toDel(cur->getLink(*it));
	delete cur;
}

void Trie::TrieStep(ostream &out, TrieNode *cur, BitSet &x, vector <string> &attrName)
{
	vector <size_t> keys;
	cur->getKeys(keys);
	for(vector <size_t>::iterator it = keys.begin(); it != keys.end(); it++)
	{
		x.set(*it);
		if(cur->getLink(*it)->isEndOfBranch())
		{
			PrintSet(out, x, attrName);
			out << endl;
		}
		TrieStep(out, cur->getLink(*it), x, attrName);
		x.reset(*it);
	}
}

Trie::Trie(){ this->root = new TrieNode(); }
Trie::~Trie(){ toDel(this->root); }

TrieNode* Trie::getRoot() { return this->root; }

void Trie::PrintTrie(ostream &out, vector <string> &attrName)
{
	TrieNode *cur = this->root;
	BitSet x;
	TrieStep(out, cur, x, attrName);
}

void Trie::insert(const BitSet &object)
{
	TrieNode *cur = this->root;
	size_t objNum = object.size();
	for(size_t index = 0; index < objNum; index++)
		if(object.test(index))
			cur = cur->insert(index);
	cur->setEnd(true);
}