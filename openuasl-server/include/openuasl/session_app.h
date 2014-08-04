#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SESSION_APP_H__
#define __OPENUASL_SERVER_SESSION_APP_H__

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <openuasl/server_conf.h>
#include <openuasl/skeleton/BaseResquerSession.h>

namespace openuasl{
	namespace server{
		class session_uav;

		class session_app : public skeleton::BaseResquerSession{
		public :
			session_app(std::string& id, SecureSocket& sock, size_t buf_size);
			virtual ~session_app();

		protected:

			virtual void RepStart(const boost::system::error_code& error);

			friend class session_uav;
		};
}
} // openuasl.server


#endif // __OPENUASL_SERVER_SESSION_APP_H__