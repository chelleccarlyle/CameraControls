#ifndef LAB_CAMERA_H
#define LAB_CAMERA_H

#include "camera.h"
#include <math.h>  
#define PI 3.1415

using namespace std;

//Global Variables
GLfloat deltat = 0.0f;

//Mouse controls
int startx, starty;

//Zoom
int zoomx = 0, zoomy = 0;

//Keyboard controls
bool zoomActive = false;

const int screenWidth = 1280;	   // width of screen window in pixels
const int screenHeight = 720;	   // height of screen window in pixels

bool animateLight = false;
bool goldTeapotSelected = true;

int focalLengths[] = {17, 24, 35, 50, 70, 100, 200};
int focalLengthIndex = 2;
int focalLength = focalLengths[focalLengthIndex];
string focalText = "Focal length: " + to_string(focalLength) + "mm";

GLfloat lightPos[] = {0, 10, 0, 1.0f};

GLfloat gold_ambient[] = {0.24725f,0.1995f,0.0745f,1.0f};
GLfloat gold_diffuse[] = {0.75164f,0.60648f,0.22648f,1.0f};
GLfloat gold_specular[] = {0.628281f,0.555802f,0.366065f,1.0f};

GLfloat silver_ambient[] = {0.19225f,0.19225f,0.19225f,1.0f};
GLfloat silver_diffuse[] = {0.50754f,0.50754f,0.50754f,1.0f};
GLfloat silver_specular[] = {0.508273,0.508273,0.508273,1.0f};

GLfloat shininess[] = {0.4f * 128};

GLfloat plane[] = {1.0f, 1.0f, 1.0f, 1.0f};

Camera cam; // global camera object

struct TransformInfo {
    
    // holds transformation info
    Vector3    vTranslate,
    vRotate,
    vScale;
    
};

// functions //////////////////////////////////////////////////
void glRotatefv( Vector3 r ) {
    
    glRotatef( r.x, 1, 0, 0 );
    glRotatef( r.y, 0, 1, 0 );
    glRotatef( r.z, 0, 0, 1 );
    
}

void glTranslatefv( Vector3 t ) {
    
    glTranslatef( t.x, t.y, t.z);
    
}

void glScalefv( Vector3 s ) {
    
    glScalef( s.x, s.y, s.z);
    
}

void doTransform( TransformInfo & t ) {
    
    glTranslatefv( t.vTranslate );
    glRotatefv( t.vRotate );
    glScalefv( t.vScale );
    
}

TransformInfo goldTeapotTransInfo = {
    Vector3(0.0f, 0.0f, 0.0f), //translation
    Vector3(0.0f, 0.0f, 0.0f), //rotation
    Vector3(1.0f, 1.0f, 1.0f) //scale
};

TransformInfo lightTransInfo = {
    Vector3(0.0f, 0.0f, -3.0f), //translation
    Vector3(0.0f, 0.0f, 0.0f), //rotation
    Vector3(1.0f, 1.0f, 1.0f) //scale
};

TransformInfo silverTeapotTransInfo = {
    Vector3(0.0f, 0.0f, -3.0f), //translation
    Vector3(0.0f, 0.0f, 0.0f), //rotation
    Vector3(1.0f, 1.0f, 1.0f) //scale
};


#endif
