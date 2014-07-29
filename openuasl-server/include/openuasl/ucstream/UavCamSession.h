#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_UCSTREAM_UAV_CAM_SESSION_H__
#define __OPENUASL_SERVER_UCSTREAM_UAV_CAM_SESSION_H__

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <openuasl/skeleton/BaseUavSession.h>

namespace openuasl{
namespace server{
namespace ucstream{
	
	class ResquerCamSession;

	class UavCamSession : public skeleton::BaseUavSession{
	public:
		UavCamSession(std::string& id, SecureSocket& sock, size_t buf_size);
		virtual ~UavCamSession();

		virtual void Start();

		void ReadStramming(const boost::system::error_code& error, size_t bytes_transferred);
		void WriteStreamming(const boost::system::error_code& error);
		
		friend class ResquerCamSession;
	};

}}} // openuasl.server.ucstream

#endif // __OPENUASL_SERVER_UCSTREAM_UAV_CAM_SESSION_H__