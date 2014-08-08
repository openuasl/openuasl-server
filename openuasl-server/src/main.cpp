#include <stdio.h>
#include <stdlib.h>

#include <openuasl/ucstream/UCStreamServer.h>
#include <openuasl/main_server.h>
#include <boost/thread.hpp>

void uavcam_server_thread(){
	try{
	
		openuasl::server::ucstream::UCStreamServer s(UCS_SERVER_PORT);
		s.Run();
	}catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}
}


int main(void){
	boost::thread uc_thread(&uavcam_server_thread);

	try{
		openuasl::server::main_server main_s(SERVER_PORT);
		main_s.Run();

	}catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}