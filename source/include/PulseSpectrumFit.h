//
// Created by Lucy Martin on 05/02/16.
//

#ifndef OXTOOLS_PULSESPECTRUMFIT_H
#define OXTOOLS_PULSESPECTRUMFIT_H

#include <initialise.h>
#include <utilities.h>

class PulseSpectrumFit {
private:
	 TH1F* mSpectrum;
	 string mType; // Type of fit to perform
	 fs::path mOutput;
	 TH1F* mCalibSpectrum;

	 double mXmin;
	 double mXmax;
	 int mMaxPhotons;
	 TH1F* mPedRisingEdgeSpectrum;
	 TH1F* mLowPESpectrum;
	 TH1F* mHighInitialSpectrum;
	 TH1F* mHighSpectrum;
	 TF1* mPedRisingEdgeFit;
	 TF1* mLowPEFit;
	 TF1* mHighInitialFit;
	 TF1* mHighFit;
	 Double_t mPedRisingEdgePar[6];
	 Double_t mLowPEPar[11];
	 Double_t mHighInitialPar[3];
	 Double_t mHighPar[7];
	 Double_t mCalibPar[11];
	 map<uint,TF1*> mPEMap;


	 void Init();
	 void FitPedRisingEdge();
	 void FitLowPE();
	 void FitHighPE();





public:
	 PulseSpectrumFit(TH1F* spectrum, string type, fs::path output, TH1F* calib_spectrum = nullptr)
			   : mSpectrum(spectrum),
	           mType(type),
	           mOutput(output),
	           mCalibSpectrum(calib_spectrum)
	 {
		 Init();
		 mXmin = mSpectrum->GetXaxis()->GetXmin();
		 mXmax = mSpectrum->GetXaxis()->GetXmax();
		 if (strcmp(type.c_str(), "low") == 0) {
			 FitLowPE();
			 for (int i = 0; i < 11; i++) {
				 mCalibPar[i] = mLowPEPar[i];
			 }
			 DrawPedRisingEdge(fs::path(mOutput.string() + "PedRisingEdge.png"));
			 DrawLowPE(fs::path(mOutput.string() + "LowPE.png"));
		 }
		 if (strcmp(type.c_str(), "high") == 0) {
			 if (!calib_spectrum) THROW("calib_spectrum is nullptr");

			 mSpectrum = mCalibSpectrum;
			 mXmin = mSpectrum->GetXaxis()->GetXmin();
			 mXmax = mSpectrum->GetXaxis()->GetXmax();
			 FitLowPE();
			 for (int i = 0; i < 11; i++) {
				 mCalibPar[i] = mLowPEPar[i];
			 }
			 DrawLowPE(fs::path(mOutput.string() + "Calib.png"));
			 mSpectrum = spectrum;
			 mXmin = mSpectrum->GetXaxis()->GetXmin();
			 mXmax = mSpectrum->GetXaxis()->GetXmax();

			 FitHighPE();
			 DrawHighInitial(fs::path(mOutput.string() + "HighInitial.png"));
			 DrawHigh(fs::path(mOutput.string() + "High.png"));
		 }
		 if (strcmp(type.c_str(), "both") == 0) {
			 if (!calib_spectrum) THROW("calib_spectrum is nullptr");

			 mSpectrum = mCalibSpectrum;
			 mXmin = mSpectrum->GetXaxis()->GetXmin();
			 mXmax = mSpectrum->GetXaxis()->GetXmax();
			 FitLowPE();
			 for (int i = 0; i < 11; i++) {
				 mCalibPar[i] = mLowPEPar[i];
			 }
			 DrawLowPE(fs::path(mOutput.string() + "Calib.png"));
			 mSpectrum = spectrum;
			 mXmin = mSpectrum->GetXaxis()->GetXmin();
			 mXmax = mSpectrum->GetXaxis()->GetXmax();

			 FitLowPE();
			 DrawPedRisingEdge(fs::path(mOutput.string() + "PedRisingEdge.png"));
			 DrawLowPE(fs::path(mOutput.string() + "LowPE.png"));
			 FitHighPE();
			 DrawHighInitial(fs::path(mOutput.string() + "HighInitial.png"));
			 DrawHigh(fs::path(mOutput.string() + "High.png"));
		 }
	 }

	 void DrawPedRisingEdge(fs::path output);
	 void DrawLowPE(fs::path output);
	 void DrawHighInitial(fs::path output);
	 void DrawHigh(fs::path output);
	 float GetTrueCharge(float x);
	 float ConvertMeasuredCharge(float x);
};

#endif //OXTOOLS_PULSESPECTRUMFIT_H
