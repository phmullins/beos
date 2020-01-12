#!/bin/sh

# MountBeDiskk v0.1.2 (c) 2000 Patrick H. Mullins
# A Python-based tool for mounting BeOS hardfile containers.
# Created: Janurary 25th, 2000 @ 9:48 PM

# Get location of current directory
launchDir=$(dirname $0)

alert --warning "MountBeDisk v0.1.2 (c) 2000, Patrick H. Mullins
Mount The Container?" "Yes" "No"
retval=$?
if [ $retval -eq 0 ]
then
mkdir  $launchDir /mnt
mount -t bfs $launchDir/bedisk.img /mnt
sync
alert --warning "Container Successfully Mounted. You can now view and/or add files."
fi

if [ $retval -eq 1 ]
then
alert --warning "Thank You for using BeDisk!"
fi
