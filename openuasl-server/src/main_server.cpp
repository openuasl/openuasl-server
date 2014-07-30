#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <openuasl/main_server.h>
#include <openuasl/session_app.h>
#include <openuasl/session_uav.h>

namespace openuasl{
	namespace server{
			main_server::main_server(unsigned short port) : skeleton::SecureBaseServer(port){

			context_.set_options(
				boost::asio::ssl::context::default_workarounds
				| boost::asio::ssl::context::no_sslv2
				| boost::asio::ssl::context::single_dh_use);

			context_.set_password_callback(boost::bind(&main_server::get_password, this));
			context_.use_certificate_chain_file(CERT_CHAIN_PATH);
			context_.use_private_key_file(CERT_PRIKEY_PATH, boost::asio::ssl::context::pem);
			context_.use_tmp_dh_file(CERT_TMPDH_PATH);

			ssl_socket* sock = new ssl_socket(io_service_, context_);
			acceptor_.async_accept(sock->lowest_layer(),  
				boost::bind(&main_server::handle_accept, 
				this, sock, boost::asio::placeholders::error));

		}


		void main_server::handle_handshake(ssl_socket * sock,const boost::system::error_code& error){

			if (!error)
			{
				boost::system::error_code err;
				sock->async_read_some(boost::asio::buffer(_buffer, max_length), err );

				session_app *sa=NULL;
				switch(_buffer[0])
				{
				case resq_req_devid:
					resq = new resquer_session(sock);
					resq->set_devid(_buffer+1);

					printf("resquer device id : %s\n", _buffer+1);

					_smgr.insert(resq);

					sock->async_read_some(boost::asio::buffer(_buffer, NETWORK_BUF_SIZE),
						boost::bind(&main_server::handle_resq_req_qrcode, this,
						resq, boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
					break;

				case uav_req_serial:
					uav = new uav_session(sock);
					uav->set_serial(_buffer+1);

					printf("uav serial id : %s\n", _buffer+1); 

					_smgr.insert(uav);
					uav->start();
					break;

				default:
					sock->shutdown(boost::asio::socket_base::shutdown_both);
					break;
				}

				///


				//
			}
			else
			{
				delete this;
			}
		}

		void main_server::handle_accept(ssl_socket * sock,
			const boost::system::error_code& error){

				sock->async_handshake(boost::asio::ssl::stream_base::server,
					boost::bind(&main_server::handle_handshake, this,sock,
					boost::asio::placeholders::error));
		}

		std::string main_server::get_password() const {
			return "1234";
		}

	
	}
}