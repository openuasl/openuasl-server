#include <openuasl/session_app.h>
#include <openuasl/session_uav.h>
#include <openuasl/server_conf.h>

namespace openuasl{
	namespace server{
		session_app::session_app(std::string& id, SecureSocket& sock, size_t buf_size)
		:skeleton::BaseResquerSession(id, sock, buf_size){}

		session_app::~session_app(){}
		void session_app::Start(){}

}}