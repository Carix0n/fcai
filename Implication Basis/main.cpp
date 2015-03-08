#include "definitions.h"
#include <fstream>
using namespace std;

int main()
{
	char tmp;
	size_t G, M;
	ifstream in("..\\input.cxt");
	ofstream out("..\\output.txt");
	ofstream out_time("..\\time.txt");
	in >> tmp >> G >> M;
	Context context(G, M);
	vector <Implication> L;
	Closure closure;
	LinClosure linclosure;
	LinClosureMod linclosuremod;
	WildsClosure wildsclosure;

	ScanData(in, context);

	clock_t start = clock();

	BuildBasis(context, L, wildsclosure);
	/*CanonicalBasis(context, L, closure);*/
	/*CanonicalBasisImproved(context, L, closure);*/

	double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	out_time << duration;

	PrintData(out, L, context.getNameAttr());

	return 0;
}