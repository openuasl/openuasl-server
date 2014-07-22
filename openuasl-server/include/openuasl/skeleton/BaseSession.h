#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SKELETON_BASE_SESSION_H__
#define __OPENUASL_SERVER_SKELETON_BASE_SESSION_H__

#include <openuasl/skeleton/TypeDefs.h>

namespace openuasl{
namespace server{
namespace skeleton{

	template <typename ID = std::string>
	class BaseSession
	{
	public:
		ID _SessionId;
		SecureSocket _Socket;

	public:
		BaseSession(size_t buf_size, 
			IOService& io_service, SslContext& context);
		virtual ~BaseSession();
		
		virtual void Start();
		void HandleHandshake(const boost::system::error_code& error);
		void HandleRead(const boost::system::error_code& error, size_t bytes_transferred);
		void AsyncRead();
		void HandleWrite(const boost::system::error_code& error);
		void AsyncWrite(size_t buf_len);
		
	protected:
		virtual void ProcessReadBuffer(size_t read_size) = 0;
		// return : response buffer size (unit : byte)
		virtual size_t RegisterResponseBuffer() = 0;
		virtual void PrepareRead() = 0;
		virtual void ErrorHandling(const boost::system::error_code& error) = 0;
		
	protected:
		volatile size_t _WritedSize;
		volatile size_t _ReadedSize;
		size_t _BufferSize;
		char* _Buffer;
				
	};

}}} // openuasl.server.skeleton


#endif // __OPENUASL_SERVER_SKELETON_BASE_SESSION_H__
