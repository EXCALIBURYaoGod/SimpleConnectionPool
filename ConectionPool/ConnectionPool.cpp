#include "ConnectionPool.h"
#include <json/json.h>
#include <fstream>
using namespace Json;

ConnectionPool* ConnectionPool::getConnectPool()
{	
	static ConnectionPool pool;
	return &pool;
}

bool ConnectionPool::parseJsonFile()
{
	ifstream ifs("dbconf.json");
	Reader rd;
	Value root;
	rd.parse(ifs, root);
	if (root.isObject())
	{
		m_ip = root["ip"].asString();
		m_port = root["port"].asInt();
		m_user = root["userName"].asString();
		m_passwd = root["password"].asString();
		m_dbName = root["dbName"].asString();
		m_minSize = root["minSize"].asInt();
		m_maxSize = root["maxSize"].asInt();
		m_maxIdleTime = root["maxIdleTime"].asInt();
		m_timeout = root["timeout"].asInt();
		return true;
	}

	return false;
}
