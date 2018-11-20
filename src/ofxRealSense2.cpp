#include "ofxRealSense2.h"

ofxRealSense2::ofxRealSense2() {
}

ofxRealSense2::~ofxRealSense2() {
}

void ofxRealSense2::setup() {
	pipe.start();
	setStreamStatus(true, true);
}

void ofxRealSense2::setup(rs2::config _conf) {
	pipe.start(_conf);
	//setStreamStatus(true, true);
}

void ofxRealSense2::setStreamStatus(bool enableColorStream, bool enableDepthStream, ofVec2f colorSize, ofVec2f depthSize,int colorFrameRate,int depthFrameRate) {
	conf.disable_all_streams();
	if (enableColorStream) {
		conf.enable_stream(RS2_STREAM_COLOR, colorSize.x, colorSize.y, RS2_FORMAT_RGB8, colorFrameRate);
	}
	if (enableDepthStream) {
		conf.enable_stream(RS2_STREAM_DEPTH, depthSize.x, depthSize.y, RS2_FORMAT_Z16, depthFrameRate);
	}
	colorWidth = colorSize.x;
	colorHeight = colorSize.y;
	depthWidth = depthSize.x;
	depthHeight = depthSize.y;
	pipe.stop();
	pipe.start(conf);

}

void ofxRealSense2::update() {
	bFrameNew = pipe.poll_for_frames(&frames);
	if (bFrameNew) {
		bColorPixNew = false;
		bDepthPixNew = false;
		bColorizedDepthPixNew = false;
	}
}

int ofxRealSense2::getColorWidth() {
	return colorWidth;
}

int ofxRealSense2::getColorHeight() {
	return colorHeight;
}

int ofxRealSense2::getDepthWidth() {
	return depthWidth;
}

int ofxRealSense2::getDepthHeight() {
	return depthHeight;
}

ofPixels& ofxRealSense2::getColorPixels() {
	if (!bColorPixNew) {
		unsigned char * colorPixData = (unsigned char*)frames.get_color_frame().get_data();
		colorPix.setFromExternalPixels(colorPixData, colorWidth, colorHeight, OF_PIXELS_RGB);
		bColorPixNew = true;
	}
	return colorPix;
}

ofShortPixels& ofxRealSense2::getDepthPixels() {
	if (!bDepthPixNew) {
		unsigned short * depthPixData = (unsigned short*)frames.get_depth_frame().get_data();
		depthPix.setFromExternalPixels(depthPixData, depthWidth, depthHeight, OF_PIXELS_GRAY);
		bDepthPixNew = true;
	}
	return depthPix;
}

ofPixels& ofxRealSense2::getColorizedDepthPixels() {
	if (!bColorizedDepthPixNew) {
		colorizedDepthFrame = color_map(frames.get_depth_frame());
		unsigned char * colorizedDepthPixData = (unsigned char*)colorizedDepthFrame.get_data();
		colorizedDepthPix.setFromExternalPixels(colorizedDepthPixData, depthWidth, depthHeight, OF_PIXELS_RGB);
		bColorizedDepthPixNew = true;
	}
	return colorizedDepthPix;
}

ofTexture& ofxRealSense2::getColorTexture() {
	if (bFrameNew) {
		colorTex.loadData(getColorPixels());
	}
	return colorTex;
}

ofTexture& ofxRealSense2::getColorizedDepthTexture() {
	if (bFrameNew) {
		colorizedDepthTex.loadData(getColorizedDepthPixels());
	}
	return colorizedDepthTex;
}

bool ofxRealSense2::isFrameNew() {
	return bFrameNew;
}