#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SKELETON_BASE_RESQUER_SESSION_H__
#define __OPENUASL_SERVER_SKELETON_BASE_RESQUER_SESSION_H__

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <openuasl/skeleton/BaseSession.h>

namespace openuasl{
namespace server{
namespace skeleton{

	class BaseUavSession;
	
	class BaseResquerSession : public skeleton::BaseSession{
	public:
		BaseResquerSession(std::string& id, SecureSocket& sock, size_t buf_size);
		virtual ~BaseResquerSession();
		void SetDeviceId(char* buffer);
		void SetUavSession(BaseUavSession* uav);

		virtual void Start();
		
	protected:
		BaseUavSession* _Uav;

		void RepReady(const boost::system::error_code& error);
		void ReqReady(const boost::system::error_code& error, size_t bytes_transferred);
		
		void RepMismatch(const boost::system::error_code& error);

		// uav 로부터 start 신호가 들어오면 호출됨
		virtual void RepStart(const boost::system::error_code& error);
		
		friend class BaseUavSession;
	};

}}} // openuasl.server.skeleton

#endif // __OPENUASL_SERVER_SKELETON_BASE_RESQUER_SESSION_H__