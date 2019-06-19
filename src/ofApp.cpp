#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){

  // preliminares
  
  ofSetWindowTitle("Unknown Author");
  ofBackground(0);
  ofSetColor(255);
  ofSetFrameRate(60);
  ofHideCursor();

  // Fuente

  font.load("fonts/PrintChar21.ttf", 12, true, true, true);
  post = "";

  // lectura de archivos
  
  bufferAeforia = ofBufferFromFile("txt/aeforia.txt");
  bufferAitana = ofBufferFromFile("txt/aitana.txt");
  bufferCatelloo = ofBufferFromFile("txt/catelloo.txt");
  bufferExtraweg = ofBufferFromFile("txt/extraweg.txt");
  bufferInesAlpha = ofBufferFromFile("txt/inesAlpha.txt");
  bufferLilMiquela = ofBufferFromFile("txt/lilmiquela.txt");  
  
  timeAeforia = 10000;
  posXinAeforia = 0;
  posXfinAeforia = 0;
  posYinAeforia = 1;
  posYfinAeforia = 1;
  posZinAeforia = 2;
  posZfinAeforia = 2;
  startTimeAeforia = ofGetElapsedTimeMillis(); 
  
  timeAitana = 10000;
  posXinAitana = 0;
  posXfinAitana = 0;
  posYinAitana = 1;
  posYfinAitana = 1;
  posZinAitana = 2;
  posZfinAitana = 2;
  startTimeAitana = ofGetElapsedTimeMillis();

  timeCatelloo = 10000;
  posXinCatelloo = 0;
  posXfinCatelloo = 0;
  posYinCatelloo = 1;
  posYfinCatelloo = 1;
  posZinCatelloo = 2;
  posZfinCatelloo = 2;
  startTimeCatelloo = ofGetElapsedTimeMillis();

  // aeforia
  
  std::vector < std::string > filasAeforia = ofSplitString(bufferAeforia.getText(), " ");

  for (int i = 0;i < LIM1;i++){
    columnasAeforia[i] = ofSplitString(filasAeforia[i], ",");
    planosAeforia[i].setPosition(ofToFloat(columnasAeforia[i][0])*4-800, ofToFloat(columnasAeforia[i][1])*4-800, ofToFloat(columnasAeforia[i][2])*4-800);
    aeforia[i].load("img/aeforia/" + ofToString(i+1) + ".jpg");
    aeforia[i].resize(aeforia[i].getWidth()/8, aeforia[i].getHeight()/8);
    planosAeforia[i].resizeToTexture( aeforia[i].getTexture() );
  }

  // aitana
  
  std::vector < std::string > filasAitana = ofSplitString(bufferAitana.getText(), " ");

  for (int i = 0;i < LIM2;i++){
    columnasAitana[i] = ofSplitString(filasAitana[i], ",");
    planosAitana[i].setPosition(ofToFloat(columnasAitana[i][0])*4-800, ofToFloat(columnasAitana[i][1])*4-800, ofToFloat(columnasAitana[i][2])*4-800);
    aitana_basquiat[i].load("img/aitana_basquiat/" + ofToString(i+1) + ".jpg");
    aitana_basquiat[i].resize(aitana_basquiat[i].getWidth()/8, aitana_basquiat[i].getHeight()/8);
    planosAitana[i].resizeToTexture( aitana_basquiat[i].getTexture() );
  }

  // catelloo
  
  std::vector < std::string > filasCatelloo = ofSplitString(bufferCatelloo.getText(), " ");

  for (int i = 0;i < LIM1;i++){
    columnasCatelloo[i] = ofSplitString(filasCatelloo[i], ",");
    planosCatelloo[i].setPosition(ofToFloat(columnasCatelloo[i][0])*4-800, ofToFloat(columnasCatelloo[i][1])*4-800, ofToFloat(columnasCatelloo[i][2])*4-800);
    catelloo[i].load("img/catelloo/" + ofToString(i+1) + ".jpg");
    catelloo[i].resize(catelloo[i].getWidth()/8, catelloo[i].getHeight()/8);
    planosCatelloo[i].resizeToTexture( catelloo[i].getTexture() );
  }
  
  colorLight1 = ofColor(255.f, 255, 255);
  pointLight.setDiffuseColor( colorLight1 );

  reciever.setup(5612);
  centro = ofVec3f(0, 0, 0);
  
  aeforiaON = 0;
  aitanaON = 0;
  catellooON = 0; 

  rampONAeforia = 0;
  rampONAitana = 0;
  rampONCatelloo = 0; 

  opacidadAeforia = 250;
  opacidadAitana = 250;
  opacidadCatelloo = 250; 
  
}

//--------------------------------------------------------------
void ofApp::update(){
  
  pointLight.setPosition(ofGetWidth()/2, ofGetHeight()/2, camera.getDistance());

  while (reciever.hasWaitingMessages()){
        
    ofxOscMessage m;
    reciever.getNextMessage(&m);
  
    if (m.getAddress() == "/camOrbit"  &&  m.getNumArgs() ==2 ){
      int n = m.getArgAsInt(0);
      if(m.getArgAsInt(0) == 0 && m.getArgAsInt(1) == 0){
	orbitON = 0; 
      }
      else{
	orbitON = 1;
      }
      orbitX = m.getArgAsFloat(0);
      orbitY = m.getArgAsFloat(1); 
    }

    
    if (m.getAddress() == "/camOrbitX"  &&  m.getNumArgs() ==1 ){
      int n = m.getArgAsInt(0);
      if(m.getArgAsInt(0) == 0 && m.getArgAsInt(1) == 0){
	orbitON = 0; 
      }
      else{
	orbitON = 1;
      }
      orbitX = m.getArgAsFloat(0);
      //orbitY = m.getArgAsFloat(1); 
    }

      
    if (m.getAddress() == "/camOrbitY"  &&  m.getNumArgs() ==1 ){
      int n = m.getArgAsInt(0);
      if(m.getArgAsInt(0) == 0 && m.getArgAsInt(1) == 0){
	orbitON = 0; 
      }
      else{
	orbitON = 1;
      }
      orbitY = m.getArgAsFloat(0);
      //orbitY = m.getArgAsFloat(1); 
    }


    if (m.getAddress() == "/camSetPosition"  &&  m.getNumArgs() ==3 ){
      camera.setPosition(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
    }

    if (m.getAddress() == "/camLookAt"  &&  m.getNumArgs() ==3 ){
      centro = ofVec3f(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
    }

    if (m.getAddress() == "/camSetDistance"  &&  m.getNumArgs() ==1 ){
      camera.setDistance(m.getArgAsFloat(0)); 
    }

    // Aeforia

    if (m.getAddress() == "/aeforia"){
      if(m.getArgAsString(0) == "draw"  && m.getNumArgs() == 1){
	aeforiaON = 1;
	string oldpost = "draw: Aeforia";
	post = oldpost + "\n" + post;
	//inittimeDrawAeforia = ofGetElapsedTimeMillis();
	//aeforiaFadeIni = 255;
	//aeforiaFadeOut = 1;
	//	ofSleepMillis(500);
	// aeforiaON = 0; 
      }
      
      if(m.getArgAsString(0) == "clear" && m.getNumArgs() == 1){
	//aeforiaFadeIni = 1;
	//aeforiaFadeOut = 255; 
	//aeforiaFade= 1;
	//inittimeDrawAeforia = ofGetElapsedTimeMillis();
	//ofSleepMillis(500);
	aeforiaON = 0;
	string oldpost = "clear: aeforia";
	post = oldpost + "\n" + post;
      }
      
      if(m.getArgAsString(0) == "setPosition"  && m.getNumArgs() == 8){
	timeAeforia = m.getArgAsFloat(1);
	posXinAeforia = m.getArgAsInt(2);
	posXfinAeforia = m.getArgAsInt(3);
	posYinAeforia = m.getArgAsInt(4);
	posYfinAeforia = m.getArgAsInt(5);
	posZinAeforia = m.getArgAsInt(6);
	posZfinAeforia = m.getArgAsInt(7);
	rampONAeforia = 1;
	startTimeAeforia = ofGetElapsedTimeMillis(); 
      }
      if(m.getArgAsString(0) == "opacity" && m.getNumArgs() == 2){
	opacidadAeforia = m.getArgAsFloat(1); 
      }
    }

    // Aitana
    
    if (m.getAddress() == "/aitana"){
      if(m.getArgAsString(0) == "draw"  && m.getNumArgs() == 1){
	aitanaON = 1;
	string oldpost = "draw: aitana_basquiat";
	post = oldpost + "\n" + post;
      }
      if(m.getArgAsString(0) == "clear"  && m.getNumArgs() == 1){
	aitanaON = 0;
	string oldpost = "clear: aitana_basquiat";
	post = oldpost + "\n" + post;
      }
      if(m.getArgAsString(0) == "setPosition"  && m.getNumArgs() == 8){
	timeAitana = m.getArgAsFloat(1);
	posXinAitana = m.getArgAsInt(2);
	posXfinAitana = m.getArgAsInt(3);
	posYinAitana = m.getArgAsInt(4);
	posYfinAitana = m.getArgAsInt(5);
	posZinAitana = m.getArgAsInt(6);
	posZfinAitana = m.getArgAsInt(7);
	rampONAitana = 1;
	startTimeAitana = ofGetElapsedTimeMillis(); 
      }
      if(m.getArgAsString(0) == "opacity" && m.getNumArgs() == 2){
	opacidadAitana = m.getArgAsFloat(1); 
      }
    }

    // Catelloo
    
    if (m.getAddress() == "/catelloo"){
      if(m.getArgAsString(0) == "draw"  && m.getNumArgs() == 1){
	catellooON = 1;
	string oldpost = "draw: catelloo";
	post = oldpost + "\n" + post;
      }
      if(m.getArgAsString(0) == "clear"  && m.getNumArgs() == 1){
	catellooON = 0;
	string oldpost = "clear: catelloo";
	post = oldpost + "\n" + post;
      }
      if(m.getArgAsString(0) == "setPosition"  && m.getNumArgs() == 8){
	timeCatelloo = m.getArgAsFloat(1);
	posXinCatelloo = m.getArgAsInt(2);
	posXfinCatelloo = m.getArgAsInt(3);
	posYinCatelloo = m.getArgAsInt(4);
	posYfinCatelloo = m.getArgAsInt(5);
	posZinCatelloo = m.getArgAsInt(6);
	posZfinCatelloo = m.getArgAsInt(7);
	rampONCatelloo = 1;
	startTimeCatelloo = ofGetElapsedTimeMillis(); 
      }
      if(m.getArgAsString(0) == "opacity" && m.getNumArgs() == 2){
	opacidadCatelloo = m.getArgAsFloat(1); 
      }
    }
    
  }
}
  

//--------------------------------------------------------------
void ofApp::draw(){
 
  ofSetRectMode(OF_RECTMODE_CENTER);
  // camera.orbit(ofGetElapsedTimef()*25, ofGetElapsedTimef()*2, camera.getDistance(), ofVec3f(0, 0, 0));
  
  //  ofVec3f centro;
  //centro.set(500, 500, 500);
  //camera.lookAt(centro);
  ofDisableArbTex();
  // ofEnableLighting();
  //pointLight.enable();

  auto pos = camera.getGlobalPosition();
  camera.lookAt(centro);
  camera.setDistance(0);
  
  ofEnableAlphaBlending();
  //ofEnableArbTex();
  ofEnableDepthTest();

  camera.begin();

  // aeforia 

  if(aeforiaON == 1){

    /*
    if(aeforiaFade = 1){
      float tempTimer = ofGetElapsedTimeMillis() - inittimeDrawAeforia;
      opacidadAeforia = ofMap(tempTimer, 0, 500, aeforiaFadeIni, aeforiaFadeOut, true );
    }
    */
  
    ofSetColor(255, 255, 255, opacidadAeforia);

    float timerAeforia = ofGetElapsedTimeMillis() - startTimeAeforia;  
    
    for (int i = 0;i < LIM1;i++){
      planosAeforia[i].lookAt(pos);
      
      if(rampONAeforia == 1){
	float mapX, mapY, mapZ;
	
	mapX = ofMap(timerAeforia, 0, timeAeforia, ofToFloat(columnasAeforia[i][posXinAeforia]), ofToFloat(columnasAeforia[i][posXfinAeforia]), true )*4-800;
	mapY = ofMap(timerAeforia, 0, timeAeforia, ofToFloat(columnasAeforia[i][posYinAeforia]), ofToFloat(columnasAeforia[i][posYfinAeforia]), true)*4 -800;
	mapZ = ofMap(timerAeforia, 0, timeAeforia, ofToFloat(columnasAeforia[i][posZinAeforia]), ofToFloat(columnasAeforia[i][posZfinAeforia]), true )*4-800;
	
	planosAeforia[i].setPosition(mapX, mapY, mapZ);
      }
      
      aeforia[i].getTexture().bind();
      planosAeforia[i].draw();
      aeforia[i].getTexture().unbind();

      //ofSleepMillis(500);
      // aeforiaFade = 0; 
      
    }
  }
  
  // Aitana

  if(aitanaON == 1){

    float timerAitana = ofGetElapsedTimeMillis() - startTimeAitana; 
    
    ofSetColor(255, 255, 255, opacidadAitana);
    
    for (int i = 0;i < LIM2;i++){
      planosAitana[i].lookAt(pos, {0.f,1.f,0.f});
      
      if(rampONAitana == 1){
	float mapX, mapY, mapZ;
	
	mapX = ofMap(timerAitana, 0, timeAitana, ofToFloat(columnasAitana[i][posXinAitana]), ofToFloat(columnasAitana[i][posXfinAitana]), true )*4-800;
	mapY = ofMap(timerAitana, 0, timeAitana, ofToFloat(columnasAitana[i][posYinAitana]), ofToFloat(columnasAitana[i][posYfinAitana]), true)*4 -800;
	mapZ = ofMap(timerAitana, 0, timeAitana, ofToFloat(columnasAitana[i][posZinAitana]), ofToFloat(columnasAitana[i][posZfinAitana]), true )*4-800;
	
	planosAitana[i].setPosition(mapX, mapY, mapZ);
      }
      
      aitana_basquiat[i].getTexture().bind();
      planosAitana[i].draw();
      aitana_basquiat[i].getTexture().unbind();
      
    }
  }

  // Catelloo

  if(catellooON == 1){

    float timerCatelloo = ofGetElapsedTimeMillis() - startTimeCatelloo; 
    
    ofSetColor(255, 255, 255, opacidadCatelloo);
    
    for (int i = 0;i < LIM1;i++){
      planosCatelloo[i].lookAt(pos, {0.f,1.f,0.f});
      
      if(rampONCatelloo == 1){
	float mapX, mapY, mapZ;
	
	mapX = ofMap(timerCatelloo, 0, timeCatelloo, ofToFloat(columnasCatelloo[i][posXinCatelloo]), ofToFloat(columnasCatelloo[i][posXfinCatelloo]), true )*4-800;
	mapY = ofMap(timerCatelloo, 0, timeCatelloo, ofToFloat(columnasCatelloo[i][posYinCatelloo]), ofToFloat(columnasCatelloo[i][posYfinCatelloo]), true)*4 -800;
	mapZ = ofMap(timerCatelloo, 0, timeCatelloo, ofToFloat(columnasCatelloo[i][posZinCatelloo]), ofToFloat(columnasCatelloo[i][posZfinCatelloo]), true )*4-800;
	
	planosCatelloo[i].setPosition(mapX, mapY, mapZ);
      }
      
      catelloo[i].getTexture().bind();
      planosCatelloo[i].draw();
      catelloo[i].getTexture().unbind();
      
    }
  }

  ofDisableArbTex();
  ofDisableDepthTest();
  camera.end();

  ofSetColor(102, 255, 102);
  font.drawString( "Unknown Author> \n" + post, 20, 30);
  
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
