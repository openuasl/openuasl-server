#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SKELETON_BASE_SESSION_H__
#define __OPENUASL_SERVER_SKELETON_BASE_SESSION_H__

#include <openuasl/skeleton/TypeDefs.h>

namespace openuasl{
namespace server{
namespace skeleton{
		
	class BaseSession{
	public:
		std::string _SessionId;
		SecureSocket& _Socket;

	public:
		BaseSession(std::string& id, SecureSocket& sock, size_t buf_size);
		virtual ~BaseSession();
		
		virtual void Start() = 0;
		
	protected:
		size_t _BufferSize;
		char* _Buffer;
				
	};

}}} // openuasl.server.skeleton


#endif // __OPENUASL_SERVER_SKELETON_BASE_SESSION_H__
