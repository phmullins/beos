### BeDisk (v0.3)

BeDisk is nothing more then a Bash-based PGP Disk clone. BeDisk will create a container that you can mount and use as if it were a hard
drive, just like PGP Disk. BeDisk will not, however, encrypt the container. That feature *might* be added at a later date.

### Usage

The BeDisk application is actually comprised of two files. `MakeBeDisk` and `MountBeDisk`. `MakeBeDisk` is used to create a BeOS hardfile
container and `MountBeDisk` is used to unmount that container. To get started, unzip the package anywhere you'd like. The, run `MakeBeDisk`
to create the container. The default size is 200 MB. Edit this file to change the size to whatever you'd like. The container will be created
in the folder where the script is run. Warning: MakeBeDisk will overwrite any older image file found in the folder where it is run. Please
make sure that you rename your old `bedisk.img` file before creating a new container. After the container is created, run `MountBeDisk` to
mount it on the desktop. The container can now be written to just like a hard drive. When you're finished, right-click the desktop icon and
choose `un-mount`. Note: You can rename a mounted volume and it will, unfortunately, still retain its prior name. This is a bug that I am
currently working on.

### Acknowledgments

Thanks to Scot Hacker for helping me work out some bugs!

### Version History

v0.03 - BeDisk now creates and mounts containers in any folder.
v0.02 - Fixed missing icons in list view. Added better warning to MakeBeDisk.
v0.01 - Initial release.

### Future Plans

1.) Ability to encrypt and decrypt containers. Cyphers might include Idea, Ghost, Triple-DES, Blowfish or Twofish.
2.) Some kind of basic password protection scheme.
3.) Create any size container you want without editing the source file.
4.) Choose what container you want mounted.
5.) Choose a name for a new container.
6.) Basic error checking.

Note: Adding password protection or the ability to encrypt the container requires direct input from the user. Basic shell scripting has no
way of gaining that input except through the Terminal application. I might hold off on these features until I find a way of getting the input
from a BeOS `messagebox` or something similar to the alert command.

### Author
Created by [Patrick H. Mullins](http://www.pmullins.net). You can find me on  [Twitter](https://twitter.com/phmullins) and on [Telegram](https://telegram.org/) as @pmullins.

### License
Source is released under the FreeBSD (BSD-2-Clause) License [license](license.md).
