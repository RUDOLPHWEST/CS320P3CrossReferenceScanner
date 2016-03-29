#pragma once
#include <sstream>
#include <string>

using namespace std;

//This design uses inheritance for exception handling.
//The baseException defines a method for printing exception/error messages.
class baseException
{
public:
	baseException(const string& str = "") :
		msgString(str)
	{
		if (msgString == "")
			msgString = "Unspecified exception"; //default exception
	}

	string what() const
	{
		return msgString;
	}

	// The keyword "protected" allows a derived class to access msgString. 
protected:
	string msgString;
};

// failure to allocate memory (new() returns NULL)
class memoryAllocationError : public baseException
{
public:
	memoryAllocationError(const string& msg = "") :
		baseException(msg)
	{}
};

// function argument out of proper range
class rangeError : public baseException
{
public:
	rangeError(const string& msg = "") :
		baseException(msg)
	{}
};

// index out of range
class indexRangeError : public baseException
{
public:
	indexRangeError(const string& msg, int i, int size) :
		baseException()
	{
		ostringstream indexErr;

		indexErr << msg << "  index " << i << "  size = " << size << ends;
		// indexRangeError can modify msgString, since it is in
		// the protected section of baseException
		msgString = indexErr.str();
	}
};

class dimensionSizeMismatch : public baseException
{
public:
	dimensionSizeMismatch(const string& msg, int lhsSize, int rhsSize) : baseException()
	{
		ostringstream dimErr;

		dimErr << msg << ": left operand dimension size " << lhsSize << "  right operand dimension size = " << rhsSize << ends;
		// dimensionSizeMismatch can modify msgString, since it is in
		// the protected section of baseException
		msgString = dimErr.str();
	}
};



// attempt to erase from an empty container
class underflowError : public baseException
{
public:
	underflowError(const string& msg = "") :
		baseException(msg)
	{}
};


// attempt to insert into a full container
class overflowError : public baseException
{
public:
	overflowError(const string& msg = "") :
		baseException(msg)
	{}
};

//These last two may prove useful for matrix implementation
// bad object reference
class referenceError : public baseException
{
public:
	referenceError(const string& msg = "") :
		baseException(msg)
	{}
};

// feature not implemented
class notImplementedError : public baseException
{
public:
	notImplementedError(const string& msg = "") :
		baseException(msg)
	{}
};

