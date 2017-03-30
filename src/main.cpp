#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Common.hpp"
#include "Global.hpp"
#include "continousDistributionCalculator.hpp"
#include <cstdlib>

void
displayCallback()
{
  // Set the camera matrix (the projection matrix doesn't need to be touched unless the window is resized)
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrix(Global::camera.getWorldToCamera());

  // Clear the framebuffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  // // Issue OpenGL calls to draw the scene
  // if (!Global::scene.draw())
  //   exit(-1);

  // This function swaps the draw buffer and the display buffer. The current frame, in the draw buffer, is transferred to the
  // display. The previous display buffer is now the new draw buffer. Using two buffers reduces flickering, since we don't
  // draw directly to the display. (We set up double-buffering with GLUT_DOUBLE in the main function.)
  glutSwapBuffers();
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


void ShadeClouds(){

}


int
main(int argc, char * argv[])
{
    Grid grid(3,3,3,0);
    Simulation sim(3, grid);
    sim.simulate();

    // Grid finGrid = sim.getGrid(3);
    // for(int i = 0; i < 3; i++) {
    //     cout<<"x:"<<i<<endl;
    //     for(int j = 0; j < 3; j++) {
    //         for (int k = 0; k < 3; ++k){
    //             cout<<finGrid.getVoxel(i, j, k).getCloud()<<" ";
    //         }
    //         cout<<endl;
    //     }
    //     cout<<endl;
    // }

    int x=1,y=1,z=1,t=1;
    ContinousDistributionCalculator cdc(x,y,z,t);
    // Cube Center
    cdc.setSmoothingWeight(1,1,1,0,1);
    // Adjacent Face Center
    cdc.setSmoothingWeight(1,1,0,0,0.9);
    cdc.setSmoothingWeight(0,1,1,0,0.9);
    cdc.setSmoothingWeight(1,0,1,0,0.9);
    cdc.setSmoothingWeight(1,1,2,0,0.9);
    cdc.setSmoothingWeight(2,1,1,0,0.9);
    cdc.setSmoothingWeight(1,2,1,0,0.9);
    // Edge Center
    cdc.setSmoothingWeight(1,0,0,0,0.8);
    cdc.setSmoothingWeight(2,1,0,0,0.8);
    cdc.setSmoothingWeight(1,2,0,0,0.8);
    cdc.setSmoothingWeight(0,1,0,0,0.8);

    cdc.setSmoothingWeight(0,1,0,0,0.8);
    cdc.setSmoothingWeight(2,0,1,0,0.8);
    cdc.setSmoothingWeight(2,2,1,0,0.8);
    cdc.setSmoothingWeight(0,2,1,0,0.8);

    cdc.setSmoothingWeight(1,0,2,0,0.8);
    cdc.setSmoothingWeight(2,1,2,0,0.8);
    cdc.setSmoothingWeight(1,2,2,0,0.8);
    cdc.setSmoothingWeight(0,1,2,0,0.8);
    //Corners
    cdc.setSmoothingWeight(0,0,0,0,0.7);
    cdc.setSmoothingWeight(2,0,0,0,0.7);
    cdc.setSmoothingWeight(0,0,2,0,0.7);
    cdc.setSmoothingWeight(0,2,0,0,0.7);
    cdc.setSmoothingWeight(2,2,0,0,0.7);
    cdc.setSmoothingWeight(0,2,2,0,0.7);
    cdc.setSmoothingWeight(2,0,2,0,0.7);
    cdc.setSmoothingWeight(2,2,2,0,0.7);

// Cube Center
    cdc.setSmoothingWeight(1,1,1,1,1);
    // Adjacent Face Center
    cdc.setSmoothingWeight(1,1,0,1,0.9);
    cdc.setSmoothingWeight(0,1,1,1,0.9);
    cdc.setSmoothingWeight(1,0,1,1,0.9);
    cdc.setSmoothingWeight(1,1,2,1,0.9);
    cdc.setSmoothingWeight(2,1,1,1,0.9);
    cdc.setSmoothingWeight(1,2,1,1,0.9);
    // Edge Center
    cdc.setSmoothingWeight(1,0,0,1,0.8);
    cdc.setSmoothingWeight(2,1,0,1,0.8);
    cdc.setSmoothingWeight(1,2,0,1,0.8);
    cdc.setSmoothingWeight(0,1,0,1,0.8);

    cdc.setSmoothingWeight(0,1,0,1,0.8);
    cdc.setSmoothingWeight(2,0,1,1,0.8);
    cdc.setSmoothingWeight(2,2,1,1,0.8);
    cdc.setSmoothingWeight(0,2,1,1,0.8);

    cdc.setSmoothingWeight(1,0,2,1,0.8);
    cdc.setSmoothingWeight(2,1,2,1,0.8);
    cdc.setSmoothingWeight(1,2,2,1,0.8);
    cdc.setSmoothingWeight(0,1,2,1,0.8);
    //Corners
    cdc.setSmoothingWeight(0,0,0,1,0.7);
    cdc.setSmoothingWeight(2,0,0,1,0.7);
    cdc.setSmoothingWeight(0,0,2,1,0.7);
    cdc.setSmoothingWeight(0,2,0,1,0.7);
    cdc.setSmoothingWeight(2,2,0,1,0.7);
    cdc.setSmoothingWeight(0,2,2,1,0.7);
    cdc.setSmoothingWeight(2,0,2,1,0.7);
    cdc.setSmoothingWeight(2,2,2,1,0.7);
    
    ContinousGrid continousGrid = cdc.discreetToContinous(sim);

    // for(int i = 0; i < 3; i++) {
    //     for(int j = 0; j < 3; j++) {
    //         cout<<continousGrid.getVoxelValue(i, j, 2, 0)<<" ";
    //     }
    //     cout<<endl;
    // }




    // Setup for GLUT, which produces a window onto which you can draw using OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    // glutInitWindowPosition(50, 50);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cloud Animation");

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

    // Set up callbacks
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(resizeCallback);
    // Enter Glut Main Loop and wait for events
    glutMainLoop();
    return 0;
}