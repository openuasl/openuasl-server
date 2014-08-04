
#include <openuasl/server_conf.h>
#include <openuasl/session_app.h>
#include <openuasl/session_uav.h>

namespace openuasl{
namespace server{

	session_uav::session_uav(std::string& id, SecureSocket& sock, size_t buf_size)
		: skeleton::BaseUavSession(id, sock, buf_size){}

	session_uav::~session_uav(){}


}} // openuasl.server.ucstream