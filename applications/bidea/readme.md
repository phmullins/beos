### BIdea (v1.0)
BIdea is a front-end for Idea, an encryption application that I ported over to the BeOS on January 1st, 2000. BIdea is written in Python and is executed as a shell script from the Terminal.

### Instructions:
Copy `bidea.py` and `idea` to `/boot/home/config/bin`. Once done, open up a terminal and `cd` to the folder where you keep your encrypted files. Finally, type in `bidea` to start using the application. Please note that Idea does not know what type of file is being encrypted or decrypted. If someone sends you an Idea encrypted file you must know what type of file it is. Ex: .jpg, .zip and so on.  

### Bugs
This application has no implemented error checking. It will crash to the command-line if you hit `enter` at any of the prompts without typing in the information it's looking for. Also, no error message will be displayed if something goes wrong. Yes, this sucks. I will do my best to add error checking in the next version. Please email me if you have any questions or if you wish to report any problems or bugs that you may find.

### Author
Created by [Patrick H. Mullins](http://www.pmullins.net). You can find me on  [Twitter](https://twitter.com/phmullins) and on [Telegram](https://telegram.org/) as @pmullins.

### License
Source is released under the FreeBSD (BSD-2-Clause) License [license](license.md).
