#include "GameClient.h"

using std::cout;

int main(int argc, char* argv[]) {

	//initialize client
	GameClient *client = new GameClient();
    
	//run it
	client->run();
	
	delete client;
	
	return 0;
}