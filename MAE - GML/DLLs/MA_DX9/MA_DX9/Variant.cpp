#include "Variant.h"

Variant::Variant() {
	setNull();
}

Variant::Variant(int val) {
	set(val);
}

Variant::Variant(uint val) {
	set(val);
}

Variant::Variant(float val) {
	set(val);
}

Variant::Variant(double val) {
	set(val);
}

Variant::Variant(void* val) {
	set(val);
}

VariantTypes Variant::getType() {
	return type;
}

void Variant::setNull() {
	type = VariantTypeNull;
}

void Variant::set(int val) {
	type = VariantTypeInteger;
	value.Integer = val;
}

void Variant::set(uint val) {
	type = VariantTypeUnsignedInteger;
	value.UnsignedInteger = val;
}

void Variant::set(float val) {
	type = VariantTypeFloat;
	value.Float = val;
}

void Variant::set(double val) {
	type = VariantTypeDouble;
	value.Double = val;
}

void Variant::set(void* val) {
	type = VariantTypePointer;
	value.Pointer = val;
}

int Variant::getInteger() {
	if (type != VariantTypeInteger)
		return 0;

	return value.Integer;
}

uint Variant::getUnsignedInteger() {
	if (type != VariantTypeUnsignedInteger)
		return 0;

	return value.UnsignedInteger;
}

float  Variant::getFloat() {
	if (type != VariantTypeFloat)
		return 0;

	return value.Float;
}

double Variant::getDouble() {
	if (type != VariantTypeDouble)
		return 0;

	return value.Double;
}

void*  Variant::getPointer() {
	if (type != VariantTypePointer)
		return 0;

	return value.Pointer;
}
