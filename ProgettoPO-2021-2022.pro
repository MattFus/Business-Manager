QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dipendente.cpp \
    dipendentejunior.cpp \
    dipendentejuniorqlistwidgetitem.cpp \
    dipendenteqlistwidgetitem.cpp \
    dipendentesenior.cpp \
    dipendenteseniorqlistwidgetitem.cpp \
    gestore.cpp \
    main.cpp \
    mainwindow.cpp \
    progetto.cpp \
    progettoqlistwidgetitem.cpp

HEADERS += \
    ../../../Desktop/UNIV/2_Secondo anno/PROGRAMMAZIONE OGGETTI/Progetto/Gestore.h \
    dipendente.h \
    dipendentejunior.h \
    dipendentejuniorqlistwidgetitem.h \
    dipendenteqlistwidgetitem.h \
    dipendentesenior.h \
    dipendenteseniorqlistwidgetitem.h \
    gestore.h \
    mainwindow.h \
    progetto.h \
    progettoqlistwidgetitem.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
