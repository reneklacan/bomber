Bomber
======

Projekt teraz obsahuje jednoduchu hru a jednoduchy editor vyprototypovany v pythone


Pre skompilovanie je nutne najprv stiahnut zdrojaky cocos2d (musel som forknut zdrojaky, aby som pridal podporu na hw klavesnicu)

    cd client/lib
    ./download.sh
    # tu je mozno nutne poupravit/patchnut zdrojaky, popripade doinstalovat zavislosti
    cd cocos2d-x
    ./make-all-linux-project.sh 

Nasledne, ak sa vsetko podari bez chyby

    cd src/ProjLinux
    make
    ./bin/release/SimpleGame

Tada :)


Pre spustenie editora je nutne pouzit python s nainstalovanym Kivy modulom

    # ak nemate kivy tak
    easy_install kivy ALEBO pip install kivy
    # kivy je tiez zavisle na Cythone na vasom pc, tak mozno bude tiez nutne doinstalovat tento kompilator

Nasledne

    cd level-editor-prototype/src
    ./main.py
