### Phantom

This Phantom implementation (by Kaz Kylheku) can be used to encrypt and/or decrypt any file using the Phantom block cipher. I have more than a passing interest in Cryptography and ported Phantom so that BeOS users would have another choice when it came to encrypting their data.

### Installation

Open a BeOS terminal, cd to the folder containing the source code, and then type `make` folled by `enter`. if all goes well, you will have two new files called `phantom` and `filecrypt`. Finally, copy both of these to `/boot/home/config/bin`.

### Usage:

This port of the Phantom Block Cipher uses the `filecrypt` utility and a standard 16 rounds. Please modify the source code `phantom.c` if you want to use 32 round encryption. At some point I plan on releasing a Python front-end for Phantom. Please contact me if you know anything about the Phantom block cipher and how I might be able to make this implementation more useful to the BeOS community.

### Author
Phantom was created by [Kaz Kylheku](kaz@cafe.net) and ported to BeOS by [Patrick H. Mullins](http://www.pmullins.net) on July 3rd, 1999. You can find me on  [Twitter](https://twitter.com/phmullins) and on [Telegram](https://telegram.org/) as @pmullins.

### License
GNU GENERAL PUBLIC LICENSE
