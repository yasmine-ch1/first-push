QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH += $$PWD/Qt-QrCodeGenerator-main/src


CONFIG += c++17
QT       += core gui sql charts widgets axcontainer network printsupport svg
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    connection.cpp \
    generateurpdf.cpp \
    main.cpp \
    mainwindow.cpp\
    $$PWD/Qt-QrCodeGenerator-main/src/QrCodeGenerator.cpp \
    $$PWD/Qt-QrCodeGenerator-main/src/qrcodegen/qrcodegen.cpp  \
    generateurqrcode.cpp

HEADERS += \
    client.h \
    connection.h \
    generateurpdf.h \
    mainwindow.h \
    $$PWD/Qt-QrCodeGenerator-main/src/QrCodeGenerator.h \
    $$PWD/Qt-QrCodeGenerator-main/src/qrcodegen/qrcodegen.h \
    generateurqrcode.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc \
    icone.qrc \
    im.qrc \
    im1.qrc \
    image.qrc \
    img.qrc \
    logoo.qrc \
    rech.qrc \
    staa.qrc
