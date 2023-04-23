#pragma once
#include <string>
#include <iostream>
using namespace std;

class TVertex
{
private:
	TVertex* _Parent;
	string _Name;

public:
	TVertex(string Name);
	TVertex();

	void operator=(const TVertex& other);
	friend ostream& operator<<(ostream& os, const TVertex& vertex);

	string ToString() const;
	const string& Name() const;
	TVertex*& TVertex::Parent();
};

