#/bin/bash

if [ ! -d "cocos2d-x" ] ; then
    echo "Downloading cocos2d sources..."
    git clone -b dev https://github.com/reneklacan/cocos2d-x.git
else
    echo "Ok ;)"
fi
