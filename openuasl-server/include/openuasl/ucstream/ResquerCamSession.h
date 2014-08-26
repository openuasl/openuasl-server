#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_UCSTREAM_RESQUER_CAM_SESSION_H__
#define __OPENUASL_SERVER_UCSTREAM_RESQUER_CAM_SESSION_H__

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <openuasl/skeleton/BaseResquerSession.h>

namespace openuasl{
namespace server{
namespace ucstream{

	class UavCamSession;
	
	class ResquerCamSession : public skeleton::BaseResquerSession{
	public:
		ResquerCamSession(std::string& id, SecureSocket& sock, size_t buf_size);
		virtual ~ResquerCamSession();
				
	protected:
		
		virtual void RepStart(const boost::system::error_code& error);
		virtual void ReqEnd(const boost::system::error_code& error, size_t bytes_transferred);
		virtual void RepEnd(const boost::system::error_code& error);

		friend class UavCamSession;
	};

}}} // openuasl.server.ucstream

#endif // __OPENUASL_SERVER_UCSTREAM_RESQUER_CAM_SESSION_H__