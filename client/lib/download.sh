#/bin/bash

if [ ! -d cocos2d-2.1rc0-x-2.1.3 ] ; then
    echo "Downloading cocos2d sources..."
    wget http://cocos2d-x.googlecode.com/files/cocos2d-2.1rc0-x-2.1.3.zip
    unzip cocos2d-2.1rc0-x-2.1.3.zip
else
    echo "Ok ;)"
fi
