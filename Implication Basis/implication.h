#include "datastructures.h"

class Implication
{
	BitSet premise;
	BitSet conclusion;
public:
	Implication() {}
	Implication(const BitSet &initPremise, const BitSet &initConclusion) : premise(initPremise), conclusion(initConclusion) {}

	BitSet &Premise() { return premise; }
	const BitSet &Premise() const { return premise; }
	BitSet &Conclusion() { return conclusion; }
	const BitSet &Conclusion() const { return conclusion; }
	bool operator==(const Implication &impl) { return ( (this->Premise() == impl.Premise() ) && ( this->Conclusion() == impl.Conclusion() ) ); }
};