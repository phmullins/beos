### xdms

xDMS, created by Andre Rodrigues de la Rocha, can be used to decompress files compressed using all known DMS compression modes, including old and obsolete ones, and also encrypted files, for 100% compatibility. This binary was compiled from the xDMS v1.3 source. I didn't do a whole lot of testing, but it does extract DMS archives and then write them to disk as ADF's. Note: The `x` command does not work with this version. I could not find the source for the `readdisk` program, so extracting files inside a DMS archive using `readdisk` will not work.

### Installation

Copy the `xdms` file to `/boot/home/config/bin`.

### Usage:

xdms [options] <command> {<dms_file[.dms]> [+output]}

### Author
xDMS was created by Andre Rodrigues de la Rocha and ported to BeOS by [Patrick H. Mullins](http://www.pmullins.net) on June 3rd, 1999. You can find me on  [Twitter](https://twitter.com/phmullins) and on [Telegram](https://telegram.org/) as @pmullins.

### License
No license information was included with the original source.
