#include "edge.h"

TEdge::TEdge(TVertex first, TVertex second, int weight) : _FirstVertex(first), _SecondVertex(second), _Weight(weight) {}

TEdge::TEdge() : _Weight(0) {}

bool TEdge::operator>(const TEdge& other) const
{
	return _Weight > other._Weight;
}

bool TEdge::operator<(const TEdge& other) const
{
	return _Weight < other._Weight;
}

ostream& operator<<(ostream& os, const TEdge& edge)
{
	os << "{" << edge._FirstVertex.ToString() << "," << edge._SecondVertex.ToString() << "=" << edge._Weight << "}";
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
	return "{" + _FirstVertex.ToString() + "," + _SecondVertex.ToString() + "=" + to_string(_Weight) + "}";
}

TVertex& TEdge::FirstVertex()
{
	return _FirstVertex;
}

TVertex& TEdge::SecondVertex()
{
	return _SecondVertex;
}

const int& TEdge::Weight() const
{
	return _Weight;
}

std::string to_string(const TEdge& edge)
{
	return edge.ToString();
}