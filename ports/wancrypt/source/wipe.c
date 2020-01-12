
#include <stdio.h>
#include <unistd.h>

/* From wk.c */

extern long Sizeftc, Sizefkey, Sizefout;
extern int Status(long tot, char sign, long cur);

/* end */

int FWipe(char *ToWipe)
{
	FILE *ftw;
	long j, SizeToWipe;
	
	if ( (ftw = fopen(ToWipe, "r")) == NULL ) return -1;
	
	fseek(ftw, 0, SEEK_END);
	SizeToWipe = ftell(ftw);
	fclose(ftw);

	ftw = fopen(ToWipe, "w");
	
	Status(SizeToWipe, '.', 0);

	for (j = 1; j <= SizeToWipe; j++) {
		if ( (j % 2) == 0) fputc('0', ftw);
		else fputc('1', ftw);
		
		if ( Status(SizeToWipe, '.', j) == 1 ) {
			fclose(ftw);
			unlink(ToWipe);
			return 1;
		}
	}
		
	fclose(ftw);
	return 0;
}


