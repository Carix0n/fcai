#include "definitions.h"
using namespace std;

void ScanData(istream &in, Context &context)
{
	string tmp;
	getline(in, tmp);
	getline(in, tmp);
	size_t G = context.getSizeObj(), M = context.getSizeAttr();
	string name;

	for(size_t index = 0; index < G; ++index)
	{
		getline(in, name);
		context.setNameObj(index, name);
	}

	for(size_t index = 0; index < M; ++index)
	{
		getline(in, name);
		context.setNameAttr(index, name);
	}

	for(size_t row = 0; row < G; ++row)
	{
		for(size_t col = 0; col < M; ++col)
		{
			char tmp;
			in >> tmp;
			if(tmp != '.')
				context.setValue(row, col);
		}
	}
}

void PrintSet(ostream &out, BitSet &s, vector <string> &AttributeName)
{
	size_t len = s.size(), count = s.count(), bitIndex = 0;
	out << "{";
	for(size_t countIndex = 0; countIndex < count; ++bitIndex)
	{
		if(s.test(bitIndex))
		{
			out << AttributeName[bitIndex];
			if(++countIndex != count)
				out << ",";
		}
	}
	out << "}";
}

void PrintSet(ostream &out, BitSet &s)
{
	size_t len = s.size(), count = s.count(), bitIndex = 0;
	out << "{";
	for(size_t countIndex = 0; countIndex < count; ++bitIndex)
	{
		if(s.test(bitIndex))
		{
			out << bitIndex + 1;
			if(++countIndex != count)
				out << ",";
		}
	}
	out << "}";
}

void PrintImplication(ostream &out, Implication &impl, vector <string> &AttributeName)
{
	PrintSet(out, impl.Premise(), AttributeName);
	out << " -> ";
	PrintSet(out, impl.Conclusion() - impl.Premise(), AttributeName);
	out << endl;
}

void PrintImplication(ostream &out, Implication &impl)
{
	PrintSet(out, impl.Premise());
	out << " -> ";
	PrintSet(out, impl.Conclusion() - impl.Premise());
	out << endl;
}

void PrintData(ostream &out, vector <Implication> &L, vector <string> &AttributeName)
{
	size_t implNum = L.size();
	for(size_t i = 0; i < implNum; ++i)
		PrintImplication(out, L[i], AttributeName);
}

void PrintData(ostream &out, vector <Implication> &L)
{
	size_t implNum = L.size();
	for(size_t i = 0; i < implNum; ++i)
		PrintImplication(out, L[i]);
}