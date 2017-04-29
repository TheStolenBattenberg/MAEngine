#pragma once

#include <MAE/Core/Types.h>

namespace RIFFormat {
	typedef struct {
		char ChunkID[4]; //'RIFF'
		uint ChunkSize; //File Size - 8
		char Format[4]; //'WAVE'?
	} RIFF;

	typedef struct {
		char   ChunkID[4]; //'fmt '
		uint   ChunkSize; //16 Bytes.
		ushort AudioFormat; //We're looking for 1 ( PCM )
		ushort NumChannels; //Either 1 or 2, 3 is probably 5.1
		uint   SampleRate;  //Sample rate, IE 44,100, 48,000, 96, 000 etc
		uint   ByteRate;    //Byte rate. Pointless.
		ushort BlockAlign;  //BlockAlign, 1 in 8bit, 2 in 16 bit, 4 in 32bit.
		ushort BitsPerSample; //8, 16, 32 etc...
	} FMT;

	typedef struct {
		char   ChunkID[4]; //'data'
		uint   ChunkSize;  //Bytesize of Samples.
		ubyte* Samples;    //Audio Sample Data.
	} DATA;

}