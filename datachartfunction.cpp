#include "datachartwidget.h"
#include "widgetdatastructure.h"
#include "databasedefine.h"
#include "systemdefine.h"
#include <QDebug>
#include <QMessageBox>
#include <QtMath>
#include <QTime>

QList<ChartData> g_selectedSignalData;

void RealTimeDataChartWidget::DeleteSignal()
{
    int i = 0;
    int j = 0;
    int k = 0;
    QString signalName = NULL;
    QString signalModule = NULL;
    m_unixTime = QDateTime::currentDateTime().toTime_t();
    m_lastTime = m_unixTime;
    QList<int> rowList;
    int selectedRow;
    QString BUMNumber;

    if (m_isCleaning)
    {
        QList<QTableWidgetSelectionRange>ranges = m_selectedTable->selectedRanges();

        int count = ranges.count();
        for(i=0; i<count; i++)
        {
            int topRow = ranges.at(i).topRow();
            int bottomRow = ranges.at(i).bottomRow();

            //获取并排序
            for (k=topRow; k<=bottomRow; k++)
            {
                rowList.append(k);
            }
        }

        qSort(rowList.begin(), rowList.end());   //必须先对所选行进行排序，然后从后面开始删除，否则会出现错误。

        while(!rowList.isEmpty())
        {
            selectedRow = rowList.takeLast();

            if ((m_selectedTable->item(selectedRow, 0) != 0) && (m_selectedTable->item(selectedRow, 1) != 0))
            {
                BUMNumber = QString("-1");
                signalName = m_selectedTable->item(selectedRow, 0)->text();
                signalModule = m_selectedTable->item(selectedRow, 1)->text();

                if (signalModule.length() == 4)
                {
                    BUMNumber = signalModule.right(1);
                }

                for (j=0; j<g_selectedSignalData.size(); j++)
                {
                    if ((signalName == g_selectedSignalData.at(j).parameterName) &&\
                            (BUMNumber.toInt() == g_selectedSignalData.at(j).BMUNumber))
                    {
                        g_selectedSignalData.removeAt(j);
                    }
                }

                m_selectedTable->removeRow(selectedRow);
                m_signalNumber--;

                QTreeWidgetItemIterator it(m_signalTree);   //取消信号选择表中对应的选中项
                if (BUMNumber == QString("-1"))
                {
                    while (*it)
                    {
                        if (((*it)->text(0) == signalName))
                            (*it)->setCheckState(0, Qt::Unchecked);
                        ++it;
                    }
                }
                else
                {
                    while (*it)
                    {
                        if (((*it)->text(0) == signalName) && ((*it)->parent()->text(0) == BUMNumber))
                            (*it)->setCheckState(0, Qt::Unchecked);
                        ++it;
                    }
                }
            }
        }
        m_selectedTable->setRowCount(MAX_SELECTED_SIGNAL_NUMBER);

#ifdef DEBUG_MODE
        qDebug() << "Delete Result :";
        for (i=0; i<g_selectedSignalData.size(); i++)
        {
            qDebug() << g_selectedSignalData.at(i).parameterName << g_selectedSignalData.at(i).BMUNumber;
        }
        qDebug() << "";
#endif
    }
else
    {
        QMessageBox::warning(NULL, "提示", "运行中，请勿删除信号");
    }
}


void RealTimeDataChartWidget::AddSignal()
{
    int i = 0;
    bool existFlag = false;
    QTreeWidgetItemIterator itemIterator(m_signalTree);
    QString signalModule = NULL;
    QString signalName = NULL;
    QTableWidgetItem *moduleItem = NULL;
    QTableWidgetItem *signalItem = NULL;
    QString BMUNumber;
    ChartData addNode;

    if (m_isCleaning)
    {

        while (*itemIterator)
        {
            if ((*itemIterator)->checkState(0) == Qt::Checked)
            {
                BMUNumber = QString("-1");
                signalName = (*itemIterator)->text(0);
                QTreeWidgetItem *parentItem = (*itemIterator)->parent();

                while (parentItem)
                {
                    parentItem = parentItem->parent();
                    if (parentItem)
                    {
                        if (parentItem->text(0).left(3) == QString("BMU"))
                        {
                            signalModule = parentItem->text(0).left(3) + (*itemIterator)->parent()->text(0);
                            BMUNumber = (*itemIterator)->parent()->text(0);
                        }
                        else
                        {
                            signalModule = parentItem->text(0).left(3);
                        }
                    }
                }

                for (i=0; i<g_selectedSignalData.size(); i++)
                {
                    if ((g_selectedSignalData.at(i).parameterName == signalName) &&\
                            (g_selectedSignalData.at(i).BMUNumber == BMUNumber.toInt()))
                    {
                        existFlag = true;
                        break;
                    }
                }

                if (!existFlag)
                {
                    if (m_signalNumber >= MAX_SELECTED_SIGNAL_NUMBER)
                    {
#ifdef DEBUG_MODE
                        qDebug() << "Add Result :";
                        for (i=0; i<g_selectedSignalData.size(); i++)
                        {
                            qDebug() << g_selectedSignalData.at(i).parameterName << g_selectedSignalData.at(i).BMUNumber;
                        }
                        qDebug() << "";
#endif
                        QMessageBox::warning(NULL, "提示", "添加信号数超过上限");
                        return;
                    }
                    addNode.parameterName = signalName;
                    addNode.BMUNumber = BMUNumber.toInt();
                    addNode.selectedFlag = false;
                    g_selectedSignalData.append(addNode);
                    signalItem = new QTableWidgetItem(QString("%1").arg(signalName));
                    moduleItem = new QTableWidgetItem(QString("%1").arg(signalModule));
                    m_selectedTable->setItem(m_signalNumber, 0, signalItem);
                    m_selectedTable->setItem(m_signalNumber, 1, moduleItem);

                    m_signalNumber++;
                }
                existFlag = false;
            }
            itemIterator++;
        }

#ifdef DEBUG_MODE
        qDebug() << "Add Result :";
        for (i=0; i<g_selectedSignalData.size(); i++)
        {
            qDebug() << g_selectedSignalData.at(i).parameterName << g_selectedSignalData.at(i).BMUNumber;
        }
        qDebug() << "";
#endif
    }
    else
    {
        QMessageBox::warning(NULL, "提示", "运行中，请勿添加信号");
    }
}


void RealTimeDataChartWidget::InitChart()
{
    UINT time = QDateTime::currentDateTime().toTime_t();
    m_axisX->setRange(time, time + 60);    //设置范围
    m_axisX->setTickCount(7);       //设置多少格
    m_axisX->setMinorTickCount(9);   //设置每格小刻度线的数目

    m_axisX->setLabelFormat("%d");   //设置刻度的格式
    m_axisX->setGridLineVisible(true);   //网格线可见
    m_axisX->setTitleText("时间/毫秒");
//    m_axisX->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));

    m_axisY->setRange(m_minY, m_maxY);
    m_axisY->setGridLineVisible(true);
    m_axisY->setTickCount(10);
    m_axisY->setLabelFormat("%.1f");
    m_axisY->setMinorTickCount(1);
    m_axisY->setTitleText("值/（单位根据具体信号而定）");
//    m_axisY->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
}


void RealTimeDataChartWidget::wheelEvent(QWheelEvent *event)
{
    if (m_chart != NULL)
    {
        if (event->angleDelta().y() > 0) {
            m_chart->zoom(1.1);
        } else {
            m_chart->zoom(0.9);
        }
    }

    QWidget::wheelEvent(event);
}


void RealTimeDataChartWidget::InitSlot()
{
    connect(m_stopButton, SIGNAL(clicked()), this, SLOT(ControlButtonSlot()));
    connect(m_addButton, SIGNAL(clicked()), this, SLOT(AddSignal()));
    connect(m_deleteButton, SIGNAL(clicked()), this, SLOT(DeleteSignal()));
    connect(m_cleanButton, SIGNAL(clicked()), this, SLOT(CleanSignal()));
}


void RealTimeDataChartWidget::CleanSignal()
{
    int i = 0;
    int k = 0;
    QString BUMNumber;

    for (i=0; i<m_seriesAndTimer.size(); i++)
    {
        m_seriesAndTimer[i].ChartTimer->stop();
        m_chart->removeSeries(m_seriesAndTimer[i].ChartSeries);
        m_seriesAndTimer[i].ChartSeries->clear();
        delete m_seriesAndTimer[i].ChartSeries;
        delete m_seriesAndTimer[i].ChartTimer;
        m_seriesAndTimer[i].ChartSeries = NULL;
        m_seriesAndTimer[i].ChartTimer = NULL;
    }

    for (k=0; k<m_signalNumber; k++)
    {
        QString signalName = NULL;
        QString signalModule = NULL;
        BUMNumber = QString("-1");
        if ((m_selectedTable->item(k, 0) != 0) && (m_selectedTable->item(k, 1) != 0))
        {
            signalName = m_selectedTable->item(k, 0)->text();
            signalModule = m_selectedTable->item(k, 1)->text();
        }
        else
            continue;

        if (signalModule.length() == 4)
        {
            BUMNumber = signalModule.right(1);
        }

        if (signalName != NULL)
        {
            QTreeWidgetItemIterator it(m_signalTree);   //取消信号选择表中对应的选中项
            if (BUMNumber == QString("-1"))
            {
                while (*it)
                {
                    if (((*it)->text(0) == signalName))
                        (*it)->setCheckState(0, Qt::Unchecked);
                    ++it;
                }
            }
            else
            {
                while (*it)
                {
                    if (((*it)->text(0) == signalName) && ((*it)->parent()->text(0) == BUMNumber))
                        (*it)->setCheckState(0, Qt::Unchecked);
                    ++it;
                }
            }
        }

    }

    m_stopButton->setText("开始");

    if (!m_isStopping)
        m_isStopping = !m_isStopping;

    m_selectedTable->clearContents();
    g_selectedSignalData.clear();
    m_minYList.clear();
    m_maxYList.clear();
    m_seriesAndTimer.clear();
    m_signalNumber = 0;
    m_timeCount = 0;
    m_isCleaning = true;

    delete m_tip;
    delete m_axisX;
    delete m_axisY;
    delete m_chart;
    delete m_chartView;
    m_tip = 0;
    m_axisX = NULL;
    m_axisY = NULL;
    m_chart = NULL;
    m_chartView = NULL;
}


void RealTimeDataChartWidget::TimerSlot()
{
    int i = 0;

    for (i=0; i<m_seriesAndTimer.size(); i++)
    {
        if (QObject::sender() == m_seriesAndTimer.at(i).ChartTimer)
        {
            UpdateChart(i);
        }
    }

    if (m_timeCount > 60)   //当前图像显示的时长设置
    {
        if (m_axisX->tickCount() > 0)
        {
#ifdef DEBUG_MODE
            qDebug() << m_chart->plotArea().width();
            qDebug() << m_axisX->tickCount();
#endif
            if (m_lastTime < m_unixTime)
            {
                m_lastTime = m_unixTime;
                qreal x = m_chart->plotArea().width() / ((m_axisX->tickCount()-1)*(m_axisX->minorTickCount()+1));
                m_chart->scroll(x, 0);
            }
        }
#ifdef DEBUG_MODE
        else
        {
            qDebug() << "m_axisX->tickCount() = 0";
        }
#endif
    }

    m_timeCount++;
}


void RealTimeDataChartWidget::UpdateChart(int signalNumber)
{
    float value = -1;

    QVector<QPointF> oldData = m_seriesAndTimer.at(signalNumber).ChartSeries->pointsVector();
    QVector<QPointF> data;

    if (!(g_selectedSignalData[signalNumber].data.isEmpty()))
    {
        value = g_selectedSignalData[signalNumber].data.takeFirst();
        if (oldData.size() < 7200)   //全图像显示的时间长度设置，总共可显示7200个点
        {
            data = m_seriesAndTimer.at(signalNumber).ChartSeries->pointsVector();
        }
        else
        {
            /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
         * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
         */
            oldData.removeFirst();
            data = oldData;
        }

        m_unixTime = QDateTime::currentDateTime().toTime_t();
#ifdef DEBUG_MODE
        qDebug() << "count1 : " << m_timeCount;
        qDebug() << "number1 : " << value;
#endif
        data.append(QPointF(m_unixTime, value));

        m_seriesAndTimer.at(signalNumber).ChartSeries->replace(data);
    }
}


void RealTimeDataChartWidget::ControlButtonSlot()
{
    int i = 0;
    SERIES_AND_TIMER node;
    int timeInterval = 0;

    if (m_isCleaning)
    {
        m_chart = new QChart();
        m_axisX = new QValueAxis;
        m_axisY = new QValueAxis;
        if (g_selectedSignalData.size() == 0)
        {
            QMessageBox::warning(NULL, "警告", "请添加需要获取的信号参数！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }

        for (i=0; i<g_selectedSignalData.size(); i++)
        {
            node.ChartSeries = new QLineSeries;
            if (g_selectedSignalData[i].BMUNumber == -1)
            {
                node.ChartSeries->setName(QString("%1").arg(g_selectedSignalData[i].parameterName));
            }
            else
            {
                node.ChartSeries->setName(QString("%1-%2").arg(g_selectedSignalData[i].parameterName).arg(g_selectedSignalData[i].BMUNumber));
            }
            m_chart->addSeries(node.ChartSeries);

            timeInterval = GetTimerInterval(i);
            node.ChartTimer = new QTimer(this);
            node.ChartTimer->setInterval(timeInterval);

#ifdef DEBUG_MODE
            qDebug() << g_selectedSignalData[i].parameterName << ": timer : " << timeInterval;
#endif
            connect(node.ChartSeries, SIGNAL(hovered(QPointF, bool)), this, SLOT(TipSlot(QPointF, bool)));
            connect(node.ChartTimer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
            m_seriesAndTimer.append(node);
        }

        m_chart->createDefaultAxes();

        GetYRange();
        InitChart();

        for (i=0; i<m_seriesAndTimer.size(); i++)
        {
            m_chart->setAxisX(m_axisX, m_seriesAndTimer[i].ChartSeries);   //为chart设置X轴,并把轴附加到series线上
            m_chart->setAxisY(m_axisY, m_seriesAndTimer[i].ChartSeries);   //为chart设置Y轴,并把轴附加到series线上
        }

        m_chartView = new ChartView(m_chart);
        m_chartView->setRenderHint(QPainter::Antialiasing);
        m_realTimeLayout->addWidget(m_chartView, 0 ,1);
        m_isCleaning = false;
    }

    if (QObject::sender() == m_stopButton)
    {
        if (m_isStopping)
        {
            for (i=0; i<m_seriesAndTimer.size(); i++)
            {
                m_seriesAndTimer[i].ChartTimer->start();
            }

            for (i=0; i<g_selectedSignalData.size(); i++)
            {
                g_selectedSignalData[i].selectedFlag = true;
            }

            m_stopButton->setText("暂停");
        }
        else
        {
            for (i=0; i<m_seriesAndTimer.size(); i++)
            {
                m_seriesAndTimer[i].ChartTimer->stop();
            }

            for (i=0; i<g_selectedSignalData.size(); i++)
            {
                g_selectedSignalData[i].selectedFlag = false;
            }
            m_stopButton->setText("开始");
        }
        m_isStopping = !m_isStopping;
    }

#ifdef DEBUG_MODE
    qDebug() << "Selected Result :";
    for (i=0; i<g_selectedSignalData.size(); i++)
    {
        qDebug() << g_selectedSignalData.at(i).parameterName << g_selectedSignalData.at(i).selectedFlag;
    }
    qDebug() << "";
#endif
}


void RealTimeDataChartWidget::TipSlot(QPointF position, bool isHovering)
{
    if (m_tip == 0)
        m_tip = new Callout(m_chart);

    if (isHovering)
    {
        QDateTime time= QDateTime::fromTime_t(position.x());
        QString timeString = time.toString("MM/dd hh:mm:ss");
        m_tip->setText(QString("X: %1 \nY: %2 \n%3").arg((UINT)(position.x())).arg(position.y()).arg(timeString));
        m_tip->setAnchor(position);
        m_tip->setZValue(11);  //该设置与图形的层次有关，值越大，越上层。
        m_tip->updateGeometry();
        m_tip->show();
    }
    else
    {
        m_tip->hide();
    }
}


int RealTimeDataChartWidget::GetTimerInterval(int signalNumber)
{
    if (g_selectedSignalData.at(signalNumber).BMUNumber == -1)
    {
        return 1000;
    }
    else
    {
        return 500;
    }
}


void RealTimeDataChartWidget::GetYRange()
{
    int i = 0;
    bool getFlag;

    for (i=0; i<g_selectedSignalData.size(); i++)
    {
        getFlag = false;

        getFlag = GetBMSValueYRange(i);

        if (!getFlag)
        {
            getFlag = GetBMSStatusYRange(i);
            if (!getFlag)
            {
                getFlag = GetBMUValueYRange(i);
                if (!getFlag)
                {
                    getFlag = GetBMUStatusYRange(i);
                }
            }
        }
    }

    qSort(m_minYList.begin(), m_minYList.end());
    qSort(m_maxYList.begin(), m_maxYList.end());

#ifdef DEBUG_MODE
    qDebug() << "min Y list :";
    for (i=0; i<m_minYList.size(); i++)
    {
        qDebug() << m_minYList.at(i);
    }
    qDebug() << "";

    qDebug() << "max Y list :";
    for (i=0; i<m_maxYList.size(); i++)
    {
        qDebug() << m_maxYList.at(i);
    }
    qDebug() << "";
#endif

    if (!m_minYList.isEmpty())
    {
        m_minY = m_minYList.first();
    }

    if (!m_maxYList.isEmpty())
    {
        m_maxY = m_maxYList.last();
    }
}


bool RealTimeDataChartWidget::GetBMUStatusYRange(int signalNumber)
{
    //BMU状态
    if((g_selectedSignalData.at(signalNumber).parameterName == BMU_AFE_SAMPLE) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_AFE_FAULT) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV1_CELL_VOLT_LOW) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV1_CELL_VOLT_HIGH) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV1_CELL_VOLT_DIFF) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV1_MODULE_VOLT_LOW) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV1_MODULE_VOLT_HIGH) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV1_AMBIENT_TEMP_LOW) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV1_AMBIENT_TEMP_HIGH) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV1_CHRG_TEMP_LOW) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV1_CHRG_TEMP_HIGH) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV1_DISCHRG_TEMP_LOW) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV1_DISCHRG_TEMP_HIGH) ||\

            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV2_CELL_VOLT_LOW) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV2_CELL_VOLT_HIGH) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV2_CELL_VOLT_DIFF) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV2_MODULE_VOLT_LOW) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV2_MODULE_VOLT_HIGH) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV2_AMBIENT_TEMP_LOW) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV2_AMBIENT_TEMP_HIGH) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV2_CHRG_TEMP_LOW) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV2_CHRG_TEMP_HIGH) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV2_DISCHRG_TEMP_LOW) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_LV2_DISCHRG_TEMP_HIGH) ||\
            (g_selectedSignalData.at(signalNumber).parameterName.left(4) == STRING_BMU_CELL_IN_BAL))
    {
        m_minYList.append(0);
        m_maxYList.append(1);
        return true;
    }

    else if(g_selectedSignalData.at(signalNumber).parameterName == BMU_OWD_ST)
    {
        m_minYList.append(0);
        m_maxYList.append(7);
        return true;
    }

    else if(g_selectedSignalData.at(signalNumber).parameterName == BMU_CELL_BAL_MODE)
    {
        m_minYList.append(0);
        m_maxYList.append(3);
        return true;
    }

    else if(g_selectedSignalData.at(signalNumber).parameterName == BMU_CELL_BAL_ST)
    {
        m_minYList.append(0);
        m_maxYList.append(8);
        return true;
    }
    else
        return false;
}


bool RealTimeDataChartWidget::GetBMUValueYRange(int signalNumber)
{
    //BMU基本参数
    if (g_selectedSignalData.at(signalNumber).parameterName == BMU_SOC)
    {
        m_minYList.append(0);
        m_maxYList.append(100);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMU_DIFF_CELL_VOLT)
    {
        m_minYList.append(0);
        m_maxYList.append(200);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMU_DIFF_CELL_TEMP)
    {
        m_minYList.append(0);
        m_maxYList.append(10);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMU_MODULE_VOLT)
    {
        m_minYList.append(0);
        m_maxYList.append(72);
        return true;
    }

    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMU_MAX_CELL_VOLT) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_MIN_CELL_VOLT) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_AVG_CELL_VOLT) ||\
            (g_selectedSignalData.at(signalNumber).parameterName.left(7) == STRING_BMU_CELL_VOLT))
    {
        m_minYList.append(1000);
        m_maxYList.append(4500);
        return true;
    }

    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMU_MAX_CV_NO) || \
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_MIN_CV_NO) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_MAX_CT_NO) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMU_MIN_CT_NO))
    {
        m_minYList.append(0);
        m_maxYList.append(16);
        return true;
    }

    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMU_BOARD_TEMP) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMU_MAX_CELL_TEMP) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMU_MIN_CELL_TEMP) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMU_AVG_CELL_TEMP) ||\
             (g_selectedSignalData.at(signalNumber).parameterName.left(7) == STRING_BMU_CELL_TEMP))
    {
        m_minYList.append(-20);
        m_maxYList.append(75);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMU_CELL_AH)
    {
        m_minYList.append(30);
        m_maxYList.append(250);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMU_CELL_RATE_VOLT)
    {
        m_minYList.append(0);
        m_maxYList.append(65535);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMU_CELL_NUM)
    {
        m_minYList.append(8);
        m_maxYList.append(16);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMU_TEMP_NUM)
    {
        m_minYList.append(1);
        m_maxYList.append(8);
        return true;
    }

    else
        return false;
}


bool RealTimeDataChartWidget::GetBMSStatusYRange(int signalNumber)
{
    //BMS电池状态与故障信息
    if (g_selectedSignalData.at(signalNumber).parameterName == BMS_BASIC_STATUS)
    {
        m_minYList.append(0);
        m_maxYList.append(31);
        return true;
    }

    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMS_ERR_VOLT_SENSOR) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ERR_TEMP_SENSOR) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ERR_INN_COM) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ERR_CHRG_VOLT_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ERR_WIRE_INVERSED) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ERR_RELAY_STICKY) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_CELL_VOLT_LOW) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_CELL_VOLT_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_PACK_VOLT_LOW) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_PACK_VOLT_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_CHRG_TEMP_LOW) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_CHRG_TEMP_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_DISCHRG_TEMP_LOW) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_DISCHRG_TEMP_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_CHRG_CURR_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_DISCHRG_CURR_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_MODULE_VOLT_LOW) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_MODULE_VOLT_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_P_CELL_VOLT_LOW) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_P_CELL_VOLT_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_P_PACK_VOLT_LOW) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_P_PACK_VOLT_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_P_CHRG_TEMP_LOW) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_P_CHRG_TEMP_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_P_DISCHRG_TEMP_LOW) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_P_DISCHRG_TEMP_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_P_CHRG_CURR_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_P_DISCHRG_CURR_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_P_MODULE_VOLT_LOW) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_P_MODULE_VOLT_HIGH) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_POSI_RLY_ST) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_NEG_RLY_ST) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_FATAL_BMU_SENSOR) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_FATAL_BMU_AFE) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_FATAL_BMU_CV) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_FATAL_BMU_VT) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_FATAL_HVCU_COM) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_FATAL_HVCU_SENSOR))
    {
        m_minYList.append(0);
        m_maxYList.append(1);
        return true;
    }


    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMS_FORCE_CHRG_ST) ||\
            (g_selectedSignalData.at(signalNumber).parameterName == BMS_ALM_ST))
    {
        m_minYList.append(0);
        m_maxYList.append(3);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMS_RLY_STICKY)
    {
        m_minYList.append(0);
        m_maxYList.append(7);
        return true;
    }

    else
        return false;
}


bool RealTimeDataChartWidget::GetBMSValueYRange(int signalNumber)
{
    //电池模组参数
    if (g_selectedSignalData.at(signalNumber).parameterName == BMS_POLL_GLOBAL_INFO)
    {
        m_minYList.append(0);
        m_maxYList.append(3);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMS_PACK_VOLT)
    {
        m_minYList.append(100);
        m_maxYList.append(800);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMS_PACK_CURR)
    {
        m_minYList.append(-150);
        m_maxYList.append(150);
        return true;
    }

    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMS_AMBIENT_TEMP_OUT) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_AMBIENT_TEMP_IN) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_MAX_CELL_TEMP) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_MIN_CELL_TEMP) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_MAX_MODULE_CT) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_MIN_MOUDLE_CT))
    {
        m_minYList.append(-25);
        m_maxYList.append(75);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMS_SOC)
    {
        m_minYList.append(0);
        m_maxYList.append(100);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMS_PACK_PWR)
    {
        m_minYList.append(-15000);
        m_maxYList.append(15000);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMS_MAX_CHG_CURR)
    {
        m_minYList.append(0);
        m_maxYList.append(150);
        return true;
    }

    else if (g_selectedSignalData.at(signalNumber).parameterName == BMS_MAX_DISCHG_CURR)
    {
        m_minYList.append(-150);
        m_maxYList.append(0);
        return true;
    }

    //电池基本参数
    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMS_MAX_CELL_VLOT) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_MIN_CELL_VOLT))
    {
        m_minYList.append(1000);
        m_maxYList.append(4500);
        return true;
    }

    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMS_MAX_CV_NO) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_MIN_CV_NO))
    {
        m_minYList.append(0);
        m_maxYList.append(256);
        return true;
    }

    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMS_MAX_CT_NO) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_MIN_CT_NO))
    {
        m_minYList.append(0);
        m_maxYList.append(64);
        return true;
    }

    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMS_MAX_MODULE_CV) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_MIN_MODULE_CV))
    {
        m_minYList.append(1000);
        m_maxYList.append(65000);
        return true;
    }

    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMS_MAX_MCV_NO) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_MIN_MCV_NO) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_MAX_MCT_NO) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_MIN_MCT_NO))
    {
        m_minYList.append(0);
        m_maxYList.append(20);
        return true;
    }

    //BMS指令
    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMS_CHRG_FORBIDEN_MARK) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_DISCHRG_FORBIDEN_MARK) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_SLEEP_CTRL) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_RELAY_FORCE_BREAK))

    {
        m_minYList.append(85);
        m_maxYList.append(170);
        return true;
    }

    else if ((g_selectedSignalData.at(signalNumber).parameterName == BMS_CHRG_EN) ||\
             (g_selectedSignalData.at(signalNumber).parameterName == BMS_DISCHRG_EN))
    {
        m_minYList.append(0);
        m_maxYList.append(170);
        return true;
    }

    else
        return false;
}
