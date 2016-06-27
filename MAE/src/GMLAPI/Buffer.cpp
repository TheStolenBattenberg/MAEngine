#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Core/Buffer.h>
#include <MAE/Core/Memory.h>
#include <MAE/Core/Utils.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

#include <memory>

enum Type
{
	TypeU8  = 0,
	TypeU16 = 1,
	TypeU32 = 2,
	TypeS8  = 3,
	TypeS16 = 4,
	TypeS32 = 5,
	TypeF32 = 6,
	TypeF64 = 7
};

void* bufferPtr = nullptr;

DLLEXPORT double MADX9_BufferCreate()
{
	auto buf = new Buffer(new DynamicMemory());

	mamain->Buffers.add(buf);
	return ptrToDouble(buf);
}

DLLEXPORT double MADX9_BufferDestroy(double buf)
{
	auto ptr = doubleToPtr<Buffer>(buf);

	mamain->Buffers.remove(ptr);
	delete ptr;

	return ErrorOk;
}

DLLEXPORT double MADX9_BufferReserve(double buf, double amount)
{
	doubleToPtr<Buffer>(buf)->reserve((uint) amount);

	return ErrorOk;
}

DLLEXPORT double MADX9_BufferRemove(double buf, double offset, double length)
{
	doubleToPtr<Buffer>(buf)->remove((uint) offset, (uint) length);

	return ErrorOk;
}

DLLEXPORT double MADX9_BufferSeek(double buf, double offset)
{
	doubleToPtr<Buffer>(buf)->seek((uint) offset);

	return ErrorOk;
}

DLLEXPORT double MADX9_BufferTell(double buf)
{
	return doubleToPtr<Buffer>(buf)->tell();
}

DLLEXPORT double MADX9_BufferSize(double buf)
{
	return doubleToPtr<Buffer>(buf)->size();
}

DLLEXPORT double MADX9_BufferWrite(double buf, const void* data, double bufofs, double length)
{
	doubleToPtr<Buffer>(buf)->write((ubyte*) data + (uint) bufofs, (uint) length);

	return ErrorOk;
}

DLLEXPORT double MADX9_BufferWriteValue(double buf, double type, double value)
{
	switch ((Type) (uint) type)
	{
	case TypeU8:
		doubleToPtr<Buffer>(buf)->write<ubyte>((ubyte) value);
		break;
	case TypeU16:
		doubleToPtr<Buffer>(buf)->write<ushort>((ushort) value);
		break;
	case TypeU32:
		doubleToPtr<Buffer>(buf)->write<uint>((uint) value);
		break;
	case TypeS8:
		doubleToPtr<Buffer>(buf)->write<char>((char) value);
		break;
	case TypeS16:
		doubleToPtr<Buffer>(buf)->write<short>((short) value);
		break;
	case TypeS32:
		doubleToPtr<Buffer>(buf)->write<int>((int) value);
		break;
	case TypeF32:
		doubleToPtr<Buffer>(buf)->write<float>((float) value);
		break;
	case TypeF64:
		doubleToPtr<Buffer>(buf)->write<double>((double) value);
		break;
	default:
		return ErrorInv;
	}

	return ErrorOk;
}

DLLEXPORT double MADX9_BufferRead(double buf, void* data, double bufofs, double length)
{
	doubleToPtr<Buffer>(buf)->read((ubyte*) data + (uint) bufofs, (uint) length);

	return ErrorOk;
}

DLLEXPORT double MADX9_BufferReadValue(double buf, double type)
{
	switch ((Type) (uint) type)
	{
	case TypeU8:
		return doubleToPtr<Buffer>(buf)->read<ubyte>();
	case TypeU16:
		return doubleToPtr<Buffer>(buf)->read<ushort>();
	case TypeU32:
		return doubleToPtr<Buffer>(buf)->read<uint>();
	case TypeS8:
		return doubleToPtr<Buffer>(buf)->read<char>();
	case TypeS16:
		return doubleToPtr<Buffer>(buf)->read<short>();
	case TypeS32:
		return doubleToPtr<Buffer>(buf)->read<int>();
	case TypeF32:
		return doubleToPtr<Buffer>(buf)->read<float>();
	case TypeF64:
		return doubleToPtr<Buffer>(buf)->read<double>();
	default:
		return ErrorInv;
	}
}

DLLEXPORT double MADX9_BufferPoke(double buf, double offset, double bufofs, double length)
{
	doubleToPtr<Buffer>(buf)->poke((uint) offset, (ubyte*) bufferPtr + (uint) bufofs, (uint) length);

	return ErrorOk;
}

DLLEXPORT double MADX9_BufferPokeValue(double buf, double offset, double type, double value)
{
	switch ((Type) (uint) type)
	{
	case TypeU8:
		doubleToPtr<Buffer>(buf)->poke<ubyte>((uint) offset, (ubyte) value);
		break;
	case TypeU16:
		doubleToPtr<Buffer>(buf)->poke<ushort>((uint) offset, (ushort) value);
		break;
	case TypeU32:
		doubleToPtr<Buffer>(buf)->poke<uint>((uint) offset, (uint) value);
		break;
	case TypeS8:
		doubleToPtr<Buffer>(buf)->poke<char>((uint) offset, (char) value);
		break;
	case TypeS16:
		doubleToPtr<Buffer>(buf)->poke<short>((uint) offset, (short) value);
		break;
	case TypeS32:
		doubleToPtr<Buffer>(buf)->poke<int>((uint) offset, (int) value);
		break;
	case TypeF32:
		doubleToPtr<Buffer>(buf)->poke<float>((uint) offset, (float) value);
		break;
	case TypeF64:
		doubleToPtr<Buffer>(buf)->poke<double>((uint) offset, (double) value);
		break;
	default:
		return ErrorInv;
	}

	return ErrorOk;
}

DLLEXPORT double MADX9_BufferPeek(double buf, double offset, double bufofs, double length)
{
	doubleToPtr<Buffer>(buf)->peek((uint) offset, (ubyte*) bufferPtr + (uint) bufofs, (uint) length);

	return ErrorOk;
}

DLLEXPORT double MADX9_BufferPeekValue(double buf, double offset, double type)
{
	switch ((Type) (uint) type)
	{
	case TypeU8:
		return doubleToPtr<Buffer>(buf)->peek<ubyte>((uint) offset);
	case TypeU16:
		return doubleToPtr<Buffer>(buf)->peek<ushort>((uint) offset);
	case TypeU32:
		return doubleToPtr<Buffer>(buf)->peek<uint>((uint) offset);
	case TypeS8:
		return doubleToPtr<Buffer>(buf)->peek<char>((uint) offset);
	case TypeS16:
		return doubleToPtr<Buffer>(buf)->peek<short>((uint) offset);
	case TypeS32:
		return doubleToPtr<Buffer>(buf)->peek<int>((uint) offset);
	case TypeF32:
		return doubleToPtr<Buffer>(buf)->peek<float>((uint) offset);
	case TypeF64:
		return doubleToPtr<Buffer>(buf)->peek<double>((uint) offset);
	default:
		return ErrorInv;
	}
}

DLLEXPORT double MADX9_BufferSetPointer(void* ptr)
{
	bufferPtr = ptr;
	return ErrorOk;
}
