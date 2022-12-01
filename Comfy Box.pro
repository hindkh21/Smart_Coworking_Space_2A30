QT       += core gui sql
QT       += network
QT       += printsupport
QT       += charts
QT       += multimedia
QT       += serialport
QT       +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduinoEmp.cpp \
    chatemp.cpp \
    client.cpp \
    connection.cpp \
    employe.cpp \
    espaces.cpp \
    exportexcelobject.cpp \
    gestionclient.cpp \
    gestionemploye.cpp \
    gestionespace.cpp \
    main.cpp \
    mainwindow.cpp \
    mychat_employe.cpp \
    qcustomplot.cpp \
    smtp.cpp \
    statemp.cpp \
    todolist.cpp

HEADERS += \
    arduinoEmp.h \
    chatemp.h \
    client.h \
    connection.h \
    employe.h \
    espaces.h \
    exportexcelobject.h \
    gestionclient.h \
    gestionemploye.h \
    gestionespace.h \
    mainwindow.h \
    mychat_employe.h \
    qcustomplot.h \
    smtp.h \
    statemp.h \
    todolist.h

FORMS += \
    gestionclient.ui \
    gestionemploye.ui \
    gestionespace.ui \
    mainwindow.ui \
    mychat_employe.ui \
    statemp.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc