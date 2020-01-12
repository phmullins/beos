/*
              Wan-Krypt
  

	 Wan-Krypt (sounds like One-Crypt) algorithm based on one-time pad encryption.
    Copyright (C) 1998  ALoR <alor@thepentagon.com> of NeuroZone2                                                         
                                                                                                 
    This program is free software; you can redistribute it and/or modify                         
    it under the terms of the GNU General Public License as published by                         
    the Free Software Foundation; either version 2 of the License, or                            
    (at your option) any later version.                                                          
                                                                                                 
    This program is distributed in the hope that it will be useful,                              
    but WITHOUT ANY WARRANTY; without even the implied warranty of                               
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                                
    GNU General Public License for more details.                                                 
                                                                                                 
    You should have received a copy of the GNU General Public License                            
    along with this program; if not, write to the Free Software                                  
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


	To compile :	gnumake wkrypt 

	Earlier version : http://www.silab.dsi.unimi.it/~ao562686/wankrypt
 
	Improved by vim :set ts=3 tw=79

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NEUROZONE2			"RULEZ :)"
#define DEFAULT_SECURITY	61

char *versione = "1.1 release 981205";

char *optarg;
int optind, opterr, optopt;
char *ProgramName;
FILE *ftc, *fkey, *fout;
long Sizeftc, Sizefkey, Sizefout;
char wipe;
int Security, OPKResult, FWResult;
char *LogFile = NULL;
unsigned long ToKcrc, Keycrc, Outcrc;


/* help.h */

void title(void);
void usage(void);
void help(void);
void crediz(void);		/* Utilita' maxima :) */

/* crypt.h */

int OPKrypt(char *, char *, char *);

/* wipe.h */

int FWipe(char *);

/* log.h */

int logging(char *, char *, char *, char *);

/* crctab.c */

int getcrc32(unsigned long *CRC32, char *filename);

/* wk.c */

void WanKrypt(char *, char *, char *);
int Status(long tot, char sign, long cur);


/***** START *****/

int main(int argc, char *argv[])
{
int opt;

ProgramName = argv[0];
Security = DEFAULT_SECURITY;

title();

while ((opt = getopt(argc, argv, "l:s:wzh")) != -1) {
	switch(opt) {
	case 'l':
		LogFile = calloc(strlen(optarg) + 1, sizeof(char));
		strcpy(LogFile, optarg);
		break;
	case 's': 
		Security = atoi(optarg);
		break;
	case 'w': 
		wipe = 1;
		break;
	case 'z':
		crediz();
		break;
	case 'h': /* param. not required */
		help();
		break;
	case ':': /* missing parameter */
		usage();
		break;
	case '?': /* unknown option */
		usage();
		break;
	default:
		printf("\n ERROR: getopt() incorrect !!!\n");
		break;
	}
}

if( !argv[optind] || !argv[optind+1] ) { 
	printf("\nERROR: Missing File(s) !!\n");
	usage();
} else {
	WanKrypt(argv[optind], argv[optind+1], argv[optind+2]);
}

return 0;
}

/***** END *****/


int Status(long tot, char sign, long cur)	/* Damned Function: very lame implementation :( */
{
	char Ret = 0;
	float scale = 100/(float)tot/2;
	static int new;
	int i;

	if ( tot >= 50 ) {
		if ( (int)(cur * scale) == new ) {
			write(STDOUT_FILENO, &sign, sizeof(char));
			new++;
		}
	} else {
		for ( i = 0; i <= (int)(cur * scale); i++ ) {
			printf(".");
			if ( i == (int)(cur * scale) ) printf("\r");
		}     
	}

	if ( cur == tot ) {
		printf("\n");
		Ret = 1;
		new = 0;
	}	
	
	return Ret;

}


void WanKrypt(char *ToCrypt, char *KeyFile, char *OutFile)
{
	float Ratio;
	char *WKrypted;
	
	ToKcrc = Keycrc = Outcrc = 0xFFFFFFFFL;   /* Initalize CRC */
	
	if ( (ftc = fopen(ToCrypt, "r")) == NULL ) {
		printf("\n ERROR: Cannot open input file: %s\n\n", ToCrypt);
		exit(1);
	}	

	if ( (fkey = fopen(KeyFile, "r")) == NULL ) {
		printf("\n ERROR: Cannot open key file: %s\n\n", KeyFile);
		exit(1);
	}	

	fseek(ftc, 0, SEEK_END);
	Sizeftc = ftell(ftc);	

	fseek(fkey, 0, SEEK_END);
	Sizefkey = ftell(fkey);	

	fclose(ftc);
	fclose(fkey);

	getcrc32(&ToKcrc, ToCrypt);
	getcrc32(&Keycrc, KeyFile);
	
	if ( Sizeftc == 0 || Sizefkey ==0 ) {
		printf("\n ERROR: Cannot use 0 lenght file !!\n\n");
		exit(1);
	}
	
	printf("\n File to be Wan-Krypted : %s\n", ToCrypt);
	printf(  " Size (in byte)         : %ld\n", Sizeftc);
	printf(  " CRC32                  : %lX\n", ToKcrc);
	
	printf("\n Key File to be XORed   : %s\n", KeyFile);
	printf(  " Size (in byte)         : %ld\n", Sizefkey);
	printf(  " CRC32                  : %lX\n", Keycrc);

	printf("\n Security Percentage    : %d%%\n", Security);

	printf("\n Ratio                  : %.1f%%", Ratio = (float)Sizefkey*100/(float)Sizeftc );
	if ( Ratio < Security ) {
		printf("   TOO LOW!!\n");
		if (LogFile) logging(LogFile, ToCrypt, KeyFile, OutFile);
	} else 
		printf("   OK.\n");


	printf(   "\n Key File is XORed      : %.2f times\n", (float) Sizeftc/Sizefkey);

	printf("\nWan-Krypting...\n");
	printf("[----------25-----------50------------75----------]\n");

	WKrypted = calloc(strlen(OutFile), sizeof(char));
	strcpy(WKrypted, OutFile); 

	OPKResult = OPKrypt(ToCrypt, KeyFile, WKrypted);
	
	switch (OPKResult) {
		case 1:
			printf("\n Status                 : Completed succesfully\n");
			break;
		default:	
			printf("\n Status                 : NOT completed\n");
			if (LogFile) logging(LogFile, ToCrypt, KeyFile, WKrypted);
			break;
	}

	getcrc32(&Outcrc, WKrypted);

	printf("\n File Wan-Krypted       : %s\n", WKrypted);
	printf(  " Size (in byte)         : %ld \n", Sizefout);
	printf(  " CRC32                  : %lX\n", Outcrc);
	
	printf("\n Ratio                  : %.1f%%\n", Ratio = ((float)Sizefout*100/(float)Sizeftc));

	if (wipe) {
		printf("\nWiping source file...\n");
		printf("[----------25-----------50------------75----------]\n");
		
		FWResult = FWipe(ToCrypt);

		switch (FWResult) {
			case 1:
				printf("\n File \"%s\" wiped out !!\n", ToCrypt);
				break;
			case -1:
				printf("\n ERROR: Cannot open file: %s\n\n", ToCrypt);
				break;
			case 0:	
				printf("\n ERROR occurred while wiping\n");
				break;
		}
	}

	if (LogFile) logging(LogFile, ToCrypt, KeyFile, WKrypted);
	
printf("\n");


}



