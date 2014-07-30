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

			SetSslContext(CERT_CHAIN_PATH, 
				CERT_PRIKEY_PATH, CERT_TMPDH_PATH);
		}

		std::string main_server::SetCertPassword() const {
			return "1234";
		}



		void main_server::ProcessRead(SecureSocket* nsock,
			const boost::system::error_code& error){

				if(!error){

					nsock->async_read_some(
						boost::asio::buffer(_Buffer, NETWORK_BUF_SIZE),
						boost::bind(&UCStreamServer::HandleMakeSession, this,
						nsock, boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));

				}else{
					delete nsock;
				}
		}

		void main_server::HandleMakeSession(SecureSocket* nsock, 
			const boost::system::error_code& error, size_t bytes_transferred){

				if(!error){

					session_app* resq = NULL;
					session_uav* uav = NULL;
					std::string id;

					switch(_Buffer[0])
					{
					case resq_req_devid:
						id = std::string(_Buffer+1);
						std::cout << "resquer device id : " << id << std::endl;

						resq = new session_app(id, *nsock, NETWORK_BUF_SIZE);

						_ResqSmgr.InsertSession(resq);

						nsock->async_read_some(
							boost::asio::buffer(this->_Buffer, NETWORK_BUF_SIZE),
							boost::bind(&main_server::HandleResqReqQRCode, this,
							resq, boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred));
						break;

					case uav_req_serial:
						id = std::string(_Buffer+1);
						std::cout << "uav serial id : " << id << std::endl;

						uav = new session_uav(id, *nsock, UCS_IMGBUF_SIZE);

						_UavSmgr.InsertSession(uav);

						break;

					default:
						delete nsock;
						break;
					}

				}else{
					delete nsock;
				}
		}


		void main_server::HandleResqReqQRCode(session_app* resq,
			const boost::system::error_code& error, size_t bytes_transferred){

				if(!error){
					if(_Buffer[0] != resq_req_qrcode){
						_ResqSmgr.EreaseSession(resq->_SessionId);
						delete resq;

						resq->_Socket.async_read_some(
							boost::asio::buffer(_Buffer, NETWORK_BUF_SIZE),
							boost::bind(&main_server::HandleResqReqQRCode, this,
							resq, boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred));

						return;
					}

					session_uav* uav = static_cast<session_uav*>(
						_UavSmgr.GetSession(std::string(_Buffer+1, 64)));

					if(uav != NULL){
						resq->SetUavSession(uav);
						uav->SetResquerSesion(resq);
					}

					resq->Start();

				}else{
					delete resq;
				}
		}

	}
}