# BMSTestTool

This is a windows application to test NetZero battery management system.

---About environment:

(1) This application is developed base on Qt5.7.0, and the version of Qt must over 5.7.0 to support QChart API.

(2) Call the ControlCAN.dll to support the CAN communication with devices.

(3) MySQL database to save the system parameter information, my version is mysql-5.7.24-win32. Now you have to configurate the MySQL to support Chinese charactor, because our parameter names are stored in Chinese

---About functions:

(1) sql and CAN connection setting.

(2) sql and CAN connection status.
![image](https://github.com/ornothing/BMSTestTool/blob/master/image/setting%20page.png)

(3) Realtime BMS(Battery Management System) information.
![image](https://github.com/ornothing/BMSTestTool/blob/master/image/BMSInfo%20page.png)

(4) Realtime BMU(Battery Management Unit) information.
![image](https://github.com/ornothing/BMSTestTool/blob/master/image/BMUInfo%20page.png)

(5) BMS and BMU signals timeout.

(6) Save parameters and values to recent record db(saved realtime) and history record db(saved average value every 1 minute a time).

(7) Draw the realtime parameter curves(supports up to six parameters at a time).
![image](https://github.com/ornothing/BMSTestTool/blob/master/image/realtime%20curve%20page.png)

(8) Draw the history parameter curves(supports up to one parameter at a time).
![image](https://github.com/ornothing/BMSTestTool/blob/master/image/history%20curve%20page.png)

(9) Condition searching in recent record db or history record db and display in table. 
![image](https://github.com/ornothing/BMSTestTool/blob/master/image/history%20record%20page.png)

(10) Support interface to clean and rebuild the dbs(more than 1.5 millions/h records in recent record db).
