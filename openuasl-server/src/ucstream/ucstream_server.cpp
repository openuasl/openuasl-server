#include <openuasl/ucstream/ucstream_server.h>

namespace openuasl{
namespace server{
namespace ucstream{

	ucstream_server::ucstream_server(boost::asio::io_service& io_service, short port)
		: _io_service(io_service),
		_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)){
			
		boost::asio::ip::tcp::socket* sock = 
			new boost::asio::ip::tcp::socket(_io_service);

		_acceptor.async_accept(*sock,
			boost::bind(&ucstream_server::handle_accept, this, sock,
			boost::asio::placeholders::error));
	}

	void ucstream_server::handle_accept(boost::asio::ip::tcp::socket* sock,
		const boost::system::error_code& error){
			
			if(!error){
				boost::system::error_code err;
				sock->read_some(boost::asio::buffer(_buffer, NETWORK_BUF_SIZE), err);

				resquer_session* resq = NULL;
				uav_session* uav = NULL;

				switch(_buffer[0])
				{
				case resq_req_devid:
					resq = new resquer_session(sock);
					resq->set_devid(_buffer+1);

					printf("resquer device id : %s\n", _buffer+1);

					_smgr.insert(resq);
					
					sock->async_read_some(boost::asio::buffer(_buffer, NETWORK_BUF_SIZE),
						boost::bind(&ucstream_server::handle_resq_req_qrcode, this,
						resq, boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
					break;

				case uav_req_serial:
  					uav = new uav_session(sock);
					uav->set_serial(_buffer+1);

					printf("uav serial id : %s\n", _buffer+1); 

					_smgr.insert(uav);
					break;

				default:
					sock->shutdown(boost::asio::socket_base::shutdown_both);
					break;
				}

				sock = new boost::asio::ip::tcp::socket(_io_service);
				_acceptor.async_accept(*sock,
					boost::bind(&ucstream_server::handle_accept, this, sock,
					boost::asio::placeholders::error));

			}else{
				delete sock;
			}
	}

	void ucstream_server::handle_resq_req_qrcode(resquer_session* resq,
		const boost::system::error_code& error, size_t bytes_transferred){

			if(!error){
				if(_buffer[0] != resq_req_qrcode){
					delete resq;
					return;
				}
				
				resq->set_uav_session(_smgr._uav_list[std::string(_buffer+1, 64)]);
				_smgr._uav_list[std::string(_buffer+1, 64)]->set_resquer_session(resq);

				resq->start();

			}else{
				delete resq;
			}
	}

}}} // openuasl.server.ucstream