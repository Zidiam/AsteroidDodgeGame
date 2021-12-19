#include "ofApp.h"
#include <time.h>
/*
Loads in the same 3D penguin model in various file types. Demonstrates how to load in a model using both ofMesh and ofxAssimpModelLoader.
*/

//--------------------------------------------------------------
void ofApp::setup() {
    //Random Setup
    srand((unsigned)time(NULL));

    //Setup Images
    spaceBackground.load("images/space.png");

    //Setup Boolean
    gameIsLive = false;
    gameSetup = false;
    menuIsLive = true;
    menuSetup = false;

    //Setup Camera Positioning
    cam.rotate(90, cam.getSideDir());
    cam.rotate(180, cam.getUpDir());
}

void ofApp::setupGameover() {
    //Data
    menuSetup = true;

    //Images
    party1Img.load("images/party1.png");
    party2Img.load("images/party2.png");
    retryImg.load("images/retry.png");

    //Rectangles
    playRect.set(ofGetWidth() / 2 - (retryImg.getWidth()-20) / 2, ofGetHeight() / 2 - (retryImg.getHeight() + 5) / 2, retryImg.getWidth(), retryImg.getHeight() + 5); // x, y, width, height
}

void ofApp::liveGameover() {
    //GUI Setup
    ofEnableLighting();
    light.enable();
    ofDisableLighting();
    ofSetColor(255, 255, 255);
    ofDisableDepthTest();

    ofTrueTypeFont::setGlobalDpi(72);

    spaceBackground.draw(0, 0, ofGetWidth(), ofGetHeight());
    party1Img.draw(50, ofGetHeight()-300, 250, 250);
    party2Img.draw(ofGetWidth() - 300, ofGetHeight() - 300, 250, 250);

    verdana14.load("verdana.ttf", 25, false);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);
    verdana14.drawString("TOTAL DISTANCE", ofGetWidth()/2 - 100, 150);

    ofSetColor(255, 255, 0);
    verdana14.load("verdana.ttf", 80, false);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);

    string temp = ofToString(abs(spaceship.getPosition().y)/100);
    int temp1 = ofToString(abs(spaceship.getPosition().y) / 100).length();
    for (int z = 0; z < 14-temp1; z++) {
        temp = temp + "#";
    }

    verdana14.drawString(temp, 50, 100);
}

void ofApp::setupMenu() {
    //Data
    menuSetup = true;
    
    //Images
    title.load("images/title.png");
    playImg.load("images/play.png");

    //Rectangles
    playRect.set(ofGetWidth() / 2 - (playImg.getWidth()+10) / 2, ofGetHeight() / 2 - (playImg.getHeight()+5) / 2, playImg.getWidth()+10, playImg.getHeight()+5); // x, y, width, height
}

void ofApp::liveMenu() {
    spaceBackground.draw(0, 0, ofGetWidth(), ofGetHeight());
    title.draw(50, 0, ofGetWidth()-100, ofGetHeight()/5);

    if (playRect.inside(mouse.x, mouse.y)) {
        ofSetLineWidth(1);
        ofNoFill();
        ofDrawRectangle(playRect);
    }

    playImg.draw(ofGetWidth()/2 - 208/2, ofGetHeight()/2 - 117/2, 208, 117);
}

void ofApp::setupGame() {
    //Setup Ship
    spaceship = Spaceship("spaceship/Feisar_Ship.3DS", ofVec3f(0, 0, 0));
    //Setup Images
    heart.load("images/heart.png");
    fuelImg.load("images/fuel.png");

    gameSetup = true;
    //Setup Values
    glm::vec3 modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75, 0);
    left = right = up = down = false;
    lives = 3;
    gameIsLive = true;
    density = 25;
    //Setup Positioning
    cam.setPosition(spaceship.getPosition().x, spaceship.getPosition().y + 500, spaceship.getPosition().z + 200);
    light.setPosition(cam.getPosition());

    //Create List of Asteroids:
    Asteroid tempA = Asteroid("asteroid/asteroid.obj", ofVec3f(0,0,0));
    cout << "LOADING\n";
    int c = 0;
    for (int a = 0; a < 100; a++) {
        tempA.setPosition(ofVec3f((rand() % 3000) - (rand() % 3000), (-c * density) - 1000, (rand() % 3000) - (rand() % 3000)));
        asteroidList.push_back(tempA);
        asteroidPositionList.push(c);
        c += 1;
    }

    //Create List of Gas:
    Gas tempB = Gas("gas/gas.obj", ofVec3f(0, 0, 0));
    c = 0;
    for (int a = 0; a < 10; a++) {
        tempB.setPosition(ofVec3f((rand() % 3000) - (rand() % 3000), (-c * 20000) - 5000, (rand() % 3000) - (rand() % 3000)));
        gasList.push_back(tempB);
        gasPositionList.push(c);
        c += 1;
    }
}

void ofApp::liveGame() {
    //Light Setup
    ofEnableLighting();
    light.enable();
    ofDisableLighting();
    ofSetColor(255, 255, 255);
    ofDisableDepthTest();

    spaceBackground.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    ofEnableDepthTest();

    //Start Light
    light.enable();

    //Start Camera
    cam.begin();

    //Draw Objects
    spaceship.draw();
    for (int a = 0; a < asteroidList.size(); a++) {
        asteroidList[a].draw();
    }
    for (int a = 0; a < asteroidDummyList.size(); a++) {
        asteroidDummyList[a].draw();
    }
    for (int a = 0; a < gasList.size(); a++) {
        gasList[a].draw();
    }
    for (int a = 0; a < gasDummyList.size(); a++) {
        gasDummyList[a].draw();
    }

    cam.end();
    light.disable();

    //Light Setup
    ofEnableLighting();
    light.enable();
    ofDisableLighting();
    ofSetColor(255, 255, 0);
    ofDisableDepthTest();
    ofPopMatrix();

    //Distance
    verdana14.load("verdana.ttf", 12, false);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);
    verdana14.drawString("Distance: " + ofToString(floor(abs(spaceship.getPosition().y) / 100)), ofGetWidth() / 2 - 100, 15);

    //Images
    if (lives == 3) {
        heart.draw(ofGetWidth() - 100, 0, 100, 100);
        heart.draw(ofGetWidth() - 200, 0, 100, 100);
        heart.draw(ofGetWidth() - 300, 0, 100, 100);
    }
    else if (lives == 2) {
        heart.draw(ofGetWidth() - 100, 0, 100, 100);
        heart.draw(ofGetWidth() - 200, 0, 100, 100);
    }
    else if (lives == 1) {
        heart.draw(ofGetWidth() - 100, 0, 100, 100);
    }
    if (lives == 0 || spaceship.fuel <= 0){
        setupGameover();
        gameIsLive = false;
        gameSetup = false;
        menuIsLive = false;
        menuSetup = false;
    }
    fuelImg.draw(ofGetWidth() - 50, ofGetHeight() - 25, 25, 25);

    //Draw Fuel Bar
    ofNoFill(); 
    ofSetColor(0, 0, 0);
    ofDrawRectangle(ofGetWidth() - 25, ofGetHeight() - 150, 23, 148);
    ofFill();
    ofSetColor(255, 255, 255);
    ofDrawRectangle(ofGetWidth() - 24, ofGetHeight() - 148, 21, 144);
    ofSetColor(0, 255, 0);
    ofDrawRectangle(ofGetWidth() - 24, ofGetHeight() - 148 + spaceship.fuelUsed, 21, 144 - spaceship.fuelUsed);
}


void ofApp::check() {
    if (asteroidPositionList.size() > 0) {
        glm::vec3 tempSpaceship = spaceship.getPosition();
        int position = asteroidPositionList.front();
        int position2 = asteroidList[asteroidPositionList.back()].getPosition().y;
        int pastDistance = tempSpaceship.y - asteroidList[position].getPosition().y;
        bool destroy = false;
        if (asteroidDummyList.size() > 0 && tempSpaceship.y - asteroidDummyList.front().getPosition().y < -500) {
            asteroidDummyList.erase(asteroidDummyList.begin());
        }
        if (checkCollision(spaceship, asteroidList[position])) {
            lives -= 1;
            destroy = true;
        }
        else if (pastDistance < 0) {
            asteroidDummyList.push_back(asteroidList[position]);
            destroy = true;
        }
        if (destroy) {
            glm::vec3 newPosition;
            int pointx = 0;
            int pointy = position2 - density;
            int pointz = 0;

            if (left) {
                pointx = tempSpaceship.x + (rand() % 2000) + (rand() % 2000);
            }
            else if (right) {
                pointx = tempSpaceship.x - (rand() % 2000) - (rand() % 2000);
            }
            if (up) {
                pointz = tempSpaceship.z + (rand() % 2000) + (rand() % 2000);
            }
            else if (down) {
                pointz = tempSpaceship.z - (rand() % 2000) - (rand() % 2000);
            }
            if (pointx == 0) {
                pointx = tempSpaceship.x + (rand() % 2000) - (rand() % 2000);
            }
            if (pointz == 0) {
                pointz = tempSpaceship.z + (rand() % 2000) - (rand() % 2000);
            }
            if (rand() % 3 == 1) {
                newPosition = ofVec3f(tempSpaceship.x + (rand() % 1500) - (rand() % 1500), position2 - density, tempSpaceship.z + (rand() % 1500) - (rand() % 1500));
            }
            else {
                newPosition = ofVec3f(pointx, pointy, pointz);
            }
                
            asteroidList[position].setPosition(newPosition);
            asteroidPositionList.pop();
            asteroidPositionList.push(position);
        }
    }

    if (gasPositionList.size() > 0) {
        glm::vec3 tempSpaceship = spaceship.getPosition();
        int position = gasPositionList.front();
        int position2 = gasList[gasPositionList.back()].getPosition().y;
        int pastDistance = tempSpaceship.y - gasList[position].getPosition().y;
        bool destroy = false;
        if (gasDummyList.size() > 0 && tempSpaceship.y - gasDummyList.front().getPosition().y < -500) {
            gasDummyList.erase(gasDummyList.begin());
        }
        if (checkCollision2(spaceship, gasList[position])) {
            spaceship.fuel = 144;
            spaceship.fuelUsed = 0;
            destroy = true;
        }
        else if (pastDistance < 0) {
            gasDummyList.push_back(gasList[position]);
            destroy = true;
        }
        if (destroy) {
            glm::vec3 newPosition = ofVec3f(tempSpaceship.x + (rand() % 1500) - (rand() % 1500), position2 - 20000, tempSpaceship.z + (rand() % 1500) - (rand() % 1500));
            gasList[position].setPosition(newPosition);
            gasPositionList.pop();
            gasPositionList.push(position);
        }
    }

}

void ofApp::pointsCheck() {
    int dis = floor(abs(spaceship.getPosition().y) / 100);
}

//--------------------------------------------------------------
void ofApp::update() {
    //Movement
    spaceship.move(up, down, right, left);

    cam.setPosition(spaceship.getPosition().x, spaceship.getPosition().y + 500, spaceship.getPosition().z + 200);
    //light.setPosition(cam.getPosition());  
    
    check();
    pointsCheck();
}

//--------------------------------------------------------------
void ofApp::draw() {
    //Background
    ofBackgroundGradient(ofColor::white, ofColor::gray);

    if (menuIsLive) {
        if (menuSetup == false) {
            setupMenu();
        }
        liveMenu();
    }
    else if (gameIsLive) {
        if (gameSetup == false) {
            setupGame();
        }
        liveGame();
    }
    else {
        liveGameover();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (char(key) == char('w') || key == OF_KEY_UP) {
        up = true;
    }
    if (char(key) == char('a') || key == OF_KEY_LEFT) {
        left = true;
    }
    if (char(key) == char('s') || key == OF_KEY_DOWN) {
        down = true;
    }
    if (char(key) == char('d') || key == OF_KEY_RIGHT) {
        right = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if (char(key) == char('w') || key == OF_KEY_UP) {
        up = false;
    }
    if (char(key) == char('a') || key == OF_KEY_LEFT) {
        left = false;
    }
    if (char(key) == char('s') || key == OF_KEY_DOWN) {
        down = false;
    }
    if (char(key) == char('d') || key == OF_KEY_RIGHT) {
        right = false;
    }
}

bool ofApp::checkCollision(Spaceship object1, Asteroid object2) {
    ofMesh object1Mesh = object1.getMesh();
    ofMesh object2Mesh = object2.getMesh();

    int n = object1Mesh.getNumVertices();
    int n2 = object2Mesh.getNumVertices();
    float realdistance;
    glm::vec3 cur, cur2;

    for (int i = 0; i < n; i += 5) {
        for (int z = 0; z < n2; z += 5) {
            cur = object1Mesh.getVertex(i);
            cur2 = object2Mesh.getVertex(z);
            realdistance = ((abs(cur.x - cur2.x) + abs(cur.y - cur2.y) + abs(cur.z - cur2.z)) / 3);
            if (realdistance <= 5.0) {
                return true;
            }
        }
        
    }

    return false;
}

bool ofApp::checkCollision2(Spaceship object1, Gas object2) {
    float realdistance;
    glm::vec3 cur, cur2;

    cur = object1.getPosition();
    cur2 = object2.getPosition();
    realdistance = ((abs(cur.x - cur2.x) + abs(cur.y - cur2.y) + abs(cur.z - cur2.z)) / 3);
    if (realdistance <= 50) {
        return true;
    }

    return false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    mouse = ofVec2f(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    if (playRect.inside(x, y)) {
        gameIsLive = true;
        menuIsLive = false;
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}