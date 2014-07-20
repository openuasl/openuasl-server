#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SESSION_MGR_H__
#define __OPENUASL_SERVER_SESSION_MGR_H__

#include <boost/thread.hpp>
#include <boost/unordered_map.hpp>

namespace openuasl{
namespace server{

	template <class R, class U>
	class sessoin_mgr{
	private:
		boost::shared_mutex _mutex;
		
	public:
		boost::unordered_map<std::string, R> _resquer_list;
		boost::unordered_map<std::string, U> _uav_list;

		bool insert(R resq);
		bool insert(U uav);

	};
	

}} // openuasl.server

#endif // __OPENUASL_SERVER_SESSION_MGR_H__