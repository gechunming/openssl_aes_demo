#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>

int main(int argc, char *argv[])
{
	AES_KEY aes;

	unsigned char key[AES_BLOCK_SIZE];
	unsigned char iv[AES_BLOCK_SIZE];
	unsigned char input_array[512] = {0};
	unsigned char output_array[512] = {0};

	int i;

	for (i = 0; i < 36; i++) {
		input_array[i] = i;
	}
	for (i = 0; i < 16; i++) {
		key[i] = i;
	}

	for (i = 0; i < AES_BLOCK_SIZE; ++i) {
		iv[i] = 0;
	}

	if (AES_set_encrypt_key(key, 128, &aes) < 0) {
		printf("set encrypt key error\n");
	}

	AES_cbc_encrypt(input_array, output_array, 32, &aes, iv, AES_ENCRYPT);

	//now output the output
	printf("unsigned char input_array[] = {\n");
	for (i = 0; i < 33; i++) {
		printf("0x%02x,", output_array[i]);
	}
	printf("\n};\n");
	return 0;
}
