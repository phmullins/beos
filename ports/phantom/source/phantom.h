/*
 *
 * Phantom is Copyright (C) 1996 Kaz Kylheku
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * The author may be contacted at:
 *
 * Kaz Kylheku
 * 2869 East 14th Avenue
 * Vancouver, B.C.
 * CANADA
 * V5M 2H8
 * email: kaz@cafe.net
 *
 */

#include <stddef.h>

typedef unsigned char pha_key[32];		/* 256 bit key		*/
typedef unsigned char pha_cblock[16];		/* 128 bit cipherblock	*/
typedef unsigned long pha_key_internal[8];
typedef unsigned long pha_cblock_internal[4];

typedef struct {
    unsigned long piece[32][2];
} pha_schedule;

typedef unsigned char pha_sbox[256];
typedef pha_sbox pha_sbox_group[16];

void pha_schedule_key(pha_key *key, pha_schedule *sched);
void pha_encipher(pha_cblock *plain, pha_cblock *cipher, pha_schedule *sched);
void pha_decipher(pha_cblock *cipher, pha_cblock *plain, pha_schedule *sched);
void pha_cbc_encipher(pha_cblock *plain, pha_cblock *cipher, pha_cblock *ivec,
	pha_schedule *sched, size_t nbytes);
void pha_cbc_decipher(pha_cblock *cipher, pha_cblock *plain, pha_cblock *ivec,
	pha_schedule *sched, size_t nbytes);
void pha_cfb_encipher(unsigned char *plain, unsigned char *cipher,
	pha_cblock *ivec, pha_schedule *sched, size_t nbytes);
void pha_cfb_decipher(unsigned char *cipher, unsigned char *plain,
	pha_cblock *ivec, pha_schedule *sched, size_t nbytes);
int pha_phrase_to_key(char *text, size_t len, pha_key *key);
int pha_phrase_to_cblock(char *text, size_t len, pha_cblock *vec);
void pha_load_sboxes(pha_sbox_group *sbgroup);
void pha_load_sbox(int s, pha_sbox *sbox);

extern pha_sbox_group sbox;
