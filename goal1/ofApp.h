#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include "drawingExtras.h"
#include "cg_cam_extras_solution.h"

#include <vector>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void drawScene();

		//camera options
		GLboolean defaultView = true; //true:perspective false:ortogonal
		GLboolean defaultPolygonMode = true; //true:line false:fill

		//floor mesh parameters
		GLint nRows, nColumns;

		//buildings parameters
		struct building {
			GLint buildingType;
			GLfloat xBase, yBase;
			GLfloat width, length, height;
			GLint nFloors;
		};

		vector<building> layoutRow;
		vector<vector<building>> layout;

		GLfloat heightSb, rotationSb;
		GLboolean up;
};