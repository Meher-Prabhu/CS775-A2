#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "continousDistributionCalculator.hpp"
#include "Common.hpp"
#include "Global.hpp"
#include <cstdlib>

using namespace std;

void displayFunction(){
	// Set the camera matrix (the projection matrix doesn't need to be touched unless the window is resized)
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrix(Global::camera.getWorldToCamera());
	// Clear the framebuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glutSwapBuffers();
}

void shadeClouds(){

}

void renderClouds(){

}

void renderShell(int k){

}

// This function is called whenever the window is resized
void
resizeCallback(int new_width, int new_height)
{
  // Prevent a divide by zero, when window is too short (you can't make a window of zero width)
  if (new_height == 0) new_height = 1;

  // Get the aspect ratio of the window
  float aspect_ratio = new_width / (float)new_height;

  // Set the viewport to be the entire window
  glViewport(0, 0, new_width, new_height);

  // Produce a new perspective matrix, to handle the aspect ratio
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(Global::camera.getFOV(),
                 aspect_ratio,
                 Global::camera.getNearDistance(),
                 Global::camera.getFarDistance());

  // Trigger a redraw
  glutPostRedisplay();
}

int
main(int argc, char * argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	// glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Cloud Simulation");

	// Initialize GL extensions via GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK){
		// Problem: glewInit failed, something is seriously wrong
		cerr << "Error: " << glewGetErrorString(err) << endl;
		return -1;
	}
	// Check if shaders are supported
	if (!GLEW_ARB_shader_objects){
		cerr << "Your GL driver does not support shaders! Please update your driver.\n";
		cerr << "If that doesn't work, please contact course staff immediately." << endl;
		return -1;
	}

	glutDisplayFunc(displayFunction);
	glutReshapeFunc(resizeCallback);

}