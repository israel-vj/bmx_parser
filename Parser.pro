
QT += \
    widgets \

INCLUDEPATH += \
    C:/Lib/OpenSSL/1.0.2h/MinGW4.9.2/x86/include \
    C:/Lib/PoDoFo/0.9.5/MinGW4.9.2/x86/include \

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
    #C:/Lib/PoDoFo/0.9.5/MinGW4.9.2/x86/lib/libpodofo.dll.a \
    C:/Lib/PoDoFo/lib/libpodofo.a \

FORMS += \
    MainWindow.ui

