
#include <stdio.h>

/* From wk.c */

extern long Sizeftc, Sizefkey, Sizefout;
extern int Security, OPKResult, FWResult;
extern char wipe;
extern unsigned long ToKcrc, Keycrc, Outcrc;
extern char *versione;

/* end */

int logging(char *LogFile, char *ToCrypt, char *KeyFile, char *WKrypted)
{
	FILE *flog;
	
	flog = fopen(LogFile, "w");
     
	fprintf(flog, "\n --= Wan-Krypt %s =-- \n", versione);
     
	fprintf(flog, "\n File to be Wan-Krypted : %s\n", ToCrypt);
	fprintf(flog,   " Size (in byte)         : %ld\n", Sizeftc);
        fprintf(flog,   " CRC32                  : %lX\n", ToKcrc);
		
	fprintf(flog, "\n Key File to be XORed   : %s\n", KeyFile);
	fprintf(flog,   " Size (in byte)         : %ld\n", Sizefkey);
        fprintf(flog,   " CRC32                  : %lX\n", Keycrc);

	fprintf(flog, "\n Security Percentage    : %d%%\n", Security);



	fprintf(flog, "\n Ratio                  : %.1f%%", (float)Sizefkey*100/(float)Sizeftc );
	if ( (float)Sizefkey*100/(float)Sizeftc < Security ) {
		fprintf(flog, "   TOO LOW!!\n");
	} else 
		fprintf(flog, "   OK.\n");

	fprintf(flog, "\n Key File is XORed      : %.2f times\n", (float) Sizeftc/Sizefkey);

	switch (OPKResult) {
		case 1:
			fprintf(flog, "\n Status                 : Completed succesfully\n");
			break;
		default:	
			fprintf(flog, "\n Status                 : NOT completed\n");
			break;
	}

	fprintf(flog, "\n File Wan-Krypted       : %s\n", WKrypted);
	fprintf(flog,   " Size (in byte)         : %ld \n", Sizefout);
	fprintf(flog,   " CRC32                  : %lX\n", Outcrc);
	
	fprintf(flog, "\n Ratio                  : %.1f%%\n", (float)Sizefout*100/(float)Sizeftc);

	if (wipe) {
		switch (FWResult) {
			case 1:
				fprintf(flog, "\n File \"%s\" wiped out !!\n", ToCrypt);
				break;
			case -1:
				fprintf(flog, "\n ERROR: Cannot open file: %s\n\n", ToCrypt);
				break;
			case 0:	
				fprintf(flog, "\n ERROR occurred while wiping\n");
				break;
		}
	}

	fclose(flog);
	
	exit(0);
}


