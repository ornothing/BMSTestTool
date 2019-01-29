#-------------------------------------------------
#
# Project created by QtCreator 2018-11-06T11:47:09
#
#-------------------------------------------------

QT += core gui
QT += sql
QT += charts

LIBS += -LD:\QtWorkSpace\BMSTestTool\BMSTestTool -lControlCAN

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BMSTestTool
TEMPLATE = app


SOURCES += main.cpp \
    CANOperation.cpp \
    MainDialog.cpp \
    BMSInfoWidget.cpp \
    BMUInfoWidget.cpp \
    CANSQLSettingWidget.cpp \
    WorkThread.cpp \
    updatebmswidget.cpp \
    updatebmuwidget.cpp \
    mybutton.cpp \
    savetodb.cpp \
    chartview.cpp \
    callout.cpp \
    datachartwidget.cpp \
    datachartfunction.cpp \
    datatochart.cpp \
    datatablewidget.cpp \
    signaltreewidget.cpp \
    parsecandata.cpp \
    handlehistoryrecord.cpp \
    historychart.cpp

HEADERS  += \
    ControlCAN.h \
    MainDialog.h \
    BMSInfoWidget.h \
    BMUInfoWidget.h \
    CANSQLSettingWidget.h \
    WorkThread.h \
    WidgetDataStructure.h \
    mybutton.h \
    databasedefine.h \
    chartview.h \
    callout.h \
    datachartwidget.h \
    datatablewidget.h \
    signaltreewidget.h \
    systemdefine.h \
    historyrecorddefine.h \
    candatadefine.h \
    handlehistoryrecord.h \
    historychart.h
