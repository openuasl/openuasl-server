#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SESSION_APP_H__
#define __OPENUASL_SERVER_SESSION_APP_H__

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <openuasl/server_conf.h>

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

namespace openuasl{
	namespace server{
		class session_uav;

		class session_app{


		private:
			ssl_socket socket_;
			enum { max_length = 1024 };
			char data_[max_length];
			session_uav* _uav;

		public :
			std::string _device_id;
			session_app(boost::asio::io_service& io_service, boost::asio::ssl::context& context);
			ssl_socket& socket();
			void start();
			void handle_handshake(const boost::system::error_code& error);
			void handle_read(const boost::system::error_code& error,
				size_t bytes_transferred);
			void handle_write(const boost::system::error_code& error);
			void set_devid(char* buffer);
			void set_uav_session(session_uav* uav);
			void handle_rep_ready(const boost::system::error_code& error);
			void handle_req_ready(const boost::system::error_code& error, size_t bytes_transferred);

			void handle_rep_mismatch(const boost::system::error_code& error);

			friend class session_uav;
		};


	}
}
} // openuasl.server


#endif // __OPENUASL_SERVER_SESSION_APP_H__