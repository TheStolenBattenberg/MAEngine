#include <MAE/Core/Variant.h>

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

Variant::Types Variant::getType() {
	return type;
}

void Variant::setNull() {
	type = TypeNull;
}

void Variant::set(int val) {
	type = TypeInteger;
	value.Integer = val;
}

void Variant::set(uint val) {
	type = TypeUnsignedInteger;
	value.UnsignedInteger = val;
}

void Variant::set(float val) {
	type = TypeFloat;
	value.Float = val;
}

void Variant::set(double val) {
	type = TypeDouble;
	value.Double = val;
}

void Variant::set(void* val) {
	type = TypePointer;
	value.Pointer = val;
}

int Variant::getInteger() {
	if (type != TypeInteger)
		return 0;

	return value.Integer;
}

uint Variant::getUnsignedInteger() {
	if (type != TypeUnsignedInteger)
		return 0;

	return value.UnsignedInteger;
}

float Variant::getFloat() {
	if (type != TypeFloat)
		return 0;

	return value.Float;
}

double Variant::getDouble() {
	if (type != TypeDouble)
		return 0;

	return value.Double;
}

void* Variant::getPointer() {
	if (type != TypePointer)
		return 0;

	return value.Pointer;
}
