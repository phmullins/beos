## BeOS/Haiku

Here you will find applications for [BeOS](https://en.wikipedia.org/wiki/BeOS)/[Haiku](https://www.haiku-os.org/) that I have either created myself, ported to BeOS, or patched in order to make them work properly. BeOS was an operating system for personal computers first developed by Be Inc. in 1991. Haiku is an open source operating system based on BeOS. Haiku maintains binary compatibility with [BFS](https://en.wikipedia.org/wiki/Be_File_System) and the last version of BeOS and can run any application originally built for BeOS.

### BeOS Applications

BeOS applications that I have written in either Pythin or C++.

* [BIdea](/applications/bidea) - A Python front-end for the Idea encryption algorithm.
* [BeDisk](/applications/bedisk) - This is a PGP Disk clone. It will create a BeOS hardfile container and then mount it as if it were a normal hard drive. I created this in one night, so don't too expect from it. I plan on eventually adding container encryption and context-menu integration.

### BeOS Application Patches

These are applications that I have downloaded from the Internet and had to patch to get them working with BeOS.

* [WriteCD](WriteCD.zip) - A set of scripts that allow you to burn CDs under BeOS. The original archive was missing a crucial file (MakeBFS) which allows you to create BFS formatted CD's. I created the MakeBFS script and included MakeBFS in this archive.

### Application Ports

These are applications that I've ported to BeOS. Most of these are Terminal-based applications. I plan on adding GUI wrapper interfaces to some of these.

* [BxDMS](xDMS.zip) - Converts DMS archives to ADF files.
* [Enigma](benigma.zip) - German Enigma encryption cipher.
* [Lucifer](blucifer.zip) - IBM's Lucifer encryption cipher.
* [Phantom](bphantom.zip) - The Phantom (Based on GOST) random block encryption cipher.
* [Wancrypt](bwancrypt.zip) - One-Time Pad encryption cipher.
* [Idea](idea.zip) - Port of the IDEA encryption cipher.  

### Author
Created by [Patrick H. Mullins](http://www.pmullins.net). You can find me on  [Twitter](https://twitter.com/phmullins) and on [Telegram](https://telegram.org/) as @pmullins.

### License
Source is released under the FreeBSD (BSD-2-Clause) License [license](license.md).
