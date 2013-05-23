#/bin/bash

if [ ! -d cocos2d-2.1rc0-x-2.1.3 ] ; then
    echo "Missing cocos2d sources, run download.sh"
else
    cd cocos2d-2.1rc0-x-2.1.3
    patch -p1 < ../gentoo.patch
fi
