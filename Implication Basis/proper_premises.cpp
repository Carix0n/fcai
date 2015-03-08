#include "definitions.h"
using namespace std;

void MinimalCover(vector <Implication> &L, ClosureFunctor &Functor)
{
	for(size_t implInd = 0; implInd < L.size(); ++implInd)
	{
		if(implInd + 1 != L.size())
			swap(L[implInd], L.back());
		L.back().Conclusion() = Functor(L.back().Premise() | L.back().Conclusion(), L, 1);
		if(implInd + 1 != L.size())
			swap(L[implInd], L.back());
	}
	for(size_t implInd = 0; implInd < L.size();)
	{
		if(implInd + 1 != L.size())
			swap(L[implInd], L.back());
		L.back().Premise() = Functor(L.back().Premise(), L, 1);
		if(L.back().Premise() != L.back().Conclusion())
		{
			if(implInd + 1 != L.size())
				swap(L[implInd], L.back());
			++implInd;
		}
		else
			L.pop_back();
	}
}

void BuildBasis(Context &context, vector <Implication> &L, ClosureFunctor &Functor)
{
	size_t objNum = context.getSizeObj(), attrNum = context.getSizeAttr();
	vector <BitSet> objGalois(context.getObjGalois());
	vector <BitSet> closureAddition(objNum);
	BitSet attr(attrNum);
	attr.set();

	for(size_t row = 0; row < objNum; row++)
		closureAddition[row] = attr - objGalois[row];
	for(size_t col = 0; col < attrNum; ++col)
	{
		vector <BitSet> edges;
		for(size_t row = 0; row < objNum; ++row)
		{
			if(objGalois[row].test(col))
				continue;
			BitSet edge = closureAddition[row];
			edge.reset(col);
			edges.push_back(edge);
		}
		vector <BitSet> result;
		generate_transversal(edges, result);

		BitSet conclusion(attrNum);
		conclusion.set(col);
		InsertImplications(result, conclusion, L);
	}
	MinimalCover(L, Functor);
}

void InsertImplications(vector <BitSet> &premise, BitSet &consequence, vector <Implication> &L)
{
	size_t len = premise.size();
	for(size_t ind = 0; ind < len; ++ind)
		L.push_back(Implication(premise[ind], consequence));
}

void InsertImplications(const size_t &consequence, const TrieNode *cur, BitSet &premise, vector <Implication> &L)
{
	vector <size_t> keys;
	cur->getKeys(keys);
	for(vector <size_t>::iterator it = keys.begin(); it != keys.end(); it++)
	{
		TrieNode *nextNode = cur->getLink(*it);
		premise.set(nextNode->getValue());
		if(nextNode->isEndOfBranch())
		{
			BitSet cons(premise.size());
			cons.set(consequence);
			L.push_back(Implication(premise, cons));
		}
		InsertImplications(consequence, nextNode, premise, L);
		premise.reset(nextNode->getValue());
	}
}