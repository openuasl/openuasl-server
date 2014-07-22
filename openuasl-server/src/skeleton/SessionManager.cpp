#ifdef _WIN32
#define _WIN32_WINNT 0x0501
#endif // _WIN32

#include <openuasl/skeleton/SessionManager.h>

#include <string>
#include <boost/foreach.hpp>

namespace openuasl{
namespace server{
namespace skeleton{
	
	template<>
	bool SessionManager<std::string>::InsertSession(BaseSession<std::string>* session)
	{
		UniqueLock lock(this->_SharedMutex);
				
		this->_ConnectedSessions.erase(session->_SessionId);
		this->_ConnectedSessions.insert(
			boost::unordered_map<std::string, BaseSession<std::string>*>::value_type(session->_SessionId, session));
		lock.unlock();

		return true;
	}

	template<>
	void SessionManager<std::string>::EreaseSession(BaseSession<std::string>* session)
	{
		UniqueLock lock(this->_SharedMutex);

		this->_ConnectedSessions.erase(session->_SessionId);
				
		lock.unlock();
	}

	template<>
	void SessionManager<std::string>::EreaseSession(std::string& id)
	{
		UniqueLock lock(this->_SharedMutex);

		this->_ConnectedSessions.erase(id);
				
		lock.unlock();
	}

	template<>
	BaseSession<std::string>* SessionManager<std::string>::GetSession(std::string& id)
	{
		SharedLock lock(this->_SharedMutex);
		
		return this->_ConnectedSessions[id];
	}

	template<>
	bool SessionManager<std::string>::IsExistSession(std::string& session_id)
	{
		SharedLock lock(this->_SharedMutex);
		
		return (this->_ConnectedSessions.find(session_id)
			!= this->_ConnectedSessions.end())? true : false;
	}
	
	template<>
	boost::numeric::ublas::vector<std::string>* 
		SessionManager<std::string>::GetConnectedSessionIdList()
	{
		SharedLock lock(this->_SharedMutex);

		boost::numeric::ublas::vector<std::string>* result
			= new boost::numeric::ublas::vector<std::string>(_ConnectedSessions.size());
		int i = 0;
		for(boost::unordered_map<std::string, 
			BaseSession<std::string>*>::iterator it =
			_ConnectedSessions.begin();
			it != _ConnectedSessions.end(); ++it, ++i)
		{
			result->insert_element(i, it->first);
		}
			
		return result;
	}

}}} // openuasl.server.skeleton