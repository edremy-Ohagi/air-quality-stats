#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;
#define MAX_VALUE 1E16
int Choice;//the choice that user enter
string split(20, '#');//the split line
enum airqlv { 优, 良, 轻度污染, 中度污染, 重度污染, 严重污染 };
ifstream datasrc("AQ_1.csv", ios::in);//read file
ifstream datacount("AQ_1.csv", ios::in);//read file
int infon = 0;//the number of info created
const int N = 324;


class City
{
public:
	string pro;
	string cname;
	string cno = "0";
	City() = default;
	City(string ta, string tb, string tc) :cno(ta), cname(tb), pro(tc) {}
	City(string tb, string tc) :cname(tb), pro(tc) {}
	//void cnocomplement(Loadr & src) {
	//	for (int i = 0; i < infon; i++) {
	//		if (src.ptar[i].mcity.cname == cname) {
	//			cno = src.ptar[i].mcity.cno;
	//			break;
	//		}
	//	}
	//calc cno, not used. needs fix.

	void input() {
		cout << "The format is (Province) (City name)" << endl;
		cin >> pro >> cname;
	}
	void modify(string ta, string tb, string tc) {
		cno = ta;
		cname = tb;
		pro = tc;
	}
	void show() {
		cout << "In " << pro << "," << cname << ", ";
	}
};

class Date
{
public:
	int year;
	int month;
	int day;
	int YMD;// to decrease calculation//u can choose to optimize by create a new member called "YMD" in class date, it is used to trans 3number to 1 number, to  decrease the "if"
	Date(string ty, string tm, string td) {
		year = atoi(ty.c_str());
		month = atoi(tm.c_str());
		day = atoi(td.c_str());
		YMD = day + month * 100 + year * 10000;
	}
	Date() = default;
	Date(const Date& obj) {
		year = obj.year;
		month = obj.month;
		day = obj.day;
		YMD = obj.YMD;
	}
	void input() {
		cout << "The format is (Year) (Month) (Day)" << endl;
		cin >> year >> month >> day;
		YMD = day + month * 100 + year * 10000;
	}
	void modify(string ty, string tm, string td) {
		year = atoi(ty.c_str());
		month = atoi(tm.c_str());
		day = atoi(td.c_str());
		YMD = day + month * 100 + year * 10000;
	}
	void modify(const Date& obj) {
		year = obj.year;
		month = obj.month;
		day = obj.day;
		YMD = obj.YMD;
	}
	void show() {
		cout << "on " << year << "/" << month << "/" << day << ", ";
	}
	void showC() {
		cout << "On " << year << "/" << month << "/" << day << ", ";
	}
};

class Airqlt
{
public:
	string lv;
	int aqi;
	int PM25;
	int PM10;
	int SO2;
	int NO2;
	int CO;
	int O3;
	void modify(string taqi, string tlv, string t1, string t2, string t3, string t4, string t5, string t6) {
		lv = tlv,
			aqi = (atoi(taqi.c_str()));
		PM25 = (atoi(t1.c_str()));
		PM10 = (atoi(t2.c_str()));
		SO2 = (atoi(t3.c_str()));
		NO2 = (atoi(t4.c_str()));
		CO = (atoi(t5.c_str()));
		O3 = (atoi(t6.c_str()));
	}
	void show() {
		cout << "the air quality level is " << lv << ".\nThe AQI indicator is " << aqi << ".\nThe average value of PM25 in 24 hours is " << PM25 << ".\nThe average value of PM10 in 24 hours is " << PM10 << ".\nThe average value of SO2 in 24 hours is " << SO2 << ".\nThe average value of NO2 in 24 hours is " << NO2 << ".\nThe average value of CO in 24 hours is " << CO << ".\nThe average value of O3 in 24 hours is " << O3;
	}
	void showS() {
		cout << "air quality level:" << lv << ". AQI:" << aqi << ". In 24h, PM25avg:" << PM25 << ", PM10avg:" << PM10 << ", SO2avg:" << SO2 << ", NO2avg:" << NO2 << ", COavg:" << CO << ", COavg:" << O3 << ".";
	}
};

class Recordinfo {
public:
	City mcity;
	Date mdate;
	Airqlt mairqlt;

	void modify(string tcno, string tcname, string tpro, Date tdate, string taqi, string tlv, string tPM25, string tPM10, string tSO2, string tNO2, string tCO, string tO3) {
		mcity.modify(tcno, tcname, tpro);
		mdate.modify(tdate);
		mairqlt.modify(taqi, tlv, tPM25, tPM10, tSO2, tNO2, tCO, tO3);

	}
	void swap(Recordinfo& obj) {
		City t1;
		Date t2;
		Airqlt t3;
		t1 = obj.mcity;
		t2 = obj.mdate;
		t3 = obj.mairqlt;
		obj.mcity = mcity;
		obj.mdate = mdate;
		obj.mairqlt = mairqlt;
		mcity = t1;
		mdate = t2;
		mairqlt = t3;

	}
};

class Loadr {
public:
	Recordinfo* ptar = nullptr;
	const int nsize;
	Loadr(int n) :nsize(n) {
		if (nsize) {
			ptar = new Recordinfo[n];
		}
	}
	~Loadr() {
		if (nsize) {
			delete[]ptar;
			ptar = nullptr;
		}
	}
	void modify(string tcno, string tcname, string tpro, Date tdate, string taqi, string tlv, string tPM25, string tPM10, string tSO2, string tNO2, string tCO, string tO3, int n) {
		ptar[n].modify(tcno, tcname, tpro, tdate, taqi, tlv, tPM25, tPM10, tSO2, tNO2, tCO, tO3);
	}
};//Loaded Record


void Load(Loadr& fdata)
{
	Date fstart, fend, tdate;
	City fcity[N];//to optimize, create another VLA class
	int vn = 0;//the number of cities that user entered
	bool isCity = 0;//is entry has right city
	bool isTime = 0;
	bool isAllC = 0;
	cout << "Please enter the timescale you want to load. Entering beginning first, then ending." << endl;
	fstart.input();
	fend.input();
	cout << "Please enter cities you want to load. Multiple cities are supported. Type \"0\" to finish.\nType 1 to load all cities." << endl;
	for (int i = 0;; i++) {
		getline(cin, fcity[i].cname);//why fcity[0].cname cant be entered
		if (fcity[i].cname == "0")
		{
			fcity[i].cname = "";
			break;
		}
		if (fcity[i].cname == "1")
		{
			fcity[i].cname = "";
			isAllC = 1;
			break;
		}
		vn++;
	}
	cout << "Now loading..." << endl;
	string tcno, tcname, tpro, tyear, tmonth, tday, taqi, tlv, tPM25, tPM10, tSO2, tNO2, tCO, tO3, trash;
	for (int i = 0; i < 2; i++) {
		getline(datasrc, trash);
	}
	while (getline(datasrc, tcno, ',')) {
		getline(datasrc, tcname, ',');
		getline(datasrc, tpro, ',');
		getline(datasrc, tyear, '/');
		getline(datasrc, tmonth, '/');
		getline(datasrc, tday, ',');
		getline(datasrc, taqi, ',');
		getline(datasrc, tlv, ',');
		getline(datasrc, tPM25, ',');
		getline(datasrc, tPM10, ',');
		getline(datasrc, tSO2, ',');
		getline(datasrc, tNO2, ',');
		getline(datasrc, tCO, ',');
		getline(datasrc, tO3);
		for (int i = 0; i < vn; i++) {
			if (isAllC|| (tcname == fcity[i].cname)) {
				isCity = 1;
				break;
			}
		}

		tdate.modify(tyear, tmonth, tday);
		if ((tdate.YMD <= fend.YMD) && (tdate.YMD >= fstart.YMD)) {
			isTime = 1;
		}
		if (isCity && isTime) {
			fdata.modify(tcno, tcname, tpro, tdate, taqi, tlv, tPM25, tPM10, tSO2, tNO2, tCO, tO3, infon);
			infon++;
		}
		isCity = 0;
		isTime = 0;
		//to optimize, use dynamic array to decrease memory used.
	}
	cout << split << endl << "Load complete!" << endl << split << endl;
}

//###
void Search(Loadr& fdata)
{
	Date tempd;
	City tempc;
	bool isFound = 0;
	cout << "Please enter the date you want to search." << endl;
	tempd.input(); //###input means input data
	cout << "Please enter the city you want to search." << endl;
	tempc.input();
	//a function to trans cname+cpro to cno should be added(but later feiqi
	cout << "Now loading..." << endl;
	for (int i = 0; i < infon; i++)
	{
		if (tempd.YMD == fdata.ptar[i].mdate.YMD) //###mdate mcity mairqlt are member names
			if (tempc.cname == fdata.ptar[i].mcity.cname)
			{
				isFound = 1;
				cout << endl << split << endl << "Result Found!" << endl;
				fdata.ptar[i].mcity.show();
				fdata.ptar[i].mdate.show();
				fdata.ptar[i].mairqlt.show();
				cout << endl << split << endl;
			}
	}
	if (!isFound)
	{
		cout << "Not found! Please enter valid range." << endl;
	}
	cout << "Going back to Main menu..." << endl;
}

void StatCT(Loadr& fdata)
{
	int vn = 0;
	City tempc;
	int tempy;
	int sum[15] = { 0 };
	int num[15] = { 0 };
	cout << "Please enter the city you want to find" << endl;
	tempc.input();
	cout << "Please enter the year want to find." << endl;
	cin >> tempy;
	cout << "Finding the best month..." << endl;
	//calculating aqi of every month
	for (int j = 1; j <= 12; j++)
	{
		for (int i = 0; i < infon; i++)
		{
			if (tempc.cname == fdata.ptar[i].mcity.cname)
			{
				if (tempy == fdata.ptar[i].mdate.year)
				{
					if (j == fdata.ptar[i].mdate.month)
					{
						sum[j] += fdata.ptar[i].mairqlt.aqi;
						num[j] += 1;
					}
				}
			}
		}
	}//finding minimum month
	for (int i = 0; i < 15; i++) {
		if (!sum[i]) { sum[i] = MAX_VALUE; }
		if (!num[i]) { num[i] = 1; }
		sum[i] /= num[i];// should calc average aqi to avoid the lack of data
	}
	int minM = 12;
	int minaqi = sum[12];
	for (int i = 1; i <= 12; i++)
	{
		if (sum[i] < minaqi) {
			minaqi = sum[i];
			minM = i;
		}
	}
	cout << "Arranging best 10 days..." << endl;
	//create info
	for (int i = 0; i < infon; i++)
	{
		if (tempc.cname == fdata.ptar[i].mcity.cname)
		{
			if (tempy == fdata.ptar[i].mdate.year)
			{
				if (minM == fdata.ptar[i].mdate.month)
				{
					vn++;
				}
			}
		}
	}
	Loadr ftemp(vn);
	vn = 0;
	for (int i = 0; i < infon; i++)
	{
		if (tempc.cname == fdata.ptar[i].mcity.cname)
		{
			if (tempy == fdata.ptar[i].mdate.year)
			{
				if (minM == fdata.ptar[i].mdate.month)
				{
					ftemp.ptar[vn] = fdata.ptar[i];
					vn++;
				}
			}
		}
	}
	//arrange
	if (!vn) { cout << "Not found! Please enter valid entries again." << endl; }
	else {
		for (int i = 0; i < vn; i++) {
			for (int j = 0; j < vn - i - 1; j++) {
				if (ftemp.ptar[j].mairqlt.aqi > ftemp.ptar[j + 1].mairqlt.aqi) {
					ftemp.ptar[j].swap(ftemp.ptar[j + 1]);
				}
			}
		}
		cout << "Result Found!" << endl << split << endl;
		tempc.show();
		cout << "the best month in " << tempy << " is " << minM << "." << endl;
		cout << "The best ten days are: " << endl;
		for (int i = 0; i < 10; i++) {
			ftemp.ptar[i].mdate.showC();
			ftemp.ptar[i].mairqlt.showS();
			cout << endl;
		}
	}
	cout << split << endl << "Going back to Main menu..." << endl;
}
void Find(Loadr& fdata) {
	Date fstart, fend;
	int ctype = 1;
	bool isFound = 0;//没在现成的已加载数组里面找到给的数据里面的城市，就新增一个数组成员，命名城市等。
	struct Citypro {
		int caqi = 0;
		string cname;
		string cpro;
		int validn = 0;//valid entries
	};//City properties
	cout << "Please enter the timescale you want to load. Entering beginning first, then ending." << endl;
	fstart.input();
	fend.input();
	Citypro loadc[N];
	cout << "Counting cities..." << endl;
	loadc[0].cname = fdata.ptar[0].mcity.cname;
	loadc[0].cpro = fdata.ptar[0].mcity.pro;
	for (int i = 0; i < infon; i++) {
		for (int j = 0; j < ctype; j++) {
			if (loadc[j].cname == fdata.ptar[i].mcity.cname) {
				isFound = 1;
			}
		}
		if (!isFound) {
			loadc[ctype].cname = fdata.ptar[i].mcity.cname;
			loadc[ctype].cpro = fdata.ptar[i].mcity.pro;
			ctype++;
		}
		isFound = 0;
	}
	cout << "Loading entries..." << endl;
	for (int i = 0; i < infon; i++) {
		for (int j = 0; j < ctype; j++) {
			if (loadc[j].cname == fdata.ptar[i].mcity.cname) {
				loadc[j].caqi += fdata.ptar[i].mairqlt.aqi;
				loadc[j].validn++;
			}
		}
	}
	cout << "Calculating the best city..." << endl;
	for (int j = 0; j < ctype; j++) {
		loadc[j].caqi /= loadc[j].validn;
	}
	int mincity = 1;
	int minaqi = 114514;
	for (int j = 0; j < ctype; j++) {
		if (loadc[j].caqi <= minaqi) {
			mincity = j;
			minaqi = loadc[j].caqi;
		}
	}
	cout << "Result Found!" << endl << split << endl;
	cout << "The best city in the timescale is " << loadc[mincity].cname << "," << loadc[mincity].cpro<<"." << endl;
	cout << "It's Average aqi is " << loadc[mincity].caqi << "." << endl << split << endl;
	cout << "Going back to Main menu..." << endl;
}

void StatPol(Loadr& fdata) {
	struct pollution {
		string pname;
		int pvalue = 0;
	};
	struct tmonth {
		int year;
		int month;
	} fmonth;
	string fcname;
	int validn = 0;
	pollution airp[6];
	airp[0].pname = "PM25";
	airp[1].pname = "PM10";
	airp[2].pname = "SO2";
	airp[3].pname = "NO2";
	airp[4].pname = "CO";
	airp[5].pname = "O3";
	cout << "Please enter the timescale you want to analyse.\nThe format is (Year) (Month)." << endl;
	cin >> fmonth.year >> fmonth.month;
	cout << "Please enter the city you want to analyse.The format is (City name)." << endl;
	cin >> fcname;
	cout << "Loading enties..." << endl;
	for (int i = 0; i < infon; i++) {
		if (fdata.ptar[i].mcity.cname == fcname) {
			if (fdata.ptar[i].mdate.year == fmonth.year) {
				if (fdata.ptar[i].mdate.month == fmonth.month) {
					airp[0].pvalue += fdata.ptar[i].mairqlt.PM25;
					airp[1].pvalue += fdata.ptar[i].mairqlt.PM10;
					airp[2].pvalue += fdata.ptar[i].mairqlt.SO2;
					airp[3].pvalue += fdata.ptar[i].mairqlt.NO2;
					airp[4].pvalue += fdata.ptar[i].mairqlt.CO;
					airp[5].pvalue += fdata.ptar[i].mairqlt.O3;//to optimize, use array in class airqlt.
					validn++;
				}
			}
		}
	}
	if (!validn) { cout << "Not Found! Please enter valid entries again." << endl; }
	else {
		cout << "Calculating main pollution..." << endl;
		for (int i = 0; i < 6; i++) {
			airp[i].pvalue /= validn;
		}
		int maxp = 0;
		int maxpv = airp[0].pvalue;
		for (int i = 0; i < 6; i++) {
			if (airp[i].pvalue > maxpv) {
				maxp = i;
				maxpv = airp[i].pvalue;
			}
		}
		cout << "Result Found!" << endl << split << endl;
		cout << "On " << fmonth.year << '\\' << fmonth.month << ", in " << fcname << ", the main pollution is " << airp[maxp].pname << ", it's average value is " << maxpv << "." << endl << split << endl;
	}
}
// load should can be used even if loaded, but the original data should be overwritten(wont do it)
// load should provide 3 modes: only time, only city, time and city.(wont do it)
// can use double on data to make calc more good
// should consider when two number equa in min and max functions
//###
int Select() {
	cout << split << endl << "\t\tMain Menu\nPlease enter a number to select function you want to use.\n1.Search information by city and time.\n2.Show the best month of a city in a specific year.\n3.Find the best city in a specific timescale.\n4.Show statistics about airpollution by month and city.\n5.Exit.\n" << split << endl;
	cin >> Choice;
	return Choice;
}
int main()
{

	cout << split << endl;
	cout << "Welcome to city air quality information management system (v 1.00)" << endl;
	cout << "Before lauching, please load data first." << endl;
	cout << split << endl;
	//Creating VLA
	int tempn = 0;
	string buffer;
	while (getline(datacount, buffer, '\n')) { tempn++; }
	datacount.close();
	tempn -= 2;
	Loadr fdata(tempn);
	//VLA created
	Load(fdata);
	do
	{
		switch (Select())
		{
		case 1:
			Search(fdata);
			break;
		case 2:
			StatCT(fdata);
			break;
		case 3:Find(fdata); break;
		case 4:StatPol(fdata); break;
			//case 0:Load(); break;
		case 5:
		{
			cout << "Successfully closed!\nHave a nice day!";
			return 0;
			break;
		}

		default:
		{
			cout << "Invalid number! Please input again." << endl;
		}
		}
	} while (1);
}