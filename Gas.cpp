#include "Gas.h"

Gas::Gas() {

}

Gas::Gas(string modelLocation, glm::vec3 position)
{
    gas.loadModel(modelLocation);
    gas.setPosition(position.x, position.y, position.z);
    setupDefaults();
}

void Gas::draw() {
    /*
    ofSetColor(ofColor::gray);
    gas_mesh.drawWireframe();

    glPointSize(2);
    ofSetColor(ofColor::white);
    gas_mesh.drawVertices();
    */
    gas.drawFaces();
}

void Gas::setupDefaults() {
    glm::vec3 modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75, 0);
    gas.setScale(.21, .21, .21);
    gas.setRotation(2, 180, 1, 0, 0);
    gas.setRotation(0, 180, 0, 1, 0);

    gasMeshMove = gas.getPosition();
}

glm::vec3 Gas::getPosition() {
    return gas.getPosition();
}

ofxAssimpModelLoader Gas::getModel() {
    return gas;
}

ofMesh Gas::getMesh() {
    gas_mesh = gas.getCurrentAnimatedMesh(0);
    int z = gas_mesh.getNumVertices();
    for (int i = 0; i < z; i++) {
        gas_mesh.setVertex(i, ofDefaultVertexType(gas_mesh.getVertex(i).x + gasMeshMove.x, gas_mesh.getVertex(i).y + gasMeshMove.y, gas_mesh.getVertex(i).z + gasMeshMove.z));
    }
    return gas_mesh;
}

glm::vec3 Gas::getMeshPosition() {
    return gasMeshMove;
}

void Gas::setPosition(glm::vec3 point) {
    gas.setPosition(point.x, point.y, point.z);
    gasMeshMove = gas.getPosition();
}