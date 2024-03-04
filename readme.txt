radwan ganem 322509951
moslem asaad 315646802
here we will document our changes/steps we did in the engine:

steps:
same engine from assignment 2 with all the fixes from the privious tirguls
added fixes from tirgul 6 in files: MovableGLM.cpp, MovableGLM.h, game.cpp, main.cpp
added fixes from tirgul 8 in files: game.cpp
added fixes from tirgul 9 in files: scene.cpp

InputManager.h changes
1. added cases for user input: GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_R, GLFW_KEY_L, GLFW_KEY_U
GLFW_KEY_D, GLFW_KEY_B, GLFW_KEY_F, GLFW_KEY_SPACE, GLFW_KEY_Z, GLFW_KEY_A, GLFW_KEY_M (Mixer Bonus)
2. scroll_callback() changed for Part 3.2.3

game.h and game.cpp changes:
1. added variables:
const float key_call_back_rotation_angle = -90.0f; // used for key arrows
float rotation_angle = -90.0f; // used for key inputs
#define cubeSize 3
int index_array[3][3][3]; // index array as suggested in assignment pdf
float R = 0; // used to save angle on the right and for locks
float L = 0; // used to save angle on the left and for locks
float U = 0; // used to save angle on the up and for locks
float D = 0; // used to save angle on the down and for locks
float B = 0; // used to save angle on the back and for locks
float F = 0; // used to save angle on the front and for locks

Init() function changed as in tirgul 8

2. added functions:
bool NotLocked(std::string input);
void KeyUp(); // Part 1.3
void KeyDown(); // Part 1.3
void KeyLeft(); // Part 1.3
void KeyRight(); // Part 1.3
void KeyR(); // Part 3.1.a : rotate right wall
void KeyL(); // Part 3.1.b : rotate left wall
void KeyU(); // Part 3.1.c  : rotate up wall
void KeyD(); // Part 3.1.d : rotate down wall
void KeyB(); // Part 3.1.e : rotate back wall
void KeyF(); // Part 3.1.f : rotate front wall
void KeySpace(); // Part 3.1.g : flipping rotation direction
void KeyZ(); // Part 3.1.h : dividing rotation angle by 2
void KeyA(); // Part 3.1.i  : multiply rotation angle by 2
void KeyMBonus(); // Part 7 : Mixer bonus
int GetRandomNumber(); // Generate Random number for random step
(note for the mixer bonus to run it: the user should input M, then he will be asked how many random steps he would want,
 his choice should range from 1 to 20 and mixer will run and the result should be shown in the engine and steps done will be found in mixer.txt output file

MovableGLM.cpp and MovableGLM.h changes:
1. MakeTrans() changed same as tirgul 8
2. added function GetRot() that return the transpose of rot

scene.cpp changes:
1. fixed Draw() function same as tirgul 9 to fix the background color
2. changes MouseProccessing() function for Parts 3.2.1 and 3.2.2 in the assignment

note: all explanation of implementation is in the code

