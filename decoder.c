#include "lbccodec.h"
#include <stdio.h>
#include <stdlib.h>

#define SAMPLES_PER_FRAME 240

int main(int argc, char *argv[]) {
	if (argc < 4) {
		printf("usage: ./decoder MODE encoded.bin decoded.raw\n\n");
		printf("MODES:\n0: 5.33333 kbps ACELP\n1: 6.4 kbps MPC-MLQ\n");
		return -1;
	}

	int mode = atoi(argv[1]);
	int BYTES_PER_FRAME;
	if (mode == 0) {
		BYTES_PER_FRAME = 20;
		g723_i(1, 0);
		printf("using 5.33333 kbps ACELP\n");
	} else {
		BYTES_PER_FRAME = 24;
		g723_i(0, 0);
		printf("using 6.4 kbps MPC-MLQ\n");
	};

	short outbuf[SAMPLES_PER_FRAME];
	unsigned char inbuf[BYTES_PER_FRAME];

	FILE *fin = fopen(argv[2], "rb");
	FILE *fout = fopen(argv[3], "wb");

	int i = 0;
	while(fread(inbuf, 1, BYTES_PER_FRAME, fin) == BYTES_PER_FRAME) {
		printf("frames decoded: %d\r", i);
		fflush(stdout);
		g723_d(inbuf, outbuf);
		fwrite(outbuf, SAMPLES_PER_FRAME, 2, fout);
		i++;
	}
	return 0;
}
