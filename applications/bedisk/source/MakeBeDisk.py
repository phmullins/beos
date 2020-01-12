#!/bin/sh

# MakeBeDisk v0.1.2 (c) 2000 Patrick H. Mullins
# A Python-based tool for creating BeOS hardfile containers.
# Created: Janurary 25th, 2000 @ 8:29 PM

# Get location of current directory
launchDir=$(dirname $0)

alert --warning "MakeBeDisk v0.1.2 (c) 2000, Patrick H. Mullins
This will overwrite your old container. Do you wish to create a new one?" "Yes" "No"
retval=$?
if [ $retval -eq 0 ]
then
mkdir /boot/home/bedisk
alert --warning "Creating container...this may take a while. Click Ok to begin."
dd if=/dev/zero of=$launchDir/bedisk.img bs=1024k count=200
mkbfs 2048 $launchDir/bedisk.img
sync
alert --warning "Container created. You may now run MountBeDisk to mount the image."
fi

if [ $retval -eq 1 ]
then
alert --warning "Thank You for using BeDisk!"
fi
