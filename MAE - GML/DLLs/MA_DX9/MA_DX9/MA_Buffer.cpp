#include "Main.h"
#include "Types.h"
#include "Buffer.h"
#include "Memory.h"
#include "Utils.h"

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

void* bufferPtr = 0;

DLLEXPORT double MADX9_BufferCreate()
{
	return putInto(new Buffer(new DynamicMemory()), mamain->Buffers);
}

DLLEXPORT double MADX9_BufferDestroy(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return 0;

	delete mamain->Buffers[(uint) ind];
	mamain->Buffers[(uint) ind] = 0;

	return 1;
}

DLLEXPORT double MADX9_BufferReserve(double ind, double amount)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return 0;

	mamain->Buffers[(uint) ind]->reserve((uint) amount);

	return 1;
}

DLLEXPORT double MADX9_BufferRemove(double ind, double offset, double length)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return 0;

	mamain->Buffers[(uint) ind]->remove((uint) offset, (uint) length);

	return 1;
}

DLLEXPORT double MADX9_BufferSeek(double ind, double offset)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return 0;

	mamain->Buffers[(uint) ind]->seek((uint) offset);

	return 1;
}

DLLEXPORT double MADX9_BufferTell(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return -1;

	return mamain->Buffers[(uint) ind]->tell();
}

DLLEXPORT double MADX9_BufferSize(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return -1;

	return mamain->Buffers[(uint) ind]->size();
}

DLLEXPORT double MADX9_BufferWrite(double ind, const void* data, double bufofs, double length)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return 0;

	mamain->Buffers[(uint) ind]->write((ubyte*) data + (uint) bufofs, (uint) length);

	return 1;
}

DLLEXPORT double MADX9_BufferWriteValue(double ind, double type, double value)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return 0;

	switch ((Type) (uint) type)
	{
	case TypeU8:
		mamain->Buffers[(uint) ind]->write<ubyte>((ubyte) value);
		break;
	case TypeU16:
		mamain->Buffers[(uint) ind]->write<ushort>((ushort) value);
		break;
	case TypeU32:
		mamain->Buffers[(uint) ind]->write<uint>((uint) value);
		break;
	case TypeS8:
		mamain->Buffers[(uint) ind]->write<char>((char) value);
		break;
	case TypeS16:
		mamain->Buffers[(uint) ind]->write<short>((short) value);
		break;
	case TypeS32:
		mamain->Buffers[(uint) ind]->write<int>((int) value);
		break;
	case TypeF32:
		mamain->Buffers[(uint) ind]->write<float>((float) value);
		break;
	case TypeF64:
		mamain->Buffers[(uint) ind]->write<double>((double) value);
		break;
	default:
		return 0;
	}

	return 1;
}

DLLEXPORT double MADX9_BufferRead(double ind, void* data, double bufofs, double length)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return 0;

	mamain->Buffers[(uint) ind]->read((ubyte*) data + (uint) bufofs, (uint) length);

	return 1;
}

DLLEXPORT double MADX9_BufferReadValue(double ind, double type)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return -1;

	switch ((Type) (uint) type)
	{
	case TypeU8:
		return mamain->Buffers[(uint) ind]->read<ubyte>();
	case TypeU16:
		return mamain->Buffers[(uint) ind]->read<ushort>();
	case TypeU32:
		return mamain->Buffers[(uint) ind]->read<uint>();
	case TypeS8:
		return mamain->Buffers[(uint) ind]->read<char>();
	case TypeS16:
		return mamain->Buffers[(uint) ind]->read<short>();
	case TypeS32:
		return mamain->Buffers[(uint) ind]->read<int>();
	case TypeF32:
		return mamain->Buffers[(uint) ind]->read<float>();
	case TypeF64:
		return mamain->Buffers[(uint) ind]->read<double>();
	}

	return 1;
}

DLLEXPORT double MADX9_BufferPoke(double ind, double offset, double bufofs, double length)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return 0;

	mamain->Buffers[(uint) ind]->poke((uint) offset, (ubyte*) bufferPtr + (uint) bufofs, (uint) length);

	return 1;
}

DLLEXPORT double MADX9_BufferPokeValue(double ind, double offset, double type, double value)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return 0;

	switch ((Type) (uint) type)
	{
	case TypeU8:
		mamain->Buffers[(uint) ind]->poke<ubyte>((uint) offset, (ubyte) value);
		break;
	case TypeU16:
		mamain->Buffers[(uint) ind]->poke<ushort>((uint) offset, (ushort) value);
		break;
	case TypeU32:
		mamain->Buffers[(uint) ind]->poke<uint>((uint) offset, (uint) value);
		break;
	case TypeS8:
		mamain->Buffers[(uint) ind]->poke<char>((uint) offset, (char) value);
		break;
	case TypeS16:
		mamain->Buffers[(uint) ind]->poke<short>((uint) offset, (short) value);
		break;
	case TypeS32:
		mamain->Buffers[(uint) ind]->poke<int>((uint) offset, (int) value);
		break;
	case TypeF32:
		mamain->Buffers[(uint) ind]->poke<float>((uint) offset, (float) value);
		break;
	case TypeF64:
		mamain->Buffers[(uint) ind]->poke<double>((uint) offset, (double) value);
		break;
	default:
		return 0;
	}

	return 1;
}

DLLEXPORT double MADX9_BufferPeek(double ind, double offset, double bufofs, double length)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return 0;

	mamain->Buffers[(uint) ind]->peek((uint) offset, (ubyte*) bufferPtr + (uint) bufofs, (uint) length);

	return 1;
}

DLLEXPORT double MADX9_BufferPeekValue(double ind, double offset, double type)
{
	if (!isValidIndex((uint) ind, mamain->Buffers))
		return -1;

	switch ((Type) (uint) type)
	{
	case TypeU8:
		return mamain->Buffers[(uint) ind]->peek<ubyte>((uint) offset);
	case TypeU16:
		return mamain->Buffers[(uint) ind]->peek<ushort>((uint) offset);
	case TypeU32:
		return mamain->Buffers[(uint) ind]->peek<uint>((uint) offset);
	case TypeS8:
		return mamain->Buffers[(uint) ind]->peek<char>((uint) offset);
	case TypeS16:
		return mamain->Buffers[(uint) ind]->peek<short>((uint) offset);
	case TypeS32:
		return mamain->Buffers[(uint) ind]->peek<int>((uint) offset);
	case TypeF32:
		return mamain->Buffers[(uint) ind]->peek<float>((uint) offset);
	case TypeF64:
		return mamain->Buffers[(uint) ind]->peek<double>((uint) offset);
	}

	return 1;
}

DLLEXPORT double MADX9_BufferSetPointer(void* ptr)
{
	bufferPtr = ptr;
	return 1;
}
