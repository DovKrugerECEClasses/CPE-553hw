#pragma once

/*
	This function is allowed to assume that src and dest are 8-byte aligned,
	therefore copying a uint64_t-worth of data should be 8 times faster
	Since n is not guaranteed to be a multiple of 8, you must at the end handle
	any remaining bytes 1 by 1.
 */
void copymemAlignedNoOverlap(void* dest, void* src, unit32_t numBytes) {
	char* p = dest;
	char* q = src;
	for (uint32_t i = 0; i < numbytes; i++)
		p[i] = q[i];
}

/*
	In this code you must check whether dest < src + numbytes or src < dest + numbytes
	and make sure that the copy ends up correct regardless.
	You must also not assume that src and dest are 8-byte aligned.
	This is effectively the same code as memcpy
 */
void copymemAlignedOverlap(void* dest, void* src, uint32_t numbytes) {
	char* p = dest;
	char* q = src;
	for (uint32_t i = 0; i < numbytes; i++)
		p[i] = q[i];
}

void copyUnaligned(void* dest, void* src, uint32_t numbytes) {
	char* p = dest;
	char* q = src;
	for (uint32_t i = 0; i < numbytes; i++)
		p[i] = q[i];
}

void copyBytes(void* dest, void* src, uint32_t numbytes) {
	char* p = dest;
	char* q = src;
	for (uint32_t i = 0; i < numbytes; i++)
		p[i] = q[i];
}
