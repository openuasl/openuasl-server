#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_UCSTREAM_UCSTREAM_SERVER_H__
#define __OPENUASL_SERVER_UCSTREAM_UCSTREAM_SERVER_H__

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <openuasl/skeleton/SecureBaseServer.h>

#include <openuasl/server_conf.h>
#include <openuasl/skeleton/SessionManager.h>
#include <openuasl/ucstream/ResquerSession.h>

namespace openuasl{
namespace server{
namespace ucstream{

class UCStreamServer : public skeleton::SecureBaseServer{
public:
	UCStreamServer(unsigned short port);
	
protected:
// base server's pure virtual methods
	virtual std::string SetCertPassword() const;

	virtual void ProcessRead(SecureSocket* nsock,
			const boost::system::error_code& error);

// for device certificate
	virtual void HandleMakeSession(SecureSocket* nsock, 
			const boost::system::error_code& error, size_t bytes_transferred);
	virtual void HandleResqReqQRCode(ResquerSession* resq,
		const boost::system::error_code& error, size_t bytes_transferred);

private:
	skeleton::SessionManager _ResqSmgr;
	skeleton::SessionManager _UavSmgr;
	char _Buffer[NETWORK_BUF_SIZE];
};

}}} // openuasl.server.ucstream


#endif // __OPENUASL_SERVER_UCSTREAM_UCSTREAM_SERVER_H__
