#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SKELETON_BASE_UAV_SESSION_H__
#define __OPENUASL_SERVER_SKELETON_BASE_UAV_SESSION_H__

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <openuasl/skeleton/BaseSession.h>

namespace openuasl{
namespace server{
namespace skeleton{
	
	class BaseResquerSession;

	class BaseUavSession : public skeleton::BaseSession{
	public:
		BaseUavSession(std::string& id, SecureSocket& sock, size_t buf_size);
		virtual ~BaseUavSession();
		void SetSerialId(char* buffer);
		void SetResquerSesion(BaseResquerSession* resq);

		// uav certificate 다 한 다음 호출됨
		virtual void Start();
		
		void RepReady(const boost::system::error_code& error);
		void ReqStart(const boost::system::error_code& error, size_t bytes_transferred);

	protected:
		BaseResquerSession* _Resq;

		friend class BaseResquerSession;
	};

}}} // openuasl.server.skeleton

#endif // __OPENUASL_SERVER_SKELETON_BASE_UAV_SESSION_H__