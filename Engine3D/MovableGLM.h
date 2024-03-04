#pragma once
#include "../res/includes/glm/glm.hpp"

class MovableGLM 
{
public:
	MovableGLM();
	glm::mat4 MakeTrans(const glm::mat4 &prevTransformations) const;
	glm::mat4 MakeTrans() const;
	void MyTranslate(glm::vec3 delta, int mode);
	void MyRotate(float angle, const glm::vec3 &vec, int mode);
	void MyScale(glm::vec3 scale);
	void ZeroTrans();

	glm::mat3 GetRot();
private:
	glm::mat4 trans;
	glm::mat4 rot;
	glm::mat4 scl;
	glm::mat4 trans1, trans2; // from tirgul 6
};