#include "definitions.h"

size_t LongInt::calculate_new_length()
{
	size_t len = 0;
	for(size_t blockInd = this->block_num; blockInd != 0;)
	{
		--blockInd;
		for(size_t bitInd = this->BLOCK_SIZE; bitInd != 0;)
		{
			--bitInd;
			if((this->data[blockInd] >> bitInd) & 1)
				len = blockInd * this->BLOCK_SIZE + bitInd + 1;
		}
	}
	return len;
}

void LongInt::set_block_num(size_t num, unsigned long long value)
{
	if(num / this->BLOCK_SIZE + 1 > this->block_num)
	{
		this->block_num = num;
		this->data.resize(this->block_num, 0);
	}
}

LongInt::LongInt(size_t len)
{
	this->BLOCK_SIZE = 64;
	this->block_num = len / this->BLOCK_SIZE + 1;
	this->length = 0;
	this->data.resize(this->block_num, 0);
}

void LongInt::set_bit(size_t pos, bool value)
{
	if(value && pos >= this->length)
		this->length = pos + 1;
	else if(!value && pos == this->length - 1)
		this->length = calculate_new_length();
	if(pos / this->BLOCK_SIZE + 1 > this->block_num)
		set_block_num(pos / this->BLOCK_SIZE + 1);
	if(value)
		this->data[pos / this->BLOCK_SIZE] |= ((unsigned long long)1 << (pos % this->BLOCK_SIZE));
	else
		this->data[pos / this->BLOCK_SIZE] = ~((~this->data[pos / this->BLOCK_SIZE]) | ((unsigned long long)1 << (pos % this->BLOCK_SIZE)));
}

size_t LongInt::get_length()
{
	return this->length;
}

bool LongInt::operator[](size_t pos)
{
	return (this->data[pos / this->BLOCK_SIZE] >> (pos % this->BLOCK_SIZE)) & 1 ? true : false;
}

LongInt& LongInt::operator++()
{
	size_t index = 0;
	while(((this->data[index / BLOCK_SIZE] >> (index % BLOCK_SIZE)) & 1) && index < this->length)
	{
		this->set_bit(index, false);
		++index;
	}
	this->set_bit(index, true);
	return *this;
}

LongInt& LongInt::operator--()
{
	size_t index = 0;
	while(!((this->data[index / BLOCK_SIZE] >> (index % BLOCK_SIZE)) & 1))
	{
		this->set_bit(index, true);
		++index;
	}
	this->set_bit(index, false);
	return *this;
}

bool LongInt::operator<(LongInt &a)
{
	size_t this_len = this->get_length();
	size_t a_len = a.get_length();
	if(this_len < a_len)
		return true;
	else if(this_len > a_len)
		return false;
	else
	{
		for(size_t index = this->block_num; index != 0;)
		{
			--index;
			if(this->data[index] < a.data[index])
				return true;
			else if(this->data[index] > a.data[index])
				return false;
		}
		return false;
	}
}

bool LongInt::operator<=(LongInt &a)
{
	size_t this_len = this->get_length();
	size_t a_len = a.get_length();
	if(this_len < a_len)
		return true;
	else if(this_len > a_len)
		return false;
	else
	{
		for(size_t index = this->block_num; index != 0;)
		{
			--index;
			if(this->data[index] < a.data[index])
				return true;
			else if(this->data[index] > a.data[index])
				return false;
		}
		return true;
	}
}