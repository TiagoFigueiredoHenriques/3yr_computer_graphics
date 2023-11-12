#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	glEnable(GL_DEPTH_TEST);
	ofBackground(0.05, 0.05, 0.05);

	//set floor mesh parameters
	nRows = 11;
	nColumns = 21;

	//initialize building parameters
	for (int r = 0; r < nRows; r++) {
		for (int c = 0; c < nColumns; c++) {
			building b;

			//randomly determine building type
			float probability = ofRandom(0, 100);
			if (probability < 60) {
				b.buildingType = 0;
			}
			else if (probability >= 60 && probability < 95) {
				b.buildingType = 1;
			}
			else {
				b.buildingType = 2;
			}

			//set base coordinates
			b.xBase = (-nColumns / 2.0) + 0.5 + c;
			b.yBase = (-nRows / 2.0) + 0.5 + r;

			//set building dimensions
			b.width = ofRandom(0.3, 0.8);
			b.length = ofRandom(0.3, 0.8);
			b.height = ofRandom(2, 4);

			//set number of floors
			b.nFloors = round(ofRandom(1, 3));

			layoutRow.push_back(b);
		}

		layout.push_back(layoutRow);
		layoutRow.clear();
	}

	//set a random building in the layout as type 2
	layout[round(ofRandom(nRows - 1))][round(ofRandom(nColumns - 1))].buildingType = 3;

	//initialize animation variables 
	up = true;
	heightSb = 0;
	rotationSb = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	//check building 2 height state
	if (heightSb >= 4.5) {
		up = true;
	}

	if (heightSb <= 0.1) {
		up = false;
	}

	//adjust height and rotation based on the current direction
	if (!up) {
		heightSb += 0.01;
		rotationSb++;
	}
	else if (up)
	{
		heightSb -= 0.01;
		rotationSb--;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	//------------------------- main view -------------------------
	if (defaultPolygonMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glViewport(0, 0, gw(), gh());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (defaultView) {
		glFrustum(-gw() / gh() / 1.5, gw() / gh() / 1.5, gw() / gh() / 1.5, -gw() / gh() / 1.5, 1, 1000); //perspective view
	}
	else {
		glOrtho(-gw() / gh() / 0.1, gw() / gh() / 0.1, gw() / gh() / 0.1, -gw() / gh() / 0.1, 1, 1000); //ortogonal view
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	if (defaultView) {
		lookat(0, 18, 6, 0, 0, 0, 0, 1, 0); //perspective view
	}
	else {
		lookat(0, 10, 10, 0, 0, 0, 0, 1, 0); //ortogonal view
	}

	drawScene();

	glPopMatrix();

	//------------------------- top view -------------------------
	glViewport(10, gh() - gw() / 4, gw() / 4, gw() / 4);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (defaultView) {
		glFrustum(-gw() / gh() / 1.5, gw() / gh() / 1.5, gw() / gh() / 1.5, -gw() / gh() / 1.5, 1, 1000); //perspective view
	}
	else {
		glOrtho(-gw() / gh() / 0.1, gw() / gh() / 0.1, gw() / gh() / 0.1, -gw() / gh() / 0.1, 1, 1000); //ortogonal view
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	if (defaultView) {
		lookat(0, 0, 15, 0, 0, 0, 0, 1, 0); //perspective view
	}
	else {
		lookat(0, 0, 10, 0, 0, 0, 0, 1, 0); //ortogonal view
	}

	drawScene();

	glPopMatrix();

	//------------------------- frontal view -------------------------
	glViewport(gw() - gw() / 4 - 10, gh() - gw() / 4, gw() / 4, gw() / 4);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (defaultView) {
		glFrustum(gw() / gh() / 1.5, -gw() / gh() / 1.5, -gw() / gh() / 1.5, gw() / gh() / 1.5, 1, 1000); //perspective view
	}
	else {
		glOrtho(gw() / gh() / 0.1, -gw() / gh() / 0.1, -gw() / gh() / 0.1, gw() / gh() / 0.1, 1, 1000); //ortogonal view
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	if (defaultView) {
		lookat(0, 18, 0, 0, 0, 0, 0, 0, 1); //perspective view
	}
	else {
		lookat(0, 10, 0, 0, 0, 0, 0, 0, 1); //ortogonal view
	}

	drawScene();

	glPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawScene() {
	floorMesh(nRows, nColumns);

	//iterate through the layout and draw buildings
	for (const auto& layoutRow : layout) {
		for (const auto& b : layoutRow) {
			switch (b.buildingType)
			{
			case 1:
				building1(b.nFloors, b.xBase, b.yBase, b.width, b.length, b.height);
				break;

			case 2:
				building2(b.nFloors, b.xBase, b.yBase, b.width, b.height);
				break;

			case 3:
				specialBuilding(b.xBase, b.yBase, heightSb, rotationSb);
				break;

			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case '1':
		defaultView = !defaultView;
		break;

	case '2':
		defaultPolygonMode = !defaultPolygonMode;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
