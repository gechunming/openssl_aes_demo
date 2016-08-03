#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>

#include "test.h"

int main(int argc, char *argv[])
{
	AES_KEY aes;

	unsigned char key[AES_BLOCK_SIZE];
	unsigned char iv[AES_BLOCK_SIZE];

	unsigned char output_array[512];	
	int i;
#if 0
	for (i = 0; i < 32; i++) {
		input_array[i] = i;
	}
#endif
	for (i = 0; i < 16; i++) {
		key[i] = i;
	}

	for (i = 0; i < AES_BLOCK_SIZE; ++i) {
		iv[i] = 0;
	}

	if (AES_set_decrypt_key(key,128,&aes) < 0) {
		printf("set decrpyt key error\n");
	}

	AES_cbc_encrypt(input_array, output_array, 32, &aes, iv, AES_DECRYPT);
	printf("encrypted data\n");
	for (i=0; i<32; ++i) {  
		printf("0x%02x,", input_array[i]);
	}  
	printf("\n");  
	printf("decrypted:\n");  
	for (i=0; i<32; ++i) {  
		printf("0x%02x,", output_array[i]);
	}  
	printf("\n");  
}
