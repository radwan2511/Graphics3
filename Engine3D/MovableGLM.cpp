#include "MovableGLM.h"
#include <stdio.h>
#include "../res/includes/glm/gtc/matrix_transform.hpp"
#include "../res/includes/glm/gtc/quaternion.hpp"


static void printMat(const glm::mat4 mat)
{
	printf(" matrix: \n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%f ", mat[j][i]);
		printf("\n");
	}
}

MovableGLM::MovableGLM()
{
	ZeroTrans();
}

glm::mat4 MovableGLM::MakeTrans(const glm::mat4 &prevTransformations) const
{
	return prevTransformations * MakeTrans();
}

glm::mat4 MovableGLM::MakeTrans() const
{
	//return   trans * rot * scl; // from tirgul 6
	// trans * rot * scl -> spining in place
	// scl * rot * translate -> spining around the other center
	return   rot * trans * scl; // from tirgul 8
	//return   trans * scl * rot; // from tirgul 9
}

void MovableGLM::MyTranslate(glm::vec3 delta,int mode)
{
	trans = glm::translate(trans,delta);
}

void  MovableGLM::MyRotate(float angle,const glm::vec3 &vec,int mode)
{
	rot = glm::rotate(rot,angle,vec); // from tirgul 6 use radian angles
}
	
void  MovableGLM::MyScale(glm::vec3 scale)
{
	scl = glm::scale(scl,scale);
}

void MovableGLM::ZeroTrans()
{
	trans = glm::mat4(1);
	rot = glm::mat4(1);
	scl = glm::mat4(1);
}

glm::mat3 MovableGLM::GetRot()
{
	//return rot; 
	// return transpose of rot
	return glm::mat3(
		glm::vec3(rot[0][0], rot[1][0], rot[2][0]),
		glm::vec3(rot[0][1], rot[1][1], rot[2][1]),
		glm::vec3(rot[0][2], rot[1][2], rot[2][2])
	);;
}