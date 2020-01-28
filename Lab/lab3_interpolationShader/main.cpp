#include "stdafx.h"

using std::string;

Scene *scene;
GLFWwindow *window;

//////////////////////////////////////////////////////////
////  Key press callback /////////////////////////////////
//////////////////////////////////////////////////////////
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
		if (scene)
			scene->animate(!(scene->animating()));
}

////////////////////////////////////////////////////////
//////  Create the scene and initialise ////////////////
////////////////////////////////////////////////////////
void initializeGL() 
{
	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	scene = new RGBCubeScene();

	scene->initScene();
}

////////////////////////////////////////////////////////
/////// Main loop  /////////////////////////////////////
////////////////////////////////////////////////////////
void mainLoop()
{
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) 
	{
		//GLUtils::checkForOpenGLError(__FILE__,__LINE__);
		scene->update((float)glfwGetTime());
		scene->render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

///////////////////////////////////////////////////////
//// resize ///////////////////////////////////////////
///////////////////////////////////////////////////////
void resizeGL(int w, int h)
{
	scene->resize(w, h);
}

///////////////////////////////////////////////////////
///////  Main  ////////////////////////////////////////
///////////////////////////////////////////////////////
int main(int argc, char *argv[])
{

	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);

	// Select OpenGL 4.3 with a forward compatible core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);

	// Open the window
	string title = "Interpolation Shader";
	window = glfwCreateWindow(500, 500, title.c_str(), NULL, NULL);
	if (!window) 
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	// Load the OpenGL functions.
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

	if (!didLoad) 
	{
		//Claen up and abort
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Initialization
	initializeGL();

	// Enter the main loop
	mainLoop();

	// Close window and terminate GLFW
	glfwTerminate();

	// Exit program
	exit(EXIT_SUCCESS);
}