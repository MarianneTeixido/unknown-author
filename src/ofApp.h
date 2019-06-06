#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define LIM1 527 // fuentes
#define LIM2 144
//#define LIM 27 // fuentes



class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofBuffer buffer1;
		ofBuffer buffer2;
		ofVec3f nodos[LIM1];
		ofPlanePrimitive fuentes[LIM1];
		std::vector < std::string > columna[LIM1];

		
		ofVec3f nodos2[LIM2];
		ofPlanePrimitive fuentes2[LIM2];
		std::vector < std::string > columna2[LIM2];
		
		ofEasyCam camera;
		ofLight pointLight;
		ofColor colorLight1;
		
		ofImage aeforia[LIM1];
		ofImage aitana_basquiat[LIM2];

		// parametros gui

		ofxFloatSlider opacidad1;
		ofxFloatSlider opacidad2;
		ofxFloatSlider camDistance;
		ofxToggle toogle1;
		ofxToggle toogle2;
		ofxPanel gui; 

};
