#include <openuasl/skeleton/NetworkLogger.h>
#include <openuasl/skeleton/TypeDefs.h>

#include <boost/filesystem/fstream.hpp>
#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/format.hpp>

typedef boost::unique_lock<boost::shared_mutex> \
	UniqueLock;

namespace openuasl{
namespace server{
namespace skeleton{
	
	std::string NetworkLogger::e_Connect("connect");
	std::string NetworkLogger::e_Disconnect("disconnect");
	std::string NetworkLogger::e_ReadBuffer("readbuf");
	std::string NetworkLogger::e_WriteBuffer("writebuf");

	std::string NetworkLogger::m_Connect("remote client connected");
	std::string NetworkLogger::m_Disconnect("remote client disconnected");

	NetworkLogger::NetworkLogger(std::string& dir)
		: _DirectoryName(dir)	
	{}

	NetworkLogger::~NetworkLogger(){}

	void NetworkLogger::ConnectedEvent(std::string& ip)
	{
		WriteLogEvent(e_Connect, ip, m_Connect);
	}

	void NetworkLogger::DisconnectedEvent(std::string& ip)
	{
		WriteLogEvent(e_Disconnect, ip, m_Disconnect);
	}

	void NetworkLogger::ReadBufferEvent(std::string& ip, char* buffer, size_t read_size)
	{
		std::string hex;

		for (int i = 0; i < read_size; ++i)
		{
			char hexcode[3] = { 0, };
			sprintf_s(hexcode, "%02x", buffer[i] & 0xFF);
 
			hex += hexcode;
		}

		WriteLogEvent(e_ReadBuffer, ip, hex);
	}
	
	void NetworkLogger::WriteBufferEvent(std::string& ip, char* buffer, size_t write_size)
	{

	}

	
	void NetworkLogger::WriteLogEvent(std::string& e, std::string& ip, std::string& m)
	{
		std::string time_string, file_name;
 
		boost::posix_time::ptime now =
			boost::posix_time::second_clock::local_time();
		
		struct tm T = boost::posix_time::to_tm(now);
 
		file_name = boost::str(boost::format("%1$04d%2%%3$02d%2%%4$02d") 
			%(T.tm_year + 1900) %"." %(T.tm_mon + 1) %T.tm_mday);

		time_string = boost::str(boost::format("%1$02d%2%%3$02d%2%%4$02d")
			%T.tm_hour %":" %T.tm_min %T.tm_sec );
		
		boost::filesystem::path fname(file_name+".log");

		UniqueLock lock(_SharedMutex);

		boost::filesystem::ofstream ofs(_DirectoryName/fname, std::ios_base::app);
		ofs << ProcessLogString(time_string, e, ip, m) << std::endl;
		ofs.close();

		lock.unlock();
		
	}

	std::string NetworkLogger::ProcessLogString(std::string& time, 
			std::string& e, std::string& ip, std::string& m)
	{
		return std::string(time+"/"+e+"/"+ip+"/"+m);
	}


}}} // openuasl.server.skeleton