// ofxFaceTrack2 example: SIMPLE EXAMPLE
//
// This example shows minimal usage of the ofxFaceTracker2 addon,
// doing simple landmark detection and pose estimation
//

#pragma once

#include "ofMain.h"
#include "ofxFaceTracker2.h"
#include "ofxAssimpModelLoader.h"
#include "tracker_instance_diagnosis.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	ofxFaceTracker2 tracker;
	ofVideoGrabber grabber;

	ofBoxPrimitive box;

	ofxAssimpModelLoader loader;
	ofMesh head_mesh;

	ofVideoPlayer video_player;

	int w_width;
	int w_height;


	ofCamera camera;

	ofLight light_1;

	TrackerInstanceDiagnosis diag;
};
