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

    gameSetup = true;
    //Setup Values
    glm::vec3 modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75, 0);
    left = right = up = down = false;
    lives = 3;
    gameIsLive = true;
    distance = 0;

    //Setup Positioning
    cam.setPosition(spaceship.getPosition().x, spaceship.getPosition().y + 500, spaceship.getPosition().z + 200);
    light.setPosition(cam.getPosition());

    //Create List of Asteroids:
    Asteroid tempA = Asteroid("asteroid/asteroid.obj", ofVec3f((rand() % 7000) - (rand() % 7000), (-0 * 250) - 1000, (rand() % 7000) - (rand() % 7000)));;
    cout << "LOADING\n";
    int c = 0;
    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 30; b++) {
            tempA.setPosition(ofVec3f((rand() % 7000) - (rand() % 7000), (-c * 250) - 1000, (rand() % 7000) - (rand() % 7000)));
            asteroidList.push_back(tempA);
            asteroidPositionList.push(c);
            c += 1;
        }
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
    else {
        setupGameover();
        gameIsLive = false;
        gameSetup = false;
        menuIsLive = false;
        menuSetup = false;
    }
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

    cam.end();
    light.disable();

    //Light Setup
    ofEnableLighting();
    light.enable();
    ofDisableLighting();
    ofSetColor(255, 255, 0);
    ofDisableDepthTest();
    verdana14.load("verdana.ttf", 12, false);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);
    verdana14.drawString("Distance: " + ofToString(floor(abs(spaceship.getPosition().y) / 100)), ofGetWidth() / 2 - 100, 15);

    ofPopMatrix();
    ofDisableDepthTest();
}


void ofApp::check() {
    glm::vec3 tempSpaceship = spaceship.getPosition();
    int remove = -1;
    /*
    int pos = spaceship.getPosition().y;
    if (pos % 500 == 0) {
        Asteroid temp = Asteroid("asteroid/asteroid.obj", ofVec3f(tempSpaceship.x + (rand() % 7000) - (rand() % 7000), tempSpaceship.y - (rand() % 5000) - 5000, tempSpaceship.z + (rand() % 7000) - (rand() % 7000)));
        asteroidList.push_back(temp);
        asteroidPointsList.push_back(temp.getPosition());
    }
    */
    //Can speed to check closest asteroid
    if (asteroidPositionList.size() > 0){
        int position = asteroidPositionList.front();
        int testDistance = glm::distance(tempSpaceship, asteroidList[position].getPosition());
        int pastDistance = tempSpaceship.y - asteroidList[position].getPosition().y;
        int position2 = asteroidPositionList.back();

        if (pastDistance < 0) {
            asteroidList[position].setPosition(ofVec3f(tempSpaceship.x + (rand() % 7000) - (rand() % 7000), asteroidList[position2].getPosition().y - 250, tempSpaceship.z + (rand() % 7000) - (rand() % 7000)));
            asteroidPositionList.pop();
            asteroidPositionList.push(position);
        }
        else if (testDistance < 100 && checkCollision(spaceship, asteroidList[position])) {
            lives -= 1;
            asteroidList[position].setPosition(ofVec3f(tempSpaceship.x + (rand() % 7000) - (rand() % 7000), asteroidList[position2].getPosition().y - 250, tempSpaceship.z + (rand() % 7000) - (rand() % 7000)));
            asteroidPositionList.pop();
            asteroidPositionList.push(position);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    //Movement
    spaceship.move(up, down, right, left);

    cam.setPosition(spaceship.getPosition().x, spaceship.getPosition().y + 500, spaceship.getPosition().z + 200);
    //light.setPosition(cam.getPosition());  
    
    check();
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
    float nearestDistance = 0;

    int nearestIndex = 0;
    float distance;
    int realdistance;
    glm::vec3 cur, cur2;
    for (int i = 0; i < n; i += 5) {
        for (int z = 0; z < n2; z += 5) {
            cur = object1Mesh.getVertex(i);
            cur2 = object2Mesh.getVertex(z);
            distance = glm::distance(cur, cur2);
            if (i == 0 || distance < nearestDistance) {
                nearestDistance = distance;
                nearestVertex1 = cur;
                nearestVertex2 = cur2;
                nearestIndex = i;
                realdistance = (abs(abs(nearestVertex1.x) - abs(nearestVertex2.x)) + abs(abs(nearestVertex1.y) - abs(nearestVertex2.y)) + abs(abs(nearestVertex1.z) - abs(nearestVertex2.z))) / 3;
                if (realdistance <= 3) {
                    break;
                }
            }
        }
    }

    realdistance = (abs(abs(nearestVertex1.x) - abs(nearestVertex2.x)) + abs(abs(nearestVertex1.y) - abs(nearestVertex2.y)) + abs(abs(nearestVertex1.z) - abs(nearestVertex2.z))) / 3;

    if (realdistance <= 3) {
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
