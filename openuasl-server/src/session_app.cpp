#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <openuasl/session_app.h>
#include <openuasl/session_uav.h>

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

namespace openuasl{
	namespace server{
		session_app::session_app(std::string& id, SecureSocket& sock, size_t buf_size)
		:skeleton::BaseResquerSession(id, sock, buf_size){}

		session_app::~session_app(){}

		void session_app::

	}

}