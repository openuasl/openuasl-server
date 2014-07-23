#ifdef _WIN32
#define _WIN32_WINNT 0x0501
#endif // _WIN32
#include <openuasl/skeleton/BaseSession.h>

namespace openuasl{
namespace server{
namespace skeleton{

	BaseSession::BaseSession(size_t buf_size,
		IOService& io_service, SslContext& context)
	: _Socket(io_service, context)
	{
		this->_Buffer = new char[buf_size];
		_BufferSize = buf_size;
	}

	BaseSession::~BaseSession()
	{
		delete [] this->_Buffer;
		boost::system::error_code error;
		
		_Socket.lowest_layer().shutdown(boost::asio::ip::tcp::socket::shutdown_send, error);
		_Socket.lowest_layer().close(error);
	}
	
	void BaseSession::Start()
	{
		_Socket.async_handshake(boost::asio::ssl::stream_base::server,
			boost::bind(&BaseSession::HandleHandshake, this,
			boost::asio::placeholders::error));
	}
		
	void BaseSession::HandleHandshake(const boost::system::error_code& error)
	{
		if (!error)
		{
			_Socket.async_read_some(boost::asio::buffer(_Buffer, _BufferSize),
				boost::bind(&BaseSession::HandleRead, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			ErrorHandling(error);
		}
	}

	void BaseSession::HandleRead(const boost::system::error_code& error, size_t bytes_transferred)
	{
		if (!error)
		{
			_ReadedSize = bytes_transferred;
			ProcessReadBuffer(bytes_transferred);
			_WritedSize = RegisterResponseBuffer();
			AsyncWrite(_WritedSize);
		}
		else
		{
			ErrorHandling(error);
		}
	}

	void BaseSession::AsyncRead()
	{
		_Socket.async_read_some(boost::asio::buffer(_Buffer, _BufferSize),
				boost::bind(&BaseSession::HandleRead, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
		
	void BaseSession::HandleWrite(const boost::system::error_code& error)
	{
		if (!error)
		{
			PrepareRead();
			AsyncRead();
		}
		else
		{
			ErrorHandling(error);
		}
	}
		
	void BaseSession::AsyncWrite(size_t buf_len)
	{
		boost::asio::async_write(_Socket,
				boost::asio::buffer(_Buffer, buf_len),
				boost::bind(&BaseSession::HandleWrite, this,
				boost::asio::placeholders::error));
	}
	
}}} // openuasl.server.skeleton