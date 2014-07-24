#include <openuasl/ucstream/ResquerSession.h>
#include <openuasl/ucstream/UavSession.h>
#include <openuasl/server_conf.h>


namespace openuasl{
namespace server{
namespace ucstream{
	
	ResquerSession::ResquerSession(std::string& id, SecureSocket& sock, size_t buf_size)
		:skeleton::BaseSession(id, sock, buf_size), _Uav(NULL){}
	
	void ResquerSession::Start(){
		
		if(this->_Uav == NULL){
			this->_Buffer[0] = resq_rep_mismatch;
			_Socket.async_write_some(boost::asio::buffer(this->_Buffer, 1),
				boost::bind(&ResquerSession::RepMismatch, this,
				boost::asio::placeholders::error));

		}else{
			this->_Buffer[0] = resq_rep_ready;
			_Socket.async_write_some(boost::asio::buffer(_Buffer, 1),
				boost::bind(&ResquerSession::RepReady, this,
				boost::asio::placeholders::error));
		}
	}

	void ResquerSession::SetDeviceId(char* buffer){		
		this->_SessionId = std::string(buffer);
	}

	void ResquerSession::SetUavSession(UavSession* uav){
		this->_Uav = uav;
	}

	void ResquerSession::RepReady(const boost::system::error_code& error){

		if(!error){

			_Socket.async_read_some(
				boost::asio::buffer(this->_Buffer, this->_BufferSize),
				boost::bind(&ResquerSession::ReqReady, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));

		}else{
			delete this;
		}
	}

	void ResquerSession::ReqReady(
		const boost::system::error_code& error, size_t bytes_transferred){
			
			if(!error && _Buffer[0] == resq_req_ready){
				_Buffer[0] = uav_rep_ready;
				_Uav->_Socket.async_write_some(
					boost::asio::buffer(this->_Buffer, 1),
					boost::bind(&ResquerSession::RepReady, _Uav,
					boost::asio::placeholders::error));

			}else{
				delete this;
			}
	}

	void ResquerSession::RepMismatch(
		const boost::system::error_code& error){

			if(!error){


			}else{	
				delete this;
			}
	}

	void ResquerSession::RepStart(const boost::system::error_code& error){

		if(!error){
						
			_Uav->Start();

		}else{
			delete this;
		}
	}


}}} // openuasl.server.ucstream