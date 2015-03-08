#include "definitions.h"
using namespace std;

/*void RecurrentTransversals(vector <BitSet> &edges, Trie &trie, const size_t attrNum)
{
	size_t edgesNum = edges.size();
	BitSet active_e(edgesNum);
	active_e.set();
	BitSet current_trans(attrNum);
	TransStep(edges, trie, current_trans, active_e, 0);
}

void TransStep(vector <BitSet> &edges, Trie &trie, BitSet &current_trans, BitSet &active_e, const size_t cur)
{
	if(cur == edges.size())
		trie.insert(current_trans);
	else if(!active_e.test(cur))
		TransStep(edges, trie, current_trans, active_e, cur + 1);
	else
	{
		size_t setLen = edges[cur].size();
		size_t edgesNum = edges.size();

		for(size_t setIndex = 0; setIndex < setLen; setIndex++)
		{
			BitSet mark_e(edgesNum);
			current_trans.set(setIndex);

			for(size_t edgeInd = cur; edgeInd < edgesNum; edgeInd++)
			{
				if(active_e.test(edgeInd) && edges[edgeInd].test(setIndex))
				{
					active_e.reset(edgeInd);
					mark_e.set(edgeInd);
				}
			}

			TransStep(edges, trie, current_trans, active_e, cur + 1);
			
			current_trans.reset(setIndex);
			for(size_t edgeInd = cur; edgeInd < edgesNum; edgeInd++)
				if(mark_e.test(edgeInd))
					active_e.set(edgeInd);
		}
	}
}*/

void generate_transversal(vector <BitSet> &edge, vector <BitSet> &transv_res)
{
	const size_t vertexNum = edge[0].size(); // number of vertex in the initial hypergraph
	vector <BitSet> genNode;
	vector <size_t> transv;

	genNode.push_back(BitSet(vertexNum));
	genNode[0].set();
	transv.push_back(0);

	AddNextHyperedge(edge, genNode, transv, transv_res, 0);
}

void AddNextHyperedge(vector <BitSet> &edge, vector <BitSet> &genNode, vector <size_t> &transv, vector <BitSet> &transv_res, const size_t level)
{
	const size_t vertexNum = edge[0].size(); // number of vertex in the initial hypergraph

	if(level == edge.size())
	{
		// last hyperedge
		BitSet T(vertexNum);
		fill_in_transversals(genNode, transv, transv_res, T, 0);
		return;
	}

	bool beta = false;
	vector < pair <size_t, size_t> > gammaInd; // индексы обобщенных вершин гамма после разделения на две
	vector <size_t> gammaTransv; // в каких позициях transv происходят разделения
	const size_t genNodeInitSize = genNode.size();
	
	vector <BitSet> genNodePrev(genNode);
	vector <size_t> transv_prev(transv);

	for(size_t vertexInd = 0; vertexInd < genNodeInitSize; ++vertexInd)
	{
		bool isAlpha = !genNode[vertexInd].intersects(edge[level]);
		bool isBeta = genNode[vertexInd].is_subset_of(edge[level]);
		vector <size_t>::iterator it = find(transv.begin(), transv.end(), vertexInd);
		bool trans_member = (it != transv.end());

		if(isBeta && trans_member)
			beta = true;
		if(!isAlpha && !isBeta)
		{
			BitSet X = genNode[vertexInd] & edge[level];
			genNode.push_back(BitSet(genNode[vertexInd] - X));
			genNode[vertexInd] = X;
			if(trans_member)
			{
				gammaInd.push_back(make_pair(vertexInd, genNode.size() - 1));
				gammaTransv.push_back(it - transv.begin());
			}
		}
	}

	size_t gammaNum = gammaTransv.size();

	if(!beta)
	{
		// appropriate nodes
		BitSet T(vertexNum);

		for(size_t gamma = 0; gamma < gammaNum; ++gamma)
		{
			transv[gammaTransv[gamma]] = gammaInd[gamma].second;
			T |= genNode[gammaInd[gamma].second];
		}

		for(size_t ind = 0; ind < transv_prev.size(); ++ind)
			T |= genNode[transv_prev[ind]];

		for(size_t genNodeInd = 0; genNodeInd < genNode.size(); ++genNodeInd)
		{
			// transversal doesn't contain genNodeInd && this node is in the current edge
			if(!genNode[genNodeInd].intersects(T) && genNode[genNodeInd].is_subset_of(edge[level]))
			{
				if(IsAppropriateNode(edge, level, genNodePrev, transv_prev, T | genNode[genNodeInd]))
				{
					transv.push_back(genNodeInd);
					AddNextHyperedge(edge, genNode, transv, transv_res, level + 1);
					transv.pop_back();
				}
			}
		}

	}

	LongInt count(gammaNum + 1);
	LongInt max(gammaNum + 1);
	max.set_bit(gammaNum, true);
	if(!beta)
		count.set_bit(0, true);

	for(; count < max; ++count)
	{
		for(size_t gamma = 0; gamma < gammaNum; ++gamma)
			transv[gammaTransv[gamma]] = (count[gamma]) ? gammaInd[gamma].first : gammaInd[gamma].second;
		AddNextHyperedge(edge, genNode, transv, transv_res, level + 1);
	}

	for(size_t ind = 0; ind < gammaNum; ++ind)
		transv[gammaTransv[ind]] = gammaInd[ind].first;
	genNode = genNodePrev;
}

bool IsAppropriateNode(vector <BitSet> &edge, const size_t level, vector <BitSet> &genNode, vector <size_t> &transv, BitSet &T)
{
	bool appropriate = true;
	// try to erase node and get a non-transversal
	for(vector <size_t>::iterator genNodeIt = transv.begin(); genNodeIt != transv.end() && appropriate; ++genNodeIt)
		if(IsTransversal(edge, level, T - genNode[*genNodeIt]))
			appropriate = false;
	return appropriate;
}

bool IsTransversal(vector <BitSet> &edge, const size_t level, BitSet &T)
{
	bool res = true;
	for(size_t edgeInd = 0; edgeInd < level && res; ++edgeInd)
		if(!T.intersects(edge[edgeInd]))
			res = false;
	return res;
}

void fill_in_transversals(vector <BitSet> &genNode, vector <size_t> &transv, vector <BitSet> &transv_res, BitSet &T, size_t level)
{
	if(level == transv.size())
	{
		transv_res.push_back(T);
		return;
	}

	size_t attrNum = genNode[0].size();

	for(size_t ind = 0; ind < attrNum; ++ind)
	{
		if(genNode[transv[level]].test(ind))
		{
			T.set(ind);
			fill_in_transversals(genNode, transv, transv_res, T, level + 1);
			T.reset(ind);
		}
	}
}