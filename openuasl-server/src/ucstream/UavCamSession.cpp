#include <openuasl/ucstream/UavCamSession.h>
#include <openuasl/ucstream/ResquerCamSession.h>
#include <openuasl/server_conf.h>

namespace openuasl{
namespace server{
namespace ucstream{

	UavCamSession::UavCamSession(std::string& id, SecureSocket& sock, size_t buf_size)
		: skeleton::BaseUavSession(id, sock, buf_size){}

	UavCamSession::~UavCamSession(){}

// override
	void UavCamSession::Start(){

		_Socket.async_read_some(
			boost::asio::buffer(this->_Buffer, this->_BufferSize),
			boost::bind(&UavCamSession::ReadStramming, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	}
	
	void UavCamSession::ReadStramming(
		const boost::system::error_code& error, size_t bytes_transferred){

		if(!error){
			_Resq->_Socket.async_write_some(
				boost::asio::buffer(this->_Buffer, bytes_transferred),
				boost::bind(&UavCamSession::WriteStreamming, this,
				boost::asio::placeholders::error));

		}else{
			delete this;
		}
	}

	void UavCamSession::WriteStreamming(const boost::system::error_code& error){

		if(!error){

			_Socket.async_read_some(
				boost::asio::buffer(this->_Buffer, this->_BufferSize),
				boost::bind(&UavCamSession::ReadStramming, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));

		}else{
			delete this;
		}
	}


}}} // openuasl.server.ucstream