QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Administrator.cpp \
    BaseUserInfo.cpp \
    CarInsurance.cpp \
    CreateAccount.cpp \
    Customer.cpp \
    Desk.cpp \
    HomeInsurance.cpp \
    Insurance.cpp \
    LifeInsurance.cpp \
    login.cpp \
    main.cpp

HEADERS += \
    Administrator.h \
    BaseUserInfo.h \
    CarInsurance.h \
    CreateAccount.h \
    Customer.h \
    Desk.h \
    HomeInsurance.h \
    Insurance.h \
    LifeInsurance.h \
    login.h

FORMS += \
    CreateAccount.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
