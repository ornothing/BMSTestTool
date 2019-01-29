#ifndef CANSQLSETTINGWIDGET_H
#define CANSQLSETTINGWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>
#include "ControlCAN.h"
#include "WorkThread.h"


class CANSQLSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CANSQLSettingWidget(QWidget *parent = 0);
    ~CANSQLSettingWidget();

    bool m_valueFlag;
    bool m_statusFalg;

    /** 系统设置 **/
    QGridLayout *m_systemSettingLayout;

    /** SQL连接设置 **/
    void StartSQLSetting();
    QGroupBox *m_sqlSettingGroup;
    QGridLayout *m_sqlSettingLayout;
    QLineEdit *m_hostEdit;
    QLineEdit *m_databaseEdit;
    QLineEdit *m_userEdit;
    QLineEdit *m_PasswordEdit;
    QLabel *m_sqlStatus;
    QPushButton *m_sqlConnectBut;
    ValueThread *m_valueThread;
    QPushButton *m_cleanRecentBut;
    QPushButton *m_cleanHistoryBut;

    /** CAN连接设置 **/
    void StartCanSetting();
    QGroupBox *m_startCANGroup;
    QGridLayout *m_startCANLayout;
    //Start CAN setting
    QComboBox *m_devTypeCombo;
    QComboBox *m_devIndexCombo;
    QComboBox *m_channelCombo;
    QComboBox *m_baudCombo;
    QComboBox *m_modeCombo;
    QLineEdit *m_time0Edit;
    QLineEdit *m_time1Edit;
    QPushButton *m_canConnectBut;
    QPushButton *m_canDisconnectBut;
    QCheckBox *m_openAllCANBox;
    CANThread *m_recvCANthread;
    QTimer *m_dbConnectionTimer;
    QSqlDatabase m_mainDB;

    /** 串口收发 **/
    void CANSendGUI();
    QGroupBox *m_canSendGroup;
    QGridLayout *m_canSendLayout;
    QLineEdit *m_sendID;
    QLineEdit *m_sendData;
    QPushButton *m_sendButton;
    QTextEdit *m_dispalyCAN;

    /** 测试编号与历史保存 **/
    void TestConfig();
    QGroupBox *m_testConfigGroup;
    QGridLayout *m_testConfigLayout;
    QLineEdit *m_testNumber;
    QLineEdit *m_bmuNumber;
    QTextEdit *m_testDescription;
    QPushButton *m_saveText;

    int m_connectionFlag;   //连接标识
    int m_devType;   //设备类型
    int m_devIndex;   //设备索引
    int m_channelIndex;   //通道索引
    int m_time0;
    int m_time1;
    void GetTimeCode(int baud);
    int StartCAN(int devType, int devIndex, int canIndex, VCI_INIT_CONFIG config);

    int Str2Data(unsigned char *str, unsigned char *data, int len, int flag);
    int Char2Int(unsigned char chr, unsigned char *cint);
    void Transmit(bool successFlag, VCI_CAN_OBJ frameinfo);
    void RebuildRecentTable(QString currentTime);

private slots:
    void OnConnectDatabase();
    void OnConncetCAN();
    void OnDisconnectCAN();
    void OnCANSend();
    void UpdateUI(uint64_t count);
    void HandleSqlConnectionStatus();
    void SaveTestCase();
    void CleanRecentDB();
    void CleanHistoryDB();
    void PinrtErrorInfo(QString errorstring);
};

#endif // CANSQLSETTINGWIDGET_H
