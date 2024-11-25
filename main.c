#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "sph_bmw.h"

void dumpHex(void *ptr, int ln) {
	printf("hex dump: ");
	for(int i = 0; i < ln; i++)
		printf("%02x", (*((char*)ptr+i)) & 0xff);
	printf("\n");
}

inline static void __attribute__((optimize("O0"))) poisonStack(char v) {
	char st[65536];
	memset(st, v, sizeof(st)); // 0xAA is a common pattern for debugging
}

int main() {
	unsigned char in[32];
	uint32_t hashA[8];
	sph_bmw256_context ctx_bmw;
	sph_bmw256_context ctx_bmw2;

	// init in
	for(int i = 0; i < 32; i++) in[i] = i*8;

	printf("input");
	dumpHex(in, sizeof(in));

	// pass 32 bytes of input
	sph_bmw256_init(&ctx_bmw);
	sph_bmw256(&ctx_bmw, in, 32);
	sph_bmw256_close(&ctx_bmw, hashA);

	// output
	dumpHex(hashA, 32);

	printf("input");
	dumpHex(in, sizeof(in));

	poisonStack(0x42);

	sph_bmw256_init(&ctx_bmw2);
	sph_bmw256(&ctx_bmw2, in, 32);
	sph_bmw256_close(&ctx_bmw2, hashA);

	dumpHex(hashA, 32);
	return 0;
}
