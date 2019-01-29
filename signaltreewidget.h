#ifndef SIGNALTREEWIDGET_H
#define SIGNALTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QList>

class SignalTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    SignalTreeWidget();
    ~SignalTreeWidget();

    QList<QTreeWidgetItem *> m_signalList;
    void InitSignalTree();
    void CreateBMSCellModelParItem();
    void CreateBMSCellBasicParItem();
    void CreateBMSCellStatusItem();
    void CreateBMSCommandItem();
    void CreateBMUStatusItem();
    void CreateBMUBasicParaItem();
    void CreateBMUBalItem();
    void CreateBMUCellVoltItem();
    void CreateBMUCellTempItem();
    void CreateBMUConfigItem();
};


#endif // SIGNALTREEWIDGET_H
