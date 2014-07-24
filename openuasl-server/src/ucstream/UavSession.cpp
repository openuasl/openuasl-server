#include <openuasl/ucstream/UavSession.h>
#include <openuasl/ucstream/ResquerSession.h>
#include <openuasl/server_conf.h>

namespace openuasl{
namespace server{
namespace ucstream{

	UavSession::UavSession(std::string& id, SecureSocket& sock, size_t buf_size)
		: skeleton::BaseSession(id, sock, buf_size){}
	
	void UavSession::SetSerialId(char* buffer){
		this->_SessionId = std::string(buffer);
	}

	void UavSession::SetResquerSesion(ResquerSession* resq){
		this->_Resq = resq;
	}

	void UavSession::Start(){

		_Socket.async_read_some(
			boost::asio::buffer(this->_Buffer, this->_BufferSize),
			boost::bind(&UavSession::ReadStramming, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	}

	void UavSession::RepReady(const boost::system::error_code& error){
				
		if(!error){

			_Socket.async_read_some(
				boost::asio::buffer(this->_Buffer, this->_BufferSize),
				boost::bind(&UavSession::ReqStart, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));

		}else{
			delete this;
		}
	}

	void UavSession::ReqStart(
		const boost::system::error_code& error, size_t bytes_transferred){

			if(!error && _Buffer[0] == uav_req_start){

				_Buffer[0] = resq_rep_start;
				_Resq->_Socket.async_write_some(boost::asio::buffer(_Buffer, 1),
					boost::bind(&ResquerSession::RepStart, _Resq,
					boost::asio::placeholders::error));
			}else{
				delete this;
			}
	}

	void UavSession::ReadStramming(
		const boost::system::error_code& error, size_t bytes_transferred){

		if(!error){

			_Resq->_Socket.async_write_some(
				boost::asio::buffer(this->_Buffer, bytes_transferred),
				boost::bind(&UavSession::WriteStreamming, this,
				boost::asio::placeholders::error));

		}else{
			delete this;
		}
	}

	void UavSession::WriteStreamming(const boost::system::error_code& error){

		if(!error){

			_Socket.async_read_some(
				boost::asio::buffer(this->_Buffer, this->_BufferSize),
				boost::bind(&UavSession::ReadStramming, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));

		}else{
			delete this;
		}
	}


}}} // openuasl.server.ucstream