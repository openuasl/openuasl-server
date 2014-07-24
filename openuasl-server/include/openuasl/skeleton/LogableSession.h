#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SKELETON_LOGABLE_SESSION_H__
#define __OPENUASL_SERVER_SKELETON_LOGABLE_SESSION_H__

#include <openuasl/skeleton/TypeDefs.h>

#include <openuasl/skeleton/BaseSession.h>
#include <openuasl/skeleton/SessionManager.h>
#include <openuasl/skeleton/NetworkLogger.h>

namespace openuasl{
namespace server{
namespace skeleton{

	class LogableSession : public BaseSession{
	public:
		SessionManager<>* _SessionManager;
		NetworkLogger* _LogManager;
				
	public:
		LogableSession(size_t buf_len, 
			IOService& io_service, SslContext& context);

		virtual ~LogableSession();

		virtual void Start();

		std::string GetIpAddress();
		
	protected:
		virtual void ProcessReadBuffer(size_t read_size);
		virtual size_t RegisterResponseBuffer();
		virtual void PrepareRead();
		virtual void ErrorHandling(const boost::system::error_code& error);

	};

}}} // openuasl.server.skeleton


#endif // __OPENUASL_SERVER_SKELETON_LOGABLE_SESSION_H__
