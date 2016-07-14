#include <GMLAPI/Main.h>
#include <GMLAPI/Stream.h>
#include <GMLAPI/Utils.h>

enum Type {
	TypeU8  = 0,
	TypeU16 = 1,
	TypeU32 = 2,
	TypeS8  = 3,
	TypeS16 = 4,
	TypeS32 = 5,
	TypeF32 = 6,
	TypeF64 = 7
};

static void* bufferPtr = nullptr;

DLLEXPORT double MAE_StreamDestroy(double stream) {
	auto ptr = doubleToPtr<Stream>(stream);

	streams.remove(ptr);
	delete ptr;

	return 1;
}

DLLEXPORT double MAE_StreamRead(double stream, void* dest, double offset, double length) {
	doubleToPtr<Stream>(stream)->read((ubyte*) dest + (uint) offset, (uint) length);

	return 1;
}

DLLEXPORT double MAE_StreamReadValue(double stream, double type) {
	auto ptr = doubleToPtr<Stream>(stream);

	switch ((Type) (uint) type) {
	case TypeU8:
		return ptr->read<ubyte>();
	case TypeU16:
		return ptr->read<ushort>();
	case TypeU32:
		return ptr->read<uint>();
	case TypeS8:
		return ptr->read<char>();
	case TypeS16:
		return ptr->read<short>();
	case TypeS32:
		return ptr->read<int>();
	case TypeF32:
		return ptr->read<float>();
	case TypeF64:
		return ptr->read<double>();
	}

	return 0;
}

DLLEXPORT double MAE_StreamWrite(double stream, const void* src, double offset, double length) {
	doubleToPtr<Stream>(stream)->write((ubyte*) src + (uint) offset, (uint) length);

	return 1;
}

DLLEXPORT double MAE_StreamWriteValue(double stream, double type, double value) {
	auto ptr = doubleToPtr<Stream>(stream);

	switch ((Type) (uint) type) {
	case TypeU8:
		ptr->write<ubyte>((ubyte) value);
		break;
	case TypeU16:
		ptr->write((ushort) value);
		break;
	case TypeU32:
		ptr->write<uint>((uint) value);
		break;
	case TypeS8:
		ptr->write<char>((char) value);
		break;
	case TypeS16:
		ptr->write<short>((short) value);
		break;
	case TypeS32:
		ptr->write<int>((int) value);
		break;
	case TypeF32:
		ptr->write<float>((float) value);
		break;
	case TypeF64:
		ptr->write<double>((double) value);
		break;
	}

	return 1;
}

DLLEXPORT double MAE_StreamPeek(double stream, double strofs, double offset, double length) {
	doubleToPtr<Stream>(stream)->peek((uint) strofs, (ubyte*) bufferPtr + (uint) offset, (uint) length);

	return 1;
}

DLLEXPORT double MAE_StreamPeekValue(double stream, double strofs, double type) {
	auto ptr = doubleToPtr<Stream>(stream);

	switch ((Type) (uint) type) {
	case TypeU8:
		return ptr->peek<ubyte>((uint) strofs);
	case TypeU16:
		return ptr->peek<ushort>((uint) strofs);
	case TypeU32:
		return ptr->peek<uint>((uint) strofs);
	case TypeS8:
		return ptr->peek<char>((uint) strofs);
	case TypeS16:
		return ptr->peek<short>((uint) strofs);
	case TypeS32:
		return ptr->peek<int>((uint) strofs);
	case TypeF32:
		return ptr->peek<float>((uint) strofs);
	case TypeF64:
		return ptr->peek<double>((uint) strofs);
	}

	return 0;
}

DLLEXPORT double MAE_StreamPoke(double stream, double strofs, double offset, double length) {
	doubleToPtr<Stream>(stream)->poke((uint) strofs, (ubyte*) bufferPtr + (uint) offset, (uint) length);

	return 1;
}

DLLEXPORT double MAE_StreamPokeValue(double stream, double strofs, double type, double value) {
	auto ptr = doubleToPtr<Stream>(stream);

	switch ((Type) (uint) type) {
	case TypeU8:
		ptr->poke<ubyte>((uint) strofs, (ubyte) value);
		break;
	case TypeU16:
		ptr->poke<ushort>((uint) strofs, (uint) value);
		break;
	case TypeU32:
		ptr->poke<uint>((uint) strofs, (uint) value);
		break;
	case TypeS8:
		ptr->poke<char>((uint) strofs, (char) value);
		break;
	case TypeS16:
		ptr->poke<short>((uint) strofs, (short) value);
		break;
	case TypeS32:
		ptr->poke<int>((uint) strofs, (int) value);
		break;
	case TypeF32:
		ptr->poke<float>((uint) strofs, (float) value);
		break;
	case TypeF64:
		ptr->poke<double>((uint) strofs, (double) value);
		break;
	}

	return 1;
}

DLLEXPORT double MAE_StreamTell(double stream) {
	return doubleToPtr<Stream>(stream)->tell();
}

DLLEXPORT double MAE_StreamSeek(double stream, double pos) {
	doubleToPtr<Stream>(stream)->seek((uint) pos);

	return 1;
}
