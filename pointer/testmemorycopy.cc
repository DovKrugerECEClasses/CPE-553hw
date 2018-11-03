#include <cstring>
#include <iostream>
#include <memory.h>
#include "memorycopy.hh"

using namespace std;
/*
 * this function tests whether each copy function behaves as it is supposed to
 * Once this is established, test the speed of each function to compare their speed
 */
void correctnessTest() {
	char src[] = "This is a test";
	char dest1[15];
	copymemAlignedNoOverlap(dest, src, sizeof(src));
	
	cout << "Test1 dest=" << dest << "\n";
	
	char src[32] = "This is a test";
	copymemAlignedOverlap(src+8, src, strlen(src));
	cout << "Test2 buffer=" << src << "\n";

	char src2[32] = "Testing testing 123";
	copymemAlignedOverlap(src2, src2+8, strlen(src2)-8);
	cout << "Test3 buffer=" << src2 << "\n";
}

void speedtest1(char* dest, char* src, uint32_t n) {
	copymemAlignedNoOverlap(dest, src, n);
}

void speedtest2(char* dest, char* src, uint32_t n) {
	 copymemAlignedOverlap(dest, src, n);
}

void speedtest3(char* dest, char* src, uint32_t n) {
	memcpy(dest, src, n);
}



int main(int argc, char* argv[]) {
	if (argc < 3) {
		cerr << "Usage: testmemcopy test# numbytes\n";
		exit(-1);
	}
	
	uint32_t testNum = atoi(argv[1]);
	uint32_t n = atoi(argv[2]);
	char * p = new char[n];
	char * q = new char[n];
	
	switch(testNum) {
	case 0: correctnessTest(); break;
	case 1: speedTest1(p, q, n); break;
	case 2: speedTest2(p+8, p, n-8); break; // test copying forwards in overlap buffer
	case 3: speedTest2(p, p+8, n-8); break; // test copying backwards in overlap buffer
	case 4: speedTest3(p, q, n); break;     // test memcpy separate buffers
	case 5: speedTest3(p, p+8, n-8); break; // test memcpy, overlapping fwd
	case 6: speedTest3(p+8, p, n-8); break; // test memcpy, overlapping backward
	case 7: speedTest1(p+2, q, n-2); break; // test copy forwards unaligned
	case 8: speedTest4(p, q, n); break;     // test bytewise copy aligned
	case 9: speedTest4(p+1, q, n-1); break; // test bytewise copy unaligned
	default:
		cerr << "No test selected\n";
	}

	copymemAlignedOverlap(p, p+8, n-8);



	delete [] p;
	delete [] q;
}
