#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define LIM1 200 
#define LIM2 100
#define LIM3 50

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
  
  ofBuffer bufferAeforia;
  ofBuffer bufferAitana;
  ofBuffer bufferCatelloo;
  ofBuffer bufferExtraweg;
  ofBuffer bufferInesAlpha;
  ofBuffer bufferLilMiquela; 
  		
  ofEasyCam camera;
  ofLight pointLight;
  ofColor colorLight1;
  ofTrueTypeFont font;
  string post;
  // string oldpost;
  
  float camDistance;
  
  ofxOscReceiver reciever;
  ofxOscSender sender;

  int orbitON;
  float orbitX;
  float orbitY;

  ofVec3f centro;

  // aeforia
  
  ofImage aeforia[LIM1];

  ofPlanePrimitive planosAeforia[LIM1];
  std::vector < std::string > columnasAeforia[LIM1];
  
  int aeforiaON;
  float opacidadAeforia;
  float startTimeAeforia;
  float timeAeforia; 
  float posXinAeforia, posXfinAeforia, posYinAeforia, posYfinAeforia, posZinAeforia, posZfinAeforia;
  int rampONAeforia; 
  //float inittimeDrawAeforia;
  //int aeforiaFade;
  //float aeforiaFadeIni;
  //float aeforiaFadeOut; 
  
  // aitana
  	
  ofImage aitana_basquiat[LIM2];

  ofPlanePrimitive planosAitana[LIM2];
  std::vector < std::string > columnasAitana[LIM2];
  
  int aitanaON;
  float opacidadAitana;
  float startTimeAitana;  
  float timeAitana; 
  float posXinAitana, posXfinAitana, posYinAitana, posYfinAitana, posZinAitana, posZfinAitana;
  int rampONAitana;

   // catelloo
  	
  ofImage catelloo[LIM1];

  ofPlanePrimitive planosCatelloo[LIM1];
  std::vector < std::string > columnasCatelloo[LIM1];

  int catellooON;
  float opacidadCatelloo;
  float startTimeCatelloo;  
  float timeCatelloo; 
  float posXinCatelloo, posXfinCatelloo, posYinCatelloo, posYfinCatelloo, posZinCatelloo, posZfinCatelloo;
  int rampONCatelloo; 
  
};
