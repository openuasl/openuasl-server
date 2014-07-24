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

namespace openuasl{
namespace server{
namespace skeleton{

	class SecureBaseServer{
	public:
		SecureBaseServer(unsigned short port);
		virtual ~SecureBaseServer();
		
		virtual bool Run();

	protected:
		IOService _IOService;
		SslContext _SslContext;

		void SetSslContext(std::string cert_path,
			std::string pri_key_path, std::string dh_path);
		
		virtual std::string SetCertPassword() const = 0;
		
		virtual void HandleAccept(SecureSocket* nsock,
			const boost::system::error_code& error);

		virtual void HandleHandshake(SecureSocket* nsock,
			const boost::system::error_code& error);

		virtual void ProcessRead(SecureSocket* nsock,
			const boost::system::error_code& error) = 0;

	private:
		Acceptor _Acceptor;
		bool _IsSetSslContext;
	};

}}} // openuasl.server.skeleton


#endif // __OPENUASL_SERVER_SKELETON_SECURE_BASE_SERVER_H__
