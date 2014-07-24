#ifdef _WIN32
#define _WIN32_WINNT 0x0501
#endif // _WIN32
#include <openuasl/skeleton/BaseSession.h>

namespace openuasl{
namespace server{
namespace skeleton{

	BaseSession::BaseSession(std::string& id, SecureSocket& sock, size_t buf_size)
		: _Socket(sock), _SessionId(id)
	{
		this->_Buffer = new char[buf_size];
		_BufferSize = buf_size;
	}

	BaseSession::~BaseSession()
	{
		delete [] this->_Buffer;
		boost::system::error_code error;
		_Socket.shutdown(error);
	}
	
}}} // openuasl.server.skeleton