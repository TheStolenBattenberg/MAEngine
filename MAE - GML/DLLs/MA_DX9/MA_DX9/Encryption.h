#pragma once

/**
 * Includes
 */
#include "Main.h"
#include "Types.h"

class Encryption { //Probably won't add all of these, and it might be better to get a third party library anyway.
public:
	enum ENC_TYPE {
		ENC_XOR,	//https://en.wikipedia.org/wiki/XOR_cipher
		ENC_TEA,	//https://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm
		ENC_AES,	//https://en.wikipedia.org/wiki/Advanced_Encryption_Standard
		ENC_RC4		//https://en.wikipedia.org/wiki/RC4
	};

	enum HSH_TYPE {
		HSH_MD5,	//https://en.wikipedia.org/wiki/MD5
		HSH_SHA256	//https://en.wikipedia.org/wiki/SHA-2
	};

	char* encrypt(ENC_TYPE type, char* data, uint datalength, char* key, uint keylength);
	char* decrypt(ENC_TYPE type, char* data, uint datalength, char* key, uint keylength);

	char* hash(HSH_TYPE type, char* data);
};