#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetVerticalSync(true);
    cam.setDeviceID(1);
	cam.setup(640, 480);
	
	tracker.setup();
	tracker.setRescale(.5);
    
    //======load audio files
    //state walk
    heyBabe.load("Hey Babe.mp3");
    walk.load("Walk.mp3");
    runaway.load("Runaway.mp3");
    xcusme.load("xcusme.mp3");
    comeHere.load("come here.mp3");
    sup.load("sup.mp3");
    whistle.load("whistle.mp3");
    walkFast.load("walk fast.mp3");
    where.load("Where.mp3");
    
    //state appraoch
    body.load("Body.mp3");
    heySexy.load("HeySexy.mp3");
    lookGood.load("LookGood.mp3");
    pumpkin.load("Pumpkin2.mp3");
    attractive.load("Attractive.mp3");
    
    //state neutral face
    sadFace.load("SadFace.mp3");
    smileAtMe.load("Smile.mp3");
    serious.load("Serious.mp3");
    hang.load("Hang.mp3");
    
    //state offer
    feast.load("Feast.mp3");
    howAreYou.load("HowAreYou.mp3");
    yum.load("Yum.mp3");
    sip.load("Sip.mp3");
    knockUp.load("Knock Up.mp3");    
    
    
    //======load soundplayers to vectors
    //state walk
    walkAudios.push_back(heyBabe);
    walkAudios.push_back(walk);
    walkAudios.push_back(runaway);
    walkAudios.push_back(xcusme);
    walkAudios.push_back(comeHere);
    walkAudios.push_back(sup);
    walkAudios.push_back(walkFast);
    walkAudios.push_back(whistle);
    walkAudios.push_back(where);
    
    //state appraoch
    approachAudios.push_back(body);
    approachAudios.push_back(heySexy);
    approachAudios.push_back(lookGood);
    //approachAudios.push_back(where);
    approachAudios.push_back(pumpkin);
    approachAudios.push_back(attractive);
    approachAudios.push_back(whistle);
    
    //state neutral face
    nfAudios.push_back(smileAtMe);
    nfAudios.push_back(sadFace);
    nfAudios.push_back(serious);
    nfAudios.push_back(hang);
    
    //state offer
    offerAudios.push_back(feast);
    offerAudios.push_back(howAreYou);
    offerAudios.push_back(yum);
    offerAudios.push_back(knockUp);
    offerAudios.push_back(sip);
    
//    cout<<"walk audio size: "<<walkAudios.size()<<endl;
//    cout<<"approach audio size: "<<approachAudios.size()<<endl;
//    cout<<"nf audio size: "<<nfAudios.size()<<endl;
//    cout<<"offer audio size: "<<offerAudios.size()<<endl;
    
    //======set up expressions
    classifier.load("expressions");


}

void ofApp::update() {
    

//    cam.listDevices();
    
    uint64_t now = ofGetElapsedTimeMillis();
    dt = now - finishPlayTime - startPlayTime;
    
	cam.update();
    
	if(cam.isFrameNew()) {
		if(tracker.update(toCv(cam))) {
			classifier.classify(tracker);
		}		
	}
    
    
    if(currentState == STATE_NULL)
    {
        if (tracker.getAge() > age && tracker.getScale() < scale)
        {
            currentState = STATE_WALK;
        }
        
        if(tracker.getAge() > age && tracker.getScale() > scale)
        {
            currentState = STATE_APPROACH;
        }
        
    }
    
    
    else if(currentState == STATE_WALK)
    {
        if (tracker.getScale() > scale)
        {
            currentState = STATE_APPROACH;
        }
        
        if (tracker.getAge() < age)
        {
            currentState = STATE_NULL;
        }
    }
    
    
    else if(currentState == STATE_APPROACH){
        
        if (tracker.getScale() < scale)
        {
            currentState = STATE_WALK;
        }

        //if too much condition, it gets too sensitive
        if (classifier.getProbability(1) > nProb)
        {
            currentState = STATE_NEUTRAL_FACE;
        }
        
        else if (classifier.getProbability(2) > sProb)
        {
            currentState = STATE_OFFER;
        }
        
        else if (tracker.getAge() < age)
        {
            currentState = STATE_NULL;
        }
    }

    
    else if(currentState == STATE_OFFER)
    {
        if (classifier.getProbability(2) < sProb )
        {
            currentState = STATE_NEUTRAL_FACE;
        }
        
        else if (tracker.getAge() < age)
        {
            currentState = STATE_NULL;
        }
        
        else if (tracker.getScale() < scale)
        {
            currentState = STATE_WALK;
        }
    }
    
    
    else if(currentState == STATE_NEUTRAL_FACE)
    {
        if(tracker.getScale() < scale)
        {
            currentState = STATE_WALK;
        }

        else if(classifier.getProbability(2) > sProb)
        {
            currentState = STATE_OFFER;
        }
            
        else if (tracker.getAge() < age)
        {
            currentState = STATE_NULL;
        }
        
    }
    
    string states[5] = { " null", " walk"," approach", " neutral face", " offer"};
    std::cout<< "state" << states[currentState] << std::endl;
    
    
    
    switch (currentState)
    {
        case STATE_NULL:
        {
            break;
        }
            
            
        case STATE_WALK:
        {
            if (!currentTrack.isPlaying())
            {
                int randomTrack = (int)ofRandom(walkAudios.size());
                currentTrack = walkAudios[randomTrack];
                cout << "walk randomTrack: " << randomTrack << endl;
                currentTrack.play();
            }
            
            break;
        }
            
            
        case STATE_APPROACH:
        {
            if (!currentTrack.isPlaying())
            {
                int randomTrack = (int)ofRandom(approachAudios.size());
                currentTrack = approachAudios[randomTrack];
                cout << "appraoch randomTrack: " << randomTrack << endl;
                currentTrack.play();
            }
            
            break;
        }
            
            
        case STATE_NEUTRAL_FACE:
        {
            if (!currentTrack.isPlaying())
            {
                int randomTrack = (int)ofRandom(nfAudios.size());
                currentTrack = nfAudios[randomTrack];
                cout << "neutral f randomTrack: " << randomTrack << endl;
                currentTrack.play();
            }
    
            break;
        }
            
            
        case STATE_OFFER:
        {
            if (!currentTrack.isPlaying())
            {
                int randomTrack = (int)ofRandom(offerAudios.size());
                currentTrack = offerAudios[randomTrack];
                cout << "offer randomTrack: " << randomTrack << endl;
                currentTrack.play();
            }
            
            break;
        }
    }
}

void ofApp::draw() {
    
    std::cout << "age" <<tracker.getAge() << std::endl;
    std::cout << "scale" <<tracker.getScale() << std::endl;
    std::cout << "neutral probability"<<classifier.getProbability(2) << std::endl;
    
	ofSetColor(255);
	cam.draw(0, 0);
	tracker.draw();
    
	int w = 100, h = 12;
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(5, 10);
	int n = classifier.size();
	int primary = classifier.getPrimaryExpression();
	for(int i = 0; i < n; i++){
		ofSetColor(i == primary ? ofColor::red : ofColor::black);
		ofDrawRectangle(0, 0, w * classifier.getProbability(i) + .5, h);
		ofSetColor(255);
		ofDrawBitmapString(classifier.getDescription(i), 5, 9);
		ofTranslate(0, h + 5);
	}
	ofPopMatrix();
	ofPopStyle();
	
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
	ofDrawBitmapStringHighlight(
		string() +
		"r - reset\n" +
		"e - add expression\n" +
		"a - add sample\n" +
		"s - save expressions\n",
//		"l - load expressions",
		14, ofGetHeight() - 7 * 12);
    // maybe do this outside the screen???
    
//    std::cout<<"walk audio size"<<walkAudios.size()<<std::endl;
//    std::cout<<"bool:"<<walkAudios[0, 1, 2].isPlaying()<<std::endl; //seems like this does not really work
    
}

void ofApp::keyPressed(int key) {
    
	if(key == 'r') {
		tracker.reset();
		classifier.reset();
	}
	if(key == 'e') {
		classifier.addExpression();
	}
	if(key == 'a') {
		classifier.addSample(tracker);
	}
	if(key == 's') {
		classifier.save("expressions");
	}
//	if(key == 'l') {
//		classifier.load("expressions");
//	}
}
