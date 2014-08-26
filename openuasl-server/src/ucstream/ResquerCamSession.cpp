#include <openuasl/ucstream/ResquerCamSession.h>
#include <openuasl/ucstream/UavCamSession.h>
#include <openuasl/server_conf.h>


namespace openuasl{
namespace server{
namespace ucstream{
	
	ResquerCamSession::ResquerCamSession(std::string& id, SecureSocket& sock, size_t buf_size)
		:skeleton::BaseResquerSession(id, sock, buf_size){}
	
	ResquerCamSession::~ResquerCamSession(){}
		
// override
	void ResquerCamSession::RepStart(const boost::system::error_code& error){
		
		if(!error){
						
			BaseResquerSession::RepStart(error);
			
			_Socket.async_read_some(
					boost::asio::buffer(this->_Buffer, this->_BufferSize),
					boost::bind(&ResquerCamSession::ReqEnd, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));

		}else{
			delete this;
		}
	}

	void ResquerCamSession::ReqEnd(
		const boost::system::error_code& error, size_t bytes_transferred){

			if(!error){

				_Uav->_Socket.async_write_some(
					boost::asio::buffer(this->_Buffer, bytes_transferred),
					boost::bind(&ResquerCamSession::RepEnd, this,
					boost::asio::placeholders::error));

			}else{
				delete this;
			}
	}

	void ResquerCamSession::RepEnd(const boost::system::error_code& error){
		if(!error){

			std::cout << "[ uav camera streamming end! ]" << std::endl;
			std::cout << _SessionId << std::endl;

		}

		delete this;
	}

}}} // openuasl.server.ucstream