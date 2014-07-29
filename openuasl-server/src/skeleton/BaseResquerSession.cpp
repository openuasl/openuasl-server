#include <openuasl/skeleton/BaseResquerSession.h>
#include <openuasl/skeleton/BaseUavSession.h>
#include <openuasl/server_conf.h>


namespace openuasl{
namespace server{
namespace skeleton{
	
	BaseResquerSession::BaseResquerSession(std::string& id, SecureSocket& sock, size_t buf_size)
		:skeleton::BaseSession(id, sock, buf_size), _Uav(NULL){}
	
	BaseResquerSession::~BaseResquerSession(){}

	void BaseResquerSession::Start(){
		
		if(this->_Uav == NULL){
			this->_Buffer[0] = resq_rep_mismatch;
			_Socket.async_write_some(boost::asio::buffer(this->_Buffer, 1),
				boost::bind(&BaseResquerSession::RepMismatch, this,
				boost::asio::placeholders::error));

		}else{
			this->_Buffer[0] = resq_rep_ready;
			_Socket.async_write_some(boost::asio::buffer(_Buffer, 1),
				boost::bind(&BaseResquerSession::RepReady, this,
				boost::asio::placeholders::error));
		}
	}

	void BaseResquerSession::SetDeviceId(char* buffer){		
		this->_SessionId = std::string(buffer);
	}

	void BaseResquerSession::SetUavSession(BaseUavSession* uav){
		this->_Uav = uav;
	}

	void BaseResquerSession::RepReady(const boost::system::error_code& error){

		if(!error){

			_Socket.async_read_some(
				boost::asio::buffer(this->_Buffer, this->_BufferSize),
				boost::bind(&BaseResquerSession::ReqReady, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));

		}else{
			delete this;
		}
	}

	void BaseResquerSession::ReqReady(
		const boost::system::error_code& error, size_t bytes_transferred){
			
			if(!error && _Buffer[0] == resq_req_ready){
				_Buffer[0] = uav_rep_ready;
				_Uav->_Socket.async_write_some(
					boost::asio::buffer(this->_Buffer, 1),
					boost::bind(&BaseUavSession::RepReady, _Uav,
					boost::asio::placeholders::error));

			}else{
				delete this;
			}
	}

	void BaseResquerSession::RepMismatch(
		const boost::system::error_code& error){

			if(!error){


			}else{	
				delete this;
			}
	}

	void BaseResquerSession::RepStart(const boost::system::error_code& error){

		if(!error){
						
			_Uav->Start();

		}else{
			delete this;
		}
	}


}}} // openuasl.server.skeleton