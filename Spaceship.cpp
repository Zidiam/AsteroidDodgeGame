#include "Spaceship.h"

Spaceship::Spaceship(string modelLocation, glm::vec3 position)
{
    spaceship.loadModel(modelLocation);
    spaceship.setPosition(position.x, position.y, position.z);
    setupDefaults();
}

void Spaceship::move(bool up, bool down, bool right, bool left) {
    spaceshipMove.y -= speed;
    if (up && countup == speed) {
        spaceshipMove.z += speed;
    }
    else if (up && countup < speed) {
        spaceshipMove.z += countup;
        countup += 1;
    }
    else if (countup > 0) {
        spaceshipMove.z += countup;
        countup -= 1;
    }

    if (down && countdown == speed) {
        spaceshipMove.z -= speed;
    }
    else if (down && countdown < speed) {
        spaceshipMove.z -= countdown;
        countdown += 1;
    }
    else if (countdown > 0) {
        spaceshipMove.z -= countdown;
        countdown -= 1;
    }

    if (left && countleft == speed) {
        spaceshipMove.x += speed;
    }
    else if (left && countleft < speed) {
        spaceshipMove.x += countleft;
        countleft += 1;
    }
    else if (countleft > 0) {
        spaceshipMove.x += countleft;
        countleft -= 1;
    }

    if (right && countright == speed) {
        spaceshipMove.x -= speed;
    }
    else if (right && countright < speed) {
        spaceshipMove.x -= countright;
        countright += 1;
    }
    else if (countright > 0) {
        spaceshipMove.x -= countright;
        countright -= 1;
    }
}

void Spaceship::draw() {
    spaceship_mesh = spaceship.getCurrentAnimatedMesh(0);

    int z = spaceship_mesh.getNumVertices();
    for (int i = 0; i < z; i++) {
        spaceship_mesh.setVertex(i, ofDefaultVertexType(spaceship_mesh.getVertex(i).x + spaceshipMove.x + spaceshipMeshMove.x, spaceship_mesh.getVertex(i).y + spaceshipMove.y + spaceshipMeshMove.y, spaceship_mesh.getVertex(i).z + spaceshipMove.z + spaceshipMeshMove.z));
    }

    spaceship.setPosition((spaceshipCoords.x + spaceshipMove.x), (spaceshipCoords.y + spaceshipMove.y), (spaceshipCoords.z + spaceshipMove.z));

    /*
    ofSetColor(ofColor::gray);
    spaceship_mesh.drawWireframe();

    glPointSize(2);
    ofSetColor(ofColor::white);
    spaceship_mesh.drawVertices();
    */
    spaceship.drawFaces();
}

void Spaceship::setupDefaults() {
    spaceship.setScale(.68, .68, .68);
    spaceship.setRotation(2, 90, 1, 0, 0);
    spaceship.setRotation(0, 180, 0, 0, 1);

    spaceshipCoords = spaceship.getPosition();
    spaceshipMove = ofVec3f(0, 0, 0);
    spaceshipMeshMove = spaceship.getPosition();

    countup = countdown = countright = countleft = 0;
    speed = 25;
}

glm::vec3 Spaceship::getPosition() {
    return spaceship.getPosition();
}

glm::vec3 Spaceship::getMeshPosition() {
    return spaceshipMeshMove;
}

ofxAssimpModelLoader Spaceship::getModel() {
    return spaceship;
}

ofMesh Spaceship::getMesh() {
    return spaceship_mesh;
}