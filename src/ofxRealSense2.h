#pragma once

#include "ofMain.h"
#include <librealsense2/rs.hpp>

class ofxRealSense2
{
public:
	ofxRealSense2();
	~ofxRealSense2();
	void setup();
	void setup(rs2::config _conf);
	void update();

	void setStreamStatus(bool enableColorStream, bool enableDepthStream, ofVec2f colorSize = ofVec2f(640, 480), ofVec2f depthSize = ofVec2f(1280, 720),int colorFrameRate = 30,int depthFrameRate = 30);

	int getColorWidth();
	int getColorHeight();
	int getDepthWidth();
	int getDepthHeight();

	ofPixels& getColorPixels();
	ofShortPixels& getDepthPixels();
	ofPixels& getColorizedDepthPixels();
	
	ofTexture& getColorTexture();
	ofTexture& getColorizedDepthTexture();

	bool isFrameNew();

private:
	rs2::config conf;
	rs2::pipeline pipe;
	rs2::frameset frames;
	rs2::colorizer color_map;
	rs2::frame colorizedDepthFrame;

	ofPixels colorPix;
	ofShortPixels depthPix;
	ofPixels colorizedDepthPix;

	ofTexture colorTex;
	ofTexture colorizedDepthTex;

	int colorWidth = 640;
	int colorHeight = 480;
	int depthWidth = 1280;
	int depthHeight = 720;
	bool bFrameNew = false;
	bool bColorPixNew = false;
	bool bDepthPixNew = false;
	bool bColorizedDepthPixNew = false;
};
