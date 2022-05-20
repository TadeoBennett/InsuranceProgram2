QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AdminQueries.cpp \
    Administrator.cpp \
    BaseUserInfo.cpp \
    CarInsurance.cpp \
    CreateAccount.cpp \
    Customer.cpp \
    CustomerQueries.cpp \
    Database.cpp \
    Desk.cpp \
    DeskQueries.cpp \
    HomeInsurance.cpp \
    Insurance.cpp \
    InsuranceProgram.cpp \
    LifeInsurance.cpp \
    Menu.cpp \
    login.cpp \
    main.cpp

HEADERS += \
    AdminQueries.h \
    Administrator.h \
    BaseUserInfo.h \
    CarInsurance.h \
    CreateAccount.h \
    Customer.h \
    CustomerQueries.h \
    Database.h \
    Desk.h \
    DeskQueries.h \
    HomeInsurance.h \
    Insurance.h \
    InsuranceProgram.h \
    LifeInsurance.h \
    Menu.h \
    login.h

FORMS += \
    CreateAccount.ui \
    Menu.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
