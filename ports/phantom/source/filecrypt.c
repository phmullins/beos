/*
 *
 * Phantom Cipher is Copyright (C) 1996 Kaz Kylheku
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

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "phantom.h"

#define MIN(a,b) ((a) < (b) ? (a) : (b))

static void parse_args(char **argv);
static void usage(void);
static void help(void);
static char *get_password(char *buf, char *buf2, char *prompt, size_t len, int confirm);
static void do_encrypt(char *infile, char *outfile, char *phrase, char *salt);
static void do_decrypt(char *infile, char *outfile, char *phrase);
static void get_key(pha_key *key, char *phrase);
static void get_ivec(pha_cblock *ivec, char *phrase);

static char pass[513];
static char conf[513];
static char salt[513];

static int encrypting;
static char *infile_name;
static char *outfile_name;
static char *key_phrase;
static char *salt_phrase;

int main(int argc, char **argv)
{
    parse_args(argv);

    if (encrypting && !salt_phrase) {
	get_password(salt_phrase = salt, NULL, "salt: ", sizeof salt, 0);
	if (!*salt) {
	    puts("quit");
	    exit(EXIT_SUCCESS);
	}
    }

    if (!key_phrase) {
	do {
	    get_password(key_phrase = pass, conf, "password: ",
		    sizeof pass, encrypting);
	    if (!*key_phrase)
		exit(EXIT_SUCCESS);
	} while (encrypting && strcmp(key_phrase, conf));
    }

    if (encrypting)
	do_encrypt(infile_name, outfile_name, key_phrase, salt_phrase);
    else
	do_decrypt(infile_name, outfile_name, key_phrase);

    return 0;
}

static void parse_args(char **argv)
{
    if (*++argv) {
	if (argv[0][0] == '-') {
	    switch (argv[0][1]) {
	    case 'e':
		encrypting = 1;
		break;
	    case 'd':
		break;
	    case 'h':
		help();
	    default:
		usage();
	    }
	    if (!(infile_name = *++argv)) {
		infile_name = "-";
		outfile_name = "-";
		return;
	    } else if (!(outfile_name = *++argv)) {
		outfile_name = "-";
		return;
	    }

	    if (encrypting) {
		if (!(salt_phrase = *++argv))
		    return;
	    }
	    key_phrase = *++argv;
	} else {
	    usage();
	}
    } else {
	usage();
    }
}

static void usage(void)
{
    char *text =
	"Phantom Cipher File Encryption\n"
	"Copyright 1997 by Kaz Kylheku Jr.\n"
	"Vancouver, B.C., Canada\n"
	"\n"
	"to encrypt:\n"
	"\n"
	"phantom -e [ <infile> [ <outfile> [ <salt_phrase> [ <key_phrase> ] ] ] ]\n"
	"\n"
	"to decrypt:\n"
	"\n"
	"phantom -d [ <infile> [ <outfile> [ <key_phrase> ] ] ]\n"
	"\n"
	"for extra help:\n"
	"\n"
	"phantom -h\n"
	"\n";


    fputs(text, stderr);
    exit(EXIT_FAILURE);
}

void help(void)
{
    char *text =
"Phantom Cipher File Encryption\n"
"Copyright 1997 by Kaz Kylheku Jr.\n"
"Vancouver, B.C., Canada\n"
"\n"
"This is a program which enciphers (or encrypts) files using the Phantom\n"
"cipher. Phantom is a block cipher which works on 128 bit cipher blocks and has\n"
"a key length of 256 bits. This program uses the cipher in the standard CBC\n"
"(cipher block chaining) mode; a mode of using a block cipher in a way which\n"
"provides extra security by hiding regularities in the plaintext. In a\n"
"nutshell, each plaintext block is exclusive-or-ed with the previous cipher\n"
"block prior to being encrypted. The first cipher block is xor-ed with a\n"
"randomized initial vector.  The 256 bit key is derived from a password phrase\n"
"(also called key phrase) using a one-way hashing function. Assume that each\n"
"letter of English text provides only 1.5 bits of ``entropy'' (information\n"
"content), hence to take advantage of the full security offered by a 256 bit\n"
"key, you must type a very long phrase. Choose something that is easy to\n"
"remember, but of a highly personal rather than cultural nature---something\n"
"that could be guessed only by someone who has lived in your shoes for most of\n"
"your life.  It's better not to specify the phrase (and salt phrase) on the\n"
"command line; leave them out and the program will let you enter them\n"
"interactively. The salt phrase is a piece of text which is hashed to form the\n"
"initial vector. It is not asked for during decryption because the\n"
"initial vector is retrieved directly from the the first cipher block of the\n"
"encrypted file.  Since you don't have to remember the salt phrase, it can (and\n"
"ought to) consist of about 20 or so characters of purely random nonsense\n"
"typing. Both the salt phrase and the key phrase may be up to 512 characters.\n";

    fputs(text, stdout);
    exit(EXIT_SUCCESS);
}

static char *get_password(char *buf, char *buf2, char *prompt, size_t len, int confirm)
{
    int term = open("/dev/tty", O_RDWR);
    FILE *term_s;
    struct termios save, new;
    char *fgetsret, *nl;

    if (term < 0) {
	perror("couldn't open /dev/tty");
	exit(EXIT_FAILURE);
    }

    term_s = fdopen(term, "a+");

    if (!term_s) {
	perror("fdopen failed on /dev/tty");
	exit(EXIT_FAILURE);
    }

    tcgetattr(term, &save);
    new = save;
    new.c_lflag &= ~ECHO;
    new.c_lflag |= ECHONL;
    tcsetattr(term, TCSANOW, &new);
    fprintf(term_s, "%s", prompt);
    fflush(term_s);
    fgetsret = fgets(buf, len, term_s);
    fseek(term_s, 0, SEEK_CUR);
    if ((nl = strchr(buf, '\n')))
	*nl = 0;
    if (confirm) {
	fprintf(term_s, "again: ");
	fflush(term_s);
	fgetsret = fgets(buf2, len, term_s);
	fseek(term_s, 0, SEEK_CUR);
	if ((nl = strchr(buf2, '\n')))
	    *nl = 0;
	if (strcmp(buf, buf2))
	    fprintf(term_s, "they don't match\n");
    }
    tcsetattr(term, TCSANOW, &save);
    fclose(term_s);
    return fgetsret;
}

static void do_encrypt(char *infile, char *outfile, char *phrase, char *salt)
{
    pha_key key;
    pha_schedule sched;
    unsigned char buf[1024];
    size_t n_in, n_out;
    pha_cblock ivec;

    FILE *in, *out;

    get_key(&key, phrase);
    get_ivec(&ivec, salt);

    pha_schedule_key(&key, &sched);

    if (strcmp(infile, "-") == 0)
	in = stdin;
    else
	in = fopen(infile, "rb");

    if (!in) {
	perror(infile);
	exit(EXIT_FAILURE);
    }

    if (strcmp(infile, "-") == 0)
	out = stdout;
    else
	out = fopen(outfile, "wb");

    if (!out) {
	perror(outfile);
	exit(EXIT_FAILURE);
    }

    fwrite(&ivec, 1, sizeof ivec, out);		/* store initial vector	*/

    while ((n_in = n_out = fread(buf, 1, sizeof buf, in))) {
	while (n_out % 16)
	    buf[n_out++] = n_in % 256;
	pha_cbc_encipher((pha_cblock *) buf, (pha_cblock *) buf, &ivec,
	    &sched, n_out);
	fwrite(buf, 1, n_out, out);
	if (n_in < sizeof buf)
	    break;
    }
    if (n_in % 16 == 0) {
	memset(buf, 0, 16);
	pha_cbc_encipher((pha_cblock *) buf, (pha_cblock *) buf, &ivec,
	    &sched, 16);
	fwrite(buf, 1, 16, out);
    }
    fclose(in);
    fclose(out);
}

static void do_decrypt(char *infile, char *outfile, char *phrase)
{
    pha_key key;
    pha_schedule sched;
    unsigned char buf[1024];
    size_t nbytes;
    pha_cblock ivec, save;
    int saved = 0;

    FILE *in, *out;

    get_key(&key, phrase);
    pha_schedule_key(&key, &sched);

    if (strcmp(infile, "-") == 0)
	in = stdin;
    else
	in = fopen(infile, "rb");

    if (!in) {
	perror(infile);
	exit(EXIT_FAILURE);
    }

    if (strcmp(outfile, "-") == 0)
	out = stdout;
    else
	out = fopen(outfile, "wb");

    if (!out) {
	perror(outfile);
	exit(EXIT_FAILURE);
    }

    fread(&ivec, 1, sizeof ivec, in);	/* get initial vector	*/

    while ((nbytes = fread(buf, 1, sizeof buf, in))) {
	if (saved)
	    fwrite(&save, 1, 16, out);
	nbytes -= nbytes % 16;	/* chop input down to multiple of 16 */
	pha_cbc_decipher((pha_cblock *) buf, (pha_cblock *) buf, &ivec,
	    &sched, nbytes);
	if (nbytes < sizeof buf) {
	    fwrite(buf, 1, nbytes - 16 + buf[nbytes-1] % 16, out);
	    break;
	} else {
	    fwrite(buf, 1, nbytes - 16, out);
	    memcpy(&save, buf + nbytes - 16, 16);
	    saved = 1;
	}
    }

    if (nbytes == 0)
	fwrite(&save, 1, buf[sizeof buf - 1] % 16, out);

    fclose(in);
    fclose(out);
}

static void get_key(pha_key *key, char *phrase)
{
    if (!pha_phrase_to_key(phrase, strlen(phrase), key)) {
	fprintf(stderr, "key too long\n");
	exit(EXIT_FAILURE);
    }
}

static void get_ivec(pha_cblock *ivec, char *phrase)
{
    if (!pha_phrase_to_cblock(phrase, strlen(phrase), ivec)) {
	fprintf(stderr, "salt too long\n");
	exit(EXIT_FAILURE);
    }
}
