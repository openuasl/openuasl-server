#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SKELETON_NETWORK_LOGGER_H__
#define __OPENUASL_SERVER_SKELETON_NETWORK_LOGGER_H__

#include <openuasl/skeleton/TypeDefs.h>

typedef boost::shared_mutex \
	SharedMutex;
typedef boost::filesystem::path \
	FilePath;

namespace openuasl{
namespace server{
namespace skeleton{
	
	class NetworkLogger{
	public:
		NetworkLogger(std::string& dir);
		~NetworkLogger();

		void ConnectedEvent(std::string& ip);
		void DisconnectedEvent(std::string& ip);

		void ReadBufferEvent(std::string& ip, char* buffer, size_t read_size);
		void WriteBufferEvent(std::string& ip, char* buffer, size_t write_size);

	protected:
		static std::string e_Connect;
		static std::string e_Disconnect;
		static std::string e_ReadBuffer;
		static std::string e_WriteBuffer;

		static std::string m_Connect;
		static std::string m_Disconnect;
		
	protected:
		virtual void WriteLogEvent(
			std::string& e, std::string& ip, std::string& m);
		
		virtual std::string ProcessLogString(std::string& time, 
			std::string& e, std::string& ip, std::string& m);

	private:
		FilePath _DirectoryName;
		SharedMutex _SharedMutex;
	};

}}} // openuasl.server.skeleton


#endif // __OPENUASL_SERVER_SKELETON_NETWORK_LOGGER_H__
