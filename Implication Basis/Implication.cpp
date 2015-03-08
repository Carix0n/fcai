#include "definitions.h"

Implication::Implication() {}

Implication::Implication(BitSet &initPremise, BitSet &initConclusion)
{
	this->premise = initPremise;
	this->conclusion = initConclusion;
}

BitSet& Implication::Premise() { return this->premise; }

const BitSet& Implication::Premise() const { return this->premise; }

BitSet& Implication::Conclusion() { return this->conclusion; }

const BitSet& Implication::Conclusion() const { return this->conclusion; }

bool Implication::operator==(const Implication &impl)
{
	return ( (this->Premise() == impl.Premise() ) && ( this->Conclusion() == impl.Conclusion() ) );
}