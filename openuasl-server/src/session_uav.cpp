
#include <openuasl/server_conf.h>
#include <openuasl/session_app.h>
#include <openuasl/session_uav.h>

namespace openuasl{
	namespace server{

		session_uav::session_uav(std::string& id, SecureSocket& sock, size_t buf_size)
			: skeleton::BaseUavSession(id, sock, buf_size){}

		session_uav::~session_uav(){}

		void session_uav::Start(){
			_Socket.async_read_some(
				boost::asio::buffer(this->_Buffer, this->_BufferSize),
				boost::bind(&session_uav::ReaduavStreamming, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}


		void session_uav::ReaduavStreamming( //������̵忡�� �о���°�
			const boost::system::error_code& error, size_t bytes_transferred){

				if(!error){	
					_Resq->_Socket.async_write_some(
						boost::asio::buffer(this->_Buffer, bytes_transferred),
						boost::bind(&session_uav::WriteappStreamming, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred)
						);

				}else{
					delete this;
				}
		}


		void session_uav::WriteappStreamming( //�ۿ� ���°�
			const boost::system::error_code& error, size_t bytes_transferred){

				if(!error){
					_Socket.async_read_some(
						boost::asio::buffer(this->_Buffer, this->_BufferSize),
						boost::bind(&session_uav::ReaduavStreamming, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred)
						);

				}else{
					delete this;
				}
		}

	}
} 