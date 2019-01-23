//
// Created by Jason Watson on 04/11/15.
//

#include <HillasParameter.h>
#include <Camera.h>

void HillasParameter::Init() {
	mIntensity = 0;
	mXCenter = 0;
	mYCenter = 0;
	mPhi = 0;
	mLength = 0;
	mWidth = 0;
	mMissPart = 0;
	mMiss = 0;
	mDistance = 0;
	mAzwidth = 0;
	mSdash_x3 = 0;
	mAsymmetry = 0;
	mMissDist = 0;
	mAlpha = 0;
	mEllipse = NULL;
	mWidthLine = NULL;
	mLengthLine = NULL;
	mEllipseCenter = NULL;
}

//Function to calculate hillas parameters and return a set of structure hillas
void HillasParameter::SetHillasParameter(string branch_name) {

	double pi = TMath::Pi();

	//Intialise the variables
	double nx_sum = 0;
	double nx2_sum = 0;
	double nx3_sum = 0;
	double ny_sum = 0;
	double ny2_sum = 0;
	double ny3_sum = 0;
	double nxy_sum = 0;
	double nx2y_sum = 0;
	double nxy2_sum = 0;

	double x = 0;
	double y = 0;
	double n = 0;


//calculate sums of pixel position and amplitude
	for (auto &entry_pair : pEvent->GetEntryMap()) {
		auto &entry = entry_pair.second;
		int pixel_id = entry.GetPixelId();

		x = pEvent->GetCamera()->GetPixel(pixel_id).GetXpix();
		y = pEvent->GetCamera()->GetPixel(pixel_id).GetYpix();
		n = entry.GetBranchValue(branch_name);

		mIntensity += n;

		nx_sum += n * x;
		ny_sum += n * y;
		nxy_sum += n * x * y;

		nx2_sum += n * x * x;
		ny2_sum += n * y * y;

		nx3_sum += n * x * x * x;
		ny3_sum += n * y * y * y;

		nx2y_sum += n * x * x * y;
		nxy2_sum += n * x * y * y;
	}

//calculate moments
	mXCenter = nx_sum / mIntensity;
	double x2_m = nx2_sum / mIntensity;
	double x3_m = nx3_sum / mIntensity;
	mYCenter = ny_sum / mIntensity;
	double y2_m = ny2_sum / mIntensity;
	double y3_m = ny3_sum / mIntensity;
	double xy_m = nxy_sum / mIntensity;
	double x2y_m = nx2y_sum / mIntensity;
	double xy2_m = nxy2_sum / mIntensity;

//calculate deviations
	double s_x2 = x2_m - (mXCenter * mXCenter);
	double s_x3 = x3_m - (3 * mXCenter * x2_m) + (2 * mXCenter * mXCenter * mXCenter);
	double s_y2 = y2_m - (mYCenter * mYCenter);
	double s_y3 = y3_m - (3 * mYCenter * y2_m) + (2 * mYCenter * mYCenter * mYCenter);
	double s_xy = xy_m - (mXCenter * mYCenter);
	double s_xy2 = xy2_m - (2 * mYCenter * xy_m) - (y2_m * mXCenter)
	               + (2 * mXCenter * mYCenter * mYCenter);
	double s_x2y = x2y_m - (2 * mXCenter * xy_m) - (x2_m * mYCenter)
	               + (2 * mYCenter * mXCenter * mXCenter);

// intermediary
	double d = s_y2 - s_x2;
	double s = sqrt((d * d) + (4 * s_xy * s_xy));
	double u = 1.0 - d / s;
	double v = 2.0 - u;
	double w = sqrt(4 * (y2_m - x2_m) * (y2_m - x2_m) * xy_m * xy_m);
	double tan_phi = ((d + s) * mYCenter + 2 * s_xy * mXCenter)
	                 / (2 * s_xy * mYCenter - (d - s) * mXCenter);

//calculate Hillas parameters
	mPhi = atan(tan_phi);
	mLength = sqrt((s_x2 + s_y2 + s) / 2);
	mWidth = sqrt((s_x2 + s_y2 - s) / 2);
	mMissPart = (1.0 / 3) * (u * mXCenter * mXCenter + v * mYCenter * mYCenter) -
	            (2 * s_xy * mXCenter * mYCenter / s);
	mMiss = sqrt(mMissPart);
	mDistance = sqrt(mXCenter * mXCenter + mYCenter * mYCenter);
	mAzwidth = sqrt((mXCenter * mXCenter * y2_m - 2 * mXCenter * mYCenter * xy_m +
	                 x2_m * mYCenter * mYCenter) / (mDistance * mDistance));
	mSdash_x3 = s_x3 * pow(cos(mPhi), 3) +
			  3 * s_x2y * pow(cos(mPhi), 2) * sin(mPhi) + 3 * s_xy2 * cos(mPhi) * pow(sin(mPhi), 2)
			      + s_y3 * pow(sin(mPhi), 3);
	mAsymmetry = (pow(mSdash_x3, (1.0 / 3))) / mLength;
	mMissDist = mMiss / mDistance;
	mAlpha = (asin(mMissDist)) * 180 / pi;

}

void HillasParameter::Draw() {
	DrawEllipse();
	DrawWidthLine();
	DrawLengthLine();
	DrawEllipseCenter();
}

void HillasParameter::DrawEllipse() {
	if (!mEllipse) {
		double rotation = TMath::Pi() / 2 + mPhi;
		mEllipse = new TEllipse(mXCenter, mYCenter, mWidth, mLength);
		mEllipse->SetTheta(rotation * 180 / TMath::Pi());
		mEllipse->SetFillColorAlpha(kWhite, 0.2);
		mEllipse->SetLineColor(kMagenta);
		mEllipse->SetLineWidth(2);
	}
	mEllipse->Draw("same");
}

void HillasParameter::DrawWidthLine() {
	if (!mWidthLine) {
		double rotation = TMath::Pi() / 2 + mPhi;
		double wx1 = mXCenter + mWidth * cos(rotation);
		double wx2 = mXCenter + mWidth * cos(rotation + TMath::Pi());
		double wy1 = mYCenter + mWidth * sin(rotation);
		double wy2 = mYCenter + mWidth * sin(rotation + TMath::Pi());
		mWidthLine = new TLine(wx1, wy1, wx2, wy2);
		mWidthLine->SetLineColor(kMagenta);
		mWidthLine->Draw();
	}
	mWidthLine->Draw("same");
}

void HillasParameter::DrawLengthLine() {
	if (!mLengthLine) {
		double rotation = TMath::Pi() / 2 + mPhi;
		double lx1 = mXCenter - mLength * sin(rotation);
		double lx2 = mXCenter - mLength * sin(rotation + TMath::Pi());
		double ly1 = mYCenter + mLength * cos(rotation);
		double ly2 = mYCenter + mLength * cos(rotation + TMath::Pi());
		mLengthLine = new TLine(lx1, ly1, lx2, ly2);
		mLengthLine->SetLineColor(kMagenta);
		mLengthLine->Draw();
	}
	mLengthLine->Draw("same");
}

void HillasParameter::DrawEllipseCenter() {
	if (!mEllipseCenter) {
		mEllipseCenter = new TGraph();
		mEllipseCenter->SetPoint(mEllipseCenter->GetN(), mXCenter, mYCenter);
		mEllipseCenter->SetMarkerColor(kMagenta + 1);
	}
	mEllipseCenter->Draw("* same");
}
