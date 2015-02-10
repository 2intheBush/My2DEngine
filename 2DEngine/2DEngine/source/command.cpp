#include "command.h"

void MoveUpCommand::MoveUp()
{
	InputHandler::vertMovement = 1.f;
}

void MoveDownCommand::MoveDown()
{
	InputHandler::vertMovement = -1.f;
}

void MoveLeftCommand::MoveLeft()
{
	InputHandler::horzMovement = -1.f;
}

void MoveRightCommand::MoveRight()
{
	InputHandler::horzMovement = 1.f;
}
