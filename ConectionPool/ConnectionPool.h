#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include "MysqlConn.h"
using namespace std;

class ConnectionPool  //������
{
public:
	static ConnectionPool* getConnectPool();
	ConnectionPool(const ConnectionPool& obj) = delete;
	ConnectionPool& operator=(const ConnectionPool& obj) = delete;
	shared_ptr<MysqlConn> getConnection();
	~ConnectionPool();
private:

	//ʵ������Ҫ�������һ�������캯��Ӧ����Ϊ˽��
	ConnectionPool();
	bool parseJsonFile();	//����json����
	void produceConnection();
	void recycleConnection();
	void addConnection();

	string m_ip;	//������ip��ַ
	string m_user;	//�������û���
	string m_passwd;	//����������
	string m_dbName;	//��������Ӧ���ݿ�����
	unsigned short m_port;	//��������Ӧ���ʶ˿�
	int m_minSize;	//���ӳ���С�߳���
	int m_maxSize;
	int m_timeout;
	int m_maxIdleTime;
	queue<MysqlConn*> m_connectionQ;
	mutex m_mutexQ;
	condition_variable m_cond;
};

