#include "resquer_session.h"
#include "uav_session.h"

namespace bssm{
namespace blueeyes{
namespace imgstream{

	uav_session::uav_session(boost::asio::ip::tcp::socket* sock)
		: _socket(sock){}

	boost::asio::ip::tcp::socket* uav_session::socket(){
		return _socket;
	}

	void uav_session::set_serial(char* buffer){
		this->_serial_id = std::string(buffer);
	}

	void uav_session::set_resquer_session(resquer_session* resq){
		this->_resq = resq;
	}

	void uav_session::start_streamming(){

		_socket->async_read_some(boost::asio::buffer(_buffer, IMGS_IMGBUF_SIZE),
			boost::bind(&uav_session::handle_read_streamming, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	}

	void uav_session::handle_rep_ready(const boost::system::error_code& error){

		if(!error){

			_socket->async_read_some(boost::asio::buffer(_buffer, IMGS_NETBUF_SIZE),
				boost::bind(&uav_session::handle_req_start, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));

		}else{
			delete this;
		}
	}

	void uav_session::handle_req_start(
		const boost::system::error_code& error, size_t bytes_transferred){

			if(!error && _buffer[0] == uav_req_start){

				_buffer[0] = resq_rep_start;
				_resq->socket()->async_write_some(boost::asio::buffer(_buffer, 1),
					boost::bind(&resquer_session::handle_rep_start, _resq,
					boost::asio::placeholders::error));
			}else{
				delete this;
			}
	}

	void uav_session::handle_read_streamming(
		const boost::system::error_code& error, size_t bytes_transferred){

		if(!error){
			boost::system::error_code err;
			_resq->socket()->write_some(
				boost::asio::buffer(_buffer, bytes_transferred), err);

			if(!err){
				_socket->async_read_some(boost::asio::buffer(_buffer, IMGS_IMGBUF_SIZE),
					boost::bind(&uav_session::handle_read_streamming, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
			}else{
				delete this;
			}
		}else{
			delete this;
		}
	}

}}} // bssm.blueeyes.imgstream