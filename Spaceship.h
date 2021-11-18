#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"

class Spaceship {

    public:
        Spaceship(string modelLocation, glm::vec3 position);
        ofxAssimpModelLoader spaceship;
        glm::vec3 spaceshipCoords, spaceshipMove, spaceshipMeshMove;
        ofMesh spaceship_mesh;
        void setupDefaults();
        void move(bool up, bool down, bool right, bool left);
        void draw();
        glm::vec3 getPosition();
        ofxAssimpModelLoader getModel();
        ofMesh getMesh();
        glm::vec3 getMeshPosition();
        int speed, countup, countdown, countright, countleft;
};
