#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_MAIN_SERVER_H__
#define __OPENUASL_SERVER_MAIN_SERVER_H__

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <openuasl/server_conf.h>
#include <openuasl/skeleton/SessionManager.h>
#include <openuasl/session_app.h>
#include <openuasl/skeleton/SecureBaseServer.h>

namespace openuasl{
	namespace server{
		class main_server : public skeleton::SecureBaseServer{


		private:
			skeleton::SessionManager _ResqSmgr;
			skeleton::SessionManager _UavSmgr;
			char _Buffer[NETWORK_BUF_SIZE];

		protected:
			virtual std::string SetCertPassword() const;

			virtual void ProcessRead(SecureSocket* nsock,
				const boost::system::error_code& error);


			// for device certificate
			virtual void HandleMakeSession(SecureSocket* nsock, 
				const boost::system::error_code& error, size_t bytes_transferred);
			virtual void HandleResqReqQRCode(session_app* resq,
				const boost::system::error_code& error, size_t bytes_transferred);

		public:
			main_server(unsigned short port);

		};

	}
} // openuasl.server


#endif // __OPENUASL_SERVER_MAIN_SERVER_H__
