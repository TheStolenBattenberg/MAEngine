#pragma once

#include <MAE/Core/Types.h>

class Variant
{
public:
	enum Types
	{
		TypeNull,
		TypeInteger,
		TypeUnsignedInteger,
		TypeFloat,
		TypeDouble,
		TypePointer
	};

	Variant();
	Variant(int val);
	Variant(uint val);
	Variant(float val);
	Variant(double val);
	Variant(void* val);

	Types getType();

	void setNull();

	void set(int val);
	void set(uint val);
	void set(float val);
	void set(double val);
	void set(void* val);

	int    getInteger();
	uint   getUnsignedInteger();
	float  getFloat();
	double getDouble();
	void*  getPointer();

private:
	Types type;

	union
	{
		int    Integer;
		uint   UnsignedInteger;
		float  Float;
		double Double;
		void*  Pointer;
	} value;
};
