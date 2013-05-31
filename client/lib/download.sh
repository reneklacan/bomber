#/bin/bash

if [ ! -d "cocos2d-x" ] ; then
    echo "Downloading cocos2d sources..."
    git clone https://github.com/simpliplant/cocos2d-x.git
else
    echo "Ok ;)"
fi
