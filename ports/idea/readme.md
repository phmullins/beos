### Idea

Idea (Richard De Moliner) can be used to encrypt and/or decrypt any file using the International Data Encryption Algorithm. I have more than a passing interest in Cryptography and ported Idea so that BeOS users would have another choice when it came to encrypting their data.

### Installation

Copy the `idea` file to `/boot/home/config/bin`.

### Usage:

I left the original `idea_cmd.txt` in the source folder so that you could read all the arguments that can be passed to Idea. However, if all you want to do is encrypt and/or decrypt a file with a simple passphrase you can use the following syntax:

Encrypt a file:

`$ idea -ek "myPassword" input.wav output.dea`

Arguments: -e = encrypt, -k is the passphrase, input.wav is the input file, and output.dea is the output file.

Decrypt a file:

`$ idea -dk "myPassword" input.dea output.wav`

Arguments: -d = decrypt, -k is the passphrase, input.dea is the input file, and output.wav is the output file.

I have tested Idea with all kinds of different file formats and it works perfectly, assuming you know what type of file you're dealing with. Please let me know if you find any bugs.

### Author
Idea was created by [Richard De Moliner](demoliner@isi.ee.ethz.ch) and ported to BeOS by [Patrick H. Mullins](http://www.pmullins.net). You can find me on  [Twitter](https://twitter.com/phmullins) and on [Telegram](https://telegram.org/) as @pmullins.

### License
No license information was included with the original source.
