#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  // preliminares
  
  ofSetWindowTitle("Unknown Artist");
  ofBackground(0);
  ofSetColor(255);
  ofSetFrameRate(60);
  //ofHideCursor();

  // gui
  gui.setup("Unknown Artist");
  gui.add(opacidad1.setup("opacidad aeforia", 200, 20, 255));
  gui.add(opacidad2.setup("opacidad a_basquiat", 200, 20, 255));

  // lectura de archivos
  
  buffer1 = ofBufferFromFile("txt/aeforia.txt"); // reading into the buffer
  buffer2 = ofBufferFromFile("txt/aitana.txt"); // reading into the buffer
  //camera.setPosition(200, 200, 200);
  // txt a nodos

  /*

    r = sqrt(x*x+y*y+z*z);
    theta = atan2(y,x);
    phi = atan2(sqrt(x*x+y*y),z);
    
  */

   
  std::vector < std::string > filas = ofSplitString(buffer1.getText(), " ");

  for (int i = 0;i < LIM1;i++){
    columna[i] = ofSplitString(filas[i], ",");

    nodos[i].set(ofToFloat(columna[i][0])*4-800, ofToFloat(columna[i][1])*4-800, ofToFloat(columna[i][2])*4-800 );    
    fuentes[i].setPosition(nodos[i]);

    aeforia[i].load("img/aeforia/" + ofToString(i+1) + ".jpg");
    aeforia[i].resize(aeforia[i].getWidth()/8, aeforia[i].getHeight()/8);
    //ofLoadImage(texturas[i], "img/aeforia/" + ofToString(i) + ".jpg");
    fuentes[i].resizeToTexture( aeforia[i].getTexture() );
  }
  
  
  std::vector < std::string > filas2 = ofSplitString(buffer2.getText(), " ");

  for (int i = 0;i < LIM2;i++){
    columna2[i] = ofSplitString(filas2[i], ",");
    nodos2[i].set(ofToFloat(columna2[i][0])*4-800, ofToFloat(columna2[i][1])*4-800, ofToFloat(columna2[i][2])*4-800 );
    fuentes2[i].setPosition(nodos2[i]);
    aitana_basquiat[i].load("img/aitana_basquiat/" + ofToString(i+1) + ".jpg");
    aitana_basquiat[i].resize(aitana_basquiat[i].getWidth()/8, aitana_basquiat[i].getHeight()/8);
    //ofLoadImage(texturas[i], "img/aeforia/" + ofToString(i) + ".jpg");
    fuentes2[i].resizeToTexture( aitana_basquiat[i].getTexture() );
  }

  // luces
  
  colorLight1 = ofColor(255.f, 255, 255);
  pointLight.setDiffuseColor( colorLight1 );

  // coordenadas esféricas

  /*
  vector <float> longitude;
  vector <float> latitude;
  float SphereRadius = 250.0;

  for (int x=0; x<LIM1; x++) {
    for (int y=0; y<LIM1; y++) {
      latitude.push_back( ofMap(x, 0, ofToFloat(columna[x][0]), 0, (2*PI) ) );
      longitude.push_back( ofMap(y, 0, ofToFloat(columna[y][1]), 0, PI ) );
    }
  }

  for (unsigned i = 0; i<longitude.size(); i++) {
    float longTMP = longitude[i];
    float latTMP = latitude[i];
    float X = ( SphereRadius * cos(latTMP) * sin(longTMP) );
    float Y = ( SphereRadius * sin(latTMP) * sin(longTMP) );
    float Z = ( SphereRadius * cos(longTMP) );
    //    ofVec3f temp = ofVec3f(X,Y,Z);
    nodos[i].set(X, Y, Z);
    
    fuentes[i].setPosition(X, Y, Z);

    //mesh.addVertex(temp);
    //mesh.addColor( ofFloatColor(1,1,1));
  }

  */
  
}

//--------------------------------------------------------------
void ofApp::update(){
  
  pointLight.setPosition(ofGetWidth()/2, ofGetHeight()/2, camera.getDistance());
  
}
  

//--------------------------------------------------------------
void ofApp::draw(){
 
  ofSetRectMode(OF_RECTMODE_CENTER);
  //camera.orbit(ofGetElapsedTimef()*10, ofGetElapsedTimef()*2, camera.getDistance(), ofVec3f(0, 0, 0));
  
  //  ofVec3f centro;
  //centro.set(500, 500, 500);
  //camera.lookAt(centro);
  ofDisableArbTex();
  // ofEnableLighting();
  //pointLight.enable();

  auto pos = camera.getGlobalPosition();
  camera.lookAt(ofVec3f(0, 0, 0));
  //camera.setDistance(200);
  
  ofEnableAlphaBlending();
  //ofEnableArbTex();
  ofEnableDepthTest();

  camera.begin();
  
  //ofTranslate(-200, -200, -200);
  ofSetColor(255, 255, 255, opacidad1);

  //ofScale(0.125/8, 0.125/8, 0.125/8);
  //ofScale(0.125, 0.125); 
  for (int i = 0;i < LIM1;i++){
    //ofSetColor(255, 255, 255, 100);
    fuentes[i].lookAt(pos);
    //    fuentes[i].setPosition(ofToFloat(columna[i][0]), ofToFloat(columna[i][1]), ofToFloat(columna[i][2]));
    aeforia[i].getTexture().bind();
    fuentes[i].draw();
    aeforia[i].getTexture().unbind();
    //imagenes[i].draw(ofToFloat(columna[i][0]), ofToFloat(columna[i][1]), ofToFloat(columna[i][2])); 
  }

  ofSetColor(255, 255, 255, opacidad2);
  
  for (int i = 0;i < LIM2;i++){
    //ofSetColor(255, 255, 255, 100);
    fuentes2[i].lookAt(pos, {0.f,1.f,0.f});
    //fuentes2[i].setPosition(ofToFloat(columna2[i][0])-200, ofToFloat(columna2[i][1])-200, ofToFloat(columna2[i][2])-200);
    aitana_basquiat[i].getTexture().bind();
    fuentes2[i].draw();
    aitana_basquiat[i].getTexture().unbind();
    //imagenes[i].draw(ofToFloat(columna[i][0]), ofToFloat(columna[i][1]), ofToFloat(columna[i][2])); 
  }

  ofDisableArbTex();
  ofDisableDepthTest();
  camera.end();

  
 gui.draw();
 
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
