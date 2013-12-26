Bomber
======

Pre skompilovanie je nutne najprv stiahnut zdrojaky cocos2d (musel som forknut zdrojaky, aby som pridal podporu na hw klavesnicu)

    cd client/lib
    ./download.sh
    # tu je mozno nutne poupravit/patchnut zdrojaky, popripade doinstalovat zavislosti
    cd cocos2d-x
    ./make-all-linux-project.sh 

Nasledne, ak sa vsetko podari bez chyby

    cd client/src/ProjLinux
    make
    ./bin/release/bomber

Tada :)

**

Buildovanie na android (stiahnite si android sdk/ndk najprv)

    cd client/src/ProjAndroid
    ./build_native.sh
    android list target
    android update project -p . -t ID_SDK(vacsinou 1)
    android update project -p cocos2d-x/cocos2dx/platform/android/java/ -t TO_ISTE_ID_CO_V_PRIKAZE_VYSSIE
    ant debug

Ak sa vsetko podarilo, tak v zlozke "bin" sa nachadza apk subor, v nasom pripade HelloWorld-debug.apk
