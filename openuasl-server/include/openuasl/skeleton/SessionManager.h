#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SKELETON_SESSION_MANAGER_H__
#define __OPENUASL_SERVER_SKELETON_SESSION_MANAGER_H__

#include <openuasl/skeleton/TypeDefs.h>

#include <openuasl/skeleton/BaseSession.h>

#include <boost/numeric/ublas/vector.hpp>

namespace openuasl{
namespace server{
namespace skeleton{
	
	// 로그인 완료 한 세션들만 멤버로 가지고 있음
	template<typename ID = std::string>
	class SessionManager
	{
	public:
		boost::unordered_map<ID, BaseSession<ID>*> _ConnectedSessions;
		SharedMutex _SharedMutex;

	public:
		virtual bool InsertSession(BaseSession<ID>* session);
		virtual void EreaseSession(BaseSession<ID>* session);
		virtual void EreaseSession(ID& id);
		virtual BaseSession<ID>* GetSession(ID& id);
		virtual bool IsExistSession(ID& sessoin_id);
		boost::numeric::ublas::vector<ID>* GetConnectedSessionIdList();

	};

}}} // openuasl.server.skeleton


#endif // __OPENUASL_SERVER_SKELETON_SESSION_MANAGER_H__
