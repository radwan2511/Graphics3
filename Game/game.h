#pragma once
#include "scene.h"
#include <random>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

class Game : public Scene
{
public:
	
	Game();
	Game(float angle,float relationWH,float near, float far);
	void Init();
	void Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx);
	void ControlPointUpdate();
	void WhenRotate();
	void WhenTranslate();
	void Motion();
	~Game(void);


	// variables for assignment
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


	// function for assignment
	bool NotLocked(std::string input);
	void KeyUp(); // Part 1.3
	void KeyDown(); // Part 1.3
	void KeyLeft(); // Part 1.3
	void KeyRight(); // Part 1.3
	void KeyR(); // Part 3.1.a
	void KeyL(); // Part 3.1.b
	void KeyU(); // Part 3.1.c
	void KeyD(); // Part 3.1.d
	void KeyB(); // Part 3.1.e
	void KeyF(); // Part 3.1.f
	void KeySpace(); // Part 3.1.g
	void KeyZ(); // Part 3.1.h
	void KeyA(); // Part 3.1.i
	void KeyMBonus(); // Part 7 Mixer
	int GetRandomNumber(); // Generate Random number for random step
};

