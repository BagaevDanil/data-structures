#pragma once
#include <string>
#include <iostream>
using namespace std;

class Vertex
{
public:
	Vertex* parent;
	string name;
	int amount;

	Vertex(string Name);
	Vertex();

	void operator=(const Vertex& other)
	{
		this->parent = other.parent;
		this->name = other.name;
	}

	friend ostream& operator<<(ostream& os, const Vertex& dt)
	{
		if (dt.parent)
			os << dt.name << "|" << (dt.parent)->name;
			//os << dt.name << "(" << dt.height << ")" << "|" << (dt.parent)->name << "(" << (dt.parent)->height << ")";
		else
			os << dt.name << "|" << "0" << "";
		return os;
	}
};

inline Vertex::Vertex(string Name)
{
	this->name = Name;
	parent = nullptr;
	amount = 1;
}

inline Vertex::Vertex()
{
	parent = nullptr;
	amount = 1;
}