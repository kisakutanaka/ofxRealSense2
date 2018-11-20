# ofxRealSense2

realsenseSDK2.0のOpenFrameWorks用アドオンです。  
SDKのバージョンは2.13.0を利用しています。  

## セットアップ方法
「libs」→「librealsense2」→「bin」内のdllファイルをプロジェクト内の「bin」ファイルにコピーしてください。

## example

```c++
//ofApp.h
#pragma once

#include "ofMain.h"
#include "ofxRealSense2.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		ofxRealSense2 realsense;
		ofPixels colorPix;
		ofShortPixels depthPix;
		//ofPixels colorizedDepthPix;
		ofPixels bwDepthPix;

		ofTexture color;
		ofTexture depth;
		ofTexture colorizedDepth;
		ofTexture bwTex;
};
```
```c++
//ofAPP.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	realsense.setup();
	//realsense.setStreamStatus(true, true, ofVec2f(640, 480), ofVec2f(640, 360));
	bwDepthPix.allocate(realsense.getDepthWidth(), realsense.getDepthHeight(), OF_PIXELS_GRAY);
}

//--------------------------------------------------------------
void ofApp::update(){
	realsense.update();
	if (realsense.isFrameNew()) {
		colorPix = realsense.getColorPixels();
		depthPix = realsense.getDepthPixels();
		for (int i = 0; i < depthPix.size(); i++) {
			int d = depthPix[i];
			if (d >= 1000 && d <= 1500) {
				bwDepthPix[i] = 255;
			}
			else {
				bwDepthPix[i] = 0;
			}
		}
		//colorizedDepthPix = realsense.getColorizedDepthPixels();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));

	bwTex.loadData(bwDepthPix);
	color.loadData(colorPix);
	depth.loadData(depthPix);
	//colorizedDepth.loadData(colorizedDepthPix);

	color.draw(0, 120, 640, 480);
	depth.draw(640, 0, 640, 360);
	//colorizedDepth.draw(640, 360, 640, 360);
	bwTex.draw(640, 360, 640, 360);

	//realsense.getColorTexture().draw(0, 120, 640, 480);
	//realsense.getColorizedDepthTexture().draw(640, 180, 640, 360);

	
}

```
