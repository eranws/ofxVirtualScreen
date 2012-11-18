#pragma once
#include "ofNode.h"

class SceneItem : public ofNode
{
public:
	virtual void customDraw();
	ofColor color;
};

class Sensor : public SceneItem
{

};

class Screen: public SceneItem
{
public:
	Screen(void){}
	ofPoint getIntersectionPointWithLine(ofPoint p1, ofPoint p2);
	ofVec2f getScreenPointFromWorld(ofPoint);
};





class Scene : public ofNode
{
public:
	Scene(void);

	virtual void customDraw();

	Screen screen;
	Sensor sensor;


};


/**
* Determinant: http://mathworld.wolfram.com/Determinant.html
*/

float determinant(const ofMatrix4x4& _mat)
{
	
	float det =

		+_mat(0,0) * 
		ofMatrix3x3(
		_mat(1,1),_mat(1,2),_mat(1,3),
		_mat(2,1),_mat(2,2),_mat(2,3),
		_mat(3,1),_mat(3,2),_mat(3,3)).determinant()

		-_mat(0,1) * 
		ofMatrix3x3(
		_mat(1,0),_mat(1,2),_mat(1,3),
		_mat(2,0),_mat(2,2),_mat(2,3),
		_mat(3,0),_mat(3,2),_mat(3,3)).determinant()

		+_mat(0,2) * 
		ofMatrix3x3(
		_mat(1,0),_mat(1,1),_mat(1,3),
		_mat(2,0),_mat(2,1),_mat(2,3),
		_mat(3,0),_mat(3,1),_mat(3,3)).determinant()

		-_mat(0,3) * 
		ofMatrix3x3(
		_mat(1,0),_mat(1,1),_mat(1,2),
		_mat(2,0),_mat(2,1),_mat(2,2),
		_mat(3,0),_mat(3,1),_mat(3,2)).determinant();

	return det;
}
