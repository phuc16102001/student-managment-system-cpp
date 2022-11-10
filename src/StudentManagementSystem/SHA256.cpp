#include "SHA256.h"

struct Block {
	//Variable is 32 bit
	uchar data[64];		//Split 64 chars (512 bits) into a block
	uint datalen;		//Length of data above
	uint bitlen[2];		//String input len in 64 bit (using big endian)
	uint state[8];		//H0-H7
};

uint k[64] = {
	//Constant K
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

void SHA256Transform(Block* block, uchar data[])
{
	uint a, b, c, d, e, f, g, h, i, j, t1, t2, w[64];

	//Split 64 chars into 16 blocks 32 bits into 
	//1 block will contain 4 chars (4*8=32 bits)
	for (i = 0, j = 0; i < 16; ++i, j += 4)
		w[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);

	//Ext loop
	for (; i < 64; ++i)
		w[i] = SIG1(w[i - 2]) + w[i - 7] + SIG0(w[i - 15]) + w[i - 16];

	//Init hash value
	a = block->state[0];
	b = block->state[1];
	c = block->state[2];
	d = block->state[3];
	e = block->state[4];
	f = block->state[5];
	g = block->state[6];
	h = block->state[7];

	//Main loop
	for (i = 0; i < 64; ++i) {
		t1 = h + EP1(e) + CH(e, f, g) + k[i] + w[i];
		t2 = EP0(a) + MAJ(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	//Plus hash value
	block->state[0] += a;
	block->state[1] += b;
	block->state[2] += c;
	block->state[3] += d;
	block->state[4] += e;
	block->state[5] += f;
	block->state[6] += g;
	block->state[7] += h;
}

void SHA256Init(Block* block)
{
	//H0-H7
	block->datalen = 0;
	block->bitlen[0] = 0;
	block->bitlen[1] = 0;
	block->state[0] = 0x6a09e667;
	block->state[1] = 0xbb67ae85;
	block->state[2] = 0x3c6ef372;
	block->state[3] = 0xa54ff53a;
	block->state[4] = 0x510e527f;
	block->state[5] = 0x9b05688c;
	block->state[6] = 0x1f83d9ab;
	block->state[7] = 0x5be0cd19;
}

void SHA256Update(Block* block, uchar data[], uint len)
{
	//Process all the data[] (length's len)
	for (uint i = 0; i < len; ++i) {
		//Put all the input string into ctx->data
		block->data[block->datalen] = data[i];
		block->datalen++;

		//With each block (512bits = 64 chars = 64 bytes)
		if (block->datalen == 64) {
			//Hash the block then reset data
			SHA256Transform(block, block->data);

			//Plus the 512 bits (64 bytes = 64 chars)
			DBL_INT_ADD(block->bitlen[0], block->bitlen[1], 512);
			block->datalen = 0;
		}
	}
}

void SHA256Final(Block* block, uchar hash[])
{
	uint i = block->datalen;

	//Add +1 and 0's until the length is 448+512k or 448 (mod 512)
	//Then encode the string length into 64 bits variable 
	//Total length of the hash bits will have the length of 512k (k is int)
	if (block->datalen < 56) {
		block->data[i++] = 0x80;		//1000 0000

		while (i < 56)				//448 bits for 64 bits (8 bytes) for the length
			block->data[i++] = 0x00;	//0000 0000
	}
	else {
		block->data[i++] = 0x80;		//1000 0000

		while (i < 64)
			block->data[i++] = 0x00;	//0000 0000

		SHA256Transform(block, block->data);
		memset(block->data, 0, 56);
	}

	//Plus the last length of block string
	//Note: datalen != len(data) because the upper block is using i as the variable
	DBL_INT_ADD(block->bitlen[0], block->bitlen[1], block->datalen * 8);

	//Hash the last block (0's bits and the length in int64 = 8 bytes)
	block->data[63] = block->bitlen[0];
	block->data[62] = block->bitlen[0] >> 8;
	block->data[61] = block->bitlen[0] >> 16;
	block->data[60] = block->bitlen[0] >> 24;
	block->data[59] = block->bitlen[1];
	block->data[58] = block->bitlen[1] >> 8;
	block->data[57] = block->bitlen[1] >> 16;
	block->data[56] = block->bitlen[1] >> 24;

	//Hash the last block
	SHA256Transform(block, block->data);

	//Create hash string from state
	//State[k] will be place hash[4k-1,4k+3]
	for (i = 0; i < 4; ++i) {
		hash[i] = (block->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4] = (block->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8] = (block->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (block->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (block->state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (block->state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (block->state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (block->state[7] >> (24 - i * 8)) & 0x000000ff;
	}
}

string SHA256(string inputText) {
	//Convert input data into CString
	char* data = (char*)inputText.c_str();
	int strLen = strlen(data);
	
	//Init variable
	Block block;
	uchar hash[32];
	string hashStr = "";

	//Init h[]
	SHA256Init(&block);

	//Transform each block contain 64 chars
	SHA256Update(&block, (uchar*)data, strLen);

	//Final step for the block of remain and string length
	SHA256Final(&block, hash);


	char s[3];
	for (int i = 0; i < 32; i++) {
		//Convert the hash array into string
		//Each 8 bits will convert into 2 hex chars
		//log[16](2^8)=2 hex chars
		sprintf(s, "%02x", hash[i]);

		//Add into hash string
		hashStr += s;
	}

	return hashStr;
}