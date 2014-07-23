#include <openuasl/ucstream/resquer_session.h>
#include <openuasl/ucstream/uav_session.h>

namespace bssm{
namespace blueeyes{
namespace imgstream{
	
	resquer_session::resquer_session(boost::asio::ip::tcp::socket* sock)
		:_socket(sock){}

	boost::asio::ip::tcp::socket* resquer_session::socket(){
		return this->_socket;
	}

	void resquer_session::start(){
		/* blocking read and write **********************/
		boost::system::error_code err;

		if(this->_uav == NULL){
			_buffer[0] = resq_rep_mismatch;
			_socket->async_write_some(boost::asio::buffer(_buffer, 1),
				boost::bind(&resquer_session::handle_rep_mismatch, this,
				boost::asio::placeholders::error));

		}else{
			_buffer[0] = resq_rep_ready;
			_socket->async_write_some(boost::asio::buffer(_buffer, 1),
				boost::bind(&resquer_session::handle_rep_ready, this,
				boost::asio::placeholders::error));
		}
	}

	void resquer_session::set_devid(char* buffer){		
		this->_device_id = std::string(buffer);
	}

	void resquer_session::set_uav_session(uav_session* uav){
		this->_uav = uav;
	}

	void resquer_session::handle_rep_ready(const boost::system::error_code& error){

		if(!error){

			_socket->async_read_some(boost::asio::buffer(_buffer, IMGS_NETBUF_SIZE),
				boost::bind(&resquer_session::handle_req_ready, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));

		}else{
			delete this;
		}
	}

	void resquer_session::handle_req_ready(
		const boost::system::error_code& error, size_t bytes_transferred){
			
			if(!error && _buffer[0] == resq_req_ready){
				boost::system::error_code err;
				char wb[2] = {0,};

				wb[0] = uav_rep_ready;
				_uav->socket()->async_write_some(boost::asio::buffer(wb, 1),
					boost::bind(&uav_session::handle_rep_ready, _uav,
					boost::asio::placeholders::error));


			}else{
				delete this;
			}
	}

	void resquer_session::handle_rep_mismatch(
		const boost::system::error_code& error){

			if(!error)	delete this;
	}

	void resquer_session::handle_rep_start(const boost::system::error_code& error){
		if(!error){
			
			_uav->start_streamming();

		}else{
			delete this;
		}
	}


}}} // bssm.blueeyes.imgstream