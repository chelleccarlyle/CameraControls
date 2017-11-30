//
//  main.cpp
//  CameraControlsHW3
//
//  Created by Chelle Cruz on 11/28/17.
//  Copyright © 2017 Chelle Cruz. All rights reserved.
//

#ifdef _WIN32
#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#elif __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/Gl.h>
#include <GLUT/GLUT.h>
#endif

#include <iostream>

#include "Lab-Camera.h"

//<<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>>>
void myInit()
{
    
    glClearColor(0.22, 0.22, 0.22, 0);  // background is black
    
    glLineWidth(1.0);
    
    glEnable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
    
    GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightIntensity);
    
    // set the view volume shape ----
    cam.setShape((2 * atan(24.0f/(2 * focalLength))) * 180 / PI, (float)screenWidth/screenHeight, 0.5f, 200.0f);
    //---------------------------
    
    //make the initial camera
    cam.set(Point3(8, 7, 8), Point3(0, 0, 0), Vector3(0, 1, 0));
}

//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>>>>>
void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
    switch(theKey)
    {
            
        case GLUT_KEY_LEFT:
                std::cout << "Camera move left" << std::endl;
                cam.slide(-0.2,0,0);
            break;
        case GLUT_KEY_RIGHT:
                std::cout << "Camera move right" << std::endl;
                cam.slide(0.2,0,0);
            break;
        case GLUT_KEY_UP:
                std::cout << "Camera move up" << std::endl;
                cam.slide(0,0.2,0);
            break;
        case GLUT_KEY_DOWN:
                std::cout << "Camera move down" << std::endl;
                cam.slide(0,-0.2,0);
            break;
        case GLUT_KEY_PAGE_UP:
                // slide camera forward
                std::cout << "Camera zoom-in" << std::endl;
                cam.slide(0,0,-0.2);
            break;
        case GLUT_KEY_PAGE_DOWN:
                // slide camera backward
                std::cout << "Camera zoom-out" << std::endl;
                cam.slide(0,0,0.2);
            break;
        default:
            break;
    }
    glutPostRedisplay(); // draw it again
}

void keyRelease(unsigned char key, int x, int y) {
    
}

void myKeyboard(unsigned char key, int x, int y)
{
//
//    int modifiers = glutGetModifiers();
//
//    cout << modifiers << endl;
    
    //TAB pressed
    if ((int)key == 9) {
        goldTeapotSelected = !goldTeapotSelected;
        string message = goldTeapotSelected ? "Gold teapot is selected" : "Silver teapot is selected";
        std::cout << message << std::endl;
    }
    
    //ESC key -- quit application
    else if ((int)key == 27) {
        glutDestroyWindow(glutGetWindow());
        exit (0);
        return;
    }
    
    switch(key) {
        //Increase focal length
        case '+':
            focalLengthIndex = (focalLengthIndex + 1) % (sizeof(focalLengths)/sizeof(focalLengths[0]));
            focalLength = focalLengths[focalLengthIndex];
            focalText = "Focal length: " + to_string(focalLength) + "mm";
            // set the view volume shape ----
            cam.setShape((2 * atan(24.0f/(2 * focalLength))) * 180 / PI, (float)screenWidth/screenHeight, 0.5f, 200.0f);
            //---------------------------
            
            //Update camera orientation
            cam.set(Point3(cam.eye.x, cam.eye.y, cam.eye.z), Point3(cam.eye.x - cam.n.x, cam.eye.y - cam.n.y, cam.eye.z - cam.n.z), Vector3(cam.v.x, cam.v.y, cam.v.z));
            break;
        //Decrease focal length
        case '-':
            if (focalLengthIndex - 1 < 0) {
                focalLengthIndex = (sizeof(focalLengths)/sizeof(focalLengths[0])) + (focalLengthIndex - 1);
            }
            else {
                focalLengthIndex--;
            }
            focalLength = focalLengths[focalLengthIndex];
            focalText = "Focal length: " + to_string(focalLength) + "mm";
            // set the view volume shape ----
            cam.setShape((2 * atan(24.0f/(2 * focalLength))) * 180 / PI, (float)screenWidth/screenHeight, 0.5f, 200.0f);
            //---------------------------
            
            //Update camera orientation
           cam.set(Point3(cam.eye.x, cam.eye.y, cam.eye.z), Point3(cam.eye.x - cam.n.x, cam.eye.y - cam.n.y, cam.eye.z - cam.n.z), Vector3(cam.v.x, cam.v.y, cam.v.z));
            break;
        case 'a':
            //Do light animation
            animateLight = !animateLight;
            break;
        case 'r':
                std::cout << "Camera roll counter clock-wise " << std::endl;
                cam.roll(1.0);
            break; // roll the camera
        case 'R':
                std::cout << "Camera roll clock-wise" << std::endl;
                cam.roll(-1.0);
            break; // roll the camera back
        case 'p':
                std::cout << "Camera pitch up" << std::endl;
                // complete pitch function in camera.cpp and invoke cam.pitch() function
                cam.pitch(1.0);
            break;
        case 'P':
                std::cout << "Camera pitch down" << std::endl;
                // complete pitch function in camera.cpp and invoke cam.pitch() function
                cam.pitch(-1.0);
            break;
        case 'y':
                std::cout << "Camera yaw left" << std::endl;
                // complete yaw function in camera.cpp and invoke cam.yaw() function
                cam.yaw(-1.0);
            break;
        case 'Y':
                std::cout << "Camera yaw right" << std::endl;
                // complete yaw function in camera.cpp and invoke cam.yaw() function
                cam.yaw(1.0);
            break;
        case 'q':
            if (goldTeapotSelected) {
                goldTeapotTransInfo.vTranslate.x += 0.1;
            }
            else {
                silverTeapotTransInfo.vTranslate.x += 0.1;
            }
            break;
        case 'Q':
            if (goldTeapotSelected) {
                goldTeapotTransInfo.vTranslate.x -= 0.1;
            }
            else {
                silverTeapotTransInfo.vTranslate.x -= 0.1;
            }
            break;
        case 'w':
            if (goldTeapotSelected) {
                goldTeapotTransInfo.vTranslate.y += 0.1;
            }
            else {
                silverTeapotTransInfo.vTranslate.y += 0.1;
            }
            break;
        case 'W':
            if (goldTeapotSelected) {
                goldTeapotTransInfo.vTranslate.y -= 0.1;
            }
            else {
                silverTeapotTransInfo.vTranslate.y -= 0.1;
            }
            break;
        case 'e':
            if (goldTeapotSelected) {
                goldTeapotTransInfo.vTranslate.z += 0.1;
            }
            else {
                silverTeapotTransInfo.vTranslate.z += 0.1;
            }
            break;
        case 'E':
            if (goldTeapotSelected) {
                goldTeapotTransInfo.vTranslate.z -= 0.1;
            }
            else {
                silverTeapotTransInfo.vTranslate.z -= 0.1;
            }
            break;
        case 'z':
            if (goldTeapotSelected) {
                goldTeapotTransInfo.vRotate.y += 1;
            }
            else {
                silverTeapotTransInfo.vRotate.y += 1;
            }
            break;
        case 'Z':
            if (goldTeapotSelected) {
                goldTeapotTransInfo.vRotate.y -= 1;
            }
            else {
                silverTeapotTransInfo.vRotate.y -= 1;
            }
            break;
        default:
            break;
    }
    glutPostRedisplay(); // draw it again
}


void myMouse(int button, int state, int x, int y) {
    
    int modifiers = glutGetModifiers();
    
    cout << modifiers << endl;
    
    if (modifiers == GLUT_ACTIVE_SHIFT) {
        zoomActive = true;
        zoomy = 0;
    }
    
    if (button == GLUT_LEFT_BUTTON) {

        if (state == GLUT_DOWN) {
            
            //Convert top left to bottom left
            y = screenHeight - y;

            startx = x;
            starty = y;
          
        }
        else if (state == GLUT_UP) {
            zoomActive = false;
        }

    }
    
}

void myMotion(int x, int y) {
    
    //Convert top left to bottom left
    y = screenHeight - y;
    int deltax = x - startx;
    int deltay = y - starty;
    
    if (zoomActive) {
        
        cout << zoomy - deltay << endl;
        
        cam.slide(0, 0, 0.1*(zoomy - deltay));

//        if (zoomy - deltay > 0) {
//            // slide camera forward
//            std::cout << "Camera zoom-in" << std::endl;
//            cam.slide(0,0,-0.2);
//        }
//        else if (zoomy - deltay < 0) {
//            // slide camera backward
//            std::cout << "Camera zoom-out" << std::endl;
//            cam.slide(0,0,0.2);
//        }
//
//        printf("Deltax: %i\n", deltax);
//        printf("Deltay: %i\n", deltay);

    }
    
    zoomy = deltay;
    
    
}

void myIdle() {
    
    if (animateLight) {
        
        deltat += 0.01;
        deltat = fmod(deltat, 1);
        
        //X
        lightPos[0] = 5 * cos(2*PI*deltat);
        //Z
        lightPos[2] = 5 * sin(2*PI*deltat);
        
    }
    
    glutPostRedisplay();
    
}

//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen
    glDisable(GL_LIGHTING);
    
    glBegin(GL_LINES);
    
    //Axes
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-5,0,0);
    glVertex3f(5,0,0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0,0,0);
    glVertex3f(0,5,0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0,0,-5);
    glVertex3f(0,0,5);
    
    //Grid
    glColor3f(0.3f, 0.3f, 0.3f);
    for (float i = -5; i <= 5; i+=0.5) {
        glVertex3f(i, 0, 5);
        glVertex3f(i, 0, -5);
        glVertex3f(5, 0, i);
        glVertex3f(-5, 0, i);
    }
    glEnd();
    
    //Display text
    glColor3f(1.0f, 1.0f, 1.0f); //Text color
    glWindowPos2i(10, 10); //Text position
    for (int i = 0; i < focalText.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, focalText[i]);
    }
    
    glEnable(GL_LIGHTING);
    
    //Place the light
    //doTransform(lightTransInfo);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    //Plane
//    glBegin(GL_POLYGON);
//
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, plane);
//    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
//    glVertex3f(5, 0.0f, 5);
//    glVertex3f(-5, 0.0f, 5);
//    glVertex3f(-5, 0.0f, -5);
//    glVertex3f(5, 0.0f, -5);
//
//    glEnd();
    
    //Gold teapot
    glPushMatrix();
    
    doTransform(goldTeapotTransInfo);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, gold_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, gold_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    
    glutSolidTeapot(1.0); // draw the teapot
    glPopMatrix();
    
    //Silver teapot
    glPushMatrix();
    
    doTransform(silverTeapotTransInfo);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, silver_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, silver_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, silver_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    
    glutSolidTeapot(1.0); // draw the teapot
    glPopMatrix();
    
    
    glutSwapBuffers();
}
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 100); // set window position on screen
    glutCreateWindow("Camera Controls - HW 3"); // open the screen window
    
    // register callback functions
    glutKeyboardFunc(myKeyboard);
    glutKeyboardUpFunc(keyRelease);
    glutSpecialFunc(mySpecialKeyboard);
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myIdle);
    
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    myInit();
    glutMainLoop();
    
    return( 0 );
}


