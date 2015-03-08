#include <vector>
#include "datastructures.h"
const int BLOCK_SIZE = 64;

using namespace std;

class Bitset
{
private:
	vector < long long > _data; // container
	unsigned long _size; // size of bitset
	unsigned long _count; // number of bits with value = 1
public:
	Bitset();
	Bitset(size_t size);
	Bitset(unsigned long size, vector < long long > bitset_pattern);
	unsigned long const size();
	unsigned long const count();
	void set(long long index, bool value);
	void set();
	void reset();
	Bitset flip(long long index);
	Bitset flip();
	bool is_subset_of(Bitset A);
	bool contains_element(long long index);
	void insert(long long index);
	void erase(long long index);
	bool operator[](int index);
	void operator = (Bitset A);
	Bitset operator & (Bitset A);
	Bitset operator | (Bitset A);
	Bitset operator - (Bitset A);
	Bitset operator ~ ();
};