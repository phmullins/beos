
                              Wan-Krypt ver. 1.1
                               ---------------
                                  ---------
                                     ---

                                   Coded By

                              ---==: ALoR :==--- 
                 ---==>  Proud member of NEURO ZONE 2  <==---

                                 November 1998


==============================================================================

*** Description ***

 Wan-Krypt (sounds like One-Crypt) is a program that implements an
 algorithm based on one-time pad encryption.
 In this way the key is XORed with the file to be Wan-Krypted producing an 
 encrypted output file. The largest is the key the safest is the algorithm.
 *the best* encryption is produced if sizeof(KEY) == sizeof(FILE)
 The one-time pad is the only encryption method proven to be unbreakable.          


*** Installation  ***

	Extract the wankrypt-X.X.tar.gz file in a directory.
		(EX. tar xvfz wankrypt-X.X.tar.gz ./ )

	To Compile : use gnumake
		(EX. gnumake wkrypt )


*** Files Description ***

 crc.c     crc32 module
 crypt.c   the actual algorithm of encryption
 help.c    help module
 log.c     logging module
 wipe.c    wipe module
 wk.c      Main program


*** Wan-Krypt history: ***

ver 1.1

	- Makefiles ( gnumake )
	- crc32 support

ver 1.0

	- GPL policy
	- very buggy percentage indicator fixed
	- logging option
	- code optimization
	  
ver 0.9

	- security percentage (default 61%)
	- OPKrypt() modified in order to apply security percentage

ver 0.7

	- wipe option (modularized in wipe.h)
	- default output file .wan

ver 0.5

	- messages during encyption enhanced
	- percentage indicator

ver 0.3

	- help is integrated and modularized in help.h

ver 0.2

	- OPKrypt() modularized in crypt.h
	- now using getopt() instead of a cycle on argv[] 

ver 0.1
	
	- main program (just XORing two files)



       .-.                                                         .-.
      /   \           .-.                           .-.           /   \
     /     \         /   \       .-.     .-.       /   \         /     \
 ---/-------\-------/-----\-----/---\---/---\-----/-----\-------/-------\---
   /         \     /       \   /     `-'     \   /       \     /         \
  /           \   /         `-'               `-'         \   /           \
 /             `-'                                         `-'             \

Greetings to:   Cato  (for the idea)

                ZenGa (for the help in writing C source)

                The other NEURO ZONE 2 members (10t8or, DK2DEnd, LordKasKo,
                                                MaPHas, Ob1, LastKnight, XXXX)

                And obviously the creator of one-time pad algorithm... :)

==============================================================================

               .________   ._ 
              /  .__    ) /  /      .________   ._____  
             /  (___)  / /  /      /  .__    ) /  ._  ) ..: .    .   .      .
            /  .___   / /  /      /  /   )  / /  / /_/ .. : : .         . 
           /  /   /  / /  /____  /  /___/  / /  /    :: .:: . . .    .  
          (__/   (__/ (________)(_________/ (__/   .:. : . :  .   .    .
 
            --==> ALoR <==---------------------- -  -   - 
                                  ICQ: 10666678    In IRC: WhiteFly

          e-mail: ALoR@thepentagon.com     www: http://ALoR.home.ml.org/
                                                http://alor.cjb.net

==============================================================================



