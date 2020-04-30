#ifndef _SHA_256_
#define _SHA_256_

#include "Constant.h"

#define uchar unsigned char
#define uint unsigned int

#define DBL_INT_ADD(a,b,c) if (a > 0xffffffff - (c)) ++b; a += c;	//add c into a number which store by a, b (uint)
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))				//a rotate left b times
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))			//a rotate right b times

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))						//CH
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))		//MAJ
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))	//S0
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))	//S1
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))		//S0 ext
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))		//S1 ext

string SHA256(string inputText);

#endif