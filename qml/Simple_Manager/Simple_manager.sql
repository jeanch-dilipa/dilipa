
CREATE TABLE [Provincial_region](
  [Provincial_region_id] INTEGER PRIMARY KEY, 
  [Provincial_region_name] TEXT);
  
CREATE TABLE [Municipal_area](
  [Municipal_area_id] INTEGER, 
  [Municipal_area_name] TEXT, 
  [superior] INTEGER, 
  PRIMARY KEY([Municipal_area_id], [superior]));

select * from Provincial_region;
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(1,"安徽省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(2,"澳门特别行政区");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(3,"北京市");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(4,"福建省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(5,"甘肃省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(6,"广东省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(7,"广西壮族自治区");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(8,"贵州省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(9,"海南省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(10,"河北省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(11,"河南省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(12,"黑龙江省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(13,"湖北省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(14,"湖南省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(15,"吉林省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(16,"江苏省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(17,"江西省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(18,"辽宁省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(19,"内蒙古自治区");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(20,"宁夏回族自治区");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(21,"青海省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(22,"山东省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(23,"山西省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(24,"陕西省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(25,"上海市");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(26,"四川省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(27,"台湾省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(28,"天津市");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(29,"西藏自治区");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(30,"香港特别行政区");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(31,"新疆维吾尔自治区");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(32,"云南省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(33,"浙江省");
insert into Provincial_region(Provincial_region_id,Provincial_region_name) values(34,"重庆市");
select * from Municipal_area
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(1,"合肥市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(2,"淮北市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(3,"亳州市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(4,"宿州市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(5,"蚌埠市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(6,"阜阳市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(7,"淮南市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(8,"滁州市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(9,"六安市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(10,"马鞍山市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(11,"芜湖市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(12,"宣城市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(13,"铜陵市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(14,"池州市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(15,"安庆市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(16,"黄山市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(17,"界首市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(18,"桐城市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(19,"天长市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(20,"明光市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(21,"巢湖市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(22,"宁国市",1);
insert into Municipal_area(Municipal_area_id,Municipal_area_name,superior) values(23,"潜山市",1);




