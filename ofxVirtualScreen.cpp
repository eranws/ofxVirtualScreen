#include "ofxVirtualScreen.h"
#include "ofAppRunner.h"

Scene::Scene(void)
{
	sensor.setParent(*this);
	sensor.setPosition(0, 0, 0);
	sensor.setScale(180, 50, 35);
	sensor.color = ofColor::yellow;


	screen.setScale(520.0, 326.0, 20); // visual
	//setScale(559.7, 366.0, 201.5); //physical
	
	screen.setParent(sensor);
	screen.setPosition(0, (-1) * (sensor.getScale().y + getScale().y / 2), 0);
	screen.color = ofColor::red; 

}

void Scene::customDraw()
{
	sensor.draw();
	screen.draw();
}


void SceneItem::customDraw()
{

	ofFill();
	ofSetColor(color);
	ofBox(1);

	ofNoFill();
	ofSetLineWidth(2);
	ofSetColor(color.getInverted());
	ofBox(1);

}

// http://mathworld.wolfram.com/Line-PlaneIntersection.html
ofPoint Screen::getIntersectionPointWithLine( ofPoint p4, ofPoint p5 )
{
	ofPoint hs = getScale() / 2; //= halfScale 
	ofPoint p1 = getPosition() + ofPoint(+hs.x, +hs.y, 0);
	ofPoint p2 = getPosition() + ofPoint(-hs.x, +hs.y, 0);
	ofPoint p3 = getPosition() + ofPoint(-hs.x, -hs.y, 0);
	
	float t =
		-ofMatrix4x4(
		1   ,1   ,1   ,1   ,
		p1.x,p2.x,p3.x,p4.x,
		p1.y,p2.y,p3.y,p4.y,
		p1.z,p2.z,p3.z,p4.z
		).determinant()
		/
		ofMatrix4x4(
		1   ,1   ,1   ,0   ,
		p1.x,p2.x,p3.x,p5.x-p4.x,
		p1.y,p2.y,p3.y,p5.y-p4.y,
		p1.z,p2.z,p3.z,p5.z-p4.z
		).determinant();

	ofPoint res = p4 + (p5-p4) * t;

	return res;
}

ofVec2f Screen::getScreenPointFromWorld(ofPoint p)
{
	ofPoint hs = getScale() / 2; //= halfScale 
	ofPoint dp = getPosition() + ofPoint(+hs.x, +hs.y, 0);
	
	ofVec2f res((dp.x + p.x) * ofGetScreenWidth()  / getScale().x,
		(dp.y - p.y) * ofGetScreenHeight() / getScale().y);

	return res;
}
