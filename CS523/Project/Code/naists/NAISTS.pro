#-------------------------------------------------
#
# Project created by QtCreator 2011-10-31T10:53:33
#
#-------------------------------------------------

QT       += core gui network

TARGET = NAISTS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mail/smtpclient.cpp \
    mail/mimetext.cpp \
    mail/mimepart.cpp \
    mail/mimemessage.cpp \
    mail/mimeinlinefile.cpp \
    mail/mimehtml.cpp \
    mail/mimefile.cpp \
    mail/mimeattachment.cpp \
    mail/emailaddress.cpp \
    def.cpp

HEADERS  += mainwindow.h \
    mail/smtpclient.h \
    mail/mimetext.h \
    mail/mimepart.h \
    mail/mimemessage.h \
    mail/mimeinlinefile.h \
    mail/mimehtml.h \
    mail/mimefile.h \
    mail/mimeattachment.h \
    mail/emailaddress.h \
    def.h \
    coord.h


FORMS    += mainwindow.ui

OTHER_FILES += \
    img/field.png \
    img/future.txt























