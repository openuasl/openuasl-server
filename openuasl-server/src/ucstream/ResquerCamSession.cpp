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

		BaseResquerSession::RepStart(error);

		if(!error){
						
			//_Uav->Start();
			// �����κ��� ��Ʈ���� ���� ��û�� ������.

		}else{
			delete this;
		}
	}


}}} // openuasl.server.ucstream