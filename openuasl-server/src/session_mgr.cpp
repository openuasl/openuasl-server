#include <openuasl/session_mgr.h>

namespace openuasl{
namespace server{

	typedef boost::shared_lock<boost::shared_mutex> SharedLock;
	typedef boost::unique_lock<boost::shared_mutex> UniqueLock;
	
	template<class R, class U>
	bool sessoin_mgr<R,U>::insert(R resq){

		UniqueLock lock(this->_mutex);

		this->_resquer_list.erase(resq->_device_id);
		this->_resquer_list.insert(boost::unordered_map<
			std::string, resquer_session*>::value_type(resq->_device_id, resq));

		lock.unlock();

		return true;
	}

	template<class R, class U>
	bool sessoin_mgr<R,U>::insert(U uav){

		UniqueLock lock(this->_mutex);

		this->_uav_list.erase(uav->_serial_id);
		this->_uav_list.insert(
			boost::unordered_map<std::string, uav_session*>::value_type(uav->_serial_id, uav));

		lock.unlock();

		return true;
	}


}} // openuasl.server