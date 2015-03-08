#include "datastructures.h"

class ClosureFunctor
{
public:
	virtual BitSet operator()(BitSet &X, vector <Implication> &L, const size_t erase_back = 0) = 0;
};

class Closure: public ClosureFunctor
{
public:
	BitSet operator()(BitSet &X, vector <Implication> &L, const size_t erase_back = 0);
};

class LinClosure: public ClosureFunctor
{
public:
	BitSet operator()(BitSet &X, vector <Implication> &L, const size_t erase_back = 0);
};

class LinClosureMod: public ClosureFunctor
{
public:
	BitSet operator()(BitSet &X, vector <Implication> &L, const size_t erase_back = 0);
};

class WildsClosure: public ClosureFunctor
{
public:
	BitSet operator()(BitSet &X, vector <Implication> &L, const size_t erase_back = 0);
};