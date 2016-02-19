#include "Encryption.h"

char* Encryption::encrypt(ENC_TYPE type, char* data, uint datalength, char* key, uint keylength) {
	/*char* encrypted;
	
	switch (type) {
		case ENC_XOR:
			uint keypos = 0;
			for (uint i = 0; i < datalength; ++i) {
				if (keypos > keylength)
					keypos = 0;


				encrypted[i] = data[i] ^ key[keypos];
				keypos++;
			}
		break;
	}
	return encrypted;*/
	return nullptr;
}

char* Encryption::decrypt(ENC_TYPE type, char* data, uint datalength, char* key, uint keylength) {
	/*char* decrypted;

	switch (type) {
	case ENC_XOR:
		uint keypos = 0;
		for (uint i = 0; i < datalength; ++i) {
			if (keypos > keylength)
				keypos = 0;


			decrypted[i] = data[i] ^ key[keypos];
			keypos++;
		}
		break;
	}
	return decrypted;*/
	return nullptr;
}

char* Encryption::hash(HSH_TYPE type, char* data) {
	/*char* hashed;
		//to-do.
	return hashed;*/
	return nullptr;
}