PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE "system_param_table"(
[ID] integer,
[value] integer,
[snapvalue] integer,
[defvalue] integer,
[lowvalue] integer,
[upvalue] integer,
[gain] integer,
[description] text  
);
INSERT INTO "system_param_table" VALUES(1,20,20,20,10,36,10,'除气泵电压');
INSERT INTO "system_param_table" VALUES(2,0,0,0,-20,20,10,'温度补偿');

CREATE TABLE "param_table"(
[id] integer
,[value] integer
,[snapvalue] integer
,[defvalue] integer
,[lowvalue] integer
,[upvalue] integer
,[gain] integer
,[description] text  
);
INSERT INTO "param_table" VALUES(1,370,370,370,330,400,10,'透析液温度');

CREATE TABLE "alarm_table"(
[ID] integer,
[value] integer,
[snapvalue] integer,
[defvalue] integer,
[lowvalue] integer,
[upvalue] integer,
[gain] integer,
[description] text   
);
INSERT INTO "alarm_table" VALUES(1,380,380,380,320,410,10,'温度报警上限');
INSERT INTO "alarm_table" VALUES(2,360,360,360,320,410,10,'温度报警下限');
INSERT INTO "alarm_table" VALUES(3,50,50,50,-500,700,1,'动脉压报警上限');
INSERT INTO "alarm_table" VALUES(4,-20,-20,-20,-500,700,1,'动脉压报警下限');
INSERT INTO "alarm_table" VALUES(5,200,200,200,-500,700,1,'静脉压报警上限');
INSERT INTO "alarm_table" VALUES(6,10,10,10,-500,700,1,'静脉压报警下限');
INSERT INTO "alarm_table" VALUES(7,150,150,150,-500,700,1,'跨膜压报警上限');
INSERT INTO "alarm_table" VALUES(8,0,0,0,-500,700,1,'跨膜压报警下限');

CREATE TABLE "historyTest"(
[ID] integer PRIMARY KEY AUTOINCREMENT,
[alarmDateTime] DATETIME,
[alarmCode] integer,
[alarmGrade] integer
);








CREATE TABLE cure_param_table (ID integer, name integer, value integer, snapvalue integer, defvalue integer, lowvalue integer, uppvalue integer, datatype integer, description TEXT);
INSERT INTO "cure_param_table" VALUES(NULL,101,240,240,240,0,1439,1,'治疗总时间（以分钟算）');
INSERT INTO "cure_param_table" VALUES(NULL,102,4,4,4,0,23,1,'设置治疗时间小时');

CREATE TABLE cad_param_table (defvalue integer, snapvalue integer, name integer, key TEXT, lowvalue integer, value integer, uppvalue integer, description text);
INSERT INTO "cad_param_table" VALUES(15,15,1,'normal_clean_run_time',5,15,30,'常规清洗时间');
INSERT INTO "cad_param_table" VALUES(800,800,2,'normal_clean_flow',300,800,800,'常规清洗流量');

CREATE TABLE historyalarm
(
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  alarmNum INT,
  alarmDateTime DATETIME,
  mode INT,
  runTime INT,
  apValue INT,
  vpValue INT,
  tmpValue INT,
  airCheck INT,
  bloodId INT,
  bloodLeak INT,
  yk INT,
  yj1 INT,
  yj2 INT,
  yj3 INT,
  rtAcond INT,
  rtBcond INT,
  Ccond INT,
  rtArpm INT,
  rtBrpm INT,
  UFrpm INT,
  Atemp INT,
  Btemp INT,
  Ctemp INT,
  WG1 INT,
  WG6 INT,
  jph INT,
  jpl INT,
  fph INT,
  fpl INT,
  dp INT,
  qpV INT,
  np INT,
  QPrpm INT,
  DPrpm INT,
  YPrpm INT,
  dpt INT,
  ypt INT,
  dsFlow INT
);
CREATE TABLE formula_table (formulaID integer PRIMARY KEY, formulaName text, BConcentrate int, pureWater int, Na int, K int, Ca int, Mg int, HCO3 int, NaCl int, NaHCO3_g int, P_AC int, isShow int, actualNa int);
INSERT INTO "formula_table" VALUES(0,'AK',1830,34000,1400,2000,1750,500,310,30600,590,4000,2,1400);
INSERT INTO "formula_table" VALUES(1,'MT',1225,32775,1380,2000,1750,500,320,0,840,3000,1,1380);
INSERT INTO "formula_table" VALUES(2,'COBE',1260,32740,1430,2500,1500,500,335,0,817,1500,1,1430);
INSERT INTO "formula_table" VALUES(3,'NIPRO',1830,32170,1380,2500,1500,750,290,0,482,1000,1,1380);
DELETE FROM sqlite_sequence;
INSERT INTO "sqlite_sequence" VALUES('historyalarm',3369);
COMMIT;
