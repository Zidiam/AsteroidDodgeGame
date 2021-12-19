#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"

class Gas {

public:
    Gas();
    Gas(string modelLocation, glm::vec3 position);
    ofxAssimpModelLoader gas;
    glm::vec3 gasMeshMove;
    ofMesh gas_mesh;
    void setupDefaults();
    void draw();
    glm::vec3 getPosition();
    ofxAssimpModelLoader getModel();
    ofMesh getMesh();
    glm::vec3 getMeshPosition();
    void setPosition(glm::vec3 point);
};
