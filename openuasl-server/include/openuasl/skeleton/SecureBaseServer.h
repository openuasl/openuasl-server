#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SKELETON_SECURE_BASE_SERVER_H__
#define __OPENUASL_SERVER_SKELETON_SECURE_BASE_SERVER_H__

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <openuasl/skeleton/TypeDefs.h>
#include <openuasl/skeleton/LogableSession.h>
#include <openuasl/skeleton/NetworkLogger.h>


namespace openuasl{
namespace server{
namespace skeleton{

	class SecureBaseServer
	{
	public:
		SessionManager<> _SessionManager;
		NetworkLogger* _LogManager;

		SecureBaseServer(unsigned short port, int buf_len);
		~SecureBaseServer();
		void HandleAccept(LogableSession* new_session,
			const boost::system::error_code& error);
		virtual bool Run();

	protected:
		IOService _IOService;
		SslContext _SslContext;

		void SetSslContext(std::string cert_path,
			std::string pri_key_path, std::string dh_path);
		void SetLogManager(NetworkLogger* logmgr);

		virtual std::string SetCertPassword() const = 0;
		virtual LogableSession* AllocSession() = 0;
		virtual void InitAcceptedSession(LogableSession* new_session) = 0;

	private:
		Acceptor _Acceptor;
		int _BufferLength;
		bool _IsSetSslContext;
		bool _IsSetLogManager;
	};

}}} // openuasl.server.skeleton


#endif // __OPENUASL_SERVER_SKELETON_SECURE_BASE_SERVER_H__
