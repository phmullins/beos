
#include <stdio.h>

/* From wk.c */

extern char *ProgramName;
extern char *versione;

/* end */

void title(void)
{
	printf("\n --= Wan-Krypt %s by ALoR of NeuroZone2 =-- \n", versione);
}


void usage(void)
{
static char *options[] = {
	"",
	" files:",
	"  FILE          file to be Wan-Krypted",
	"  KEYFILE       file to be XORed with FILE",
	"  OUTFILE       Wan-Krypted output file (default is FILE.wan)",
	"",
	" options:",
	"  -s num        sets the grade of security (dafault is 61%)",
	"  -w            wipes the input file",
	"  -l LOGFILE    generates log file",
	"  -h            detailed help",
	"  -z            credits :)",
	"", NULL};
char **cpp;

	fprintf (stderr, "\nusage:  %s [-s num] [-w] [-l LOGFILE] [-h] FILE KEYFILE [OUTFILE]\n", ProgramName);
		for (cpp = options; *cpp; cpp++)
			fprintf (stderr, "%s\n", *cpp);

exit(1);
}

void help(void)
{

static char *desc[] = {
	"",
	" Wan-Krypt (sounds like One-Crypt) is a program that implements an",
	" algorithm based on one-time pad encryption.",
	" In this way the key is XORed with the file to be Wan-Krypted and it",
	" produces an output file. The largest is the key the safest is the",
	" algorithm. *the best* encryption is produced if sizeof(KEY) == sizeof(FILE)",
	" The one-time pad is the only encryption method proven to be unbreakable.",
	"",NULL};

static char *help[] = {
	"",
	" files:",
	"",
	"  FILE          file to be Wan-Krypted.",
	"                it can be a text file or binary or whatever you want",
	"",
	"  KEYFILE       file to be XORed with FILE",
	"                key file *must* be enought large to fit security",
	"                percentage (default 61%)",
	"                I suggest to use digitalized image as keyfile.",
	"                a .gif or .jpg image is optimum for a good encryption",
	"                Johnny Mnemonic RuLeZ... :)",
	"",
	"  OUTFILE       Wan-Krypted output file (default is FILE.wan)",
	"                you can specify your own output file.",
	"",
	" detailed options:",
	"",
	"  -s num        sets the minumum security. (default is 61%)",
	"                the 'num' value must be between 1 and 100",
	"                it rappresents the sizeof(KEYFILE)*100/sizeof(FILE)",
	"",
	"  -w            wipes out the input FILE.",
	"                the input FILE is filled with '010101' mantainig the",
	"                original size, then deleted.",
	"",
	"  -l LOGFILE    geterates log file.",
	"                log file contains variuos info such as file and kay",
	"                size, ratio, security %, ecc.",
	"                to avoid crypt-analisys i suggest to wipe or not",
	"                create at all this file",
	"",
	"  -h            this help :)",
	"",
	"  -z            credits",	
	"", NULL};
char **cpp;

	for (cpp = desc; *cpp; cpp++)
		printf ("%s\n", *cpp);
  
	printf ("\nusage:  %s [-s num] [-w] [-l LOGFILE] [-h] FILE KEYFILE [OUTFILE]\n", ProgramName);
		for (cpp = help; *cpp; cpp++)
			printf ("%s\n", *cpp);

exit(0);
}

void crediz(void)
{
static char *credit[] = {
	"",
	".--------------------------------------------------------------------.",
	"|        Wan-Krypt : a One Pad based algorithm of encryption.        |",
	"|                                                                    |",
	"+-- Born from the mad mind of: --------------------------------------+",
	"|                                                                    |", 
	"|     ALoR       ALoR@thepentagon.com                                |",
	"|                                                                    |",
	"+-- Special Thanks to: ----------------------------------------------+",
	"|                                                                    |",
	"|     Cato       ( for the idea )                                    |",
	"|     ZenGa      ( for the help in writing C source )                |",
	"|                                                                    |",
	"|                                                                    |",
	"`--------------------------------------------------------------------'",
	"", NULL};
char **cpp;
  
	for (cpp = credit; *cpp; cpp++)
		printf ("%s\n", *cpp);

exit(0);
}
