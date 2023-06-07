#include<iostream>
#include<conio.h>
#include<mysql.h>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
class stud;
class tea;
class motorroom;
vector<stud> studs;
vector<motorroom> room;
void getapplys();
vector<vector<string>> studapplys;
vector<tea> teas;
string applyroom;

const char* host = "127.0.0.1";
const char* user = "root";
const char* pw = "123456";
const char* database_name = "motorroom_apply";
const int port = 3306;


class login {
public:
	login(string n,string c) {
		name = n;
		cipher = c;
	}
	login(){}
	void logins() {
		int choose;
		string studd = "1.学生代表";
		string tead = "2.老师";
		string manager = "3.管理员";
		string logout = "4.退出";
		cout << "请选择需要的服务" << endl;
		cout << "********************" << endl;
		cout << studd<< endl;
		cout << tead << endl;
		cout << manager << endl;
		cout << logout << endl;
		cout << "********************" << endl;
		cout << "你的选择:"<<endl;
		cin >> choose ;
		sub(choose);
	}
	void sub(int j);
public:
	string name;
	string cipher;
};

class stud :public login {
public:
	stud(string s,string n,string c):login(n,c) {
		snum = s;
	}
	void funcmenu();
	void func();
	void apply();
	void getapply();
	void cancelapply();
	void logon();
	vector<string> studapply;
	string snum;
};

class tea :public login {
public:
	vector<tea> teas;
	tea(string w,string n,string c):login(n,c) {
		wnum = w;
	}
	void funcmenu();
	void func();
	void check();
	void logon();
	string wnum;
};

class admin :public login {
public:
	vector<admin> admins;
	admin(string n,string c):login(n,c) {

	}
	void funcmenu();
	void func();
	void addid();
	void logon();
private:
};

class motorroom {
public:
	motorroom(int i,bool j) {
		count = i;
		empty = j;
	}
	void inroom() {
		motorroom const a(20,false);
		motorroom const b(50,false);
		motorroom const c(100,false);
		room.push_back(a);
		room.push_back(b);
		room.push_back(c);
		MYSQL* con = mysql_init(NULL);
		//设置字符编码
		mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
		if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
		{
			cout << "连接数据库错误" << mysql_error(con) << endl;
			return;
		}
		string emplyed = a.empty ? "使用" : "未使用";
		char sqla[1024];
		sprintf_s(sqla, "insert into motorroom values(%d,%d,'%s');",
			1,a.count,emplyed.c_str());
		if (mysql_query(con, sqla))
		{
			
		}
		else
		{
			cout << "提交成功" << endl;
		}

		emplyed = b.empty ? "使用" : "未使用";
		char sqlb[1024];
		sprintf_s(sqlb, "insert into motorroom values(%d,%d,'%s');",
			2, b.count, emplyed.c_str());
		if (mysql_query(con, sqlb))
		{
			
		}
		else
		{
			cout << "提交成功" << endl;
		}

		emplyed = c.empty ? "使用" : "未使用";
		char sqlc[1024];
		sprintf_s(sqlc, "insert into motorroom values(%d,%d,'%s');",
			3, c.count, emplyed.c_str());
		if (mysql_query(con, sqlc))
		{
			
		}
		else
		{
			cout << "提交成功" << endl;
		}
	}
	int count;
	bool empty;
};

void getmotorroom() {
	for (int i = 0; i < 3; i++)
	{
		cout << i + 1 << "号机房" << "大小为" << room.at(i).count << endl;
		cout << "使用情况:" << (room.at(i).empty ? "已使用" : "未使用") << endl;
	}
	
}

void studlogin() {
	string  a, b, c;
	cout << "学号:" << endl;
	cin >> a;
	cout << "姓名:" << endl;
	cin >> b;
	cout << "登陆密码:" << endl;
	cin >> c;
	char c0;
	while ((c0 = _getch()) != '\r')
	{
		if (c0!= 8)
		{
			c.push_back(c0);
			putchar('*');
		}
	}
	cout << endl;
	stud studtest(a, b, c);
	MYSQL* con = mysql_init(NULL);
	//设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		cout << "连接数据库错误" << mysql_error(con) << endl;
		return;
	}

	char stuloginsql[4096];
	sprintf_s(stuloginsql, "select * from student where student_id=('%s');",
		studtest.snum.c_str());
	if (mysql_query(con, stuloginsql))
	{
		cout << "查询失败" << endl;
	}
	else
	{
		cout << "查询成功" << endl;
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	row = mysql_fetch_row(res);
	if (row==NULL)
	{
		cout << "查无此人，请联系管理员添加" << endl;
		studtest.logins();
	}
	else
	{
		cout << "登录成功" << endl;
		studtest.funcmenu();
		studtest.func();
	}
}

void tealogin() {
	string a, b, c;
	cout << "职工号:" << endl;
	cin >> a;
	cout << "姓名:" << endl;
	cin >> b;
	cout << "登陆密码:" << endl;
	cin >> c;
	char c1;
	while ((c1 = _getch()) != '\r')
	{
		if (c1 != 8)
		{
			c.push_back(c1);
			putchar('*');
		}
	}
	cout << endl;
	tea teatest(a, b, c);
	MYSQL* con = mysql_init(NULL);
	//设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		cout << "连接数据库错误" << mysql_error(con) << endl;
		return;
	}

	char tealoginsql[4096];
	sprintf_s(tealoginsql, "select * from teacher where teacher_id=('%s');",
		teatest.wnum.c_str());
	if (mysql_query(con, tealoginsql))
	{
		cout << "查询失败" << endl;
	}
	else
	{
		cout << "查询成功" << endl;
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		cout << "查无此人，请联系管理员添加" << endl;
		teatest.logins();
	}
	else
	{
		cout << "登录成功" << endl;
		teatest.funcmenu();
		teatest.func();
	}
}

void cleanapply() {
	studapplys.clear();
	MYSQL* con = mysql_init(NULL);
	//设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		cout << "连接数据库错误" << mysql_error(con) << endl;
		return;
	}

	char sqlclear[1024];
	sprintf_s(sqlclear, "delete from apply;");
	if (mysql_query(con, sqlclear))
	{
		cout << "提交失败" << endl;
	}
	else
	{
		cout << "提交成功" << endl;
	}
	cout << "已清空所有预约" << endl;
}

void addteaid() {
	string a, b, c;
	cout << "添加的老师职工号为:" << endl;
	cin >> a;
	cout << "添加的老师姓名为:" << endl;
	cin >> b;
	cout << "添加的老师登录密码为:" << endl;
	cin >> c;
	tea addtea(a, b, c);
	auto it = find_if(teas.begin(), teas.end(), [&addtea](tea findif) {
		return findif.wnum == addtea.wnum;
		});
	if (it != teas.end())
	{
		cout << "已有此号，无需添加" << endl;
	}
	else
	{
		teas.push_back(addtea);
		cout << "添加成功" << endl;
	}
	MYSQL* con = mysql_init(NULL);
	//设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		cout << "连接数据库错误" << mysql_error(con) << endl;
		return;
	}

	char asql[1024];
	sprintf_s(asql, "insert into teacher values('%s','%s','%s');",
		addtea.wnum.c_str(), addtea.name.c_str(), addtea.cipher.c_str());
	if (mysql_query(con, asql))
	{
		cout << "提交失败" << endl;
	}
	else
	{
		cout << "提交成功" << endl;
	}
}

void addstudid() {
	string a, b, c;
	cout << "添加的学生学号为:" << endl;
	cin >> a;
	cout << "添加的学生姓名为:" << endl;
	cin >> b;
	cout << "添加的学生登录密码为:" << endl;
	cin >> c;
	stud addstud(a, b, c);
	auto it = find_if(studs.begin(), studs.end(), [&addstud](stud findif) {
		return findif.snum == addstud.snum;
		});
	if (it != studs.end())
	{
		cout << "已有此号，无需添加" << endl;
	}
	else
	{
		studs.push_back(addstud);
		cout << "添加成功" << endl;
	}

	MYSQL* con = mysql_init(NULL);
	//设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		cout << "连接数据库错误" << mysql_error(con) << endl;
		return ;
	}

	char sql[1024];
	sprintf_s(sql, "insert into student values('%s','%s','%s');", 
		addstud.snum.c_str(), addstud.name.c_str(), addstud.cipher.c_str());
	if (mysql_query(con, sql))
	{
		cout << "提交失败" << endl;
	}
	else
	{
		cout << "提交成功" << endl;
	}
}

void getidstud() {
	MYSQL* con = mysql_init(NULL);
	//设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		cout << "连接数据库错误" << mysql_error(con) << endl;
		return;
	}

	char idsql[4096];
	sprintf_s(idsql, "select * from student;");
	if (mysql_query(con, idsql))
	{
		cout << "查询失败" << endl;
	}
	else
	{
		cout << "查询成功" << endl;
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		cout << "学号:" << row[0] << endl;
		cout << "姓名:" << row[1] << endl;
		cout << "密码:" << row[2] << endl;
	}
}

void getidtea() {
	/*for (int i = 0; i < teas.size(); i++)
	{
		cout << "教师姓名:" << teas.at(i).name << "\t" << "教师学号:" << teas.at(i).wnum
			<< "\t" << "教师登录密码:" << teas.at(i).cipher << endl;
	}*/
	MYSQL* con = mysql_init(NULL);
	//设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		cout << "连接数据库错误" << mysql_error(con) << endl;
		return;
	}

	char teasql[4096];
	sprintf_s(teasql, "select * from teacher;");
	if (mysql_query(con,teasql))
	{
		cout << "查询失败" << endl;
	}
	else
	{
		cout << "查询成功" << endl;
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		cout << "职工号:" << row[0] << endl;
		cout << "姓名:" << row[1] << endl;
		cout << "密码:" << row[2] << endl;
	}
}

void getid() {
	int getidchoose;
	cout << "查看学生请填1" << endl;
	cout << "查看教师请填2" << endl;
	cin >> getidchoose;
	switch (getidchoose)
	{
	case 1:
		getidstud();
		break;
	case 2:
		getidtea();
		break;
	default:
		cout << "请输入1或2,重新输入" << endl;
		getid();
		break;
	}
}

void login::sub(int choose) {
	int change;
	switch (choose)
	{
	case 1: {
		studlogin();
		break; }
	case 2: {
		tealogin();
		logins();
		break; }
	case 3: {
		string a, b, c;
		cout << "管理员姓名:" << endl;
		cin >> a;
		cout << "登陆密码:" << endl;
		char b1;
		while ((b1 = _getch()) != '\r')
		{
			if (b1 != 8)
			{
				b.push_back(b1);
				putchar('*');
			}
		}
		cout << endl;
		admin admintest(a, b);
		admintest.funcmenu();
		admintest.func();
		break; }
	default: {
		cout << "错误，请重新输入" << endl;
		cin >> change;
		sub(change);
		break; }
	}
}

void stud::funcmenu() {
	cout << "********************" << endl;
	cout << "1.申请预约" << endl;
	cout << "2.查看自身的预约" << endl;
	cout << "3.查看所有预约" << endl;
	cout << "4.取消预约" << endl;
	cout << "5.退出登录" << endl;
	cout << "********************" << endl;
}

void stud::apply() {
	string infojudge;
	string applyinfo;
	getmotorroom();
	infojudge = this->name + "   " + this->snum;
	string snum1 = this->snum;
	string info;
	string status;
	applyinfo += "现况:";
	status = "未审核";
	applyinfo += status += "    ";
	applyinfo += "机房号:";
	cout << "申请机房号:" << endl;
	cin >> info;
	applyinfo += info += "   ";
	applyinfo += "预约时间:";
	cout << "预约时间:" << endl;
	cin >> info;
	applyinfo += info;
	cout << "已提交申请" << endl;
	(this->studapply).push_back(applyinfo);
	MYSQL* con = mysql_init(NULL);
	//设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		cout << "连接数据库错误" << mysql_error(con) << endl;
		return;
	}

	char sqlapp[4096];
	sprintf_s(sqlapp, "insert into apply values('%s',%d,'%s');",
		applyinfo.c_str(),0, snum1.c_str());
	if (mysql_query(con, sqlapp))
	{
		cout << "提交失败" << endl;
	}
	else
	{
		cout << "提交成功" << endl;
	}
	funcmenu();
	func();
}

void stud::getapply() { 
	/*for (int i = 0; i < (this->studapply).size(); i++)
	{
		cout << studapply.at(i) << endl;
	}*/
	MYSQL* con = mysql_init(NULL);
	//设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		cout << "连接数据库错误" << mysql_error(con) << endl;
		return;
	}

	char idsql[4096];
	sprintf_s(idsql, "select * from apply where applied_id=('%s');",
		this->snum.c_str());
	if (mysql_query(con, idsql))
	{
		cout << "查询失败" << endl;
	}
	else
	{
		cout << "查询成功" << endl;
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		cout << "学号:" << row[2] << endl;
		cout << "序号:" << row[1] << endl;
		cout << "申请:" << row[0] << endl;
	}
	funcmenu();
	func();
}

void stud::cancelapply() {
	for (int i = 0; i < studapply.size(); i++) {
		cout << "申请记录为:" << studapply.at(i) << endl;
	}
	int cancel;
	cout << "取消的预约序号为:" << endl;
	cin >> cancel; 
	studapply.erase(remove(studapply.begin(),studapply.end(),(studapply.at(cancel-1))));
	MYSQL* con = mysql_init(NULL);
	//设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		cout << "连接数据库错误" << mysql_error(con) << endl;
		return;
	}

	char sqlcel[1024];
	sprintf_s(sqlcel, "delete from apply where apply_id=(%d);",
		cancel);
	if (mysql_query(con, sqlcel))
	{
		cout << "提交失败" << endl;
	}
	else
	{
		cout << "提交成功" << endl;
	}
	cout << "该预约已取消" << endl;
	funcmenu();
	func();
}

void stud::logon() {
	auto it = find_if(studs.begin(), studs.end(), [this](stud findif) {
		return findif.snum == this->snum;
		});
	if (it != studs.end())
	{
		it->studapply.assign(this->studapply.begin(), this->studapply.end());
	}
	cout << "已退出登陆" << endl;
	cout << endl;
	logins();
}

void stud::func() {
	int funcchoose;
	cout << "请选择你需要的服务序号:" << endl;
	cin >> funcchoose;
	switch (funcchoose)
	{
	case 1:
		apply();
		break;
	case 2:
		getapply();
		break;
	case 3:
		getapplys();
		funcmenu();
		func();
		break;
	case 4:
		cancelapply();
		break;
	case 5:
		logon();
		break;
	default:
		cout << "请输入数字1～5，请重新输入:" << endl;
		func();
		break;
	}
}

void tea::funcmenu() {
	cout << "********************" << endl;
	cout << "1.查看所有预约" << endl;
	cout << "2.审核预约" << endl;
	cout << "3.注册登陆" << endl;
	cout << "********************" << endl;
}

void tea::func() {
	int choose;
	cout << "请选择你需要的服务序号:" << endl;
	cin >> choose;
	switch (choose)
	{
	case 1:
		getapplys();
		funcmenu();
		func();
		break; 
	case 2:
		check();
		funcmenu();
		func();
	case 3:
		logon();
		break;
	default:
		cout << "请输入数字1～3，请重新输入:" << endl;
		func();
		break;
	}
}

void tea::check() {
	int x, y;
	cout << endl;
	getapplys();
	cout << "请选择学生序号:" << endl;
	cin >> x;
	cout << "请选择学生预约序号:" << endl;
	cin >> y;
	if (x-1 < studs.size() && y-1 < studs.at(x - 1).studapply.size())
	{  
		studs.at(x - 1).studapply.at(y - 1).replace(5,10,"已通过");
		studs.at(x - 1).studapply.at(y - 1).insert(11,"   ");
		const char fr=studs.at(x - 1).studapply.at(y - 1).at(21);
		string tg = studs.at(x - 1).studapply.at(y - 1);
		int roomid = fr - '0' - 1;
		room.at(fr - '0'-1).empty=true;
		string applied = "被预约";
		MYSQL* con = mysql_init(NULL);
		//设置字符编码
		mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
		if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
		{
			cout << "连接数据库错误" << mysql_error(con) << endl;
			return;
		}
		char tgsql[1024];
		sprintf_s(tgsql, "update apply set apply=('%s)' where apply_id=(%d) ;",
			tg.c_str(), y);
		if (mysql_query(con, tgsql))
		{
			cout << "提交失败" << endl;
		}

		char csql[1024];
		sprintf_s(csql, "update motorroom set room_empty=('%s') where room_id=(%d); ",
			applied.c_str(),roomid);
		if (mysql_query(con, csql))
		{
			cout << "提交失败" << endl;
		}
		else
		{
			cout << "提交成功" << endl;
		}
		cout << "已设置" << endl;
	}
	else
	{
		cout << "查无此值" << endl;
	}
}

void tea::logon(){
	cout << "已退出登陆" << endl;
	cout << endl;
	logins();
}

void admin::funcmenu() {
	cout << "******************************" << endl;
	cout << "1.添加学生或老师账号" << endl;
	cout << "2.选择查看学生或教师的全部信息" << endl;
	cout << "3.查看机房的全部信息" << endl;
	cout << "4.清空所有的预约记录" << endl;
	cout << "5.注销登录" << endl;
	cout << "******************************" << endl;
}

void admin::func() {
	int funcchoose;
	cout << "请选择你需要的服务序号:" << endl;
	cin >> funcchoose;
	switch (funcchoose)
	{
	case 1:
		addid();
		funcmenu();
		func();
		break;
	case 2:
		getid();
		funcmenu();
		func();
	case 3:
		getmotorroom();
		funcmenu();
		func();
		break;
	case 4:
		cleanapply();
		break;
	case 5:
		logon();
		break;
	default:
		cout << "请输入数字1～5，请重新输入:" << endl;
		func();
		break;
	}
}

void admin::addid() {
	int addchoose;
	cout << endl;
	cout << "1.学生" << endl;
	cout << "2.老师" << endl;
	cout << "请选择你需要添加的人员身份:" << endl;
	cin >> addchoose;
	switch (addchoose)
	{
	case 1:
		addstudid();
		break;
	case 2:
		addteaid();
		break;
	default:
		cout << "输入的值已超出索引范围，请重新输入" << endl;
		addid();
		break;
	}
}

void admin::logon() {
	cout << "退出登录" << endl;
	cout << endl;
	logins();
}

void getapplys() {
	MYSQL* con = mysql_init(NULL);
	//设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		cout << "连接数据库错误" << mysql_error(con) << endl;
		return;
	}

	char sesql[4096];
	sprintf_s(sesql, "select * from apply;");
	if (mysql_query(con, sesql))
	{
		cout << "查询失败" << endl;
	}
	else
	{
		cout << "查询成功" << endl;
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		cout << "学号:" << row[2] << endl;
		cout << "序号:"<<row[1] << endl;
		cout << "申请:"<<row[0] << endl;
	}
}

void setwindowstyle() {
	system("title 机房管理系统");
	system("color 07");
	system("mode con cols=75 lines=25");
}

int main() {
	setwindowstyle();
    motorroom roomtest(1,true);
	roomtest.inroom();
	login logintest;
	logintest.logins();
	return 0;
}