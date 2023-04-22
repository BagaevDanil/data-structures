#pragma once
#include "vertex.h"

class TEdge
{
private:
	TVertex* _FirstVertex;
	TVertex* _SecondVertex;
	int _Weight;

public:
	TEdge(TVertex* firstVertex, TVertex* secondVertex, int weight);
	TEdge();
	
	bool operator>(const TEdge& other);
	bool operator<(const TEdge& other);
	friend ostream& operator<<(ostream& os, const TEdge& dt);
	void operator=(const TEdge& other);

	std::string ToString() const;
};