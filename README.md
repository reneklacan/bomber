Bomber
======

Projekt teraz obsahuje len zakladny priklad zo zdrojakov cocos2d, ale usposobeny tak, aby fungoval so zakladnym layoutom, ktory budeme pouzivat.


Pre skompilovanie je nutne najprv stiahnut zdrojaky cocos2d

    cd src/Lib
    ./download.sh
    #tu je mozno nutne poupravit/patchnut zdrojaky, popripade doinstalovat zavislosti
    cd cocos2d-2.1rc0-x-2.1.3
    ./make-all-linux-project.sh 

Nasledne, ak sa vsetko podari bez chyby

    cd src/ProjLinux
    make
    ./bin/release/HelloCpp

Tada :)
