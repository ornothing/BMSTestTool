#ifndef DATABASEDEFINE_H
#define DATABASEDEFINE_H

#include <QString>

/*
近期数据表用来储存最近一天的测试数据。
近期数据表分为近期数值表与近期状态表，分别用来存储数值型数据和状态型数据。

RecentValue：近期数值表。记录终端每一条发过来的数值信息。
+---------------+----------------------+------+-----+-------------------+-----------------------------+
| Field         | Type                 | Null | Key | Default           | Extra                       |
+---------------+----------------------+------+-----+-------------------+-----------------------------+
| SerialNumber  | int(10) unsigned     | NO   | PRI | NULL              | auto_increment              |
| RecvTime      | timestamp            | NO   | MUL | CURRENT_TIMESTAMP | on update CURRENT_TIMESTAMP |
| TestNumber    | smallint(5) unsigned | YES  | MUL | NULL              |                             |
| SignalID      | int(10) unsigned     | YES  | MUL | NULL              |                             |
| ParameterName | varchar(21)          | YES  | MUL | NULL              |                             |
| Value         | smallint(5) unsigned | YES  |     | NULL              |                             |
| Ratio         | float(2,1)           | YES  |     | 1.0               |                             |
| Offset        | smallint(6)          | YES  |     | 0                 |                             |
+---------------+----------------------+------+-----+-------------------+-----------------------------+



RecentStatus：近期状态表。记录每一次终端状态变化时的状态信息，状态没有变化时，不记录。
+---------------+----------------------+------+-----+-------------------+-----------------------------+
| Field         | Type                 | Null | Key | Default           | Extra                       |
+---------------+----------------------+------+-----+-------------------+-----------------------------+
| SerialNumber  | int(10) unsigned     | NO   | PRI | NULL              | auto_increment              |
| ChangeTime    | timestamp            | NO   | MUL | CURRENT_TIMESTAMP | on update CURRENT_TIMESTAMP |
| TestNumber    | smallint(5) unsigned | YES  | MUL | NULL              |                             |
| SignalID      | int(10) unsigned     | YES  | MUL | NULL              |                             |
| ParameterName | varchar(21)          | YES  | MUL | NULL              |                             |
| Status        | tinyint(3) unsigned  | YES  |     | NULL              |                             |
+---------------+----------------------+------+-----+-------------------+-----------------------------+



历史数据表，用来存储过往所有的历史测试数据（不包括最近一天的）。
每次测试开始之前，都需要对本次测试的编号进行配置。同时软件会自动检测系统日期是否发生变化，如果发生变化，系统会提示测试人员保存近期数据到历史数据表格中。

HistoryValue table：历史数值表。更新是，历史数值表是按照一分钟的间隔，取出近期数值表中的某一个信号参数在这一分钟内的所有信息（可能有很多条，
具体依信号的发送频率而定），然后对这些信息进行取最大值、最小值与平均值，然后生成一条记录存放在该表中，作为该信号参数在这个时间段内的历史信息。
+---------------+----------------------+------+-----+-------------------+-----------------------------+
| Field         | Type                 | Null | Key | Default           | Extra                       |
+---------------+----------------------+------+-----+-------------------+-----------------------------+
| SerialNumber  | int(10) unsigned     | NO   | PRI | NULL              | auto_increment              |
| StartTime     | timestamp            | NO   | MUL | CURRENT_TIMESTAMP | on update CURRENT_TIMESTAMP |
| TestNumber    | smallint(5) unsigned | YES  | MUL | NULL              |                             |
| SignalID      | int(10) unsigned     | YES  | MUL | NULL              |                             |
| ParameterName | varchar(21)          | YES  | MUL | NULL              |                             |
| MaxValue      | smallint(5) unsigned | YES  |     | NULL              |                             |
| MinValue      | smallint(5) unsigned | YES  |     | NULL              |                             |
| AverageValue  | float(10,1)          | YES  |     | NULL              |                             |
| Ratio         | float(2,1)           | YES  |     | 1.0               |                             |
| Offset        | smallint(6)          | YES  |     | NULL              |                             |
+---------------+----------------------+------+-----+-------------------+-----------------------------+


HistoryStatus：历史状态表。直接将当前近期状态表中的所有数据直接添加到历史状态表中。
+---------------+----------------------+------+-----+-------------------+-----------------------------+
| Field         | Type                 | Null | Key | Default           | Extra                       |
+---------------+----------------------+------+-----+-------------------+-----------------------------+
| SerialNumber  | int(10) unsigned     | NO   | PRI | NULL              | auto_increment              |
| ChangeTime    | timestamp            | NO   | MUL | CURRENT_TIMESTAMP | on update CURRENT_TIMESTAMP |
| TestNumber    | smallint(5) unsigned | YES  | MUL | NULL              |                             |
| SignalID      | int(10) unsigned     | YES  | MUL | NULL              |                             |
| ParameterName | varchar(21)          | YES  | MUL | NULL              |                             |
| Status        | tinyint(3) unsigned  | YES  |     | NULL              |                             |
+---------------+----------------------+------+-----+-------------------+-----------------------------+

mysql> select current_timestamp - interval 7 day;
+------------------------------------+
| current_timestamp - interval 7 day |
+------------------------------------+
| 2018-11-27 20:20:46                |
+------------------------------------+
1 row in set (0.00 sec)

*/

//void SaveHistoryStatus(QString time, QString current);


/** 数据库名称 **/
#define RECENT_RECORD "RecentRecord"
#define HISTORY_RECORD "HistoryRecord"
#define TEST_CASE "TestCase"

//#define RATIO_0_0_0_0_1 0.0001
//#define RATIO_0_0_0_0_0_1 0.00001
//#define RATIO_0_1 0.1
//#define RATIO_1 1
//#define OFFSET_0 0
//#define OFFSET_100 -100
//#define OFFSET_3000 -3000

#define HISTORY_DAYS 7
#define SOURCE_RECORD 1
#define AVERAGE_RECORD 2


/* -------------- 信号定义 -------------*/
//电池模组参数
#define SIG_0x4200 0x4200
#define SIG_0x4210 0x4210
#define SIG_0x18FF02C0 0x18FF02C0
#define SIG_0x4220 0x4220
//电池基本参数
#define SIG_0x4230 0x4230
#define SIG_0x4240 0x4240
#define SIG_0x4260 0x4260
#define SIG_0x4270 0x4270
//电池状态信息与故障信息
#define SIG_0x4250 0x4250
#define SIG_0x18FF02A0 0x18FF02A0
#define SIG_0x18FF04A0 0x18FF04A0
//指令
#define SIG_0x4280 0x4280
#define SIG_0x8200 0x8200
#define SIG_0x8210 0x8210
#define SIG_0x8220 0x8220

//BMU状态
#define SIG_0x18FF00B0 0x18FF00B0
//BMU基本参数
#define SIG_0x18FF01B0 0x18FF01B0
#define SIG_0x18FF02B0 0x18FF02B0
#define SIG_0x18FF10B0 0x18FF10B0
#define SIG_0x18FF20B0 0x18FF20B0
//均衡状态
#define SIG_0x18FF30B0 0x18FF30B0
//单体电压
#define SIG_0x18FF40B0 0x18FF40B0
#define SIG_0x18FF41B0 0x18FF41B0
#define SIG_0x18FF42B0 0x18FF42B0
#define SIG_0x18FF43B0 0x18FF43B0
//单体温度
#define SIG_0x18FF50B0 0x18FF50B0
//模组配置
#define SIG_0x18FF60B0 0x18FF60B0


/** BMS cmd **/
//0x4200
#define STRING_0x4200 "0x4200"
#define BMS_POLL_GLOBAL_INFO "获取总体信息"

/** BMS电池模组参数 **/
//0x4210
#define STRING_0x4210 "0x4210"
#define BMS_PACK_VOLT "电池组总压"
#define BMS_PACK_CURR "电池组电流"
#define BMS_AMBIENT_TEMP_OUT "环境温度(外)"
#define BMS_SOC "BMS_SOC"
#define BMS_PACK_PWR "电池组功率"

//0x18FF02C0
#define STRING_0x18FF02C0 "0x18FF02C0"
#define BMS_AMBIENT_TEMP_IN "环境温度(内)"

//0x4220
#define STRING_0x4220 "0x4220"
#define BMS_MAX_CHG_CURR "最大充电电流"
#define BMS_MAX_DISCHG_CURR "最大放电电流"

/** BMS电池基本参数 **/
//0x4230
#define STRING_0x4230 "0x4230"
#define BMS_MAX_CELL_VLOT "BMS最高单芯电压"
#define BMS_MIN_CELL_VOLT "BMS最低单芯电压"
#define BMS_MAX_CV_NO "BMS最高单芯电压编号"
#define BMS_MIN_CV_NO "BMS最低单芯电压编号"

//0x4240
#define STRING_0x4240 "0x4240"
#define BMS_MAX_CELL_TEMP "BMS最高单芯温度"
#define BMS_MIN_CELL_TEMP "BMS最低单芯温度"
#define BMS_MAX_CT_NO "BMS最高单芯温度编号"
#define BMS_MIN_CT_NO "BMS最低单芯温度编号"

//0x4260
#define STRING_0x4260 "0x4260"
#define BMS_MAX_MODULE_CV "模组中最高单芯电压值"
#define BMS_MIN_MODULE_CV "模组中最低单芯电压值"
#define BMS_MAX_MCV_NO "模组中最高单芯电压编号"
#define BMS_MIN_MCV_NO "模组中最低单芯电压编号"

//0x4270
#define STRING_0x4270 "0x4270"
#define BMS_MAX_MODULE_CT "模组中最高单芯温度值"
#define BMS_MIN_MOUDLE_CT "模组中最低单芯温度值"
#define BMS_MAX_MCT_NO "模组中最高单芯温度编号"
#define BMS_MIN_MCT_NO "模组中最低单芯温度编号"

/** BMS电池状态与故障信息 **/
//0x4250
#define STRING_0x4250 "0x4250"
#define BMS_BASIC_STATUS "基础状态"

#define BMS_ERR_VOLT_SENSOR "电压传感器故障"
#define BMS_ERR_TEMP_SENSOR "温度传感器故障"
#define BMS_ERR_INN_COM "内部通信故障"
#define BMS_ERR_CHRG_VOLT_HIGH "充电电压高故障"
#define BMS_ERR_WIRE_INVERSED "动力线反接故障"
#define BMS_ERR_RELAY_STICKY "继电器粘滞故障"

#define BMS_ALM_CELL_VOLT_LOW "告警：单体电压低"
#define BMS_ALM_CELL_VOLT_HIGH "告警：单体电压高"
#define BMS_ALM_PACK_VOLT_LOW "告警：总电压低"
#define BMS_ALM_PACK_VOLT_HIGH "告警：总电压高"
#define BMS_ALM_CHRG_TEMP_LOW "告警：充电温度低"
#define BMS_ALM_CHRG_TEMP_HIGH "告警：充电温度高"
#define BMS_ALM_DISCHRG_TEMP_LOW "告警：放电温度低"
#define BMS_ALM_DISCHRG_TEMP_HIGH "告警：放电温度高"
#define BMS_ALM_CHRG_CURR_HIGH "告警：充电电流大"
#define BMS_ALM_DISCHRG_CURR_HIGH "告警：放电电流大"
#define BMS_ALM_MODULE_VOLT_LOW "告警：模组电压低"
#define BMS_ALM_MODULE_VOLT_HIGH "告警：模组电压高"

#define BMS_P_CELL_VOLT_LOW "保护：单体电压低"
#define BMS_P_CELL_VOLT_HIGH "保护：单体电压高"
#define BMS_P_PACK_VOLT_LOW "保护：总电压低"
#define BMS_P_PACK_VOLT_HIGH "保护：总电压高"
#define BMS_P_CHRG_TEMP_LOW "保护：充电温度低"
#define BMS_P_CHRG_TEMP_HIGH "保护：充电温度高"
#define BMS_P_DISCHRG_TEMP_LOW "保护：放电温度低"
#define BMS_P_DISCHRG_TEMP_HIGH "保护：放电温度高"
#define BMS_P_CHRG_CURR_HIGH "保护：充电电流大"
#define BMS_P_DISCHRG_CURR_HIGH "保护：放电电流大"
#define BMS_P_MODULE_VOLT_LOW "保护：模组电压低"
#define BMS_P_MODULE_VOLT_HIGH "保护：模组电压高"

//0x18FF02A0
#define STRING_0x18FF02A0 "0x18FF02A0"
#define BMS_FORCE_CHRG_ST "强制充电状态"
#define BMS_POSI_RLY_ST "继电器1闭合状态"
#define BMS_NEG_RLY_ST "继电器2闭合状态"
#define BMS_RLY_STICKY "继电器粘滞"
#define BMS_ALM_ST "故障等级"

//0x18FF04A0
#define STRING_0x18FF04A0 "0x18FF04A0"
#define BMS_FATAL_BMU_SENSOR "BMU AFE采样故障"
#define BMS_FATAL_BMU_AFE "BMU AFE Fault Pin"
#define BMS_FATAL_BMU_CV "BMU电压采样故障"
#define BMS_FATAL_BMU_VT "BMU温度采样故障"
#define BMS_FATAL_HVCU_COM "高压控制器通信故障"
#define BMS_FATAL_HVCU_SENSOR "高压控制器采样故障"

/** BMS指令 **/
//0x4280
#define  STRING_0x4280 "0x4280"
#define BMS_CHRG_FORBIDEN_MARK "充电禁止标志"
#define BMS_DISCHRG_FORBIDEN_MARK "放电禁止标志"

//0x8200
#define STRINGP_0x8200 "0x8200"
#define BMS_SLEEP_CTRL "休眠控制"

//0x8210
#define STRING_0x8210 "0x8210"
#define BMS_CHRG_EN "充电使能"
#define BMS_DISCHRG_EN "放电使能"

//0x8220
#define STRING_0x8220 "0x8220"
#define BMS_RELAY_FORCE_BREAK "总体信息"

/** BMU状态 **/
//0x18FF00Bx
#define STRING_0x18FF00Bx "0x18FF00Bx"
#define BMU_AFE_SAMPLE "AFE采样状态"
#define BMU_AFE_FAULT "AFE故障状态"
#define BMU_OWD_ST "断线检测(OWD)状态"

#define BMU_LV1_CELL_VOLT_LOW "单芯电压低一级"
#define BMU_LV1_CELL_VOLT_HIGH "单芯电压高一级"
#define BMU_LV1_CELL_VOLT_DIFF "单芯电压差一级"
#define BMU_LV1_MODULE_VOLT_LOW "模组电压低一级"
#define BMU_LV1_MODULE_VOLT_HIGH "模组电压高一级"
#define BMU_LV1_AMBIENT_TEMP_LOW "环境温度低一级"
#define BMU_LV1_AMBIENT_TEMP_HIGH "环境温度高一级"
#define BMU_LV1_CHRG_TEMP_LOW "充电温度低一级"
#define BMU_LV1_CHRG_TEMP_HIGH "充电温度高一级"
#define BMU_LV1_DISCHRG_TEMP_LOW "放电温度低一级"
#define BMU_LV1_DISCHRG_TEMP_HIGH "放电温度高一级"

#define BMU_LV2_CELL_VOLT_LOW "单芯电压低二级"
#define BMU_LV2_CELL_VOLT_HIGH "单芯电压高二级"
#define BMU_LV2_CELL_VOLT_DIFF "单芯电压差二级"
#define BMU_LV2_MODULE_VOLT_LOW "模组电压低二级"
#define BMU_LV2_MODULE_VOLT_HIGH "模组电压高二级"
#define BMU_LV2_AMBIENT_TEMP_LOW "环境温度低二级"
#define BMU_LV2_AMBIENT_TEMP_HIGH "环境温度高二级"
#define BMU_LV2_CHRG_TEMP_LOW "充电温度低二级"
#define BMU_LV2_CHRG_TEMP_HIGH "充电温度高二级"
#define BMU_LV2_DISCHRG_TEMP_LOW "放电温度低二级"
#define BMU_LV2_DISCHRG_TEMP_HIGH "放电温度高二级"

/** BMU基本参数 **/
//0x18FF01Bx
#define STRING_0x18FF01Bx "0x18FF01Bx"
#define BMU_SOC "单板SOC"
#define BMU_DIFF_CELL_VOLT "单芯电压差"
#define BMU_DIFF_CELL_TEMP "单芯温度差"

//0x18FF02Bx
#define STRING_0x18FF02Bx "0x18FF02Bx"
#define BMU_MODULE_VOLT "模组电压"
#define BMU_BOARD_TEMP "板载温度"

//0x18FF10Bx
#define STRING_0x18FF10Bx "0x18FF10Bx"
#define BMU_MAX_CELL_VOLT "BMU最高单芯电压"
#define BMU_MIN_CELL_VOLT "BMU最低单芯电压"
#define BMU_AVG_CELL_VOLT "平均单芯电压"
#define BMU_MAX_CV_NO "BMU最高单芯电压编号"
#define BMU_MIN_CV_NO "BMU最低单芯电压编号"

//0x18FF20Bx
#define STRING_0x18FF20Bx "0x18FF20Bx"
#define BMU_MAX_CELL_TEMP "BMU最高单芯温度"
#define BMU_MIN_CELL_TEMP "BMU最低单芯温度"
#define BMU_AVG_CELL_TEMP "平均单芯温度"
#define BMU_MAX_CT_NO "BMU最高单芯温度编号"
#define BMU_MIN_CT_NO "BMU最低单芯温度编号"

/** BMU均衡状态 **/
//0x18FF30Bx
#define STRING_0x18FF30Bx "0x18FF30Bx"
#define STRING_BMU_CELL_IN_BAL "均衡电芯"
#define BMU_CELL_BAL_MODE "均衡模式"
#define BMU_CELL_BAL_ST "均衡状态"
#define BMU_CELL_IN_BAL_0 "均衡电芯0"
#define BMU_CELL_IN_BAL_1 "均衡电芯1"
#define BMU_CELL_IN_BAL_2 "均衡电芯2"
#define BMU_CELL_IN_BAL_3 "均衡电芯3"
#define BMU_CELL_IN_BAL_4 "均衡电芯4"
#define BMU_CELL_IN_BAL_5 "均衡电芯5"
#define BMU_CELL_IN_BAL_6 "均衡电芯6"
#define BMU_CELL_IN_BAL_7 "均衡电芯7"
#define BMU_CELL_IN_BAL_8 "均衡电芯8"
#define BMU_CELL_IN_BAL_9 "均衡电芯9"
#define BMU_CELL_IN_BAL_10 "均衡电芯10"
#define BMU_CELL_IN_BAL_11 "均衡电芯11"
#define BMU_CELL_IN_BAL_12 "均衡电芯12"
#define BMU_CELL_IN_BAL_13 "均衡电芯13"
#define BMU_CELL_IN_BAL_14 "均衡电芯14"
#define BMU_CELL_IN_BAL_15 "均衡电芯15"

/** BMU单体电压 **/
//0x18FF40Bx
#define STRING_0x18FF40Bx "0x18FF40Bx"
#define STRING_BMU_CELL_VOLT "BMU单芯电压"
#define BMU_CELL_VOLT_0 "BMU单芯电压0"
#define BMU_CELL_VOLT_1 "BMU单芯电压1"
#define BMU_CELL_VOLT_2 "BMU单芯电压2"
#define BMU_CELL_VOLT_3 "BMU单芯电压3"

//0x18FF41Bx
#define STRING_0x18FF41Bx "0x18FF41Bx"
#define BMU_CELL_VOLT_4 "BMU单芯电压4"
#define BMU_CELL_VOLT_5 "BMU单芯电压5"
#define BMU_CELL_VOLT_6 "BMU单芯电压6"
#define BMU_CELL_VOLT_7 "BMU单芯电压7"

//0x18FF42Bx
#define STRING_0x18FF42Bx "0x18FF42Bx"
#define BMU_CELL_VOLT_8 "BMU单芯电压8"
#define BMU_CELL_VOLT_9 "BMU单芯电压9"
#define BMU_CELL_VOLT_10 "BMU单芯电压10"
#define BMU_CELL_VOLT_11 "BMU单芯电压11"

//0x18FF43Bx
#define  STRING_0x18FF43Bx "0x18FF43Bx"
#define BMU_CELL_VOLT_12 "BMU单芯电压12"
#define BMU_CELL_VOLT_13 "BMU单芯电压13"
#define BMU_CELL_VOLT_14 "BMU单芯电压14"
#define BMU_CELL_VOLT_15 "BMU单芯电压15"

/** BMU单体温度 **/
//0x18FF50Bx
#define  STRING_0x18FF50Bx "0x18FF50Bx"
#define STRING_BMU_CELL_TEMP "BMU单芯温度"
#define BMU_CELL_TEMP_0 "BMU单芯温度0"
#define BMU_CELL_TEMP_1 "BMU单芯温度1"
#define BMU_CELL_TEMP_2 "BMU单芯温度2"
#define BMU_CELL_TEMP_3 "BMU单芯温度3"

/** BMU模组配置 **/
//0x18FF60Bx
#define STRING_0x18FF60Bx "0x18FF60Bx"
#define BMU_CELL_AH "电芯安时数"
#define BMU_CELL_RATE_VOLT "电芯标称电压"
#define BMU_CELL_NUM "模组电池串数"
#define BMU_TEMP_NUM "模组温度采样点数量"


#endif // DATABASEDEFINE_H
