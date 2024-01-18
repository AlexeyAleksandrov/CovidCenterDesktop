QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customstyles.cpp \
    main.cpp \
    mainwindow.cpp \
    models/authresult.cpp \
    models/authresultstatus.cpp \
    models/jwttoken.cpp \
    models/order.cpp \
    models/registerresult.cpp \
    models/registerresultstatus.cpp \
    models/signinmodel.cpp \
    models/signupmodel.cpp \
    services/authservice.cpp \
    services/clientsauthservice.cpp \
    services/httpclient.cpp \
    services/membersauthservice.cpp \
    timerthread.cpp \
    models/service.cpp \
    models/analyzerresult.cpp \
    models/user.cpp \
    models/servicedata.cpp

HEADERS += \
    customstyles.h \
    mainwindow.h \
    models/authresult.h \
    models/authresultstatus.h \
    models/jwttoken.h \
    models/order.h \
    models/registerresult.h \
    models/registerresultstatus.h \
    models/signinmodel.h \
    models/signupmodel.h \
    services/authservice.h \
    services/clientsauthservice.h \
    services/httpclient.h \
    services/membersauthservice.h \
    timerthread.h \
    models/service.h \
    models/analyzerresult.h \
    models/user.h \
    models/servicedata.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    CovidCenterDesktop_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sources.qrc
