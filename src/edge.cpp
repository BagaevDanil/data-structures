#include "edge.h"


TEdge::TEdge() : _FirstVertex(nullptr), _SecondVertex(nullptr), _Weight(-1) {}


TEdge::TEdge(TVertex* first, TVertex* second, int weight) : _FirstVertex(first), _SecondVertex(second), _Weight(weight) {}


bool TEdge::operator>(const TEdge& other)
{
	return _Weight > other._Weight;
}


bool TEdge::operator<(const TEdge& other)
{
	return _Weight < other._Weight;
}


ostream& operator<<(ostream& os, const TEdge& edge)
{
	os << *(edge._FirstVertex) << "_-_" << *(edge._SecondVertex) << endl;
	return os;
}


void TEdge::operator=(const TEdge& other)
{
	_FirstVertex = other._FirstVertex;
	_SecondVertex = other._SecondVertex;
	_Weight = other._Weight;
}


std::string TEdge::ToString() const
{
	return _FirstVertex->ToString() + "<->" + _SecondVertex->ToString();
}