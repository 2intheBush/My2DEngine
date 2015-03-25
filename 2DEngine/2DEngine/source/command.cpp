 #include "command.h"

void Command::HandleInput(GLFWwindow* a_window)
{
	window = a_window;
	horzAxis = vertAxis = 0;
	if (IsKeyPressed(w)){ vertAxis += 1.f; };
	if (IsKeyPressed(s)){ vertAxis += -1.f; };
	if (IsKeyPressed(d)){ horzAxis += 1.f; };
	if (IsKeyPressed(a)){ horzAxis += -1.f; };
}