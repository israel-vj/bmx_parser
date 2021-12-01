
QT += \
    widgets \

INCLUDEPATH += \
    C:/Lib/OpenSSL/1.1.1m/mingw81/include \
    C:/Lib/PoDoFo/0.9.7/mingw81/include \

HEADERS += \
    TextExtractor.h \
    MainWindow.h \
    FileParser.h

SOURCES += \
    main.cpp \
    TextExtractor.cpp \
    MainWindow.cpp \
    FileParser.cpp

LIBS += \
    C:/Lib/PoDoFo/0.9.7/mingw81/lib/libpodofo.dll.a \

FORMS += \
    MainWindow.ui

