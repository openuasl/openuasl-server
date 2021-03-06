#ifdef _WIN32
#pragma once
#endif // _WIN32

#ifndef __OPENUASL_SERVER_SKELETON_SESSION_MANAGER_H__
#define __OPENUASL_SERVER_SKELETON_SESSION_MANAGER_H__

#include <openuasl/skeleton/TypeDefs.h>
#include <openuasl/skeleton/BaseSession.h>


typedef boost::shared_mutex \
		SharedMutex;
typedef boost::numeric::ublas::vector<std::string> \
		StringVector;

namespace openuasl{
namespace server{
namespace skeleton{
		
	typedef boost::unordered_map<std::string, BaseSession*> \
		SessionList;

	class SessionManager{
	public:
		SessionList _ConnectedSessions;
		SharedMutex _SharedMutex;

	public:
		virtual bool InsertSession(BaseSession* session);
		virtual void EreaseSession(BaseSession* session);
		virtual void EreaseSession(std::string& id);
		virtual BaseSession* GetSession(std::string& id);
		virtual bool IsExistSession(std::string& id);
		StringVector* GetConnectedSessionIdList();

	};

}}} // openuasl.server.skeleton


#endif // __OPENUASL_SERVER_SKELETON_SESSION_MANAGER_H__
