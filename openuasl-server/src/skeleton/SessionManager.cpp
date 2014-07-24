#ifdef _WIN32
#define _WIN32_WINNT 0x0501
#endif // _WIN32

#include <openuasl/skeleton/SessionManager.h>

#include <string>
#include <boost/foreach.hpp>

namespace openuasl{
namespace server{
namespace skeleton{
	
	bool SessionManager::InsertSession(BaseSession* session)
	{
		UniqueLock lock(this->_SharedMutex);
				
		this->_ConnectedSessions.erase(session->_SessionId);
		this->_ConnectedSessions.insert(SessionList::value_type(session->_SessionId, session));
		lock.unlock();

		return true;
	}
		
	void SessionManager::EreaseSession(BaseSession* session)
	{
		UniqueLock lock(this->_SharedMutex);

		this->_ConnectedSessions.erase(session->_SessionId);
				
		lock.unlock();
	}
		
	void SessionManager::EreaseSession(std::string& id)
	{
		UniqueLock lock(this->_SharedMutex);

		this->_ConnectedSessions.erase(id);
				
		lock.unlock();
	}
		
	BaseSession* SessionManager::GetSession(std::string& id)
	{
		SharedLock lock(this->_SharedMutex);
		
		return this->_ConnectedSessions[id];
	}

	bool SessionManager::IsExistSession(std::string& id)
	{
		SharedLock lock(this->_SharedMutex);
		
		return (this->_ConnectedSessions.find(id)
			!= this->_ConnectedSessions.end())? true : false;
	}
	
	StringVector* SessionManager::GetConnectedSessionIdList()
	{
		SharedLock lock(this->_SharedMutex);

		boost::numeric::ublas::vector<std::string>* result
			= new boost::numeric::ublas::vector<std::string>(_ConnectedSessions.size());
		int i = 0;
		for(SessionList::iterator it =	_ConnectedSessions.begin();
			it != _ConnectedSessions.end(); ++it, ++i)
		{
			result->insert_element(i, it->first);
		}
			
		return result;
	}

}}} // openuasl.server.skeleton