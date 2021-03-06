/* 
 * aes.cc 
 * - Show the usage of AES encryption/decryption 
 */  

#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <openssl/aes.h>  

int main(int argc, char** argv) {  
	AES_KEY aes;  
	unsigned char key[AES_BLOCK_SIZE];        // AES_BLOCK_SIZE = 16  
	unsigned char iv[AES_BLOCK_SIZE];         // init vector  
	unsigned char* input_string;  
	unsigned char* encrypt_string;  
	unsigned char* decrypt_string;  
	unsigned int len;        // encrypt length (in multiple of AES_BLOCK_SIZE)  
	unsigned int i;  

	// check usage  
	if (argc != 2) {  
		fprintf(stderr, "%s <plain text>\n", argv[0]);  
		exit(-1);  
	}  

	// set the encryption length  
	len = 0;  
	if ((strlen(argv[1]) + 1) % AES_BLOCK_SIZE == 0) {  
		len = strlen(argv[1]) + 1;  
	} else {  
		len = ((strlen(argv[1]) + 1) / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;  
	}  
	printf("AES_BLOCK_SIZE=%d, len=%d\n", AES_BLOCK_SIZE, len);
	len = 32;

	// set the input string  
	input_string = (unsigned char*)calloc(len, sizeof(unsigned char));  
	if (input_string == NULL) {  
		fprintf(stderr, "Unable to allocate memory for input_string\n");  
		exit(-1);  
	}  
	strncpy((char*)input_string, argv[1], strlen(argv[1]));  

	//for input_string test
	for (i = 0; i < 36; i++) {
		input_string[i] = i;
	}
	// Generate AES 128-bit key  
	for (i=0; i<16; ++i) {  
		key[i] = i;  
	}  

	// Set encryption key  
	for (i=0; i<AES_BLOCK_SIZE; ++i) {  
		iv[i] = 0;  
	}  
	if (AES_set_encrypt_key(key, 128, &aes) < 0) {  
		fprintf(stderr, "Unable to set encryption key in AES\n");  
		exit(-1);  
	}  

	// alloc encrypt_string  
	encrypt_string = (unsigned char*)calloc(len, sizeof(unsigned char));      
	if (encrypt_string == NULL) {  
		fprintf(stderr, "Unable to allocate memory for encrypt_string\n");  
		exit(-1);  
	}  

	// encrypt (iv will change)  
	AES_cbc_encrypt(input_string, encrypt_string, len, &aes, iv, AES_ENCRYPT);  

	// alloc decrypt_string  
	decrypt_string = (unsigned char*)calloc(len, sizeof(unsigned char));  
	if (decrypt_string == NULL) {  
		fprintf(stderr, "Unable to allocate memory for decrypt_string\n");  
		exit(-1);  
	}  

	// Set decryption key  
	for (i=0; i<AES_BLOCK_SIZE; ++i) {  
		iv[i] = 0;  
	}  
	if (AES_set_decrypt_key(key, 128, &aes) < 0) {  
		fprintf(stderr, "Unable to set decryption key in AES\n");  
		exit(-1);  
	}  

	// decrypt  
	AES_cbc_encrypt(encrypt_string, decrypt_string, len, &aes, iv,   
			AES_DECRYPT);  

	// print  
	printf("input_string = \n");  
	for (i=0; i < len;++i) {
		printf("0x%02x,", input_string[i]);
	}
	printf("\nencrypted string = \n");  
	for (i=0; i<len; ++i) {  
		printf("0x%x%x,", (encrypt_string[i] >> 4) & 0xf,   
				encrypt_string[i] & 0xf);      
	}  
	printf("\n");  
	printf("decrypted string = \n");  
	for (i=0; i < len;++i) {
		printf("0x%02x,", decrypt_string[i]);
	}
	printf("\n");

	return 0;  
}  
