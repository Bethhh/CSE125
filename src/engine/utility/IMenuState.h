#ifndef I_MENU_STATE_H
#define I_MENU_STATE_H

#include "..\network\TCPConnection.h"

//forward declarations
class GameClient;

/*
 * IMenuState.h
 * Description: This class is the interface for all defferent menu states. Clients 
 * have multiple menu states, while the server has none. Both client and server have only one game state. 
 */
class IMenuState
{
public:
	IMenuState * changeTo;
	GameClient * gameclient;
	bool submit;

	IMenuState() : changeTo(nullptr) {}

	virtual ~IMenuState(){}

	virtual void init(GameClient*)			= 0;
	virtual void cleanup()		= 0;

	virtual void handleEvents() = 0;
	virtual void update()       = 0;

	virtual void draw()			= 0;

	//non-virtual methods
	//void changeState(IGameState *state);
	//IGameState * checkState();
};

#endif