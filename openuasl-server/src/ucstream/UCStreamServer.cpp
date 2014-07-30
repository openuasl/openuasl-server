#include <openuasl/ucstream/UCStreamServer.h>
#include <openuasl/ucstream/ResquerCamSession.h>
#include <openuasl/ucstream/UavCamSession.h>

namespace openuasl{
namespace server{
namespace ucstream{

// public
	UCStreamServer::UCStreamServer(unsigned short port)
		: skeleton::SecureBaseServer(port){
			
		SetSslContext(CERT_CHAIN_PATH, 
			CERT_PRIKEY_PATH, CERT_TMPDH_PATH);
	}

// protected
// base server's pure virtual methods
	std::string UCStreamServer::SetCertPassword() const{
		return "1234";
	}
	
	void UCStreamServer::ProcessRead(SecureSocket* nsock,
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

// for device certificate
	void UCStreamServer::HandleMakeSession(SecureSocket* nsock, 
		const boost::system::error_code& error, size_t bytes_transferred){

			if(!error){

				ResquerCamSession* resq = NULL;
				UavCamSession* uav = NULL;
				std::string id;

				switch(_Buffer[0])
				{
				case resq_req_devid:
					id = std::string(_Buffer+1, 64);
					std::cout << "resquer device id : " << id << std::endl;

					resq = new ResquerCamSession(id, *nsock, NETWORK_BUF_SIZE);
					
					_ResqSmgr.InsertSession(resq);
					
					nsock->async_read_some(
						boost::asio::buffer(this->_Buffer, NETWORK_BUF_SIZE),
						boost::bind(&UCStreamServer::HandleResqReqQRCode, this,
						resq, boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
					break;

				case uav_req_serial:
					id = std::string(_Buffer+1, 64);
					std::cout << "uav serial id : " << id << std::endl;

  					uav = new UavCamSession(id, *nsock, UCS_IMGBUF_SIZE);
					
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
	
	void UCStreamServer::HandleResqReqQRCode(ResquerCamSession* resq,
		const boost::system::error_code& error, size_t bytes_transferred){

			if(!error){
				if(_Buffer[0] != resq_req_qrcode){
					_ResqSmgr.EreaseSession(resq->_SessionId);
					delete resq;

					resq->_Socket.async_read_some(
						boost::asio::buffer(_Buffer, NETWORK_BUF_SIZE),
						boost::bind(&UCStreamServer::HandleResqReqQRCode, this,
						resq, boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));

					return;
				}

				UavCamSession* uav = static_cast<UavCamSession*>(
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

}}} // openuasl.server.ucstream