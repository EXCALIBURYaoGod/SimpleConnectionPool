#include <iostream>
#include <memory>
#include "MysqlConn.h"
#include "ConnectionPool.h"
using namespace std;


//1.非连接池模式建立数据库连接
void op1(int begin, int end)
{
	for (int i = begin; i < end; i++)
	{
		MysqlConn conn;
		conn.connect("root", "yaogod990710", "test", "localhost");
		char sql[1024] = { 0 };
		sprintf(sql, R"(CREATE TABLE u%dsers(
		id INT AUTO_INCREMENT PRIMARY KEY, 
		username VARCHAR(50) NOT NULL, 
		email VARCHAR(100) NOT NULL, 
		birthdate DATE,
		is_active BOOLEAN DEFAULT TRUE))", i);
		conn.update(sql);
	}
}

//2.连接池模式建立数据库连接
void opmultiConnect(ConnectionPool* pool, int begin, int end)
{
	for (int i = begin; i < end; i++)
	{
		shared_ptr<MysqlConn> conn = pool->getConnection();
		char sql[1024] = { 0 };
		sprintf(sql, R"(CREATE TABLE u%dsers(
		id INT AUTO_INCREMENT PRIMARY KEY, 
		username VARCHAR(50) NOT NULL, 
		email VARCHAR(100) NOT NULL, 
		birthdate DATE,
		is_active BOOLEAN DEFAULT TRUE))", i);
		conn->update(sql);
	}
}

void testTime()
{
#if 0
	steady_clock::time_point begin = steady_clock::now();
	op1(0, 50);
	steady_clock::time_point end = steady_clock::now();
	auto op1Time = end - begin;
	cout << "单线程用时：" << op1Time.count() << "纳秒";
#else
	ConnectionPool* pool = ConnectionPool::getConnectPool();
	steady_clock::time_point begin = steady_clock::now();
	opmultiConnect(pool, 0, 50);
	steady_clock::time_point end = steady_clock::now();
	auto op2Time = end - begin;
	cout << "单线程用时：" << op2Time.count() << "纳秒";
#endif
}
int main()
{	
	testTime();
	return 0;
}