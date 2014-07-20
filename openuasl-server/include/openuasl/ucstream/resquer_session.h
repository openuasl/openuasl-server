#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_UCSTREAM_RESQUER_SESSION_H__
#define __OPENUASL_SERVER_UCSTREAM_RESQUER_SESSION_H__

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <openuasl/server_conf.h>

namespace openuasl{
namespace server{
namespace ucstream{

	class uav_session;
	
	class resquer_session{
	private:
		boost::asio::ip::tcp::socket* _socket;
		char _buffer[NETWORK_BUF_SIZE];
		uav_session* _uav;
		
	public:
		std::string _device_id;

		resquer_session(boost::asio::ip::tcp::socket* sock);
		boost::asio::ip::tcp::socket* socket();
		void start();
		void set_devid(char* buffer);
		void set_uav_session(uav_session* uav);

		void handle_rep_ready(const boost::system::error_code& error);
		void handle_req_ready(const boost::system::error_code& error, size_t bytes_transferred);
		
		void handle_rep_mismatch(const boost::system::error_code& error);

		void handle_rep_start(const boost::system::error_code& error);
		
		friend class uav_session;
	};

}}} // openuasl.server.ucstream

#endif // __OPENUASL_SERVER_UCSTREAM_RESQUER_SESSION_H__