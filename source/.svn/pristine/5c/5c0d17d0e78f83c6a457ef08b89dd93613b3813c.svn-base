//
// Created by Lucy Martin on 12/12/15.
//

#ifndef OXTOOLS_SIMULATION_H
#define OXTOOLS_SIMULATION_H

#include <initialise.h>
#include <utilities.h>
#include <Filepath.h>


class PMTSimulation {
private:
	 class Config{
		  friend class PMTSimulation;
	 private:
		  Config() {Init();}
		  uint32_t mNumEvents;
		  int mMeanPhotonsPerPixel;
		  float mLaserTimeMean;
		  float mLaserTimeRMS;
		  float mReadoutWindow; // ns
		  float mReadoutResolution; // ns
		  float mPhotonBinning;
		  float mQE;
		  float mNSBRate; // Hz
		  float mThermalRate;
		  float mCrosstalkProb;
		  float mFirstDynodeScatterProb;
		  float mFirstDynodeScatterDelay;
		  float mFirstDynodeScatterFWHM;
		  int mNDynodes;
		  double mOverallGain;
		  float mTransitTime; // ns
		  float mTransitJitter; // ns
		  float mCurrentBinning;
		  float mResistance;
		  float mTemperature;
		  float mBandwidth;
		  double mWindowSize;


		  bool mLaser;
		  bool mNSB;
		  bool mThermal;
		  bool mCrosstalk;
		  bool mLatepulse;
		  bool mAnalogueNoise;
		  bool mDigitalNoise;



		  void Init();
	 public:
		  GETSET(NumEvents, mNumEvents, uint32_t);
		  GETSET(MeanPhotonsPerPixel, mMeanPhotonsPerPixel, int);
		  GETSET(LaserTimeMean,mLaserTimeMean,float);
		  GETSET(LaserTimeRMS,mLaserTimeRMS,float);
		  GETSET(ReadoutWindow,mReadoutWindow,float);
		  GETSET(ReadoutResolution,mReadoutResolution,float);
		  GETSET(PhotonBinning,mPhotonBinning,float);
		  GETSET(QuantumEfficiency,mQE,float);
		  GETSET(NSBRate,mNSBRate,float);
		  GETSET(ThermalRate,mThermalRate,float);
		  GETSET(CrosstalkProb,mCrosstalkProb,float);
		  GETSET(FirstDynodeScatterProb,mFirstDynodeScatterProb,float);
		  GETSET(FirstDynodeScatterDelay,mFirstDynodeScatterDelay,float);
		  GETSET(FirstDynodeScatterFWHM,mFirstDynodeScatterFWHM,float);
		  GETSET(NDynodes,mNDynodes,int);
		  GETSET(OverallGain,mOverallGain,double);
		  GETSET(TransitTime,mTransitTime,float);
		  GETSET(TransitJitter,mTransitJitter,float);
		  GETSET(CurrentBinning,mCurrentBinning,float);
		  GETSET(Resistance,mResistance,float);
		  GETSET(Temperature,mTemperature,float);
		  GETSET(Bandwidth,mBandwidth,float);
		  GETSET(WindowSize,mWindowSize,float);


		  GETSET(LaserActivated, mLaser, bool);
		  GETSET(NSBActivated, mNSB, bool);
		  GETSET(ThermalActivated, mThermal, bool);
		  GETSET(CrosstalkActivated, mCrosstalk, bool);
		  GETSET(LatepulseActivated, mLatepulse, bool);
		  GETSET(AnalogueNoiseActivated, mAnalogueNoise, bool);
		  GETSET(DigitalNoiseActivated, mDigitalNoise, bool);

	 };
	 Config mConfig;

	 bool mVerbose;
	 TH1F* mContainerHist;
	 vector<double> mLatepulseVector;
	 static vector<int> sCrosstalkVector;
	 uint64_t mTotal;
	 uint64_t mLaserPhotons;
	 uint64_t mPE;
	 uint64_t mNSBElectrons;
	 uint64_t mThermalElectrons;
	 uint64_t mCrosstalkElectrons;
	 uint64_t mScattered;
	 map<int,uint64_t> mMultiplied;
	 double mT0;
	 int mWindowL;
	 int mWindowR;
	 double mMeasuredCharge;

	 void Init();
	 void Reset();
	 void InjectLaserPhotons();
	 void ConvertPhotons();
	 void InjectNSBPhotoelectrons();
	 void InjectThermalElectrons();
	 void Crosstalk();
	 void FirstDynodeScattering();
	 void DynodeChain();
	 void ConvertToVoltage();
	 void AnalogueNoise();
	 void Digitise();
	 void Integrate();


public:
	 PMTSimulation() {Init();}

	 void Run(Filepath_ptr input, fs::path output_path);
	 void SingleRun();
	 void DrawRun(string output);

	 vector<TH1F*> WaveformSteps(vector<string> titles);

	 GETREF(Config, mConfig, Config);
	 SET(Verbosity, mVerbose, bool); // 0 = silent, 1 = print step outcomes
	 GET(Waveform, mContainerHist, TH1F*)
	 GET(LaserPhotons, mLaserPhotons, uint64_t);
	 GET(PhotoElectrons, mPE, uint64_t);
	 GET(NSBElectrons, mNSBElectrons, uint64_t);
	 GET(ThermalElectrons, mThermalElectrons, uint64_t);
	 GET(CrosstalkElectrons, mCrosstalkElectrons, uint64_t);
	 GET(ScatteredElectrons, mScattered, uint64_t);
	 GET(WindowL, mWindowL, int);
	 GET(WindowR, mWindowR, int);
	 GET(MeasuredCharge, mMeasuredCharge, double);
};

#endif //OXTOOLS_SIMULATION_H
