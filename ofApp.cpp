#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		if (this->location_list[i].z < 0) {

			this->location_list[i].z += 30;
			continue;
		}

		this->radius_list[i] += this->speed_list[i];

		if (this->radius_list[i] > this->max_radius_list[i]) {

			this->location_list.erase(this->location_list.begin() + i);
			this->radius_list.erase(this->radius_list.begin() + i);
			this->speed_list.erase(this->speed_list.begin() + i);
			this->max_radius_list.erase(this->max_radius_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}

	ofColor color;
	for (int i = 0; i < 24; i++) {

		auto radius = ofMap(sin(ofGetFrameNum() * 0.05), -1, 1, 200, 300);
		auto deg = ofGetFrameNum() * 1.44 * 3 + (i % 3) * 120;

		auto location = glm::vec3(
			radius * cos(deg * DEG_TO_RAD) + ofRandom(-35, 35),
			radius * sin(deg * DEG_TO_RAD) + ofRandom(-35, 35),
			-300);

		color.setHsb(ofRandom(255), 200, 255);

		this->location_list.push_back(location);
		this->radius_list.push_back(1);
		this->speed_list.push_back(ofRandom(0.7, 1.7));
		this->max_radius_list.push_back(ofRandom(5, 20));
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	for (int i = 0; i < this->location_list.size(); i++) {

		if (this->radius_list[i] < this->max_radius_list[i] * 0.5) {

			ofSetColor(this->color_list[i]);
		}
		else {

			ofColor color;
			auto brightness = ofMap(this->radius_list[i], this->max_radius_list[i] * 0.5, this->max_radius_list[i], 255, 0);
			color.setHsb(this->color_list[i].getHue(), this->color_list[i].getSaturation(), brightness);
			ofSetColor(color);
		}

		if (this->location_list[i].z < 0) {

			ofSetColor(this->color_list[i], 200);
			ofDrawLine(this->location_list[i], this->location_list[i] - glm::vec3(0, 0, 30));
			continue;
		}

		ofDrawCircle(glm::vec2(this->location_list[i]), this->radius_list[i]);
	}

	this->cam.end();

	/*
	int start = 75;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}