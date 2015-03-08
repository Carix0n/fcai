#include <vector>
#include <map>
#include <string>
#include <boost/dynamic_bitset.hpp>
typedef boost::dynamic_bitset<> BitSet;

using namespace std;

class TrieNode
{
	size_t value;
	bool isEnd;
	TrieNode *prev;
	map <size_t, TrieNode *> next;

public:

	TrieNode();
	TrieNode(TrieNode *parent, size_t new_value);

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

class Implication
{
	BitSet premise;
	BitSet conclusion;

public:
	Implication();
	Implication(BitSet &initPremise, BitSet &initConclusion);

	BitSet &Premise();

	const BitSet &Premise() const;

	BitSet &Conclusion();

	const BitSet &Conclusion() const;

	bool operator==(const Implication &impl);
};

class Context
{
	size_t sizeObj;
	size_t sizeAttr;
	vector <BitSet> tableObj;
	vector <BitSet> tableAttr;
	vector <string> nameObj;
	vector <string> nameAttr;

public:
	Context(const size_t G, const size_t M);

	size_t getSizeObj();
	size_t getSizeObj() const;

	size_t getSizeAttr();
	size_t getSizeAttr() const;

	vector <BitSet> getObjGalois();
	vector <BitSet> getObjGalois() const;
	BitSet getObjGalois(const size_t index);
	BitSet getObjGalois(const size_t index) const;

	vector <BitSet> getAttrGalois();
	vector <BitSet> getAttrGalois() const;
	BitSet getAttrGalois(const size_t index);
	BitSet getAttrGalois(const size_t index) const;

	vector <string> getNameObj();
	vector <string> getNameObj() const;

	string getNameObj(const size_t index);
	string getNameObj(const size_t index) const;

	vector <string> getNameAttr();
	vector <string> getNameAttr() const;

	string getNameAttr(const size_t index);
	string getNameAttr(const size_t index) const;

	void setValue(const size_t G, const size_t M, const bool val = true);

	void setNameObj(const size_t index, const string &name);

	void setNameAttr(const size_t index, const string &name);
};

class LongInt
{
	vector <unsigned long long> data;
	size_t block_num;
	size_t length;
	size_t BLOCK_SIZE;

	void set_block_num(size_t num, unsigned long long value = 0);
	size_t calculate_new_length();

public:
	LongInt(size_t len);
	
	void set_bit(size_t pos, bool value);
	
	size_t get_length();

	bool operator[](size_t pos);
	LongInt& operator++();
	LongInt& operator--();
	bool operator<(LongInt &a);
	bool operator<=(LongInt &a);
};