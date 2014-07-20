#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_UCSTREAM_UAV_SESSION_H__
#define __OPENUASL_SERVER_UCSTREAM_UAV_SESSION_H__

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <openuasl/server_conf.h>

namespace openuasl{
namespace server{
namespace ucstream{
	
	class resquer_session;

	class uav_session{
	private:
		boost::asio::ip::tcp::socket* _socket;
		char _buffer[NETWORK_BUF_SIZE];
		resquer_session* _resq;

	public:
		std::string _serial_id;

		uav_session(boost::asio::ip::tcp::socket* sock);
		boost::asio::ip::tcp::socket* socket();
		void set_serial(char* buffer);
		void set_resquer_session(resquer_session* resq);
		void start_streamming();
		
		void handle_rep_ready(const boost::system::error_code& error);
		void handle_req_start(const boost::system::error_code& error, size_t bytes_transferred);
		void handle_read_streamming(
			const boost::system::error_code& error, size_t bytes_transferred);

		friend class resq_session;
	};

}}} // openuasl.server.ucstream

#endif // __OPENUASL_SERVER_UCSTREAM_UAV_SESSION_H__