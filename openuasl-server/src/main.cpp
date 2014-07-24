#include <stdio.h>
#include <stdlib.h>

#include <openuasl/ucstream/UCStreamServer.h>


int main(void){
	
	openuasl::server::ucstream::UCStreamServer s(UCS_SERVER_PORT);

	s.Run();


	return EXIT_SUCCESS;
}