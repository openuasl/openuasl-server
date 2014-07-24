#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_UCSTREAM_RESQUER_SESSION_H__
#define __OPENUASL_SERVER_UCSTREAM_RESQUER_SESSION_H__

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <openuasl/skeleton/BaseSession.h>

namespace openuasl{
namespace server{
namespace ucstream{

	class UavSession;
	
	class ResquerSession : public skeleton::BaseSession{
	public:
		ResquerSession(std::string& id, SecureSocket& sock, size_t buf_size);
		virtual ~ResquerSession();
		void SetDeviceId(char* buffer);
		void SetUavSession(UavSession* uav);

		virtual void Start();
		
	private:
		UavSession* _Uav;

		void RepReady(const boost::system::error_code& error);
		void ReqReady(const boost::system::error_code& error, size_t bytes_transferred);
		
		void RepMismatch(const boost::system::error_code& error);

		void RepStart(const boost::system::error_code& error);
		
		friend class UavSession;
	};

}}} // openuasl.server.ucstream

#endif // __OPENUASL_SERVER_UCSTREAM_RESQUER_SESSION_H__