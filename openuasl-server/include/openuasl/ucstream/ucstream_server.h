#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_UCSTREAM_UCSTREAM_SERVER_H__
#define __OPENUASL_SERVER_UCSTREAM_UCSTREAM_SERVER_H__

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <openuasl/server_conf.h>
#include <openuasl/session_mgr.h>
#include <openuasl/ucstream/resquer_session.h>
#include <openuasl/ucstream/uav_session.h>

namespace openuasl{
namespace server{
namespace ucstream{

class ucstream_server
{
public:
	ucstream_server(boost::asio::io_service& io_service, short port);

	void handle_accept(boost::asio::ip::tcp::socket* sock,
		const boost::system::error_code& error);

	void handle_resq_req_qrcode(resquer_session* resq,
		const boost::system::error_code& error, size_t bytes_transferred);

	//void handle_write(const boost::system::error_code& error);

private:
	boost::asio::io_service& _io_service;
	boost::asio::ip::tcp::acceptor _acceptor;
	sessoin_mgr<resquer_session*, uav_session*> _smgr;

	char _buffer[NETWORK_BUF_SIZE];
};

}}} // openuasl.server.ucstream


#endif // __OPENUASL_SERVER_UCSTREAM_UCSTREAM_SERVER_H__
