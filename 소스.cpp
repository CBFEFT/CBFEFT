#include <mysql.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#pragma comment(lib,"libmysql.lib")

using namespace std;

int main() {
	vector<string> temp;
	string in_line;
	string temp1="insert into test values(\"";
	string temp2 = "\")";

	//cout << "mysql client version:" << mysql_get_client_info() << endl; //version = 8.0.17로 사용하엿음

	int query_stat;
	
	MYSQL* connection = NULL , conn;
	MYSQL_RES* sql_result;
	//MYSQL_ROW sql_row;
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, NULL/*host ip 주소 */, "root", "ww0603", "weather"/*db이름*/, 3306, NULL, 0); //data연동 여부



	if (connection==NULL)
		cout << "error" << endl;
	else
		cout << "success" << endl;
	
	query_stat = mysql_query(connection, "select * from test");  //query 보내기
	sql_result = mysql_store_result(connection);

	ifstream in("날씨지문.txt");
	while (getline(in, in_line)) {
		//cout << temp1+in_line+temp2 << endl;
		string temp = temp1 + in_line + temp2;
		const char* c = temp.c_str();
		mysql_query(connection, c); //query insert 날리기
	}
	in.close();
	/*
	mysql_query(connection, "insert into test values(\"Due to inclement weather conditions and for the safety of our staff, we have elected to close our office.\")");

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) { //data확인 부분
		cout << sql_row[0] << endl;
	}*/

	mysql_close(connection);

	return 0;
}