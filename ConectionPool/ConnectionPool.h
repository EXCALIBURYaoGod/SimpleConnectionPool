#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include "MysqlConn.h"
using namespace std;

class ConnectionPool  //单例类
{
public:
	static ConnectionPool* getConnectPool();
	ConnectionPool(const ConnectionPool& obj) = delete;
	ConnectionPool& operator=(const ConnectionPool& obj) = delete;
	shared_ptr<MysqlConn> getConnection();
	~ConnectionPool();
private:

	//实例对象要求仅创建一个，构造函数应设置为私有
	ConnectionPool();
	bool parseJsonFile();	//解析json数据
	void produceConnection();
	void recycleConnection();
	void addConnection();

	string m_ip;	//服务器ip地址
	string m_user;	//服务器用户名
	string m_passwd;	//服务器密码
	string m_dbName;	//服务器对应数据库名字
	unsigned short m_port;	//服务器对应访问端口
	int m_minSize;	//连接池最小线程数
	int m_maxSize;
	int m_timeout;
	int m_maxIdleTime;
	queue<MysqlConn*> m_connectionQ;
	mutex m_mutexQ;
	condition_variable m_cond;
};

