#include "closure.h"
using namespace std;

BitSet Closure::operator()(BitSet &X, vector <Implication> &L, const size_t erase_back)
{
	const size_t attrNum = X.size();
	//erase_back == 1 if the last element of set must be deleted
	const size_t implNum = L.size() - erase_back;
	BitSet used(implNum, false);
	BitSet oldClosure(attrNum);
	oldClosure.set();
	BitSet newClosure = X;

	while(oldClosure != newClosure)
	{
		oldClosure = newClosure;
		for(size_t index = 0; index < implNum; ++index)
		{
			if(!used[index] && L[index].Premise().is_subset_of(newClosure))
			{
				newClosure |= L[index].Conclusion();
				used.set(index);
			}
		}
	}
	return newClosure;
}
BitSet LinClosure::operator()(BitSet &X, vector <Implication> &L, const size_t erase_back)
{
	BitSet res(X);
	const size_t attrNum = X.size();
	//erase_back == 1 if the last element of set must be deleted
	const size_t implNum = L.size() - erase_back;
	vector <size_t> count(implNum);
	vector <BitSet> list(attrNum, BitSet(implNum));

	for(size_t indexImpl = 0; indexImpl < implNum; ++indexImpl)
	{
		count[indexImpl] = L[indexImpl].Premise().count();
		if(!count[indexImpl])
			res |= L[indexImpl].Conclusion();
		for(size_t indexAttr = 0; indexAttr < attrNum; ++indexAttr)
			if(L[indexImpl].Premise().test(indexAttr))
				list[indexAttr].set(indexImpl);
	}

	BitSet update(res);
	size_t indexAttr = 0;

	while(update.count())
	{
		while(!update.test(indexAttr))
		{
			if(indexAttr + 1 == attrNum)
				indexAttr = 0;
			else
				indexAttr++;
		}
		update.reset(indexAttr);

		for(size_t indexImpl = 0; indexImpl < implNum; ++indexImpl)
		{
			if(list[indexAttr].test(indexImpl))
			{
				count[indexImpl]--;
				if(!count[indexImpl])
				{
					BitSet add = L[indexImpl].Conclusion() - res;
					res |= add;
					update |= add;
				}
			}
		}
	}
	return res;
}

BitSet LinClosureMod::operator()(BitSet &X, vector <Implication> &L, const size_t erase_back)
{
	BitSet res(X);
	const size_t attrNum = X.size();
	//erase_back == 1 if the last element of set must be deleted
	const size_t implNum = L.size() - erase_back;

	std::vector<size_t> count(implNum);
	std::vector<std::vector<size_t> > list(attrNum);

	for (size_t indexImpl = 0; indexImpl < implNum; ++indexImpl)
	{			
		count[indexImpl] = L[indexImpl].Premise().count();		

		for (size_t indexAttr = 0; indexAttr < attrNum; ++indexAttr)			
			if (L[indexImpl].Premise().test(indexAttr))		
				list[indexAttr].push_back(indexImpl);			
	}

	std::vector<size_t> update;	
	std::vector<bool> use(attrNum, false);

	for (size_t i = 0; i < attrNum; ++i)
	{
		if (X.test(i))		
		{
			use[i] = true;
			update.push_back(i);					
		}
	}

	while (!update.empty())
	{
		size_t ind = update.back();
		update.pop_back();

		for (size_t i = 0; i < list[ind].size(); ++i)			
		{
			size_t indexImpl = list[ind][i];
			--count[indexImpl];

			if (!count[indexImpl])
			{
				BitSet add = L[indexImpl].Conclusion() - res;
				res |= add;

				for (size_t indexAttr = 0; indexAttr < attrNum; ++indexAttr)				
					if (add.test(indexAttr) && !use[indexAttr])					
					{
						update.push_back(indexAttr);											
						use[indexAttr] = true;
					}
			}
		}		
	}

	return res;
}

BitSet WildsClosure::operator()(BitSet &X, vector <Implication> &L, const size_t erase_back)
{
	BitSet res(X);
	const size_t attrNum = X.size();
	//erase_back == 1 if the last element of set must be deleted
	const size_t implNum = L.size() - erase_back;

	vector <BitSet> list(attrNum, BitSet(implNum));

	for(size_t attrInd = 0; attrInd < attrNum; ++attrInd)
		for(size_t implInd = 0; implInd < implNum; ++implInd)
			if(L[implInd].Premise().test(attrInd))
				list[attrInd].set(implInd);

	bool stable;
	BitSet L_index(implNum);
	L_index.set();

	do 
	{
		stable = true;
		BitSet L1_index(implNum);
		for(size_t attrInd = 0; attrInd < attrNum; ++attrInd)
			if(!res.test(attrInd))
				L1_index |= list[attrInd];

		BitSet L_tmp = L_index - L1_index;
		for(size_t implInd = 0; implInd < implNum; ++implInd)
		{
			if(L_tmp.test(implInd))
			{
				res |= L[implInd].Conclusion();
				stable = false;
			}
		}
		L_index = L1_index;
	} while (!stable);

	return res;
}