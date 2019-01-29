#ifndef BMSMAINDIALOG_H
#define BMSMAINDIALOG_H

#include <QDialog>
#include <QStatusBar>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QTimer>
#include "BMSInfoWidget.h"
#include "bmuinfowidget.h"
#include "cansqlsettingwidget.h"
#include "datachartwidget.h"
#include "datatablewidget.h"

class BMSMainDialog : public QDialog
{
    Q_OBJECT

public:
    BMSMainDialog(QWidget *parent = 0);
    ~BMSMainDialog();

    QTabWidget *m_tabWidget;
    BMSInfoWidget *m_bmsInfoWidget;
    BMUInfoWidget *m_bmuInfoWidget;
    RealTimeDataChartWidget *m_realTimeChartWidget;
    DataTableWidget *m_dataTableWidget;
    CANSQLSettingWidget *m_systemSetting;
    QVBoxLayout *m_mainLayout;

    QStatusBar *m_statusBar;
    QWidget *m_statusWidget;
    QLabel *m_softwareVersion;
    QLabel *m_hardwareVersion;
    QLabel *m_dbConnection;
    QLabel *m_canConnection;

    QTimer *m_setVersionTimer;
    QTimer *m_versionTimeout;
    QTimer *m_statusTimer;
    bool m_versionFlag;
    void CreateStatusWidget();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void SetBMSVersion();
    void VersionTimeout();
    void SetStatus();

};

#endif // BMSMAINDIALOG_H
