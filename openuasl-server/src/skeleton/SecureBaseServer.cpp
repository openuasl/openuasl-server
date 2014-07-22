#ifdef _WIN32
#define _WIN32_WINNT 0x0501
#endif // _WIN32

#include <openuasl/skeleton/SecureBaseServer.h>

namespace openuasl{
namespace server{
namespace skeleton{
	
	SecureBaseServer::SecureBaseServer(unsigned short port, int buf_len)
		: _Acceptor(_IOService, 
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
		_SslContext(_IOService, boost::asio::ssl::context::sslv23),
		_BufferLength(buf_len), 
		_IsSetSslContext(false),
		_IsSetLogManager(false)
	{
		_SslContext.set_options(
			
			boost::asio::ssl::context::default_workarounds
			| boost::asio::ssl::context::no_sslv2
			| boost::asio::ssl::context::single_dh_use);
		_SslContext.set_password_callback(
			boost::bind(&SecureBaseServer::SetCertPassword, this));
	}

	SecureBaseServer::~SecureBaseServer()
	{

	}

	void SecureBaseServer::HandleAccept(LogableSession* new_session,
		const boost::system::error_code& error)
	{
		if(!error)
		{
			new_session->_SessionManager = &this->_SessionManager;
			new_session->_LogManager = this->_LogManager;

			InitAcceptedSession(new_session);

			new_session->Start();

			new_session = AllocSession();
			_Acceptor.async_accept(new_session->_Socket.lowest_layer(),
			boost::bind(&SecureBaseServer::HandleAccept, this, new_session,
			boost::asio::placeholders::error));

		}else
		{
			delete new_session;
		}
	}
	
	bool SecureBaseServer::Run()
	{
		if(_IsSetSslContext && _IsSetLogManager)
		{
			LogableSession* new_session = AllocSession();
			_Acceptor.async_accept(new_session->_Socket.lowest_layer(),
			boost::bind(&SecureBaseServer::HandleAccept, this, new_session,
			boost::asio::placeholders::error));

			_IOService.run();

			return true;
		}

		return false;
	}

	void SecureBaseServer::SetSslContext(
		std::string cert_path,
		std::string pri_key_path, std::string dh_path)
	{
		_SslContext.use_certificate_chain_file(cert_path);
		_SslContext.use_private_key_file(pri_key_path, 
			boost::asio::ssl::context::pem);
		_SslContext.use_tmp_dh_file(dh_path);

		_IsSetSslContext = true;
	}
	
	void SecureBaseServer::SetLogManager(NetworkLogger* logmgr)
	{
		this->_LogManager = logmgr;

		_IsSetLogManager = true;
	}


}}} // openuasl.server.skeleton
