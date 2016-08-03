CC=gcc  
CFLAGS=-Wall -g -O2  
LIBS=-lcrypto
   
all: dec  
   
enc: dec.c 
	$(CC) $(CFLAGS) dec.c -o $@ -lcrypto  
   
clean:  
	@rm -f enc  
