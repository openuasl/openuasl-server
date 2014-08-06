#include <stdio.h>
#include <stdlib.h>

#include <openuasl/ucstream/UCStreamServer.h>
#include <openuasl/main_server.h>


int main(void){
	
	try{
		openuasl::server::ucstream::UCStreamServer s(UCS_SERVER_PORT);
		s.Run();

		openuasl::server::main_server main_s(SERVER_PORT);
		main_s.Run();

	}catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}