#include "definitions.h"

Context::Context(const size_t G, const size_t M)
{
	this->sizeObj = G;
	this->sizeAttr = M;

	this->tableObj.resize(G);
	this->nameObj.resize(G);

	for(size_t indexObj = 0; indexObj < G; ++indexObj)
		this->tableObj[indexObj].resize(M);

	this->tableAttr.resize(M);
	this->nameAttr.resize(M);
	
	for(size_t indexAttr = 0; indexAttr < M; ++indexAttr)
		this->tableAttr[indexAttr].resize(G);
}

size_t Context::getSizeObj()
{
	return this->sizeObj;
}

size_t Context::getSizeObj() const
{
	return this->sizeObj;
}

size_t Context::getSizeAttr()
{
	return this->sizeAttr;
}

size_t Context::getSizeAttr() const
{
	return this->sizeAttr;
}

vector<BitSet> Context::getObjGalois()
{
	return this->tableObj;
}

vector<BitSet> Context::getObjGalois() const
{
	return this->tableObj;
}

BitSet Context::getObjGalois(const size_t index)
{
	if(index >= this->sizeObj)
		return BitSet();
	return this->tableObj[index];
}

BitSet Context::getObjGalois(const size_t index) const
{
	if(index >= this->sizeObj)
		return BitSet();
	return this->tableObj[index];
}

vector<BitSet> Context::getAttrGalois()
{
	return this->tableAttr;
}

vector<BitSet> Context::getAttrGalois() const
{
	return this->tableAttr;
}

BitSet Context::getAttrGalois(const size_t index)
{
	if(index >= this->sizeAttr)
		return BitSet();
	return this->tableAttr[index];
}

BitSet Context::getAttrGalois(const size_t index) const
{
	if(index >= this->sizeAttr)
		return BitSet();
	return this->tableAttr[index];
}

vector <string> Context::getNameObj()
{
	return this->nameObj;
}

vector <string> Context::getNameObj() const
{
	return this->nameObj;
}

string Context::getNameObj(const size_t index)
{
	if(index >= this->sizeObj)
		return string();
	return this->nameObj[index];
}

string Context::getNameObj(const size_t index) const
{
	if(index >= this->sizeObj)
		return string();
	return this->nameObj[index];
}

vector <string> Context::getNameAttr()
{
	return this->nameAttr;
}

vector <string> Context::getNameAttr() const
{
	return this->nameAttr;
}

string Context::getNameAttr(const size_t index)
{
	if(index >= this->sizeAttr)
		return string();
	return this->nameAttr[index];
}

string Context::getNameAttr(const size_t index) const
{
	if(index >= this->sizeAttr)
		return string();
	return this->nameAttr[index];
}

void Context::setValue(const size_t G, const size_t M, const bool val)
{
	if(G >= this->sizeObj || M >= this->sizeAttr)
		return;
	this->tableObj[G][M] = val;
	this->tableAttr[M][G] = val;
}

void Context::setNameObj(const size_t index, const string &name)
{
	if(index >= this->sizeObj)
		return;
	this->nameObj[index] = name;
}

void Context::setNameAttr(const size_t index, const string &name)
{
	if(index >= this->sizeAttr)
		return;
	this->nameAttr[index] = name;
}