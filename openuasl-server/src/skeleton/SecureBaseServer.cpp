#ifdef _WIN32
#define _WIN32_WINNT 0x0501
#endif // _WIN32

#include <openuasl/skeleton/SecureBaseServer.h>

namespace openuasl{
namespace server{
namespace skeleton{
	
// public
	SecureBaseServer::SecureBaseServer(unsigned short port)
		: _Acceptor(_IOService, 
			boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
		_SslContext(_IOService, boost::asio::ssl::context::sslv23),
		_IsSetSslContext(false){

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
	
	bool SecureBaseServer::Run()
	{
		if(_IsSetSslContext)
		{
			SecureSocket* nsock = new SecureSocket(_IOService, _SslContext);
			_Acceptor.async_accept(nsock->lowest_layer(),
				boost::bind(&SecureBaseServer::HandleAccept, this, nsock,
				boost::asio::placeholders::error));

			_IOService.run();

			return true;
		}

		return false;
	}

// protected
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

	void SecureBaseServer::HandleAccept(SecureSocket* nsock,
		const boost::system::error_code& error)
	{
		if(!error)
		{
			nsock->async_handshake(boost::asio::ssl::stream_base::server,
				boost::bind(&SecureBaseServer::HandleHandshake, this, 
				nsock, boost::asio::placeholders::error));
			
			nsock = new SecureSocket(_IOService, _SslContext);
			_Acceptor.async_accept(nsock->lowest_layer(),
				boost::bind(&SecureBaseServer::HandleAccept, this, nsock,
				boost::asio::placeholders::error));

		}else
		{
			delete nsock;

			SecureSocket* nsock = new SecureSocket(_IOService, _SslContext);
			_Acceptor.async_accept(nsock->lowest_layer(),
				boost::bind(&SecureBaseServer::HandleAccept, this, nsock,
				boost::asio::placeholders::error));
		}
	}
	
	void SecureBaseServer::HandleHandshake(SecureSocket* nsock,
		const boost::system::error_code& error){
			if(!error)
			{
				SecureBaseServer::ProcessRead(nsock, error);

			}else
			{
				delete nsock;
			}
	}



}}} // openuasl.server.skeleton
