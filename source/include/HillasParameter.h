//
// Created by Jason Watson on 04/11/15.
//

/* UNFINISHED
 * Subclass of the Event class. Calculates and holds the hillas parameters for an event.
 */

#ifndef OXTOOLS_HILLASPARAMETER_H
#define OXTOOLS_HILLASPARAMETER_H

#include <initialise.h>

class Event;

class HillasParameter {
	 friend class Event;
private:
	 HillasParameter(Event* event, string branch_name) : pEvent(event) {
		 Init();
		 SetHillasParameter(branch_name);
	 }

	 Event* pEvent;
	 double mIntensity;      // photo electrons in imageF		//Intensity is like n_sum
	 double mXCenter;
	 double mYCenter;
	 double mPhi;          // angle of major ellipse axis with respect to x-axis (rads)
	 double mLength;       // length of ellipse (cm????)
	 double mWidth;        // width of ellipse
	 double mMissPart;
	 double mMiss;
	 double mDistance;
	 double mAzwidth;
	 double mSdash_x3;
	 double mAsymmetry;
	 double mMissDist;
	 double mAlpha;

	 TEllipse* mEllipse; 		// Hillas ellipse
	 TLine* mWidthLine;
	 TLine* mLengthLine;
	 TGraph* mEllipseCenter;

	 void SetHillasParameter(string branch_name);
	 void Init();
	 void DrawEllipse();
	 void DrawWidthLine();
	 void DrawLengthLine();
	 void DrawEllipseCenter();

public:
	 void Draw();

	 GET(Event,pEvent,Event*)
	 GET(Intensity, mIntensity, double);
	 GET(XCenter, mXCenter, double);
	 GET(YCenter, mYCenter, double);
	 GET(Phi, mPhi, double);
	 GET(Length, mLength, double);
	 GET(Width, mWidth, double);
	 GET(MissPart, mMissPart, double);
	 GET(Miss, mMiss, double);
	 GET(Distance, mDistance, double);
	 GET(Azwidth, mAzwidth, double);
	 GET(Sdash_x3, mSdash_x3, double);
	 GET(Asymmetry, mAsymmetry, double);
	 GET(MissDist, mMissDist, double);
	 GET(Alpha, mAlpha, double);

};



#endif //OXTOOLS_HILLASPARAMETER_H
