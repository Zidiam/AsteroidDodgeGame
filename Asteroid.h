#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"

class Asteroid {

    public:
        Asteroid();
        Asteroid(string modelLocation, glm::vec3 position);
        ofxAssimpModelLoader asteroid;
        glm::vec3 asteroidCoords, asteroidMove, asteroidMeshMove;
        ofMesh asteroid_mesh;
        void setupDefaults();
        void move(bool up, bool down, bool right, bool left);
        void draw();
        glm::vec3 getPosition();
        ofxAssimpModelLoader getModel();
        ofMesh getMesh();
        glm::vec3 getMeshPosition();
        void setPosition(glm::vec3 point);
};
