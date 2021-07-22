#include"Menus.hpp"



void gameManager::gameLogic(RenderWindow window) {
	switch (GameState)
	{
	case gameManager::MainMenu:
	{	if(!MainMenuIsInitialized)
		break; }
	case gameManager::DefaultTetris:
	{	break; }
	case gameManager::Settings:
	{	break; };
	case gameManager::Exit:
	{	break; }
	default:
	{	break; }
	}
}