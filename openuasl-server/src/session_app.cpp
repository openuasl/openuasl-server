#include <openuasl/session_app.h>
#include <openuasl/session_uav.h>
#include <openuasl/server_conf.h>

namespace openuasl{
	namespace server{
		session_app::session_app(std::string& id, SecureSocket& sock, size_t buf_size)
			:skeleton::BaseResquerSession(id, sock, buf_size){}

		session_app::~session_app(){}

		void session_app::RepStart(const boost::system::error_code& error){

			BaseResquerSession::RepStart(error);

			if(!error){

				_Uav->Start();

				_Socket.async_write_some(
					boost::asio::buffer(this->_Buffer, this->_BufferSize),
					boost::bind(&session_app::ReadappStreamming, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));


			}else{
				delete this;
			}
		}


		void session_app::ReadappStreamming(
			const boost::system::error_code& error, size_t bytes_transferred){

				if(!error){

					_Uav->_Socket.async_write_some(
						boost::asio::buffer(this->_Buffer, bytes_transferred),
						boost::bind(&session_app::WriteuavStreamming, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));

				}else{
					delete this;
				}
		}



		void session_app::WriteuavStreamming(
			const boost::system::error_code& error, size_t bytes_transferred){

				if(!error){

					_Socket.async_read_some(
						boost::asio::buffer(this->_Buffer, this->_BufferSize),
						boost::bind(&session_app::ReadappStreamming, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));


				}else{
					delete this;
				}
		}



	}
}