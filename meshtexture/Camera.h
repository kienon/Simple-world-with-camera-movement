#pragma once

#ifndef CAM_H
#define CAM_H

class Point3D;
class Vector3D;

class Camera
{
public:
	Point3D	eye;
	Vector3D	u, v, n;
	Vector3D	forward;

	float height;

	void Set(Point3D e, Point3D l, Vector3D up);
	void Load_ModelView_Matrix();

	void Update(char key);

	void Slide(float du, float dv, float dn);
	void Pitch(float angle);
	void Yaw  (float angle);
	void Roll (float angle);
};

#endif