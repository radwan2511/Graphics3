#pragma once   //maybe should be static class
#include "display.h"
#include "game.h"


	void mouse_callback(GLFWwindow* window,int button, int action, int mods)
	{	
		if(action == GLFW_PRESS )
		{
			Game *scn = (Game*)glfwGetWindowUserPointer(window);
			double x2,y2;
			glfwGetCursorPos(window,&x2,&y2);
			scn->Picking((int)x2,(int)y2);
		}
	}
	
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Game *scn = (Game*)glfwGetWindowUserPointer(window);
		//scn->MyTranslate(glm::vec3(0,0,xoffset),0);
		scn->MyTranslate(glm::vec3(0, 0, yoffset), 0); // Part 3.2.3
		// scn->MoveCamera(0, zTranslate, 10); maybe need to implement this with move camera
		// not MyTranslate and move camera has similar efficts but they are not the same
		// רק הטלה פרסקטיבית עם 45 מעלות זווית ראייה אך עם הטלה אופטוגרפית עם 0 מעלות זווית ראיה לא נראה את זה 
	}
	
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Game *scn = (Game*)glfwGetWindowUserPointer(window);

		if(action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key)
			{
				case GLFW_KEY_ESCAPE:			
					glfwSetWindowShouldClose(window,GLFW_TRUE);
				break;
				/*case GLFW_KEY_SPACE:
					if(scn->IsActive())
						scn->Deactivate();
					else
						scn->Activate();*/
				break;

				case GLFW_KEY_UP: // Part 1.3
					//scn->MoveCamera(0,scn->zTranslate,0.4f);
					scn->KeyUp();
					break;
				case GLFW_KEY_DOWN: // Part 1.3
					//scn->shapeTransformation(scn->xGlobalRotate,-5.f);
					//cout<< "down: "<<endl;
					
					//scn->MoveCamera(0,scn->zTranslate,-0.4f);
					scn->KeyDown();
					break;
				case GLFW_KEY_LEFT: // Part 1.3
					scn->KeyLeft();
					break;
				case GLFW_KEY_RIGHT: // Part 1.3
					scn->KeyRight();
					break;

				case GLFW_KEY_R:
					scn->KeyR(); // Part 3.1.a : rotate right wall
					break;
				case GLFW_KEY_L:
					scn->KeyL(); // Part 3.1.b : rotate left wall
					break;
				case GLFW_KEY_U:
					scn->KeyU(); // Part 3.1.c : rotate up wall
					break;
				case GLFW_KEY_D:
					scn->KeyD(); // Part 3.1.d : rotate down wall
					break;
				case GLFW_KEY_B:
					scn->KeyB(); // Part 3.1.e : rotate back wall
					break;
				case GLFW_KEY_F:
					scn->KeyF(); // Part 3.1.f : rotate front wall
					break;
				case GLFW_KEY_SPACE:
					scn->KeySpace(); // Part 3.1.g : flipping rotation direction
					break;
				case GLFW_KEY_Z:
					scn->KeyZ(); // Part 3.1.h : dividing rotation angle by 2
					break;
				case GLFW_KEY_A:
					scn->KeyA(); // Part 3.1.i : multiply rotation angle by 2
					break;
				case GLFW_KEY_M: // Part 7 : Mixer bonus
					scn->KeyMBonus();
			default:
				break;
			}
		}
	}
	
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Game *scn = (Game*)glfwGetWindowUserPointer(window);

		scn->UpdatePosition((float)xpos,(float)ypos);
		if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			scn->MouseProccessing(GLFW_MOUSE_BUTTON_RIGHT);
		}
		else if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			scn->MouseProccessing(GLFW_MOUSE_BUTTON_LEFT);
		}

	}

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		Game *scn = (Game*)glfwGetWindowUserPointer(window);

		scn->Resize(width,height);
		
	}

	void Init(Display &display)
	{
		display.AddKeyCallBack(key_callback);
		display.AddMouseCallBacks(mouse_callback,scroll_callback,cursor_position_callback);
		display.AddResizeCallBack(window_size_callback);
	}
