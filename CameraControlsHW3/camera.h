#ifndef CAMERA_H
#define CAMERA_H

#include "Point3.h"
#include "Vector3.h"

class Camera {
  private:
	double viewAngle, aspect, nearDist, farDist; // view volume shape
	void setModelViewMatrix(); // tell OpenGL where the camera is	

  public:
	Camera(); // default constructor
	~Camera();
    Vector3 u,v,n;
    Point3 eye;
	void set(Point3 eye, Point3 look, Vector3 up); // like gluLookAt()	
    void slide(float delU, float delV, float delN); // slide it	
	void roll(float angle); // roll it

	void pitch(float angle); // increase pitch
	void yaw(float angle); // yaw it
    
    void setShape(float vAng, float asp, float nearD, float farD);
};

#endif
