#/bin/bash

if [ ! -d cocos2d-x ] ; then
    echo "Missing cocos2d sources, run download.sh"
else
    cd cocos2d-x
    patch -p1 < ../gentoo.patch
fi
