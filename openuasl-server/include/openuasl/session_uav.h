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

#include <openuasl/server_conf.h>
#include <openuasl/skeleton/BaseUavSession.h>

namespace openuasl{
	namespace server{

		class session_app;

		class session_uav : public skeleton::BaseUavSession{

		public:
			session_uav(std::string& id, SecureSocket& sock, size_t buf_size);
			virtual ~session_uav();
			virtual void Start();
			void ReadStramming(const boost::system::error_code& error, size_t bytes_transferred);
			void WriteStreamming(const boost::system::error_code& error, size_t bytes_transferred);

		protected:

			friend class session_app;

		};


	}

} // openuasl.server


#endif // __OPENUASL_SERVER_SESSION_UAV_H__