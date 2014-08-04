#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SESSION_UAV_H__
#define __OPENUASL_SERVER_SESSION_UAV_H__

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <openuasl/skeleton/BaseResquerSession.h>

namespace openuasl{
	namespace server{

		class session_app;

		class session_uav : public skeleton::BaseResquerSession{

		public:
			session_uav(std::string& id, SecureSocket& sock, size_t buf_size);
			virtual ~session_uav();

		protected:

			virtual void RepStart(const boost::system::error_code& error);

			friend class session_app;

		};


	}

} // openuasl.server


#endif // __OPENUASL_SERVER_SESSION_UAV_H__