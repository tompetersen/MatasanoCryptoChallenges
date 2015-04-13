#include <iostream>
#include <fstream>
#include <string.h>
#include "Base64.h"
#include "assert.h"

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#ifndef OPEN_SSL_APPLINK
#define OPEN_SSL_APPLINK
#include <openssl/applink.c>
#endif


using namespace std;

/**
 * Steps: (Win 7)
 *
 * Install OpenSSL-Win32 to C:\OpenSSL-Win32
 * (make sure to install correct Visual C++ 2008 Redistribution version before)
 * URL: https://slproweb.com/products/Win32OpenSSL.html
 * File: Win32 OpenSSL v1.0.2a
 *
 * Project-Properties -> C/C++ General -> Path and Symbols
 * Add "C:\OpenSSL-Win32\include" to Includes
 * Add "C:\OpenSSL-Win32\lib\MinGW" to Library Paths
 * Add "eay32" to Libraries (don't know what to add for "ssleay32.a")
 *
 * Add Includes to source file
 * To prevent gcc errors in applink.c add casts (void*) in includes/applink.c
 *
 *
 *
 * OpenSSL Wiki
 * EVP Symmetric Encryption and Decryption
 * https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
 *
 */


void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;
  int len;
  int plaintext_len;

  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new())) {
	  handleErrors();
  }

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
     and IV size appropriate for your cipher
     In this example we are using 128 bit AES (i.e. a 128 bit key). The
     IV size for *most* modes is the same as the block size. For AES this
     is 128 bits */
  if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL)) {
    handleErrors();
  }

  /* Provide the message to be decrypted, and obtain the plaintext output.
     EVP_DecryptUpdate can be called multiple times if necessary */
  if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) {
    handleErrors();
  }
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
     this stage.*/
  if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
	handleErrors();
  }
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

string getFileContents() {
	ifstream fIn("../7.txt");
	assert(fIn);
	string result;

	string str;
	while (fIn >> str) {
		result += str;
	}
	fIn.close();

	return result;
}


int main() {
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);

	unsigned char* KEY = (unsigned char*)"YELLOW SUBMARINE";
	string input = getFileContents();
	vector<byte> inputRaw = Base64::fromBase64(input);

	cout << "InputRawSize=" << inputRaw.size() << endl;
	unsigned char result[inputRaw.size()]; //HMMMM, verreckt wenn zu klein...
	int resultLength = decrypt(&inputRaw[0], inputRaw.size(), KEY, result);

	cout << "RESULT (length = " << resultLength << "): " << endl << endl;// << result << endl;
	for (int i = 0; i < resultLength; i++) {
		cout << result[i];
	}

	EVP_cleanup();
	ERR_free_strings();

	return 0;
}
