#ifndef RGBCubeScene_H
#define RGBCubeScene_H

#include "scene.h"

#include "gl_core_4_3.hpp"

class RGBCubeScene : public Scene
{
private:
	int width, height;
	GLuint vboHandles[3];

	GLuint vaoHandle;
	GLuint programHandle;

	void linkMe(GLint vertShader, GLint fragShader);
	GLuint indexSize;
	GLuint numberOfIndices;
	GLuint indices;

public:
	RGBCubeScene();

	void initScene();
	void update(float t);
	void render();
	void resize(int, int);

};
#endif  //RGBCubeScene_H