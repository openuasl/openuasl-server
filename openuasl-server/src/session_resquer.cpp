#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <openuasl/session_app.h>
#include <openuasl/session_uav.h>

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

namespace openuasl{
	namespace server{
		session_app::session_app(boost::asio::io_service& io_service, boost::asio::ssl::context& context)
			: socket_(io_service, context)
		{
		}


		ssl_socket::lowest_layer_type& session_app::socket()
		{
			return socket_.lowest_layer();
		}

		void session_app::start()
		{
			/* blocking read and write **********************/
			boost::system::error_code err;

			if(this->_uav == NULL){
				data_[0] = resq_rep_mismatch;
				socket_.async_write_some(boost::asio::buffer(data_, 1),
					boost::bind(&session_app::handle_rep_mismatch, this,
					boost::asio::placeholders::error));

			}else{
				data_[0] = resq_rep_ready;
				socket_.async_write_some(boost::asio::buffer(data_, 1),
					boost::bind(&session_app::handle_rep_ready, this,
					boost::asio::placeholders::error));
			}
		}
		void session_app::set_devid(char* buffer){		
			this->_device_id = std::string(buffer);
		}

		void session_app::set_uav_session(session_uav* uav){
			this->_uav = uav;
		}

		void session_app::handle_rep_ready(const boost::system::error_code& error){

			if(!error){

				socket_.async_read_some(boost::asio::buffer(data_, IMGS_NETBUF_SIZE),
					boost::bind(&session_app::handle_req_ready, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));

			}else{
				delete this;
			}
		}

		void session_app::handle_req_ready(
			const boost::system::error_code& error, size_t bytes_transferred){

				if(!error && data_[0] == resq_req_ready){
					boost::system::error_code err;
					char wb[2] = {0,};

					wb[0] = uav_rep_ready;
					boost::asio::async_write(_uav->socket(), boost::asio::buffer(data_, bytes_transferred),
						boost::bind(&session_app::handle_write, this,
						boost::asio::placeholders::error));



				}else{
					delete this;
				}
		}

		void session_app::handle_rep_mismatch(
			const boost::system::error_code& error){

				if(error)	delete this;
		}



	}

}