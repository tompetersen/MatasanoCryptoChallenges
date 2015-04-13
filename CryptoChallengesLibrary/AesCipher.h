/*
 * AesCipher.h
 *
 *  Created on: 13.04.2015
 *      Author: Tom Petersen
 */

#ifndef AESCIPHER_H_
#define AESCIPHER_H_

class AesCipher {
public:
	int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *plaintext);
	AesCipher();
	~AesCipher();
};

#endif /* AESCIPHER_H_ */
