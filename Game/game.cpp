#include "game.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}

Game::Game() : Scene()
{
}

Game::Game(float angle ,float relationWH, float near1, float far1) : Scene(angle,relationWH,near1,far1)
{ 	
}

void Game::Init()
{		

	AddShader("../res/shaders/pickingShader");	
	AddShader("../res/shaders/basicShader");
	
	//AddTexture("../res/textures/box0.bmp",false); //changed here
	//AddShape(Plane,-1,TRIANGLES);
	/*
	* from tirgul 6
	AddShape(Cube, -1, TRIANGLES); // from tirgul 6
	shapes[0]->MyScale(glm::vec3(0.25, 0.5, 0.25)); // MyScale: change the size of the object (cube) in (x,y,z)
	shapes[0]->MyTranslate(glm::vec3(0.5, 0, 0), 0); // MyTranslate: choose how to move the object

	pickedShape = 0;
	
	SetShapeTex(0,0); // from tergul 3
	MoveCamera(0,zTranslate,10);
	pickedShape = -1;
	*/
	// from tirgul 8
	AddTexture("../res/textures/plane.png", false);

	int size = 3;
	float distance = 1;
	int index = 0;

	for (float i = -distance; i <= distance; i += 1)
	{
		for (float j = -distance; j <= distance; j += 1)
		{
			for (float k = -distance; k <= distance; k += 1)
			{
				AddShape(Scene::Cube, -1, Scene::TRIANGLES);
				SetShapeTex(index, 0);
				shapes[index]->MyTranslate(glm::vec3(i, j, k), 0);
				shapes[index]->MyScale(glm::vec3(0.5, 0.5, 0.5));
				
				index_array[(int)i+1][(int)j+1][(int)k+1] = index; // initializing index array
				index++;
			}
		}
	}
	MoveCamera(0, zTranslate, 10);

	//ReadPixel(); //uncomment when you are reading from the z-buffer
}

void Game::Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx)
{
	Shader *s = shaders[shaderIndx];
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;
	s->Bind();
	s->SetUniformMat4f("MVP", MVP);
	s->SetUniformMat4f("Normal",Model);
	s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 0.0f);
	if(shaderIndx == 0)
		s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);
	else 
		s->SetUniform4f("lightColor",0.7f,0.8f,0.1f,1.0f);
	s->Unbind();
}

void Game::WhenRotate()
{
}

void Game::WhenTranslate()
{
}

void Game::Motion()
{
	if(isActive)
	{
		shapes[0]->MyRotate(0.01, glm::vec3(0, 1, 0), 0); // from tirgul 6 MyRotate: how to spin the object
	}
}

Game::~Game(void)
{
}



bool Game::NotLocked(std::string input)
{
	bool result = false;
	if (input == "R")
	{

		//result = L == 0 && U == 0 && D == 0 && B == 0 && F == 0;
		result = U == 0 && D == 0 && B == 0 && F == 0;

		if (!result)
		{
			std::cout << "could not rotate." << std::endl;
			return false;
		}
		//R = fmod(R + rotation_angle, 90);
		R += rotation_angle;
	}
	
	if (input == "L")
	{

		//result = R == 0 && U == 0 && D == 0 && B == 0 && F == 0;
		result =  U == 0 && D == 0 && B == 0 && F == 0;
		if (!result)
		{
			std::cout << "could not rotate." << std::endl;
			return false;
		}
		//L = fmod(L + rotation_angle, 90);
		L += rotation_angle;
	}
	if (input == "U")
	{

		//result = R == 0 && L == 0 && D == 0 && B == 0 && F == 0;
		result = R == 0 && L == 0 && B == 0 && F == 0;

		if (!result)
		{
			std::cout << "could not rotate." << std::endl;
			return false;
		}
		//U = fmod(U + rotation_angle, 90);
		U += rotation_angle;
	}
	if (input == "D")
	{

		//result = R == 0 && L == 0 && U == 0 && B == 0 && F == 0;
		result = R == 0 && L == 0 && B == 0 && F == 0;
		if (!result)
		{
			std::cout << "could not rotate." << std::endl;
			return false;
		}
		//D = fmod(D + rotation_angle, 90);
		D += rotation_angle;
	}
	if (input == "B")
	{

		//result = R == 0 && L == 0 && U == 0 && D == 0 && F == 0;
		result = R == 0 && L == 0 && U == 0 && D == 0;
		if (!result)
		{
			std::cout << "could not rotate." << std::endl;
			return false;
		}
		//B = fmod(B + rotation_angle, 90);
		B += rotation_angle;
	}
	if (input == "F")
	{

		//result = R == 0 && L == 0 && U == 0 && D == 0 && B == 0;
		result = R == 0 && L == 0 && U == 0 && D == 0;
		if (!result)
		{
			std::cout << "could not rotate." << std::endl;
			return false;
		}
		//F = fmod(F + rotation_angle, 90);
		F += rotation_angle;
	}
	
	//result = R == 0 && L == 0 && U == 0 && D == 0 && B == 0 && F == 0;
	
	return result;

}

// Part 1.3
void Game::KeyUp()
{
	// three time down will give the up face
	KeyDown();
	KeyDown();
	KeyDown();
}

// Part 1.3
void Game::KeyDown()
{
	// rotate around x
	int x = 1;
	int y = 0;
	int z = 0;
	for (int i = 0; i < cubeSize; i++)
	{
		for (int j = 0; j < cubeSize; j++)
		{
			for (int k = 0; k < cubeSize; k++)
			{
				shapes[index_array[i][j][k]]->MyRotate(key_call_back_rotation_angle, shapes[index_array[i][j][k]]->GetRot() * glm::vec3(x, y, z), 0);
			}
		}

		// update index_array values
				// Step 1: Transpose the matrix
		for (int y = 0; y < cubeSize; ++y) {
			for (int x = y + 1; x < cubeSize; ++x) {
				std::swap(index_array[i][y][x], index_array[i][x][y]);
			}
		}

		// Step 2: Reverse each row
		for (int y = 0; y < cubeSize; ++y) {
			for (int x = 0; x < cubeSize / 2; ++x) {
				std::swap(index_array[i][y][x], index_array[i][y][cubeSize - 1 - x]);
			}
		}

	}
}


// Part 1.3
void Game::KeyLeft()
{
	// rotate around y
	int x = 0;
	int y = -1;
	int z = 0;
	for (int i = 0; i < cubeSize; i++)
	{
		for (int j = 0; j < cubeSize; j++)
		{
			for (int k = 0; k < cubeSize; k++)
			{
				shapes[index_array[j][i][k]]->MyRotate(key_call_back_rotation_angle, shapes[index_array[j][i][k]]->GetRot() * glm::vec3(x, y, z), 0);
			}
		}

		// Step 1: Transpose the matrix
		for (int y = 0; y < cubeSize; ++y) {
			for (int x = y + 1; x < cubeSize; ++x) {
				std::swap(index_array[y][i][x], index_array[x][i][y]);
			}
		}

		// Step 2: Reverse each row
		for (int y = 0; y < cubeSize; ++y) {
			for (int x = 0; x < cubeSize / 2; ++x) {
				std::swap(index_array[y][i][x], index_array[y][i][cubeSize - 1 - x]);
			}
		}
	}
}

// Part 1.3
void Game::KeyRight()
{
	// three time left will give the right face
	KeyLeft();
	KeyLeft();
	KeyLeft();
}


void printIndexes(std::string str, int index_array[3][3][3])
{
	std::cout << str << std::endl;
	for (int i = 0; i < cubeSize; ++i) {
		for (int j = 0; j < cubeSize; ++j) {
			for (int k = 0; k < cubeSize; ++k) {
				std::cout << index_array[i][j][k];
				std::cout << ", ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

void Game::KeyR() // important note maybe need to change this function to F i.e from wall rotate
{

	if (NotLocked("R"))
	{
		//printIndexes("Before R", index_array);
		for (int i = 0; i < cubeSize; ++i) {
			for (int j = 0; j < cubeSize; ++j) {
				shapes[index_array[cubeSize - 1][i][j]]->MyRotate(rotation_angle, shapes[index_array[cubeSize - 1][i][j]]->GetRot() * glm::vec3(1, 0, 0), 0);
			}
			//std::cout << std::endl;
		}
		if(R <= -90.0f)
			while (R <= -90.0f)
			{
				// update index_array values
					// Step 1: Transpose the matrix
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = i + 1; j < cubeSize; ++j) {
						std::swap(index_array[cubeSize - 1][i][j], index_array[cubeSize - 1][j][i]);
					}
				}

				// Step 2: Reverse each row
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = 0; j < cubeSize / 2; ++j) {
						std::swap(index_array[cubeSize - 1][i][j], index_array[cubeSize - 1][i][cubeSize - 1 - j]);
					}
				}

				R += 90.0f;
			}
		else
			while (R >= 90.0f)
			{
				// rotate three time 90 will equal -90
				// update index_array values
					// Step 1: Transpose the matrix
				for (int times = 0; times < 3; times++) {
					for (int i = 0; i < cubeSize; ++i) {
						for (int j = i + 1; j < cubeSize; ++j) {
							std::swap(index_array[cubeSize - 1][i][j], index_array[cubeSize - 1][j][i]);
						}
					}

					// Step 2: Reverse each row
					for (int i = 0; i < cubeSize; ++i) {
						for (int j = 0; j < cubeSize / 2; ++j) {
							std::swap(index_array[cubeSize - 1][i][j], index_array[cubeSize - 1][i][cubeSize - 1 - j]);
						}
					}
				}
				R -= 90.0f;
			}
		/*if (abs(R) == 90.0f)
		{
			R = 0;
		}*/
	}
	//printIndexes("After R", index_array);

	/*
	std::cout << "after: " << std::endl;

	for (int i = 0; i < cubeSize; ++i) {
		for (int j = 0; j < cubeSize; ++j) {
			std::cout << index_array[cubeSize - 1][i][j];
			std::cout << ",";
		}
		std::cout << std::endl;
	}*/
}

void Game::KeyL()
{
	if (NotLocked("L"))
	{
		for (int i = 0; i < cubeSize; ++i) {
			for (int j = 0; j < cubeSize; ++j) {
				shapes[index_array[0][i][j]]->MyRotate(rotation_angle, shapes[index_array[0][i][j]]->GetRot()*glm::vec3(1, 0, 0), 0);
			}
		}
		if(L <= -90.0f)
			while (L <= -90.0f)
			{
				// Step 1: Transpose the matrix
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = i + 1; j < cubeSize; ++j) {
						std::swap(index_array[0][i][j], index_array[0][j][i]);
					}
				}

				// Step 2: Reverse each row
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = 0; j < cubeSize / 2; ++j) {
						std::swap(index_array[0][i][j], index_array[0][i][cubeSize - 1 - j]);
					}
				}

				L += 90.0f;
			}
		else while (L >= 90.0f)
		{
			for (int times = 0; times < 3; times++) {
				// Step 1: Transpose the matrix
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = i + 1; j < cubeSize; ++j) {
						std::swap(index_array[0][i][j], index_array[0][j][i]);
					}
				}

				// Step 2: Reverse each row
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = 0; j < cubeSize / 2; ++j) {
						std::swap(index_array[0][i][j], index_array[0][i][cubeSize - 1 - j]);
					}
				}
			}

			L -= 90.0f;
		}
		/*if (abs(L) == 90.0f)
			L = 0;*/

	}
}

void Game::KeyU()
{
	if (NotLocked("U"))
	{
		for (int i = 0; i < cubeSize; ++i) {
			for (int j = 0; j < cubeSize; ++j) {
				shapes[index_array[i][cubeSize - 1][j]]->MyRotate(rotation_angle, shapes[index_array[i][cubeSize - 1][j]]->GetRot() * glm::vec3(0, -1, 0), 0);
				
			}
		}
		if (U <= -90.0f)
			while (U <= -90.0f)
			{
				// Step 1: Transpose the matrix
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = i + 1; j < cubeSize; ++j) {
						std::swap(index_array[i][cubeSize - 1][j], index_array[j][cubeSize - 1][i]);
					}
				}

				// Step 2: Reverse each row
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = 0; j < cubeSize / 2; ++j) {
						std::swap(index_array[i][cubeSize - 1][j], index_array[i][cubeSize - 1][cubeSize - 1 - j]);
					}
				}

				U += 90.0f;
			}
		else while (U >= 90.0f)
		{
			for (int times = 0; times < 3; times++) {
				// Step 1: Transpose the matrix
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = i + 1; j < cubeSize; ++j) {
						std::swap(index_array[i][cubeSize - 1][j], index_array[j][cubeSize - 1][i]);
					}
				}

				// Step 2: Reverse each row
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = 0; j < cubeSize / 2; ++j) {
						std::swap(index_array[i][cubeSize - 1][j], index_array[i][cubeSize - 1][cubeSize - 1 - j]);
					}
				}
			}

			U -= 90.0f;

		}
		/*if (abs(U) == 90.0f)
			U = 0;*/

		//printIndexes("After U", index_array);
	}
}

void Game::KeyD()
{
	if (NotLocked("D"))
	{
		for (int i = 0; i < cubeSize; ++i) {
			for (int j = 0; j < cubeSize; ++j) {
				shapes[index_array[i][0][j]]->MyRotate(rotation_angle, shapes[index_array[i][0][j]]->GetRot()*glm::vec3(0, -1, 0), 0);
			}
		}
		if (D <= -90.0f)
			while (D <= -90.0f)
			{
				// Step 1: Transpose the matrix
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = i + 1; j < cubeSize; ++j) {
						std::swap(index_array[i][0][j], index_array[j][0][i]);
					}
				}

				// Step 2: Reverse each row
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = 0; j < cubeSize / 2; ++j) {
						std::swap(index_array[i][0][j], index_array[i][0][cubeSize - 1 - j]);
					}
				}
				D += 90.0f;
			}
		else while (D >= 90.0f)
		{
			for (int times = 0; times < 3; times++) {
				// Step 1: Transpose the matrix
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = i + 1; j < cubeSize; ++j) {
						std::swap(index_array[i][0][j], index_array[j][0][i]);
					}
				}

				// Step 2: Reverse each row
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = 0; j < cubeSize / 2; ++j) {
						std::swap(index_array[i][0][j], index_array[i][0][cubeSize - 1 - j]);
					}
				}
			}
			
			D -= 90.0f;
		}

		/*if (abs(D) == 90.0f)
			D = 0;*/
	}
}


void Game::KeyB()
{
	if (NotLocked("B"))
	{
		for (int i = 0; i < cubeSize; ++i) {
			for (int j = 0; j < cubeSize; ++j) {
				shapes[index_array[i][j][0]]->MyRotate(rotation_angle, shapes[index_array[i][j][0]]->GetRot()*glm::vec3(0, 0, 1), 0);
			}
		}
		if (B <= -90.0f)
			while (B <= -90.0f)
			{
				// Step 1: Transpose the matrix
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = i + 1; j < cubeSize; ++j) {
						std::swap(index_array[i][j][0], index_array[j][i][0]);
					}
				}

				// Step 2: Reverse each row
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = 0; j < cubeSize / 2; ++j) {
						std::swap(index_array[i][j][0], index_array[i][cubeSize - 1 - j][0]);
					}
				}

				B += 90.0f;
			}
		else while (B >= 90.0f)
		{
			for (int times = 0; times < 3; times++) {
				// Step 1: Transpose the matrix
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = i + 1; j < cubeSize; ++j) {
						std::swap(index_array[i][j][0], index_array[j][i][0]);
					}
				}

				// Step 2: Reverse each row
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = 0; j < cubeSize / 2; ++j) {
						std::swap(index_array[i][j][0], index_array[i][cubeSize - 1 - j][0]);
					}
				}
			}

			B -= 90.0f;
		}
		/*if (abs(B) == 90.0f)
			B = 0;*/
	}
}

void Game::KeyF()
{
	if (NotLocked("F"))
	{
		for (int i = 0; i < cubeSize; ++i) {
			for (int j = 0; j < cubeSize; ++j) {
				shapes[index_array[i][j][cubeSize-1]]->MyRotate(rotation_angle, shapes[index_array[i][j][cubeSize - 1]]->GetRot()*glm::vec3(0, 0, 1), 0);
			}
		}
		if (F <= -90.0f)
			while (F <= -90.0f)
			{
				// Step 1: Transpose the matrix
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = i + 1; j < cubeSize; ++j) {
						std::swap(index_array[i][j][cubeSize - 1], index_array[j][i][cubeSize - 1]);
					}
				}

				// Step 2: Reverse each row
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = 0; j < cubeSize / 2; ++j) {
						std::swap(index_array[i][j][cubeSize - 1], index_array[i][cubeSize - 1 - j][cubeSize - 1]);
					}
				}

				F += 90.0f;
			}
		else while (F >= 90.0f)
		{
			for (int times = 0; times < 3; times++) {
				// Step 1: Transpose the matrix
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = i + 1; j < cubeSize; ++j) {
						std::swap(index_array[i][j][cubeSize - 1], index_array[j][i][cubeSize - 1]);
					}
				}

				// Step 2: Reverse each row
				for (int i = 0; i < cubeSize; ++i) {
					for (int j = 0; j < cubeSize / 2; ++j) {
						std::swap(index_array[i][j][cubeSize - 1], index_array[i][cubeSize - 1 - j][cubeSize - 1]);
					}
				}
			}

			F -= 90.0f;
		}
		/*if (abs(F) == 90.0f)
			F = 0;*/
	}
}

void Game::KeySpace()
{
	rotation_angle *= -1;
}

void Game::KeyZ()
{
	if (abs(rotation_angle) == 45.0f)
	{
		std::cout << "reached min rotation angle 45." << std::endl;
	}
	else
		rotation_angle /= 2;
}

void Game::KeyA()
{
	if (abs(rotation_angle) == 180.0f)
	{
		std::cout << "reached max rotation angle 180." << std::endl;
	}
	else
		rotation_angle *= 2;
}


int Game::GetRandomNumber() {
	int min = 1;
	int max = 11;
	// Create a random number generator engine
	std::random_device rd;   // Obtain a random seed from the operating system
	std::mt19937 gen(rd());  // Standard Mersenne Twister engine
	std::uniform_int_distribution<int> distribution(min, max);  // Distribution from 1 to 13 inclusive

	// Generate a random number
	int randomNumber = distribution(gen);

	return randomNumber;
}

void Game::KeyMBonus()
{
	int randomSteps = -1;
	while (randomSteps < 0 || randomSteps > 20)
	{
		std::cout << "Please Enter The Number Of Random Steps (1 - 20) To Mix The Rubik's Cube\nYour Choice: ";
		std::cin >> randomSteps;
		if (randomSteps < 0 || randomSteps > 20)
		{
			std::cout << "Invalid random steps number, please try again..." << std::endl;
		}
	}

	std::string steps = "";
	for (int i = 0; i < randomSteps; i++)
	{
		int random = GetRandomNumber();
		if (random == 1)
		{
			KeyUp();
			steps += "rotate the Rubik's cube up\n";
		}
		if (random == 2)
		{
			KeyDown();
			steps += "rotate the Rubik's cube down\n";
		}
		if (random == 3)
		{
			KeyLeft();
			steps += "rotate the Rubik's cube left\n";
		}
		if (random == 4)
		{
			KeyRight();
			steps += "rotate the Rubik's cube right\n";
		}
		if (random == 5)
		{
			KeyR();
			steps += "rotate the right wall\n";
		}
		if (random == 6)
		{
			KeyL();
			steps += "rotate the left wall\n";
		}
		if (random == 7)
		{
			KeyU();
			steps += "rotate the up wall\n";
		}
		if (random == 8)
		{
			KeyD();
			steps += "rotate the down wall\n";
		}
		if (random == 9)
		{
			KeyB();
			steps += "rotate the back wall\n";
		}
		if (random == 10)
		{
			KeyF();
			steps += "rotate the front wall\n";
		}
		if (random == 11)
		{
			KeySpace();
			steps += "flipping the rotation direction\n";
		}
		/*if (random == 12)
		{
			KeyZ();
			steps += "dividing rotation angle by 2\n";
		}
		if (random == 13)
		{
			KeyA();
			steps += "multiply rotation angle by 2\n";
		}*/
	}

	// Open a file for writing
	std::ofstream mixer("mixer.txt");

	// Check if the file is opened successfully
	if (mixer.is_open()) {
		// Write a string to the file
		mixer << steps;

		// Close the file
		mixer.close();

		std::cout << "String written to file successfully." << std::endl;
	}
	else {
		std::cerr << "Error opening the file!" << std::endl;
	}

}

