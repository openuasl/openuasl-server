#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_UCSTREAM_UAV_SESSION_H__
#define __OPENUASL_SERVER_UCSTREAM_UAV_SESSION_H__

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <openuasl/skeleton/BaseSession.h>

namespace openuasl{
namespace server{
namespace ucstream{
	
	class ResquerSession;

	class UavSession : public skeleton::BaseSession{
	public:
		UavSession(std::string& id, SecureSocket& sock, size_t buf_size);
		virtual ~UavSession();
		void SetSerialId(char* buffer);
		void SetResquerSesion(ResquerSession* resq);

		virtual void Start();
		
		void RepReady(const boost::system::error_code& error);
		void ReqStart(const boost::system::error_code& error, size_t bytes_transferred);
		void ReadStramming(const boost::system::error_code& error, size_t bytes_transferred);
		void WriteStreamming(const boost::system::error_code& error);

	private:
		ResquerSession* _Resq;

		friend class ResquerSession;
	};

}}} // openuasl.server.ucstream

#endif // __OPENUASL_SERVER_UCSTREAM_UAV_SESSION_H__