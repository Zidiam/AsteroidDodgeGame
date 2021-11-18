#include "Asteroid.h"

Asteroid::Asteroid() {

}

Asteroid::Asteroid(string modelLocation, glm::vec3 position)
{
    asteroid.loadModel(modelLocation);
    asteroid.setPosition(position.x, position.y, position.z);
    setupDefaults();
}

void Asteroid::move(bool up, bool down, bool right, bool left) {
    if (up) {
        asteroidMove.y -= 5;
    }
    if (left) {
        asteroidMove.x += 5;
    }
    if (down) {
        asteroidMove.y += 5;
    }
    if (right) {
        asteroidMove.x -= 5;
    }
}

void Asteroid::draw() {
    asteroid_mesh = asteroid.getCurrentAnimatedMesh(0);

    int z = asteroid_mesh.getNumVertices();
    for (int i = 0; i < z; i++) {
        asteroid_mesh.setVertex(i, ofDefaultVertexType(asteroid_mesh.getVertex(i).x + asteroidMove.x+ asteroidMeshMove.x, asteroid_mesh.getVertex(i).y + asteroidMove.y + asteroidMeshMove.y, asteroid_mesh.getVertex(i).z + asteroidMove.z+ asteroidMeshMove.z));
    }

    asteroid.setPosition((asteroidCoords.x + asteroidMove.x), (asteroidCoords.y + asteroidMove.y), (asteroidCoords.z + asteroidMove.z));

    /*
    ofSetColor(ofColor::gray);
    asteroid_mesh.drawWireframe();

    glPointSize(2);
    ofSetColor(ofColor::white);
    asteroid_mesh.drawVertices();
    */
    asteroid.drawFaces();
}

void Asteroid::setupDefaults() {
    glm::vec3 modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75, 0);
    asteroid.setScale(.21, .21, .21);
    asteroid.setRotation(2, 180, 1, 0, 0);
    asteroid.setRotation(0, 180, 0, 1, 0);

    asteroidCoords = asteroid.getPosition();
    asteroidMove = ofVec3f(0, 0, 0);
    asteroidMeshMove = asteroid.getPosition();
}

glm::vec3 Asteroid::getPosition() {
    return asteroid.getPosition();
}

ofxAssimpModelLoader Asteroid::getModel() {
    return asteroid;
}

ofMesh Asteroid::getMesh() {
    return asteroid_mesh;
}

glm::vec3 Asteroid::getMeshPosition() {
    return asteroidMeshMove;
}

void Asteroid::setPosition(glm::vec3 point) {
    asteroid.setPosition(point.x, point.y, point.z);
    asteroidCoords = asteroid.getPosition();
    asteroidMove = ofVec3f(0, 0, 0);
    asteroidMeshMove = asteroid.getPosition();
}