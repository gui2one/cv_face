#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// All examples share data files from example-data, so setting data path to this folder
	// This is only relevant for the example apps
	//ofSetDataPathRoot(ofFile(__BASE_FILE__).getEnclosingDirectory() + "../../model/");

	w_width = 1280;
	w_height = 720;

	// Setup grabber
	grabber.setup(w_width, w_height);

	//video_player.load("audience_footage.mp4");
	video_player.load("Bill & Melinda Gates Talk Taxing The Wealthy.mp4");
	video_player.play();
	// Setup tracker
	tracker.setup();
	//tracker.setFaceDetectorImageSize((w_width * w_height) / 2);
	box = ofBoxPrimitive();
	loader.loadModel("head_centered.obj");
	head_mesh = loader.getMesh(0);
	head_mesh.enableNormals();

	
	light_1.setGlobalPosition(-20.0f, -20.0f, -10.0f);
	light_1.setPointLight();
	

	ofSetFrameRate(25.0);
	
	
}

//--------------------------------------------------------------
void ofApp::update() {
	grabber.update();

	// Update tracker when there are new frames
	if (grabber.isFrameNew()) {
		//tracker.update(grabber);
	}


	video_player.update();
	/*ofImage img = video_player.getPixels();
	img.resize(2000, 2000);*/
	tracker.update(video_player);
	//printf("video_player update\n");
	
}

//--------------------------------------------------------------
void ofApp::draw() {


	ofSetColor(ofColor(255, 255, 255, 255));
	// Draw camera image
	//grabber.draw(0, 0);

	video_player.draw(0, 0);
	// Draw tracker landmarks
	tracker.drawDebug();

	// Draw estimated 3d pose
	tracker.drawDebugPose();

	// Draw text UI
	ofDrawBitmapStringHighlight("Framerate : " + ofToString(ofGetFrameRate()), 10, 20);
	ofDrawBitmapStringHighlight("Tracker thread framerate : " + ofToString(tracker.getThreadFps()), 10, 40);


	std::vector<ofxFaceTracker2Instance> instances = tracker.getInstances();
	//printf("instances num : %d\n", instances.size());

	//camera.begin();
	
	int inc = 3;
	ofEnableDepthTest();
	ofEnableLighting();
	for (auto& instance : instances) {
		
		ofMesh landmarks_mesh = instance.getLandmarks().getImageMesh();
		light_1.enable();
		//landmarks_mesh.drawFaces();


		ofVec3f translation;
		ofQuaternion rotation;
		ofVec3f scale;
		ofQuaternion so;
		ofMatrix4x4 matrix = instance.getPoseMatrix();
		matrix.decompose(translation, rotation, scale, so);

		
		ofPushView();
		ofPushStyle();
		instance.loadPoseMatrix();

		
		ofScale(6.0f);
		

		head_mesh.draw(OF_MESH_FILL);
		//box.draw();

		light_1.disable();
		ofPopView();
		ofPopStyle();

		bool added = diag.addInstance(instance.getLabel());
		if (!added)
		{
			for(auto& data : diag.datas)
			{
				if (data.label == instance.getLabel())
				{
				
					//rotation.conj();
					TrackerInstanceDiagnosis::diagSample sample;
					sample.translation = translation;

					rotation.conj();
					sample.rotation = rotation;
					sample.scale = scale;

					data.samples.insert(data.samples.end(), sample);
					data.tx.insert(data.tx.begin(),translation.x);
					data.rx.insert(data.rx.begin(),rotation.asVec3().x / PI * 180.0);
				}

				uint max = 150;
				if (data.samples.size() > max)
				{

					data.samples.erase(data.samples.begin(), data.samples.begin() + (data.samples.size() - max));
				}

				
			}
		}

		//ofDrawBitmapStringHighlight("instance translation: " + ofToString(translation.x), 10, inc * 20);
		inc++;
	}

	ofDisableDepthTest();
	ofDisableLighting();

	diag.draw();
	//camera.end();
	
#ifndef __OPTIMIZE__
	ofSetColor(ofColor::red);
	ofDrawBitmapString("Warning! Run this app in release mode to get proper performance!", 10, 60);
	ofSetColor(ofColor::white);
#endif
}