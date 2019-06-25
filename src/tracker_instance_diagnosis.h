#pragma once

#include "ofxFaceTracker2.h"
#include "ofxFaceTracker2Instance.h"

class TrackerInstanceDiagnosis
{


	

public:

	struct diagSample {
		ofVec3f translation;
		ofQuaternion rotation;
		ofVec3f scale;
	};

	struct diagData {
		int label;

		std::vector<diagSample> samples;

		std::vector<float> tx;
		std::vector<float> ty;
		std::vector<float> tz;

		std::vector<float> rx;
		std::vector<float> ry;
		std::vector<float> rz;
	};

	TrackerInstanceDiagnosis();
	~TrackerInstanceDiagnosis();

	

	void drawCurve(ofxFaceTracker2Instance& instance);

	bool addInstance(int _label);
	void draw();

	std::vector<diagData> datas;
};
