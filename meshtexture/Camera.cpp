#include "Vector3D.h"
#include "Point3D.h"
#include "Camera.h"
#include <windows.h>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>

#define PI						3.14159265
#define D_to_R					(PI / 180.0)

void Camera::Load_ModelView_Matrix()
{
	float m[16];

	Vector3D eye_vector(eye.x, eye.y, eye.z);
	float dx = -(eye_vector.DotProduct(u));
	float dy = -(eye_vector.DotProduct(v));
	float dz = -(eye_vector.DotProduct(n));

	m[0] = u.x; m[4] = u.y; m[8] = u.z;  m[12] = dx;
	m[1] = v.x; m[5] = v.y; m[9] = v.z;  m[13] = dy;
	m[2] = n.x; m[6] = n.y; m[10] = n.z; m[14] = dz;
	m[3] = 0.0; m[7] = 0.0; m[11] = 0.0; m[15] = 1.0;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(m);
}

void Camera::Set(Point3D e, Point3D l, Vector3D up)
{
	eye.set(e.x, e.y, e.z);

	n.set(e.x - l.x, e.y - l.y, e.z - l.z);
	n = n.Unit();
	up = up.Unit();
	u = up.CrossProduct(n);
	v = n.CrossProduct(u);

	Load_ModelView_Matrix();

//	gluLookAt(e.x, e.y, e.z, l.x, l.y, l.z, up.x, up.y, up.z);

}


void Camera::Update(char key)
{
	// (Remember, increments are in the opposite direction
	//  because the Camera transform is an inverse transform)
	int slide_flag = 0;
	int roll_flag  = 0;
	int yaw_flag   = 0;
	int pitch_flag = 0;

	float du = 0.0, dv = 0.0, dn = 0.0;
	float ua = 0.0, va = 0.0, na = 0.0;

	// GET INPUT /////////////////////////////////////////////////

	double slide_inc = 1.5;
	double pitch_inc = 2.0;
	double roll_inc = 2.0;
	double yaw_inc = 2.0;


	// Camera Slides
	if(key == 'q')	{du += slide_inc; slide_flag = 1;}
	if(key == 'w')	{du -= slide_inc; slide_flag = 1;}
	if(key == 'a')	{dv += slide_inc; slide_flag = 1;}
	if(key == 's')	{dv -= slide_inc; slide_flag = 1;}
	if(key == 'z')	{dn += slide_inc; slide_flag = 1;}
	if(key == 'x')	{dn -= slide_inc; slide_flag = 1;}

	// Camera Rotations
	if(key == 'o')	{ua += pitch_inc; pitch_flag = 1;}	
	if(key == 'p')	{ua -= pitch_inc; pitch_flag = 1;}	
	if(key == 'k')	{va += yaw_inc;   yaw_flag = 1;}	
	if(key == 'l')	{va -= yaw_inc;   yaw_flag = 1;}	
	if(key == 'n')	{na += roll_inc;  roll_flag = 1;}	
	if(key == 'm')	{na -= roll_inc;  roll_flag = 1;}	

	// PERFORM TRANSFORMATIONS (IF NECCESARY) //////////////////////

	//if(abs(dy) > abs(dx)) yaw_flag = 0;
	//if(abs(dx) > abs(dy)) pitch_flag = 0;

	if(slide_flag) Slide(du, dv, dn);
	if(roll_flag)  Roll(na);
	if(pitch_flag) Pitch(ua);
	if(yaw_flag)   Yaw(va);

}


void Camera::Roll(float angle)
{
	float sn  = sin(D_to_R * angle);
	float cs  = cos(D_to_R * angle);

	Vector3D t = u;

	u.set( cs * u.x + sn * v.x, cs * u.y + sn * v.y, cs * u.z + sn * v.z);
	v.set(-sn * t.x + cs * v.x,-sn * t.y + cs * v.y,-sn * t.z + cs * v.z); 

	Load_ModelView_Matrix();
}

void Camera::Pitch(float angle)
{
	float sn  = sin(D_to_R * angle);
	float cs  = cos(D_to_R * angle);

	Vector3D t = v;

	v.set( cs * v.x + sn * n.x, cs * v.y + sn * n.y, cs * v.z + sn * n.z);
	n.set(-sn * t.x + cs * n.x,-sn * t.y + cs * n.y,-sn * t.z + cs * n.z); 

	Load_ModelView_Matrix();	
}

void Camera::Yaw(float angle)
{
	float sn  = sin(D_to_R * angle);
	float cs  = cos(D_to_R * angle);

	Vector3D t = n;

	n.set( cs * n.x + sn * u.x, cs * n.y + sn * u.y, cs * n.z + sn * u.z);
	u.set(-sn * t.x + cs * u.x,-sn * t.y + cs * u.y,-sn * t.z + cs * u.z); 

	float x = cs * forward.x + sn * forward.z;
	float z = -sn * forward.x + cs * forward.z;

	forward.set(x, 0.0, z);

	Load_ModelView_Matrix();	
}

void Camera::Slide(float du, float dv, float dn)
{
	eye.x += du * u.x + dv * v.x + dn * n.x;
	eye.y += du * u.y + dv * v.y + dn * n.y;
	eye.z += du * u.z + dv * v.z + dn * n.z;

	Load_ModelView_Matrix();
}
