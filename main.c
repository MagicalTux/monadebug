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
	char st[65536*16*2];
	memset(st, v, sizeof(st)); // 0xAA is a common pattern for debugging
}

int main() {
	unsigned char in[32] = {0x52, 0x57, 0x41, 0xcc, 0xfd, 0x92, 0x26, 0x03, 0x55, 0x37, 0x5c, 0x59, 0x72, 0xa0, 0x72, 0x46, 0x2c, 0x35, 0x11, 0x3a, 0x61, 0x91, 0xfd, 0xf1, 0xfd, 0xa1, 0x78, 0xa0, 0x89, 0x09, 0x5a, 0x3b};
	uint32_t hashA[8];
	sph_bmw256_context ctx_bmw;
	sph_bmw256_context ctx_bmw2;

	printf("input");
	dumpHex(in, sizeof(in));

	poisonStack(0);

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
