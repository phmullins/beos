
#include <stdio.h>
#include <string.h>


/* From wk.c */

extern FILE *ftc, *fkey, *fout;
extern long Sizeftc, Sizefkey, Sizefout;
extern int Status(long tot, char sign, long cur);

/* end */

int OPKrypt(char *ToCrypt, char *KeyFile, char *WKrypted)
{
	int j, OPKResult = 0;

	if ( !strcmp(WKrypted, "") ) {
		strcpy(WKrypted, ToCrypt);
		strcat(WKrypted, ".wan");
	}

	ftc = fopen(ToCrypt, "rb");
	fkey = fopen(KeyFile, "rb");
	fout = fopen(WKrypted, "wb");
	
	Status(Sizeftc, '.', 0);
	
	for(j = 1; j <= Sizeftc; j++) {					/* the Wan-Krypt algorithm */
		
		if ( feof(fkey) ) rewind(fkey);

		fputc( fgetc(ftc)^fgetc(fkey) , fout);		/* XORing */
		
		if ( Status(Sizeftc, '.', j) == 1 ) OPKResult = 1;
		
	}
	
	fseek(fout, 0, SEEK_END);                                                                 
   Sizefout = ftell(fout);
	
	fclose(ftc);
	fclose(fkey);
	fclose(fout);
	
	return OPKResult;
}


