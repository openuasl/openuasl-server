#include <openuasl/skeleton/BaseUavSession.h>
#include <openuasl/skeleton/BaseResquerSession.h>
#include <openuasl/server_conf.h>

namespace openuasl{
namespace server{
namespace skeleton{

	BaseUavSession::BaseUavSession(std::string& id, SecureSocket& sock, size_t buf_size)
		: skeleton::BaseSession(id, sock, buf_size){}

	BaseUavSession::~BaseUavSession(){}

	void BaseUavSession::SetSerialId(char* buffer){
		this->_SessionId = std::string(buffer);
	}

	void BaseUavSession::SetResquerSesion(BaseResquerSession* resq){
		this->_Resq = resq;
	}

	void BaseUavSession::Start(){
		
	}

	void BaseUavSession::RepReady(const boost::system::error_code& error){
				
		if(!error){

			_Socket.async_read_some(
				boost::asio::buffer(this->_Buffer, this->_BufferSize),
				boost::bind(&BaseUavSession::ReqStart, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));

		}else{
			delete this;
		}
	}

	void BaseUavSession::ReqStart(
		const boost::system::error_code& error, size_t bytes_transferred){

			if(!error && _Buffer[0] == uav_req_start){

				_Buffer[0] = resq_rep_start;
				_Resq->_Socket.async_write_some(boost::asio::buffer(_Buffer, 1),
					boost::bind(&BaseResquerSession::RepStart, _Resq,
					boost::asio::placeholders::error));
			}else{
				delete this;
			}
	}



}}} // openuasl.server.skeleton