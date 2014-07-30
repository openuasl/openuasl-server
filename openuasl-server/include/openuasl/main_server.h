#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_MAIN_SERVER_H__
#define __OPENUASL_SERVER_MAIN_SERVER_H__

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <openuasl/skeleton/SecureBaseServer.h>

namespace openuasl{
	namespace server{
		class main_server : public skeleton::SecureBaseServer{

		private:
			skeleton::SessionManager _ResqSmgr;
			skeleton::SessionManager _UavSmgr;
			char _Buffer[NETWORK_BUF_SIZE];

		protected:
			virtual std::string 
		public:
			main_server(boost::asio::io_service& io_service, short port);
			void start();
			void handle_handshake(ssl_socket * sock,const boost::system::error_code& error);
			void handle_accept(ssl_socket * sock,
				const boost::system::error_code& error);

			std::string get_password() const;

		};

	}
} // openuasl.server


#endif // __OPENUASL_SERVER_MAIN_SERVER_H__
