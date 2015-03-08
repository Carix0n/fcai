#include "bitset.h"

Bitset::Bitset()
{
	this->_data.resize(1, 0);
	this->_size = 0;
	this->_count = 0;
}
Bitset::Bitset(size_t size)
{
	this->_data.resize(size, 0);
	this->_size = size;
	this->_count = 0;
}
Bitset::Bitset(unsigned long size, vector < long long > bitset_pattern)
{
	this->_data = bitset_pattern;
	this->_size = size;
}
unsigned long const Bitset::size()
{
	return this->_size;
}
unsigned long const Bitset::count()
{
	return this->_count;
}
void Bitset::set(long long index, bool value)
{
	if(index + 1 > this->_size)
		return;
	// blockNum - index of long long element
	unsigned long long blockNum = index / BLOCK_SIZE;
	// bitNum - index of bit in this element
	int bitNum = index % BLOCK_SIZE;
	long long mask = 1 << bitNum;
	if(value)
	{
		if(!(this->_data[blockNum] & mask))
			this->_count++;
		this->_data[blockNum] |= mask;
	}
	else
	{
		if(this->_data[blockNum] & mask)
			this->_count--;
		this->_data[blockNum] &= ~mask;
	}
}
void Bitset::set()
{
	for(unsigned long long i = 0; BLOCK_SIZE * (i + 1) < this->_size; i++)
		this->_data[i] = 0;
	for(unsigned long long i = 0; i < this->_size % BLOCK_SIZE; i++)
		this->_data[this->_size / BLOCK_SIZE] |= (1 << i);
}
void Bitset::reset()
{
	for(int i = 0; BLOCK_SIZE * i < this->_size; i++)
		this->_data[i] = 0;
}
Bitset Bitset::flip(long long index)
{
	long long mask = 1 << (index % BLOCK_SIZE);
	this->_data[index / BLOCK_SIZE] ^= mask;
	return *this;
}
Bitset Bitset::flip()
{
	for(int i = 0; BLOCK_SIZE * (i + 1) < this->_size; i++)
	{
		this->_data[i] = ~this->_data[i];
	}
	long long mask = 0;
	for(int i = 0; i < this->_size % BLOCK_SIZE; i++)
		mask |= (1 << i);
	this->_data[this->_size / BLOCK_SIZE] ^= mask;
	return *this;
};
bool Bitset::is_subset_of(Bitset A)
{
	if(this->_count > A._count)
		return false;
	for(int i = 0; BLOCK_SIZE * (i + 1) < A.size(); i++)
		if( this->_data[i] & ~A._data[i] )
			return false;
	long long mask = 0;
	for(int i = 0; i < A._size % BLOCK_SIZE; i++)
		mask |= (1 << i);
	if( _data[ A._size / BLOCK_SIZE ] & ~A[ A._size / BLOCK_SIZE ] & mask )
		return false;
	return true;
}
bool Bitset::contains_element(long long index)
{
	long long mask = 1 << (index % BLOCK_SIZE);
	if(this->_data[index / BLOCK_SIZE] & mask)
		return true;
	else
		return false;
}
void Bitset::insert(long long index)
{
	this->set(index, 1);
}
void Bitset::erase(long long index)
{
	this->set(index, 0);
}
bool Bitset::operator[](int index)
{
	assert(index + 1 > this->_size);
	int number = index / BLOCK_SIZE;
	int bit = index % BLOCK_SIZE;
	if ( !( (_data[number] ) & (1 << bit) ) )
		return true;
	else
		return false;
}
void Bitset::operator = (Bitset A)
{
	_data.resize((A._size + BLOCK_SIZE - 1) / BLOCK_SIZE);
	for(int i = 0; BLOCK_SIZE * i < A._size; i++)
	{
		this->_data[i] = A._data[i];
	}
	return;
}
Bitset Bitset::operator & (Bitset A)
{
	const unsigned long long length = min(A._size, this->_size);
	vector < long long > result((length + BLOCK_SIZE - 1) / BLOCK_SIZE);
	for(int i = 0; BLOCK_SIZE * i < length; i++)
	{
		result[i] = A._data[i] & this->_data[i];
	}
	return Bitset(length, result);
}
Bitset Bitset::operator | (Bitset A)
{
	const unsigned long long length = min(A._size, this->_size);
	vector < long long > result((length + BLOCK_SIZE - 1) / BLOCK_SIZE);
	for(int i = 0; BLOCK_SIZE * i < length; i++)
	{
		result[i] = A._data[i] | this->_data[i];
	}
	return Bitset(length, result);
}
Bitset Bitset::operator - (Bitset A)
{
	return *this & ~A;
}
Bitset Bitset::operator ~ ()
{
	vector < long long > result( (this->_size + BLOCK_SIZE - 1) / BLOCK_SIZE);
	for(int i = 0; BLOCK_SIZE * (i + 1) < this->_size; i++)
	{
		result[i] = ~this->_data[i];
	}
	long long mask = 0;
	for(int i = 0; i < this->_size % BLOCK_SIZE; i++)
		mask |= (1 << i);
	result[this->_size / BLOCK_SIZE]  = this->_data[this->_size / BLOCK_SIZE] ^ mask;
	return Bitset( this->_size, result);
};