#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	auto R = 100.f;
	auto u_step = 1.f;
	auto v_step = 1.f;

	for (int i = 0; i < 7; i++) {

		auto r = 25.f;

		float angle_z = (i * u_step * 2) * DEG_TO_RAD;
		auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

		auto v_start = 0.f;
		auto v_len = 360.f;

		if (i % 2 == 0) {

			v_start = (ofGetFrameNum() + i * 15) % 360;
			v_len = 120;
			r = 15;
		}

		for (auto v = v_start; v < v_start + v_len; v += v_step) {

			vector<glm::vec3> vertices{
				glm::vec4(this->make_point(R, r, v * u_step * 17, v * 2), 0) * rotation_z,
				glm::vec4(this->make_point(R, r, (v + v_step) * u_step * 17, (v + v_step) * 2), 0) * rotation_z,
				glm::vec4(this->make_point(R, r, v * u_step * 17, (v + v_step) * 2), 0) * rotation_z,
				glm::vec4(this->make_point(R, r, (v - v_step) * u_step * 17, v * 2), 0) * rotation_z
			};

			auto index = this->face.getNumVertices();

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
			this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
			this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);

			for (int k = 0; k < 4; k++) {

				i % 2 == 0 ? this->face.addColor(ofColor(39)) : this->face.addColor(ofColor(239));
				i % 2 == 0 ? this->frame.addColor(ofColor(239)) : this->frame.addColor(ofColor(39));
			}
		}
	}
}


//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->face.draw();
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}