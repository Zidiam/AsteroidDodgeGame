#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
#include "../Spaceship.h"
#include "../Asteroid.h"
#include "../Gas.h"
#include <iostream>
#include <vector>

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		bool checkCollision(Spaceship object1, Asteroid object2);
		bool checkCollision2(Spaceship object1, Gas object2);
		void check();
		void pointsCheck();
		void liveGame();
		void setupGame();
		void liveMenu();
		void setupMenu();
		void liveGameover();
		void setupGameover();
		//Spaceship ship;
		Spaceship spaceship = Spaceship("spaceship/Feisar_Ship.3DS", ofVec3f(0, 0, 0));

		//Astroid Array
		queue<int> asteroidPositionList;
		vector<Asteroid> asteroidList, asteroidDummyList;

		//Gas Array
		queue<int> gasPositionList;
		vector<Gas> gasList, gasDummyList;

		//Light
		ofLight	light;

		//Camera
		ofEasyCam cam;

		//Boolean
		bool left, right, up, down;
		bool gameIsLive, gameSetup;
		bool menuIsLive, menuSetup;

		//Integers
		int lives, density;

		//Distance
		glm::vec3 nearestVertex1, nearestVertex2, asteroidCoords, asteroidMove;

		//Mouse
		glm::vec2 mouse;

		//Images
		ofImage spaceBackground, heart, title, playImg, party1Img, party2Img, retryImg, fuelImg;

		//Buttons
		ofRectangle playRect, retryRect;

		//Font
		ofTrueTypeFont verdana14;
};
