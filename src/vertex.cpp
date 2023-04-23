#include "vertex.h"

TVertex::TVertex(string name) : _Name(name), _Parent(nullptr) /*_Amount(1)*/ {}

TVertex::TVertex() : _Name(""), _Parent(nullptr) /*_Amount(1)*/ {}

void TVertex::operator=(const TVertex& other)
{
	_Parent = other._Parent;
	_Name = other._Name;
}

ostream& operator<<(ostream& os, const TVertex& vertex)
{
	os << vertex._Name << "|";

	if (!vertex._Parent) {
		os << "0";
		return os;
	}
	else {
		os << vertex._Parent->_Name;
	}

	return os;
}

string TVertex::ToString() const {
	string ans = _Name;

	if (!_Parent) {
		ans += "|0";
	}
	else {
		ans += _Parent->_Name;
	}

	return ans;
}

const string& TVertex::Name() const
{
	return _Name;
}

TVertex*& TVertex::Parent()
{
	return _Parent;
}