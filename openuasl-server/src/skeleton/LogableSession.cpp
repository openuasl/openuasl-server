#ifdef _WIN32
#define _WIN32_WINNT 0x0501
#endif // _WIN32

#include <openuasl/skeleton/LogableSession.h>

//#include <boost/algorithm/string.hpp>

namespace openuasl{
namespace server{
namespace skeleton{

	LogableSession::LogableSession(size_t buf_len, 
		IOService& io_service, SslContext& context)
		: BaseSession<>(buf_len, io_service, context)
	{
		
	}

	LogableSession::~LogableSession()
	{

	}
	
	void LogableSession::Start()
	{
		_LogManager->ConnectedEvent(GetIpAddress());

		BaseSession::Start();
	}

	std::string LogableSession::GetIpAddress()
	{
		return _Socket.lowest_layer()
			.remote_endpoint().address().to_string();
	}

	void LogableSession::ProcessReadBuffer(size_t read_size)
	{
		_LogManager->ReadBufferEvent(
			GetIpAddress(),_Buffer, read_size);
	}

	size_t LogableSession::RegisterResponseBuffer()
	{
		return 0;
	}

	void LogableSession::PrepareRead()
	{
		_LogManager->WriteBufferEvent(
			GetIpAddress(), _Buffer, _WritedSize);
	}
	
	void LogableSession::ErrorHandling(const boost::system::error_code& error)
	{
		_LogManager->DisconnectedEvent(GetIpAddress());

		delete this;
	}

	
}}} // openuasl.server.skeleton