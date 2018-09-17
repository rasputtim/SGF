/*
 * Copyright (c) 2007 Heiko Irrgang
 *
 * The license and distribution terms for this file may be
 * found in the file COPYING in this distribution or at
 * http://agnosent.com/wolfcms/open-source/sge2d/license.html
 */

#include <sge.h>

int sgeGetDistance(int x, int y, int xx, int yy) {
	int distx=xx-x;
	int disty=yy-y;

	return (int) sgeRound(sqrt(distx*distx+disty*disty));
}

char *sgeMD5(const unsigned char *data, unsigned int datalen) {
	char *ret=NULL;
	int i;
	md5_state_t md5;
	md5_byte_t digest[16];

	md5_init(&md5);
	md5_append(&md5, (const md5_byte_t *)data, datalen);
	md5_finish(&md5, digest);

	sgeMalloc(ret, char, 33);
	for (i=0; i<16; i++) {
		sprintf(ret+i*2, "%0x", digest[i]);
	}
	return ret;
}

char *sgeSHA1(const unsigned char *data, unsigned int datalen) {
	char *ret=NULL;
	int i=0;
	SHA1Context sha;

	SHA1Reset(&sha);
	SHA1Input(&sha, data, datalen);
	SHA1Result(&sha);

	sgeMalloc(ret, char, 41);
	for (i=0; i<5; i++) {
		sprintf(ret+i*8, "%08x", sha.Message_Digest[i]);
	}
	return ret;
}

