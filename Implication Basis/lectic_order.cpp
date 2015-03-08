#include "definitions.h"
using namespace std;

bool IsPrefixIdentical(BitSet &bitset1, BitSet &bitset2, const size_t prefLen)
{
	bool equal = true;
	for(size_t index = 0; (index < prefLen) && equal; ++index)
		if(bitset1.test(index) != bitset2.test(index))
			equal = false;
	return equal;
}

void CanonicalBasis(Context &context, vector <Implication> &L, ClosureFunctor &Functor)
{
	size_t objNum = context.getSizeObj(), attrNum = context.getSizeAttr();
	BitSet current(attrNum);
	vector <BitSet> objGalois(context.getObjGalois());
	vector <BitSet> attrGalois(context.getAttrGalois());

	while(current.count() != attrNum)
	{
		BitSet closure = ObjSetGalois(AttrSetGalois(current, context, attrGalois), context, objGalois);
		if(current != closure)
			L.push_back(Implication(current, closure));
		current = NextClosure(current, L, Functor);
	}
}

void CanonicalBasisImproved(Context &context, vector <Implication> &L, ClosureFunctor &Functor)
{
	vector <BitSet> objGalois(context.getObjGalois());
	vector <BitSet> attrGalois(context.getAttrGalois());
	const size_t objNum = context.getSizeObj();
	const size_t attrNum = context.getSizeAttr();

	BitSet emptySet(attrNum);
	BitSet objSet(objNum);
	objSet.set();
	BitSet A = ObjSetGalois(objSet, context, objGalois);

	if(A.any())
		L.push_back(Implication(BitSet(attrNum), A));

	size_t maxInd = attrNum - 1;
	while(A.count() != attrNum)
	{
		size_t j = maxInd + 1;
		do 
		{
			--j;
			if(A.test(j))
				A.reset(j);
			else
			{
				BitSet B = A;
				B.set(j);
				B = Functor(B, L);

				BitSet tmp(B - A);
				if(IsPrefixIdentical(tmp, emptySet, j))
				{
					A = B;
					maxInd = j;
					break;
				}
			}
		} while (j != 0);

		BitSet closureA = ObjSetGalois(AttrSetGalois(A, context, attrGalois), context, objGalois);
		if(A != closureA)
			L.push_back(Implication(A, closureA));
		BitSet tmp (closureA - A);
		if(IsPrefixIdentical(tmp, emptySet, maxInd))
		{
			A = closureA;
			maxInd = attrNum - 1;
		}
		else
			for(size_t index = maxInd + 1; index < attrNum; ++index)
				A.reset(index);
	}
}

BitSet NextClosure(BitSet &A, vector <Implication> &L, ClosureFunctor &Functor)
{
	size_t attrNum = A.size();
	BitSet res = A;
	BitSet emptySet(attrNum);

	size_t indexAttr = attrNum;
	do
	{
		--indexAttr;
		if(res.test(indexAttr))
			res.reset(indexAttr);
		else
		{
			BitSet B = res;
			B.set(indexAttr);
			B = Functor(B, L);

			BitSet tmp(B - res);
			if(IsPrefixIdentical(tmp, emptySet, indexAttr))
				return B;
		}
	} while(indexAttr != 0);
	return BitSet(attrNum);
}

BitSet ObjSetGalois(BitSet &X, Context &context, vector <BitSet> &objGalois)
{
	const size_t objNum = context.getSizeObj();
	const size_t attrNum = context.getSizeAttr();
	BitSet res(attrNum);
	res.set();

	for(size_t index = 0; index < objNum; ++index)
		if(X.test(index))
			res &= objGalois[index];
	return res;
}

BitSet AttrSetGalois(BitSet &X, Context &context, vector <BitSet> &attrGalois)
{
	const size_t objNum = context.getSizeObj();
	const size_t attrNum = context.getSizeAttr();
	BitSet res(objNum);
	res.set();

	for(size_t index = 0; index < attrNum; ++index)
		if(X.test(index))
			res &= attrGalois[index];
	return res;
}