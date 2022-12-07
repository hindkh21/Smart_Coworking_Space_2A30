QT       +=  core gui sql network multimedia multimediawidgets charts printsupport widgets axcontainer serialport
TARGET = QT_Project_On_Movie_Ticket_Booking

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
    abonnement.cpp \
    arduino.cpp \
    book.cpp \
    cancel.cpp \
    chatemp.cpp \
    client.cpp \
    connection.cpp \
    dialog_map.cpp \
    dialog_stats.cpp \
    dialog_stats_abonnement.cpp \
    employe.cpp \
    espaces.cpp \
    exportexcelobject.cpp \
    gestion_abonnement.cpp \
    gestionclient.cpp \
    gestionemploye.cpp \
    gestionespace.cpp \
    gestionreservation.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mychat_employe.cpp \
    mydb.cpp \
    qcustomplot.cpp \
    reservation.cpp \
    smtp.cpp \
    statemp.cpp \
    statesp.cpp \
    todolist.cpp

HEADERS += \
    abonnement.h \
    arduino.h \
    book.h \
    cancel.h \
    chatemp.h \
    client.h \
    connection.h \
    dialog_map.h \
    dialog_stats.h \
    dialog_stats_abonnement.h \
    employe.h \
    espaces.h \
    exportexcelobject.h \
    gestion_abonnement.h \
    gestionclient.h \
    gestionemploye.h \
    gestionespace.h \
    gestionreservation.h \
    login.h \
    mainwindow.h \
    mychat_employe.h \
    mydb.h \
    qcustomplot.h \
    reservation.h \
    smtp.h \
    statemp.h \
    statesp.h \
    todolist.h \
    webaxwidget.h

FORMS += \
    book.ui \
    cancel.ui \
    dialog_map.ui \
    dialog_stats.ui \
    dialog_stats_abonnement.ui \
    gestion_abonnement.ui \
    gestionclient.ui \
    gestionemploye.ui \
    gestionespace.ui \
    gestionreservation.ui \
    mainwindow.ui \
    mychat_employe.ui \
    statemp.ui \
    statesp.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    Images_espace/Bureau.jpg \
    Images_espace/Coworking.jpg \
    Images_espace/SalleConf.jpg \
    Images_espace/SalleReu.png \
    Images_espace/arduino.png \
    Images_espace/descr.png \
    Images_espace/excel.png \
    Images_espace/importer.png \
    Images_espace/modifier.png \
    Images_espace/paiementfacture.jpg \
    Images_espace/pdf.png \
    Images_espace/suprimer.png \
    Images_espace/trier.png \
    Images_espace/valider.png \
    imageres/310432895_2325982227549440_2476852675195435336_n.png \
    imageres/Untitled-1.png
