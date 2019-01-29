#include "signaltreewidget.h"
#include "databasedefine.h"


SignalTreeWidget::SignalTreeWidget()
{
    setHeaderLabel("信号选择");
    CreateBMSCellModelParItem();   //BMS电池模组参数
    CreateBMSCellBasicParItem();   //BMS电池基本参数
    CreateBMSCellStatusItem();   //BMS电池状态信息
    CreateBMSCommandItem();   //BMS指令
    CreateBMUStatusItem();   //BMU状态
    CreateBMUBasicParaItem();   //BMU基本参数
    CreateBMUBalItem();   //BMU均衡状态
    CreateBMUCellVoltItem();   //BMU单体电压
    CreateBMUCellTempItem();   //BMU单体温度
    CreateBMUConfigItem();   //BMU模组配置

    insertTopLevelItems(0, m_signalList);
}

SignalTreeWidget::~SignalTreeWidget()
{
    m_signalList.clear();
    clear();
}


void SignalTreeWidget::CreateBMSCellModelParItem()
{
    QTreeWidgetItem *group1 = new QTreeWidgetItem(this);
    group1->setText(0, "BMS总体信息");
    m_signalList.append(group1);

    //0x4200
    QTreeWidgetItem *sig0x4200 = new QTreeWidgetItem(group1, QStringList(QString("%1").arg(STRING_0x4200)));
    group1->addChild(sig0x4200);

    QTreeWidgetItem* subItem = new QTreeWidgetItem(sig0x4200, QStringList(QString("%1").arg(BMS_POLL_GLOBAL_INFO)));
    subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem *group = new QTreeWidgetItem(this);
    group->setText(0, "BMS电池模组参数");
    m_signalList.append(group);

    //0x4210
    QTreeWidgetItem *sig0x4210 = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x4210)));
    group->addChild(sig0x4210);

    QTreeWidgetItem* subItem11 = new QTreeWidgetItem(sig0x4210, QStringList(QString("%1").arg(BMS_PACK_VOLT)));
    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem11->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* subItem12 = new QTreeWidgetItem(sig0x4210, QStringList(QString("%1").arg(BMS_PACK_CURR)));
    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem12->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem13 = new QTreeWidgetItem(sig0x4210, QStringList(QString("%1").arg(BMS_AMBIENT_TEMP_OUT)));
    subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem13->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem14= new QTreeWidgetItem(sig0x4210, QStringList(QString("%1").arg(BMS_SOC)));
    subItem14->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem14->setCheckState(0, Qt::Unchecked);

    sig0x4210->addChild(subItem11);
    sig0x4210->addChild(subItem12);
    sig0x4210->addChild(subItem13);
    sig0x4210->addChild(subItem14);

    //0x18FF02C0
    QTreeWidgetItem *sig0x18FF02C0 = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF02C0)));
    group->addChild(sig0x18FF02C0);

    QTreeWidgetItem* subItem21 = new QTreeWidgetItem(sig0x18FF02C0, QStringList(QString("%1").arg(BMS_PACK_PWR)));
    subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem21->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem22 = new QTreeWidgetItem(sig0x18FF02C0, QStringList(QString("%1").arg(BMS_AMBIENT_TEMP_IN)));
    subItem22->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem22->setCheckState(0, Qt::Unchecked);

    sig0x18FF02C0->addChild(subItem21);
    sig0x18FF02C0->addChild(subItem22);

    //0x4220
    QTreeWidgetItem *sig0x4220 = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x4220)));
    group->addChild(sig0x4220);

    QTreeWidgetItem* subItem31 = new QTreeWidgetItem(sig0x4220, QStringList(QString("%1").arg(BMS_MAX_CHG_CURR)));
    subItem31->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem31->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem32 = new QTreeWidgetItem(sig0x4220, QStringList(QString("%1").arg(BMS_MAX_DISCHG_CURR)));
    subItem32->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem32->setCheckState(0, Qt::Unchecked);

    sig0x4220->addChild(subItem31);
    sig0x4220->addChild(subItem32);
}


void SignalTreeWidget::CreateBMSCellBasicParItem()
{
    QTreeWidgetItem *group = new QTreeWidgetItem(this);
    group->setText(0, "BMS电池基本参数");
    m_signalList.append(group);

    //0x4230
    QTreeWidgetItem *sig0x4230 = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x4230)));
    group->addChild(sig0x4230);

    QTreeWidgetItem* subItem11 = new QTreeWidgetItem(sig0x4230, QStringList(QString("%1").arg(BMS_MAX_CELL_VLOT)));
    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem11->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem12 = new QTreeWidgetItem(sig0x4230, QStringList(QString("%1").arg(BMS_MIN_CELL_VOLT)));
    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem12->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem13 = new QTreeWidgetItem(sig0x4230, QStringList(QString("%1").arg(BMS_MAX_CV_NO)));
    subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem13->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem14= new QTreeWidgetItem(sig0x4230, QStringList(QString("%1").arg(BMS_MIN_CV_NO)));
    subItem14->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem14->setCheckState(0, Qt::Unchecked);

    sig0x4230->addChild(subItem11);
    sig0x4230->addChild(subItem12);
    sig0x4230->addChild(subItem13);
    sig0x4230->addChild(subItem14);

    //0x4240
    QTreeWidgetItem *sig0x4240 = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x4240)));
    group->addChild(sig0x4240);

    QTreeWidgetItem* subItem21 = new QTreeWidgetItem(sig0x4240, QStringList(QString("%1").arg(BMS_MAX_CELL_TEMP)));
    subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem21->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem22 = new QTreeWidgetItem(sig0x4240, QStringList(QString("%1").arg(BMS_MIN_CELL_TEMP)));
    subItem22->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem22->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem23 = new QTreeWidgetItem(sig0x4240, QStringList(QString("%1").arg(BMS_MAX_CT_NO)));
    subItem23->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem23->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem24= new QTreeWidgetItem(sig0x4240, QStringList(QString("%1").arg(BMS_MIN_CT_NO)));
    subItem24->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem24->setCheckState(0, Qt::Unchecked);

    sig0x4240->addChild(subItem21);
    sig0x4240->addChild(subItem22);
    sig0x4240->addChild(subItem23);
    sig0x4240->addChild(subItem24);

    //0x4260
    QTreeWidgetItem *sig0x4260 = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x4260)));
    group->addChild(sig0x4260);

    QTreeWidgetItem* subItem31 = new QTreeWidgetItem(sig0x4260, QStringList(QString("%1").arg(BMS_MAX_MODULE_CV)));
    subItem31->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem31->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem32 = new QTreeWidgetItem(sig0x4260, QStringList(QString("%1").arg(BMS_MIN_MODULE_CV)));
    subItem32->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem32->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem33 = new QTreeWidgetItem(sig0x4260, QStringList(QString("%1").arg(BMS_MAX_MCV_NO)));
    subItem33->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem33->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem34= new QTreeWidgetItem(sig0x4260, QStringList(QString("%1").arg(BMS_MIN_MCV_NO)));
    subItem34->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem34->setCheckState(0, Qt::Unchecked);

    sig0x4260->addChild(subItem31);
    sig0x4260->addChild(subItem32);
    sig0x4260->addChild(subItem33);
    sig0x4260->addChild(subItem34);

    //0x4270
    QTreeWidgetItem *sig0x4270 = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x4270)));
    group->addChild(sig0x4270);

    QTreeWidgetItem* subItem41 = new QTreeWidgetItem(sig0x4270, QStringList(QString("%1").arg(BMS_MAX_MODULE_CT)));
    subItem41->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem41->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem42 = new QTreeWidgetItem(sig0x4270, QStringList(QString("%1").arg(BMS_MIN_MOUDLE_CT)));
    subItem42->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem42->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem43 = new QTreeWidgetItem(sig0x4270, QStringList(QString("%1").arg(BMS_MAX_MCT_NO)));
    subItem43->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem43->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem44= new QTreeWidgetItem(sig0x4270, QStringList(QString("%1").arg(BMS_MIN_MCT_NO)));
    subItem44->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem44->setCheckState(0, Qt::Unchecked);

    sig0x4270->addChild(subItem41);
    sig0x4270->addChild(subItem42);
    sig0x4270->addChild(subItem43);
    sig0x4270->addChild(subItem44);
}


void SignalTreeWidget::CreateBMSCellStatusItem()
{
    QTreeWidgetItem *group = new QTreeWidgetItem(this);
    group->setText(0, "BMS电池状态信息");
    m_signalList.append(group);

    //0x4250
    QTreeWidgetItem *sig0x4250= new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x4250)));
    group->addChild(sig0x4250);

    QTreeWidgetItem* subItem11 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_BASIC_STATUS)));
    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem11->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem12 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ERR_VOLT_SENSOR)));
    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem12->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem13 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ERR_TEMP_SENSOR)));
    subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem13->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem14 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ERR_INN_COM)));
    subItem14->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem14->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem15 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ERR_CHRG_VOLT_HIGH)));
    subItem15->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem15->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem16 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ERR_WIRE_INVERSED)));
    subItem16->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem16->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem17 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ERR_RELAY_STICKY)));
    subItem17->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem17->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem18 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ALM_CELL_VOLT_LOW)));
    subItem18->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem18->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem19 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ALM_CELL_VOLT_HIGH)));
    subItem19->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem19->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem120 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ALM_PACK_VOLT_LOW)));
    subItem120->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem120->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem121 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ALM_PACK_VOLT_HIGH)));
    subItem121->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem121->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem122 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ALM_CHRG_TEMP_LOW)));
    subItem122->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem122->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem123 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ALM_CHRG_TEMP_HIGH)));
    subItem123->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem123->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem124 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ALM_DISCHRG_TEMP_LOW)));
    subItem124->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem124->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem125 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ALM_DISCHRG_TEMP_HIGH)));
    subItem125->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem125->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem126 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ALM_CHRG_CURR_HIGH)));
    subItem126->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem126->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem127 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ALM_DISCHRG_CURR_HIGH)));
    subItem127->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem127->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem128 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ALM_MODULE_VOLT_LOW)));
    subItem128->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem128->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem129 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_ALM_MODULE_VOLT_HIGH)));
    subItem129->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem129->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem130 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_P_CELL_VOLT_LOW)));
    subItem130->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem130->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem131 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_P_CELL_VOLT_HIGH)));
    subItem131->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem131->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem132 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_P_PACK_VOLT_LOW)));
    subItem132->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem132->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem133 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_P_PACK_VOLT_HIGH)));
    subItem133->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem133->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem134 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_P_CHRG_TEMP_LOW)));
    subItem134->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem134->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem135 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_P_CHRG_TEMP_HIGH)));
    subItem135->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem135->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem136 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_P_DISCHRG_TEMP_LOW)));
    subItem136->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem136->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem137 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_P_DISCHRG_TEMP_HIGH)));
    subItem137->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem137->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem138 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_P_CHRG_CURR_HIGH)));
    subItem138->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem138->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem139 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_P_DISCHRG_CURR_HIGH)));
    subItem139->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem139->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem140 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_P_MODULE_VOLT_LOW)));
    subItem140->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem140->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem141 = new QTreeWidgetItem(sig0x4250, QStringList(QString("%1").arg(BMS_P_MODULE_VOLT_HIGH)));
    subItem141->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem141->setCheckState(0, Qt::Unchecked);

    sig0x4250->addChild(subItem11);
    sig0x4250->addChild(subItem12);
    sig0x4250->addChild(subItem13);
    sig0x4250->addChild(subItem14);
    sig0x4250->addChild(subItem15);
    sig0x4250->addChild(subItem16);
    sig0x4250->addChild(subItem17);
    sig0x4250->addChild(subItem18);
    sig0x4250->addChild(subItem19);
    sig0x4250->addChild(subItem120);
    sig0x4250->addChild(subItem121);
    sig0x4250->addChild(subItem122);
    sig0x4250->addChild(subItem123);
    sig0x4250->addChild(subItem124);
    sig0x4250->addChild(subItem125);
    sig0x4250->addChild(subItem126);
    sig0x4250->addChild(subItem127);
    sig0x4250->addChild(subItem128);
    sig0x4250->addChild(subItem129);
    sig0x4250->addChild(subItem130);
    sig0x4250->addChild(subItem131);
    sig0x4250->addChild(subItem132);
    sig0x4250->addChild(subItem133);
    sig0x4250->addChild(subItem134);
    sig0x4250->addChild(subItem135);
    sig0x4250->addChild(subItem136);
    sig0x4250->addChild(subItem137);
    sig0x4250->addChild(subItem138);
    sig0x4250->addChild(subItem139);
    sig0x4250->addChild(subItem140);
    sig0x4250->addChild(subItem141);

    //0x18FF02A0
    QTreeWidgetItem *sig0x18FF02A0= new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF02A0)));
    group->addChild(sig0x18FF02A0);

    QTreeWidgetItem* subItem21 = new QTreeWidgetItem(sig0x18FF02A0, QStringList(QString("%1").arg(BMS_FORCE_CHRG_ST)));
    subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem21->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem22 = new QTreeWidgetItem(sig0x18FF02A0, QStringList(QString("%1").arg(BMS_POSI_RLY_ST)));
    subItem22->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem22->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem23 = new QTreeWidgetItem(sig0x18FF02A0, QStringList(QString("%1").arg(BMS_NEG_RLY_ST)));
    subItem23->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem23->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem24 = new QTreeWidgetItem(sig0x18FF02A0, QStringList(QString("%1").arg(BMS_RLY_STICKY)));
    subItem24->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem24->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem25 = new QTreeWidgetItem(sig0x18FF02A0, QStringList(QString("%1").arg(BMS_ALM_ST)));
    subItem25->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem25->setCheckState(0, Qt::Unchecked);

    sig0x18FF02A0->addChild(subItem21);
    sig0x18FF02A0->addChild(subItem22);
    sig0x18FF02A0->addChild(subItem23);
    sig0x18FF02A0->addChild(subItem24);
    sig0x18FF02A0->addChild(subItem25);

    //0x18FF04A0
    QTreeWidgetItem *sig0x18FF04A0= new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF04A0)));
    group->addChild(sig0x18FF04A0);

    QTreeWidgetItem* subItem31 = new QTreeWidgetItem(sig0x18FF04A0, QStringList(QString("%1").arg(BMS_FATAL_BMU_SENSOR)));
    subItem31->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem31->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem32 = new QTreeWidgetItem(sig0x18FF04A0, QStringList(QString("%1").arg(BMS_FATAL_BMU_AFE)));
    subItem32->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem32->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem33 = new QTreeWidgetItem(sig0x18FF04A0, QStringList(QString("%1").arg(BMS_FATAL_BMU_CV)));
    subItem33->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem33->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem34 = new QTreeWidgetItem(sig0x18FF04A0, QStringList(QString("%1").arg(BMS_FATAL_BMU_VT)));
    subItem34->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem34->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem35 = new QTreeWidgetItem(sig0x18FF04A0, QStringList(QString("%1").arg(BMS_FATAL_HVCU_COM)));
    subItem35->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem35->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem36 = new QTreeWidgetItem(sig0x18FF04A0, QStringList(QString("%1").arg(BMS_FATAL_HVCU_SENSOR)));
    subItem36->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem36->setCheckState(0, Qt::Unchecked);

    sig0x18FF04A0->addChild(subItem31);
    sig0x18FF04A0->addChild(subItem32);
    sig0x18FF04A0->addChild(subItem33);
    sig0x18FF04A0->addChild(subItem34);
    sig0x18FF04A0->addChild(subItem35);
    sig0x18FF04A0->addChild(subItem36);
}


void SignalTreeWidget::CreateBMSCommandItem()
{
    QTreeWidgetItem *group = new QTreeWidgetItem(this);
    group->setText(0, "BMS指令");
    m_signalList.append(group);

    //0x4280
    QTreeWidgetItem *sig0x4280= new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x4280)));
    group->addChild(sig0x4280);

    QTreeWidgetItem* subItem11 = new QTreeWidgetItem(sig0x4280, QStringList(QString("%1").arg(BMS_CHRG_FORBIDEN_MARK)));
    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem11->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem12 = new QTreeWidgetItem(sig0x4280, QStringList(QString("%1").arg(BMS_DISCHRG_FORBIDEN_MARK)));
    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem12->setCheckState(0, Qt::Unchecked);

    sig0x4280->addChild(subItem11);
    sig0x4280->addChild(subItem12);

    //0x8200
    QTreeWidgetItem *sig0x8200= new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRINGP_0x8200)));
    group->addChild(sig0x8200);

    QTreeWidgetItem* subItem21 = new QTreeWidgetItem(sig0x8200, QStringList(QString("%1").arg(BMS_SLEEP_CTRL)));
    subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem21->setCheckState(0, Qt::Unchecked);

    sig0x8200->addChild(subItem21);

    //0x8210
    QTreeWidgetItem *sig0x8210= new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x8210)));
    group->addChild(sig0x8210);

    QTreeWidgetItem* subItem31 = new QTreeWidgetItem(sig0x8210, QStringList(QString("%1").arg(BMS_CHRG_EN)));
    subItem31->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem31->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem32 = new QTreeWidgetItem(sig0x8210, QStringList(QString("%1").arg(BMS_DISCHRG_EN)));
    subItem32->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem32->setCheckState(0, Qt::Unchecked);

    sig0x8210->addChild(subItem31);
    sig0x8210->addChild(subItem32);

    //0x8220
    QTreeWidgetItem *sig0x8220= new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x8220)));
    group->addChild(sig0x8220);

    QTreeWidgetItem* subItem41 = new QTreeWidgetItem(sig0x8220, QStringList(QString("%1").arg(BMS_RELAY_FORCE_BREAK)));
    subItem41->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem41->setCheckState(0, Qt::Unchecked);

    sig0x8220->addChild(subItem41);
}


void SignalTreeWidget::CreateBMUStatusItem()
{
    int i = 0;
    QTreeWidgetItem *group = new QTreeWidgetItem(this);
    group->setText(0, "BMU状态");
    m_signalList.append(group);

    //0x18FF00Bx
    QTreeWidgetItem *sig0x18FF00Bx = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF00Bx)));
    group->addChild(sig0x18FF00Bx);

    for (i=0; i<8; i++)
    {
        //0x18FF00Bx
        QTreeWidgetItem *deviceNumber = new QTreeWidgetItem(sig0x18FF00Bx, QStringList(QString("%1").arg(i)));
        sig0x18FF00Bx->addChild(deviceNumber);

        QTreeWidgetItem* subItem11 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_AFE_SAMPLE)));
        subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem11->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem12 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_AFE_FAULT)));
        subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem12->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem13 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_OWD_ST)));
        subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem13->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem14 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV1_CELL_VOLT_LOW)));
        subItem14->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem14->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem15 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV1_CELL_VOLT_HIGH)));
        subItem15->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem15->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem16 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV1_CELL_VOLT_DIFF)));
        subItem16->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem16->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem17 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV1_MODULE_VOLT_LOW)));
        subItem17->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem17->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem18 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV1_MODULE_VOLT_HIGH)));
        subItem18->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem18->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem19 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV1_AMBIENT_TEMP_LOW)));
        subItem19->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem19->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem120 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV1_AMBIENT_TEMP_HIGH)));
        subItem120->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem120->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem121 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV1_CHRG_TEMP_LOW)));
        subItem121->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem121->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem122 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV1_CHRG_TEMP_HIGH)));
        subItem122->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem122->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem123 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV1_DISCHRG_TEMP_LOW)));
        subItem123->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem123->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem124 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV1_DISCHRG_TEMP_HIGH)));
        subItem124->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem124->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem125 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV2_CELL_VOLT_LOW)));
        subItem125->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem125->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem126 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV2_CELL_VOLT_HIGH)));
        subItem126->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem126->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem127 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV2_CELL_VOLT_DIFF)));
        subItem127->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem127->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem128 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV2_MODULE_VOLT_LOW)));
        subItem128->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem128->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem129 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV2_MODULE_VOLT_HIGH)));
        subItem129->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem129->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem130 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV2_AMBIENT_TEMP_LOW)));
        subItem130->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem130->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem131 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV2_AMBIENT_TEMP_HIGH)));
        subItem131->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem131->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem132 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV2_CHRG_TEMP_LOW)));
        subItem132->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem132->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem133 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV2_CHRG_TEMP_HIGH)));
        subItem133->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem133->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem134 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV2_DISCHRG_TEMP_LOW)));
        subItem134->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem134->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem135 = new QTreeWidgetItem(deviceNumber, QStringList(QString("%1").arg(BMU_LV2_DISCHRG_TEMP_HIGH)));
        subItem135->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem135->setCheckState(0, Qt::Unchecked);

        deviceNumber->addChild(subItem11);
        deviceNumber->addChild(subItem12);
        deviceNumber->addChild(subItem13);
        deviceNumber->addChild(subItem14);
        deviceNumber->addChild(subItem15);
        deviceNumber->addChild(subItem16);
        deviceNumber->addChild(subItem17);
        deviceNumber->addChild(subItem18);
        deviceNumber->addChild(subItem19);
        deviceNumber->addChild(subItem120);
        deviceNumber->addChild(subItem121);
        deviceNumber->addChild(subItem122);
        deviceNumber->addChild(subItem123);
        deviceNumber->addChild(subItem124);
        deviceNumber->addChild(subItem125);
        deviceNumber->addChild(subItem126);
        deviceNumber->addChild(subItem127);
        deviceNumber->addChild(subItem128);
        deviceNumber->addChild(subItem129);
        deviceNumber->addChild(subItem130);
        deviceNumber->addChild(subItem131);
        deviceNumber->addChild(subItem132);
        deviceNumber->addChild(subItem133);
        deviceNumber->addChild(subItem134);
        deviceNumber->addChild(subItem135);
    }
}


void SignalTreeWidget::CreateBMUBasicParaItem()
{
    int i = 0;
    QTreeWidgetItem *group = new QTreeWidgetItem(this);
    group->setText(0, "BMU基本参数");
    m_signalList.append(group);

    //0x18FF01Bx
    QTreeWidgetItem *sig0x18FF01Bx = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF01Bx)));
    group->addChild(sig0x18FF01Bx);

    //0x18FF02Bx
    QTreeWidgetItem *sig0x18FF02Bx = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF02Bx)));
    group->addChild(sig0x18FF02Bx);

    //0x18FF10Bx
    QTreeWidgetItem *sig0x18FF10Bx = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF10Bx)));
    group->addChild(sig0x18FF10Bx);

    //0x18FF20Bx
    QTreeWidgetItem *sig0x18FF20Bx = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF20Bx)));
    group->addChild(sig0x18FF20Bx);

    for (i=0; i<8; i++)
    {
        //0x18FF01Bx
        QTreeWidgetItem *deviceNumbe1 = new QTreeWidgetItem(sig0x18FF01Bx, QStringList(QString("%1").arg(i)));
        sig0x18FF01Bx->addChild(deviceNumbe1);

        QTreeWidgetItem* subItem11 = new QTreeWidgetItem(deviceNumbe1, QStringList(QString("%1").arg(BMU_SOC)));
        subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem11->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem12 = new QTreeWidgetItem(deviceNumbe1, QStringList(QString("%1").arg(BMU_DIFF_CELL_VOLT)));
        subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem12->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem13 = new QTreeWidgetItem(deviceNumbe1, QStringList(QString("%1").arg(BMU_DIFF_CELL_TEMP)));
        subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem13->setCheckState(0, Qt::Unchecked);

        deviceNumbe1->addChild(subItem11);
        deviceNumbe1->addChild(subItem12);
        deviceNumbe1->addChild(subItem13);

        //0x18FF02Bx
        QTreeWidgetItem *deviceNumbe2 = new QTreeWidgetItem(sig0x18FF02Bx, QStringList(QString("%1").arg(i)));
        sig0x18FF02Bx->addChild(deviceNumbe2);

        QTreeWidgetItem* subItem21 = new QTreeWidgetItem(deviceNumbe2, QStringList(QString("%1").arg(BMU_MODULE_VOLT)));
        subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem21->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem22 = new QTreeWidgetItem(deviceNumbe2, QStringList(QString("%1").arg(BMU_BOARD_TEMP)));
        subItem22->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem22->setCheckState(0, Qt::Unchecked);

        deviceNumbe2->addChild(subItem21);
        deviceNumbe2->addChild(subItem22);

        //0x18FF10Bx
        QTreeWidgetItem *deviceNumbe3 = new QTreeWidgetItem(sig0x18FF10Bx, QStringList(QString("%1").arg(i)));
        sig0x18FF10Bx->addChild(deviceNumbe3);

        QTreeWidgetItem* subItem31 = new QTreeWidgetItem(deviceNumbe3, QStringList(QString("%1").arg(BMU_MAX_CELL_VOLT)));
        subItem31->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem31->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem32 = new QTreeWidgetItem(deviceNumbe3, QStringList(QString("%1").arg(BMU_MIN_CELL_VOLT)));
        subItem32->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem32->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem33 = new QTreeWidgetItem(deviceNumbe3, QStringList(QString("%1").arg(BMU_AVG_CELL_VOLT)));
        subItem33->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem33->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem34 = new QTreeWidgetItem(deviceNumbe3, QStringList(QString("%1").arg(BMU_MAX_CV_NO)));
        subItem34->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem34->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem35 = new QTreeWidgetItem(deviceNumbe3, QStringList(QString("%1").arg(BMU_MIN_CV_NO)));
        subItem35->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem35->setCheckState(0, Qt::Unchecked);

        deviceNumbe3->addChild(subItem31);
        deviceNumbe3->addChild(subItem32);
        deviceNumbe3->addChild(subItem33);
        deviceNumbe3->addChild(subItem34);
        deviceNumbe3->addChild(subItem35);

        //0x18FF20Bx
        QTreeWidgetItem *deviceNumbe4 = new QTreeWidgetItem(sig0x18FF20Bx, QStringList(QString("%1").arg(i)));
        sig0x18FF20Bx->addChild(deviceNumbe4);

        QTreeWidgetItem* subItem41 = new QTreeWidgetItem(deviceNumbe4, QStringList(QString("%1").arg(BMU_MAX_CELL_TEMP)));
        subItem41->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem41->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem42 = new QTreeWidgetItem(deviceNumbe4, QStringList(QString("%1").arg(BMU_MIN_CELL_TEMP)));
        subItem42->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem42->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem43 = new QTreeWidgetItem(deviceNumbe4, QStringList(QString("%1").arg(BMU_AVG_CELL_TEMP)));
        subItem43->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem43->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem44 = new QTreeWidgetItem(deviceNumbe4, QStringList(QString("%1").arg(BMU_MAX_CT_NO)));
        subItem44->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem44->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem45 = new QTreeWidgetItem(deviceNumbe4, QStringList(QString("%1").arg(BMU_MIN_CT_NO)));
        subItem45->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem45->setCheckState(0, Qt::Unchecked);

        deviceNumbe4->addChild(subItem41);
        deviceNumbe4->addChild(subItem42);
        deviceNumbe4->addChild(subItem43);
        deviceNumbe4->addChild(subItem44);
        deviceNumbe4->addChild(subItem45);
    }
}


void SignalTreeWidget::CreateBMUBalItem()
{
    int i = 0;
    int j = 0;
    QTreeWidgetItem *group = new QTreeWidgetItem(this);
    group->setText(0, "BMU均衡状态");
    m_signalList.append(group);

    //0x18FF30Bx
    QTreeWidgetItem *sig0x18FF30Bx = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF30Bx)));
    group->addChild(sig0x18FF30Bx);

    for (i=0; i<8; i++)
    {
        //0x18FF01Bx
        QTreeWidgetItem *deviceNumbe1 = new QTreeWidgetItem(sig0x18FF30Bx, QStringList(QString("%1").arg(i)));
        sig0x18FF30Bx->addChild(deviceNumbe1);

        QTreeWidgetItem* subItem11 = new QTreeWidgetItem(deviceNumbe1, QStringList(QString("%1").arg(BMU_CELL_BAL_MODE)));
        subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem11->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem12 = new QTreeWidgetItem(deviceNumbe1, QStringList(QString("%1").arg(BMU_CELL_BAL_ST)));
        subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem12->setCheckState(0, Qt::Unchecked);

        deviceNumbe1->addChild(subItem11);
        deviceNumbe1->addChild(subItem12);

        for (j=1; j<17; j++)
        {
            QTreeWidgetItem* subItem13 = new QTreeWidgetItem(deviceNumbe1, QStringList(QString("%1%2").arg(STRING_BMU_CELL_IN_BAL).arg(j-1)));
            subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            subItem13->setCheckState(0, Qt::Unchecked);
            deviceNumbe1->addChild(subItem13);
        }
    }
}


void SignalTreeWidget::CreateBMUCellVoltItem()
{
    int i = 0;
    int j = 0;
    QTreeWidgetItem *group = new QTreeWidgetItem(this);
    group->setText(0, "BMU单芯电压");
    m_signalList.append(group);

    //0x18FF40Bx
    QTreeWidgetItem *sig0x18FF40Bx = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF40Bx)));
    group->addChild(sig0x18FF40Bx);

    //0x18FF41Bx
    QTreeWidgetItem *sig0x18FF41Bx = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF41Bx)));
    group->addChild(sig0x18FF41Bx);

    //0x18FF42Bx
    QTreeWidgetItem *sig0x18FF42Bx = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF42Bx)));
    group->addChild(sig0x18FF42Bx);

    //0x18FF43Bx
    QTreeWidgetItem *sig0x18FF43Bx = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF43Bx)));
    group->addChild(sig0x18FF43Bx);


    for (i=0; i<8; i++)
    {
        //0x18FF40Bx
        QTreeWidgetItem *deviceNumbe1 = new QTreeWidgetItem(sig0x18FF40Bx, QStringList(QString("%1").arg(i)));
        sig0x18FF40Bx->addChild(deviceNumbe1);

        for (j=1; j<5; j++)
        {
            QTreeWidgetItem* subItem11 = new QTreeWidgetItem(deviceNumbe1, QStringList(QString("%1%2").arg(STRING_BMU_CELL_VOLT).arg(j-1)));
            subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            subItem11->setCheckState(0, Qt::Unchecked);
            deviceNumbe1->addChild(subItem11);
        }

        //0x18FF41Bx
        QTreeWidgetItem *deviceNumbe2 = new QTreeWidgetItem(sig0x18FF41Bx, QStringList(QString("%1").arg(i)));
        sig0x18FF41Bx->addChild(deviceNumbe2);

        for (j=5; j<9; j++)
        {
            QTreeWidgetItem* subItem12 = new QTreeWidgetItem(deviceNumbe2, QStringList(QString("%1%2").arg(STRING_BMU_CELL_VOLT).arg(j-1)));
            subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            subItem12->setCheckState(0, Qt::Unchecked);
            deviceNumbe1->addChild(subItem12);
        }

        //0x18FF42Bx
        QTreeWidgetItem *deviceNumbe3 = new QTreeWidgetItem(sig0x18FF42Bx, QStringList(QString("%1").arg(i)));
        sig0x18FF42Bx->addChild(deviceNumbe3);

        for (j=9; j<13; j++)
        {
            QTreeWidgetItem* subItem13 = new QTreeWidgetItem(deviceNumbe3, QStringList(QString("%1%2").arg(STRING_BMU_CELL_VOLT).arg(j-1)));
            subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            subItem13->setCheckState(0, Qt::Unchecked);
            deviceNumbe1->addChild(subItem13);
        }

        //0x18FF43Bx
        QTreeWidgetItem *deviceNumbe4 = new QTreeWidgetItem(sig0x18FF43Bx, QStringList(QString("%1").arg(i)));
        sig0x18FF43Bx->addChild(deviceNumbe4);


        for (j=13; j<17; j++)
        {
            QTreeWidgetItem* subItem14 = new QTreeWidgetItem(deviceNumbe4, QStringList(QString("%1%2").arg(STRING_BMU_CELL_VOLT).arg(j-1)));
            subItem14->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            subItem14->setCheckState(0, Qt::Unchecked);
        }
    }
}


void SignalTreeWidget::CreateBMUCellTempItem()
{
    int i = 0;
    int j = 0;
    QTreeWidgetItem *group = new QTreeWidgetItem(this);
    group->setText(0, "BMU单芯温度");
    m_signalList.append(group);

    //0x18FF50Bx
    QTreeWidgetItem *sig0x18FF50Bx = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF50Bx)));
    group->addChild(sig0x18FF50Bx);

    for (i=0; i<8; i++)
    {
        //0x18FF40Bx
        QTreeWidgetItem *deviceNumbe1 = new QTreeWidgetItem(sig0x18FF50Bx, QStringList(QString("%1").arg(i)));
        sig0x18FF50Bx->addChild(deviceNumbe1);

        for (j=1; j<5; j++)
        {
            QTreeWidgetItem* subItem11 = new QTreeWidgetItem(deviceNumbe1, QStringList(QString("%1%2").arg(STRING_BMU_CELL_TEMP).arg(j-1)));
            subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            subItem11->setCheckState(0, Qt::Unchecked);
            deviceNumbe1->addChild(subItem11);
        }
    }
}


void SignalTreeWidget::CreateBMUConfigItem()
{
    int i = 0;
    QTreeWidgetItem *group = new QTreeWidgetItem(this);
    group->setText(0, "BMU模组配置");
    m_signalList.append(group);

    //0x18FF60Bx
    QTreeWidgetItem *sig0x18FF60Bx = new QTreeWidgetItem(group, QStringList(QString("%1").arg(STRING_0x18FF60Bx)));
    group->addChild(sig0x18FF60Bx);

    for (i=0; i<8; i++)
    {
        //0x18FF60Bx
        QTreeWidgetItem *deviceNumbe1 = new QTreeWidgetItem(sig0x18FF60Bx, QStringList(QString("%1").arg(i)));
        sig0x18FF60Bx->addChild(deviceNumbe1);

        QTreeWidgetItem* subItem11 = new QTreeWidgetItem(deviceNumbe1, QStringList(QString("%1").arg(BMU_CELL_AH)));
        subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem11->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem12 = new QTreeWidgetItem(deviceNumbe1, QStringList(QString("%1").arg(BMU_CELL_RATE_VOLT)));
        subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem12->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem13 = new QTreeWidgetItem(deviceNumbe1, QStringList(QString("%1").arg(BMU_CELL_NUM)));
        subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem13->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* subItem14 = new QTreeWidgetItem(deviceNumbe1, QStringList(QString("%1").arg(BMU_TEMP_NUM)));
        subItem14->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem14->setCheckState(0, Qt::Unchecked);

        deviceNumbe1->addChild(subItem11);
        deviceNumbe1->addChild(subItem12);
        deviceNumbe1->addChild(subItem13);
        deviceNumbe1->addChild(subItem14);
    }
}



