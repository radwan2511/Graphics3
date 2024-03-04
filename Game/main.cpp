#include "InputManager.h"
// #include "../DisplayGLFW/display.h"
#include "game.h"
#include "../res/includes/glm/glm.hpp"
#include <stb_image.h>
#include <fstream>
#include <iostream>


// function for assignment



const int DISPLAY_WIDTH = 800;
const int DISPLAY_HEIGHT = 800;


int main(int argc,char *argv[])
{	
	const float CAMERA_ANGLE = 45.0f; // from tirgul 6 and 8 פרספקטיבי
	const float NEAR = 1.0f;
	const float FAR = 100.0f;

	Game *scn = new Game(CAMERA_ANGLE,(float)DISPLAY_WIDTH/DISPLAY_HEIGHT,NEAR,FAR);
	
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	
	Init(display);
	
	scn->Init();

	display.SetScene(scn);

	


	//scn->Motion();
	//display.SwapBuffers();

	while(!display.CloseWindow())
	{
		scn->Draw(1,0,scn->BACK,true,false);
		scn->Motion();
		display.SwapBuffers(); // get buffer from back and move it to front
		display.PollEvents(); // from tirgul 7: this function allow keyword and mouse inputs
	}
	delete scn;
	return 0;
}