#include "closure.h"
#include <iostream>
#include <time.h>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <iterator>

void ScanData(istream &in, Context &context);

void PrintData(ostream &out, vector <Implication> &L, vector <string> &AttributeName);
void PrintData(ostream &out, vector <Implication> &L);

void PrintSet(ostream &out, BitSet &s, vector <string> &AttributeName);
void PrintSet(ostream &out, BitSet &s);

void PrintImplication(ostream &out, Implication &impl, vector <string> &AttributeName);
void PrintImplication(ostream &out, Implication &impl);

void MinimalCover(vector <Implication> &L, ClosureFunctor &Functor);

void BuildBasis(Context &context, vector <Implication> &L, ClosureFunctor &Functor);

void InsertImplications(const size_t &consequence, const TrieNode *cur, BitSet &premise, vector <Implication> &L);

void InsertImplications(vector <BitSet> &premise, BitSet &consequence, vector <Implication> &L);

bool IsPrefixIdentical(BitSet &bitset1, BitSet &bitset2, const size_t prefLen);

BitSet NextClosure(BitSet &A, vector <Implication> &L, ClosureFunctor &Functor);

void CanonicalBasis(Context &context, vector <Implication> &L, ClosureFunctor &Functor);

void CanonicalBasisImproved(Context &context, vector <Implication> &L, ClosureFunctor &Functor);

BitSet ObjSetGalois(BitSet &X, Context &context, vector <BitSet> &objGalois);

BitSet AttrSetGalois(BitSet &X, Context &context, vector <BitSet> &attrGalois);

void RecurrentTransversals(vector <BitSet> &edges, Trie &trie, const size_t attrNum);

void TransStep(vector <BitSet> &edges, Trie &trie, BitSet &current_trans, BitSet &active_e, const size_t cur);

void generate_transversal(vector <BitSet> &edge, vector <BitSet> &transv_res);

void AddNextHyperedge(vector <BitSet> &edge, vector <BitSet> &genNode, vector <size_t> &transv, vector <BitSet> &transv_res, const size_t level);

bool IsAppropriateNode(vector <BitSet> &edge, const size_t level, vector <BitSet> &genNode, vector <size_t> &transv, BitSet &T);

bool IsTransversal(vector <BitSet> &edge, const size_t level, BitSet &T);

void fill_in_transversals(vector <BitSet> &genNode, vector <size_t> &transv, vector <BitSet> &transv_res, BitSet &T, size_t level);