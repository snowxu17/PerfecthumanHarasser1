#pragma once

#include "ofMain.h"
#include "ofxFaceTracker.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
	ExpressionClassifier classifier;
    
    float scale = 4.0;
    float nProb = .2;
    float sProb = .2;
    float age = 3.0;
    
    enum State
    {
        STATE_NULL,
        STATE_WALK,
        STATE_APPROACH,
        STATE_NEUTRAL_FACE,
        STATE_OFFER
    };
    
    State lastState = STATE_APPROACH;
    State currentState = STATE_NULL;
    
    uint64_t startPlayTime;
    uint64_t finishPlayTime;
    uint64_t dt;
 

    //State walk
    ofSoundPlayer heyBabe;
    ofSoundPlayer walk;
    ofSoundPlayer xcusme;
    ofSoundPlayer comeHere;
    ofSoundPlayer whistle;
    ofSoundPlayer runaway;
    ofSoundPlayer sup;
    ofSoundPlayer walkFast;
    ofSoundPlayer where;
    
    //state approach
    ofSoundPlayer body;
    ofSoundPlayer heySexy;
    ofSoundPlayer lookGood;
    ofSoundPlayer pumpkin;
    ofSoundPlayer attractive;
    
    //state neutral face
    ofSoundPlayer sadFace;
    ofSoundPlayer smileAtMe;
    ofSoundPlayer serious;
    ofSoundPlayer hang;
    
    //state offer
    ofSoundPlayer feast;
    ofSoundPlayer howAreYou;
    ofSoundPlayer yum;
    ofSoundPlayer sip;
    ofSoundPlayer knockUp;    
    
    std::vector<ofSoundPlayer> walkAudios;
    std::vector<ofSoundPlayer> approachAudios;
    std::vector<ofSoundPlayer> nfAudios;
    std::vector<ofSoundPlayer> offerAudios;
    
    // Current track playing. 
    ofSoundPlayer currentTrack;
    
};
