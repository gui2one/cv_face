#include "tracker_instance_diagnosis.h"

TrackerInstanceDiagnosis::TrackerInstanceDiagnosis()
{
}

TrackerInstanceDiagnosis::~TrackerInstanceDiagnosis()
{
}

void TrackerInstanceDiagnosis::drawCurve(ofxFaceTracker2Instance& instance)
{

	
	printf("drawing instance curve n : %d\n", instance.getLabel());
}

bool TrackerInstanceDiagnosis::addInstance(int _label)
{
	for each (auto data in datas)
	{
		if (data.label == _label)
		{
			//printf("already in list \n");
			return false;
		}
	}

	diagData data;
	data.label = _label;
	datas.push_back(data);
	printf("NOT in list , added\n\n\n\n");
	return true;
}

void TrackerInstanceDiagnosis::draw()
{

	if (datas.size() > 0) {

		diagData curData = datas[datas.size() - 1];
		int x_offset = 50;
		int y_offset = 200;

		ofDrawBitmapStringHighlight("Face " + ofToString(curData.label) + " Translation", x_offset - 30, y_offset - 30);

		ofPolyline tx_line;
		
		ofSetColor(ofColor(255, 30, 30, 255));
		std::vector<glm::vec3> verts;
		for (int i = 0; i < curData.samples.size(); i++)
		{
			verts.push_back(glm::vec3(
				(float)i * 3.0f + x_offset,
				(curData.samples[i].translation.x * 0.1f) + y_offset,
				0.0f
			));
		}
		tx_line.addVertices(verts);		
		tx_line.draw();


		ofPolyline ty_line;

		ofSetColor(ofColor(30, 255, 30, 255));
		verts.clear();
		for (int i = 0; i < curData.samples.size(); i++)
		{
			verts.push_back(glm::vec3(
				(float)i * 3.0f + x_offset,
				(curData.samples[i].translation.y * 0.1f) + y_offset,
				0.0f
			));
		}
		ty_line.addVertices(verts);
		ty_line.draw();

		ofPolyline tz_line;

		ofSetColor(ofColor(30, 30, 255, 255));
		verts.clear();
		for (int i = 0; i < curData.samples.size(); i++)
		{
			verts.push_back(glm::vec3(
				(float)i * 3.0f + x_offset,
				(curData.samples[i].translation.z * 0.01f) + y_offset,
				0.0f
			));
		}
		tz_line.addVertices(verts);
		tz_line.draw();





		y_offset += 180.0f;
		ofDrawBitmapStringHighlight("Face " + ofToString(curData.label) + " Rotation", x_offset - 30, y_offset - 30);

		ofPolyline rx_line;

		ofSetColor(ofColor(255, 30, 30, 255));
		verts.clear();
		for (int i = 0; i < datas[datas.size() - 1].samples.size(); i++)
		{
			verts.push_back(glm::vec3(
				(float)i * 3.0f + x_offset,
				(datas[datas.size() - 1].samples[i].rotation.asVec3().x / PI * 180.0) + y_offset,
				0.0f
			));
		}
		rx_line.addVertices(verts);
		rx_line.draw();


		ofPolyline ry_line;

		ofSetColor(ofColor(30, 255, 30, 255));
		verts.clear();
		for (int i = 0; i < datas[datas.size() - 1].samples.size(); i++)
		{
			verts.push_back(glm::vec3(
				(float)i * 3.0f + x_offset,
				(datas[datas.size() - 1].samples[i].rotation.asVec3().y / PI * 180.0) + y_offset,
				0.0f
			));
		}
		ry_line.addVertices(verts);
		ry_line.draw();

		ofPolyline rz_line;

		ofSetColor(ofColor(30, 30, 255, 255));
		verts.clear();
		for (int i = 0; i < datas[datas.size() - 1].samples.size(); i++)
		{
			verts.push_back(glm::vec3(
				(float)i * 3.0f + x_offset,
				(datas[datas.size() - 1].samples[i].rotation.asVec3().z / PI * 180.0) + y_offset,
				0.0f
			));
		}
		rz_line.addVertices(verts);
		rz_line.draw();




		// no scaling needed it seems, the tracker just moves in Z

		//y_offset += 180.0f;
		//ofDrawBitmapStringHighlight("Face " + ofToString(curData.label) + " Scale", x_offset - 30, y_offset - 30);

		//ofPolyline sx_line;

		//ofSetColor(ofColor(255, 30, 30, 255));
		//verts.clear();
		//for (int i = 0; i < datas[datas.size() - 1].samples.size(); i++)
		//{
		//	verts.push_back(glm::vec3(
		//		(float)i * 3.0f + x_offset,
		//		((datas[datas.size() - 1].samples[i].scale.x - 1.0f) * 100.0f) + y_offset,
		//		0.0f
		//	));
		//}
		//sx_line.addVertices(verts);
		//sx_line.draw();


		//ofPolyline sy_line;

		//ofSetColor(ofColor(30, 255, 30, 255));
		//verts.clear();
		//for (int i = 0; i < datas[datas.size() - 1].samples.size(); i++)
		//{
		//	verts.push_back(glm::vec3(
		//		(float)i * 3.0f + x_offset,
		//		((datas[datas.size() - 1].samples[i].scale.y - 1.0f) * 100.0f) + y_offset,
		//		0.0f
		//	));
		//}
		//sy_line.addVertices(verts);
		//sy_line.draw();

		//ofPolyline sz_line;

		//ofSetColor(ofColor(30, 30, 255, 255));
		//verts.clear();
		//for (int i = 0; i < datas[datas.size() - 1].samples.size(); i++)
		//{
		//	verts.push_back(glm::vec3(
		//		(float)i * 3.0f + x_offset,
		//		((datas[datas.size() - 1].samples[i].scale.z - 1.0f) * 100.0f) + y_offset,
		//		0.0f
		//	));
		//}
		//sz_line.addVertices(verts);
		//sz_line.draw();
	}

	
	
}
