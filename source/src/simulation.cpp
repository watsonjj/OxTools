//
// Created by Jason Watson on 05/02/2016.
//

#include <simulation.h>

vector<int> PMTSimulation::sCrosstalkVector;

void PMTSimulation::Init() {
	gRandom = new TRandom3(0);
	Reset();
}

void PMTSimulation::Reset() {
	delete gDirectory->FindObject("waveform");
	mContainerHist = new TH1F(Form("waveform"), "waveform", int(ceil(mConfig.GetReadoutWindow())/mConfig.GetPhotonBinning())+1, 0, mConfig.GetReadoutWindow());
	mLatepulseVector.clear();
	mTotal = 0;
	mLaserPhotons = 0;
	mNSBElectrons = 0;
	mPE = 0;
	mThermalElectrons = 0;
	mCrosstalkElectrons = 0;
	mScattered = 0;
	mMultiplied.clear();
	mWindowL = 0;
	mWindowR = 0;
	mMeasuredCharge = 0;
}

void PMTSimulation::Config::Init() {
	mNumEvents = 1;
	mMeanPhotonsPerPixel = 1;
	mLaserTimeMean = 22; // TODO: constant to look correct?
	mLaserTimeRMS = 0.01; // TODO: typical of a laser?
	mReadoutWindow = 90;
	mReadoutResolution = 1;
	mPhotonBinning = 1E-3;
	mNSBRate = 20E6;
	mQE = 0.35; 	// assume wavelength is 400nm and QE is 35% (from data sheet of PMT)
	mThermalRate = 20; // from given value of 20Hz at 25 degrees
	mCrosstalkProb = 0.01;
	mFirstDynodeScatterProb = 0.05; // (B. Lubsandorzhiev, 2000)
	mFirstDynodeScatterDelay = 4*2/8; // 2/8ths of Transit tims TODO: correct?
	mFirstDynodeScatterFWHM = 0.4; // same as jitter TODO: correct?
	mNDynodes = 8;
	mOverallGain = 3.3E5;
	mTransitTime = 4;
	mTransitJitter = 0.4;
	mCurrentBinning = 0.1;
	mResistance = 1E5;
	mTemperature = 293;
	mBandwidth = 1E15;
	mWindowSize = 5;

	mLaser = true;
	mNSB = false;
	mThermal = false;
	mCrosstalk = true;
	mLatepulse = true;
	mAnalogueNoise = true;
	mDigitalNoise = true;
}

void PMTSimulation::SingleRun() {
	Reset();
	if (mConfig.GetLaserActivated()) InjectLaserPhotons();
	ConvertPhotons();
	if (mConfig.GetNSBActivated()) InjectNSBPhotoelectrons();
	if (mConfig.GetThermalActivated()) InjectThermalElectrons();
	if (mConfig.GetCrosstalkActivated()) Crosstalk();
	if (mConfig.GetLatepulseActivated()) FirstDynodeScattering();
	DynodeChain();
	ConvertToVoltage();
	if (mConfig.GetAnalogueNoiseActivated()) AnalogueNoise();
	Digitise();
//			if (mConfig.GetDigitalNoiseActivated()) DigitalNoise();
	Integrate();
}

void PMTSimulation::Run(Filepath_ptr input, fs::path output_path) {

	// Extract camera geometry
	Run_ptr run = input->Read();
	Camera input_camera = run->GetCamera(0);
	int num_pixels = input_camera.GetNumPixels();

	// Create new run
	Run_ptr new_run = run;
	new_run->Init();
	for (auto& pixel_pair : input_camera.GetPixelMap()) {
		auto& pixel = pixel_pair.second;
		new_run->AddPixel(0,pixel);
	}

	Progress progress(GetConfig().GetNumEvents()*num_pixels, "Running Simulation : ",1);
	uint32_t count = 0;
	for (uint32_t c_event=0; c_event<mConfig.GetNumEvents(); c_event++) {
		for (uint32_t c_pixel=0; c_pixel<num_pixels; c_pixel++) {

			if (!input_camera.GetPixelMap().count(c_pixel)) continue;

			progress.Print(count++);
			Reset();
			if (mConfig.GetLaserActivated()) InjectLaserPhotons();
			ConvertPhotons();
			if (mConfig.GetNSBActivated()) InjectNSBPhotoelectrons();
			if (mConfig.GetThermalActivated()) InjectThermalElectrons();
			if (mConfig.GetCrosstalkActivated()) Crosstalk();
			if (mConfig.GetLatepulseActivated()) FirstDynodeScattering();
			DynodeChain();
			ConvertToVoltage();
			if (mConfig.GetAnalogueNoiseActivated()) AnalogueNoise();
			Digitise();
//			if (mConfig.GetDigitalNoiseActivated()) DigitalNoise();
			Integrate();

			// Add this entry to new_run
			Entry entry;
			entry.sInvestigation = "Simulation";
			entry.mEventId = c_event;
			entry.mSourceEventId = c_event;
			entry.mEventTimestamp = c_event;
			entry.mCameraId = 0;
			entry.mPixelId = c_pixel;
			entry.mBranchValueMap["fPulseHeight"] = 0;
			entry.mBranchValueMap["fPulseArea"] = (float) mMeasuredCharge;
			entry.mBranchValueMap["fPulsePosition"] = (float) mT0;
			entry.mBranchValueMap["fTrueNPE"] = mPE;
			new_run->AddEntry(0, entry);
		}
	}

	new_run->SetStats();
	new_run->Write(output_path);

}

void PMTSimulation::DrawRun(string output) {

	vector<string> titles = {"Laser","Photocathode","NSB","Crosstalk","Dynodes","Latepulses","Volts","AnalogueNoise","Digitised"};

	TCanvas* canvas = new TCanvas("c1", "c1", 4000, 3000);
	canvas->Divide(2,(int)titles.size());

	vector<TH1F *> saved_waveform_hists = WaveformSteps(titles);

	map<int,TH1F*> spectrums;
	for (int i = 0; i < titles.size(); i++) {
		spectrums[i] = new TH1F(Form("%d",i),titles[i].c_str(),200, -20, 20);
		spectrums[i]->SetCanExtend(TH1::kAllAxes);
	}

	Progress progress(GetConfig().GetNumEvents(), "Running Simulation : ",1);
	uint32_t count = 0;
	vector<double> Lwindows(9);
	vector<double> Rwindows(9);
	for (uint32_t c_event=0; c_event<GetConfig().GetNumEvents(); c_event++) {

		progress.Print(count++);

		vector<double> steps(9);
		Reset();
		InjectLaserPhotons();
		Integrate();
		Lwindows[0] = mContainerHist->GetBinLowEdge(GetWindowL());
		Rwindows[0] = mContainerHist->GetBinLowEdge(GetWindowR());
		steps[0] = GetMeasuredCharge();
		ConvertPhotons();
		Integrate();
		Lwindows[1] = mContainerHist->GetBinLowEdge(GetWindowL());
		Rwindows[1] = mContainerHist->GetBinLowEdge(GetWindowR());
		steps[1] = GetMeasuredCharge();
		InjectNSBPhotoelectrons();
		Integrate();
		Lwindows[2] = mContainerHist->GetBinLowEdge(GetWindowL());
		Rwindows[2] = mContainerHist->GetBinLowEdge(GetWindowR());
		steps[2] = GetMeasuredCharge();
		Crosstalk();
		Integrate();
		Lwindows[3] = mContainerHist->GetBinLowEdge(GetWindowL());
		Rwindows[3] = mContainerHist->GetBinLowEdge(GetWindowR());
		steps[3] = GetMeasuredCharge();

		delete gDirectory->FindObject("backup");
		TH1F *backup = (TH1F *) GetWaveform()->Clone("backup");
		DynodeChain();
		Integrate();
		Lwindows[4] = mContainerHist->GetBinLowEdge(GetWindowL());
		Rwindows[4] = mContainerHist->GetBinLowEdge(GetWindowR());
		steps[4] = GetMeasuredCharge();
		delete gDirectory->FindObject("waveform");
		mContainerHist = (TH1F *) backup->Clone("waveform");

		FirstDynodeScattering();
		DynodeChain();
		Integrate();
		Lwindows[5] = mContainerHist->GetBinLowEdge(GetWindowL());
		Rwindows[5] = mContainerHist->GetBinLowEdge(GetWindowR());
		steps[5] = GetMeasuredCharge();
		ConvertToVoltage();
		Integrate();
		Lwindows[6] = mContainerHist->GetBinLowEdge(GetWindowL());
		Rwindows[6] = mContainerHist->GetBinLowEdge(GetWindowR());
		steps[6] = GetMeasuredCharge();
		AnalogueNoise();
		Integrate();
		Lwindows[7] = mContainerHist->GetBinLowEdge(GetWindowL());
		Rwindows[7] = mContainerHist->GetBinLowEdge(GetWindowR());
		steps[7] = GetMeasuredCharge();
		Digitise();
		Integrate();
		Lwindows[8] = mContainerHist->GetBinLowEdge(GetWindowL());
		Rwindows[8] = mContainerHist->GetBinLowEdge(GetWindowR());
		steps[8] = GetMeasuredCharge();

		for (int i = 0; i < steps.size(); i++) {
			spectrums[i]->Fill(steps[i]);
		}
	}

	for (int i = 0; i<titles.size(); i++) {
		canvas->cd((2*i)+1);
		saved_waveform_hists[i]->SetStats(0);
		saved_waveform_hists[i]->SetTitle(titles[i].c_str());
		gStyle->SetTitleFontSize(0.09);
		saved_waveform_hists[i]->Draw();

		saved_waveform_hists[i]->GetYaxis()->SetLabelSize(0.1);
		saved_waveform_hists[i]->GetXaxis()->SetLabelSize(0.1);
		gPad->Update();
		TLine* Lline = new TLine(Lwindows[i],gPad->GetUymin(),Lwindows[i],gPad->GetUymax());
		TLine* Rline = new TLine(Rwindows[i],gPad->GetUymin(),Rwindows[i],gPad->GetUymax());
		Lline->SetLineColor(kRed);
		Rline->SetLineColor(kRed);
		Lline->Draw();
		Rline->Draw();

		canvas->cd((2*i)+2);
		spectrums[i]->SetStats(0);
		spectrums[i]->Draw();
		gPad->SetLogy();
		spectrums[i]->GetYaxis()->SetLabelSize(0.1);
		spectrums[i]->GetXaxis()->SetLabelSize(0.1);
	}

	fs::path save_directory = "~/Software/outputs/simulation";
	fs::path save_name = output + ".png";
	fs::path save_path = save_directory / save_name;
	if (boost::filesystem::create_directories(save_path.parent_path()))
		COUTP("[directory][new] "<< save_path);
	canvas->SaveAs(save_path.c_str());
	COUTP("[file][output] " << save_path);

}

void PMTSimulation::InjectLaserPhotons() {
	mLaserPhotons = (uint64_t)gRandom->Poisson(mConfig.GetMeanPhotonsPerPixel()); // does this need to be applied to each photon individually
	mTotal = mLaserPhotons;
	for (uint64_t i=0; i < mLaserPhotons; i++) {
		double t = gRandom->Gaus(mConfig.GetLaserTimeMean(), mConfig.GetLaserTimeRMS());
		mContainerHist->Fill(t);
	}
	mT0 = mConfig.GetLaserTimeMean();
	if (mVerbose) COUTP(Form("Laser Photons           %d (%d)", (uint32_t)mLaserPhotons,(uint32_t)mTotal));
}

void PMTSimulation::ConvertPhotons() {
	for (int bin=1; bin<mContainerHist->GetNbinsX()+1; bin++) {
		uint64_t nPhotons = (uint64_t) mContainerHist->GetBinContent(bin);
		uint64_t n = 0;
		for (uint64_t photon=0; photon<nPhotons; photon++) {
			if (gRandom->Uniform() <= mConfig.GetQuantumEfficiency()) {
				n++;
			}
		}
		mPE += n;
		mContainerHist->SetBinContent(bin, n);
	}
	mTotal = mPE;
	if (mVerbose) COUTP(Form("PhotoElectrons          %d (%d)", (uint32_t)mPE, (uint32_t)mTotal));
}

void PMTSimulation::InjectNSBPhotoelectrons() {
	//TODO: Should be added after QE?
	//TODO: NSB per pixel?
	mNSBElectrons = (uint64_t)gRandom->Poisson(mConfig.GetNSBRate() * 1E-9 * mConfig.GetReadoutWindow());
	for (uint64_t i = 0; i < mNSBElectrons; i++) {
		double t = mConfig.GetReadoutWindow()*gRandom->Uniform();
		mContainerHist->Fill(t);
	}
	mTotal += mNSBElectrons;
	if (mVerbose) COUTP(Form("NSB Electrons           %d (%d)", (uint32_t)mNSBElectrons, (uint32_t)mTotal));
}

void PMTSimulation::InjectThermalElectrons() {
	mThermalElectrons = (uint64_t)gRandom->Poisson(mConfig.GetThermalRate() * 1E-9 * mConfig.GetReadoutWindow());
	for (uint64_t i = 0; i < mThermalElectrons; i++) {
		double t = mConfig.GetReadoutWindow()*gRandom->Uniform();
		mContainerHist->Fill(t);
	}
	mTotal += mThermalElectrons;
	if (mVerbose) COUTP(Form("Thermal Electrons       %d (%d)", (uint32_t)mThermalElectrons, (uint32_t)mTotal));
}

void PMTSimulation::Crosstalk() {
	vector<int> saveVector;
	// Add electrons TODO: change this to be pixel dependant, maybe using a static map. Will need to loop through whole camera for each step
	for (int bin : sCrosstalkVector) {
		saveVector.push_back(bin);
		mCrosstalkElectrons++;
	}
	sCrosstalkVector.clear();
	// Remove electrons
	for (int bin=1; bin<mContainerHist->GetNbinsX()+1; bin++) {
		uint64_t nElectrons = (uint64_t) mContainerHist->GetBinContent(bin);
		for (uint64_t electron=0; electron < nElectrons; electron++) {
			if (gRandom->Uniform() <= mConfig.GetCrosstalkProb()) {
				sCrosstalkVector.push_back(bin);
				mCrosstalkElectrons--;
			}
			else {
				saveVector.push_back(bin);
			}
		}
	}
	// Store the electrons
	mContainerHist->Reset();
	for (int bin : saveVector) {
		mContainerHist->AddBinContent(bin);
	}
	mTotal += mCrosstalkElectrons;
	if (mVerbose) COUTP(Form("Crosstalk Electrons     %d (%d)", (uint32_t)mCrosstalkElectrons, (uint32_t)mTotal));
}

void PMTSimulation::FirstDynodeScattering() {
	vector<double> saveVector;
	for (int bin=1; bin<mContainerHist->GetNbinsX()+1; bin++) {
		uint64_t nElectrons = (uint64_t) mContainerHist->GetBinContent(bin);
		double t = mContainerHist->GetBinCenter(bin);
		for (uint64_t electron=0; electron < nElectrons; electron++) {
			if (gRandom->Uniform() <= mConfig.GetFirstDynodeScatterProb()) {
				mScattered++;
				double sigma = 2.3548 * mConfig.GetFirstDynodeScatterFWHM();
				double new_t = t + gRandom->Gaus(mConfig.GetFirstDynodeScatterDelay(),sigma);
				saveVector.push_back(new_t);
			}
			else {
				saveVector.push_back(t);
			}
		}
	}
	mContainerHist->Reset();
	for (double t : saveVector) {
		mContainerHist->Fill(t);
	}
	if (mVerbose) COUTP(Form("Scattered Electrons     %d (%d)", (uint32_t)mScattered, (uint32_t)mTotal));
}

void PMTSimulation::DynodeChain() {
	delete gDirectory->FindObject("multiplied");
	TH1F *multipliedHist = (TH1F *) mContainerHist->Clone("multiplied");
	for (int bin = 1; bin < mContainerHist->GetNbinsX() + 1; bin++) {
		uint64_t nElectrons = (uint64_t) mContainerHist->GetBinContent(bin);
		double t = mContainerHist->GetBinCenter(bin);
		for (uint64_t electron = 0; electron < nElectrons; electron++) {
			uint64_t n = 1;
			for (int dynode = 0; dynode < mConfig.GetNDynodes(); dynode++) {
				uint64_t m = 0;
				for (uint64_t e = 0; e < n; e++) {
					m += gRandom->Poisson(pow(mConfig.GetOverallGain(), (1.0 / mConfig.GetNDynodes())));
				}
				n = m;
				mMultiplied[dynode] += n;
			}
			for (uint64_t e = 0; e < n; e++) {
				double new_t = t + gRandom->Gaus(mConfig.GetTransitTime(), mConfig.GetTransitJitter());
				multipliedHist->Fill(new_t);
			}
		}
	}
	mT0 = mConfig.GetLaserTimeMean() + mConfig.GetTransitTime();
	delete gDirectory->FindObject("waveform");
	mContainerHist = (TH1F *) multipliedHist->Clone("waveform");
	for (int dynode = 0; dynode < mConfig.GetNDynodes(); dynode++) {
		mTotal = mMultiplied[dynode];
		if (mVerbose)
			COUTP(Form("Dynode %d Electrons      %d (%d)", dynode, (uint32_t)mMultiplied[dynode], (uint32_t)mTotal));
	}
}

void PMTSimulation::ConvertToVoltage() {
	float rebin =  (mContainerHist->GetNbinsX()) / (mConfig.GetReadoutWindow() / mConfig.GetCurrentBinning());
	mContainerHist->Rebin(int(rebin));
	for (int bin=1; bin<mContainerHist->GetNbinsX()+1; bin++) {
		double nElectrons = mContainerHist->GetBinContent(bin);
		double current = (nElectrons*1.6E-19)/(mConfig.GetCurrentBinning()*1E-9);
		double voltage = mConfig.GetResistance() * current;
		mContainerHist->SetBinContent(bin, voltage);
	}
}

void PMTSimulation::AnalogueNoise() {
	//TODO: fourier transform of noise spectrum...
	double variance = 4 * mConfig.GetTemperature() * 1.38E-23 * mConfig.GetResistance() *
	                  mConfig.GetBandwidth();
	for (int bin = 1; bin < mContainerHist->GetNbinsX() + 1; bin++) {
		double voltage = mContainerHist->GetBinContent(bin) + gRandom->Gaus(0, sqrt(variance));
		mContainerHist->SetBinContent(bin, voltage);
	}
}

void PMTSimulation::Digitise() {
	//TODO: add digitisation noise
	float rebin = mContainerHist->GetNbinsX() / (mConfig.GetReadoutWindow() / mConfig.GetReadoutResolution());
	mContainerHist->Rebin(int(rebin));
}

void PMTSimulation::Integrate() {
	// Find peak height
	mMeasuredCharge = 0.;
	mWindowL = mContainerHist->FindBin(mT0 - mConfig.mWindowSize/2);
	mWindowR = mContainerHist->FindBin(mT0 + mConfig.mWindowSize/2);
	double total = 0;
	for (int bin=1; bin<mContainerHist->GetNbinsX()+1; bin++) {
		double value = mContainerHist->GetBinContent(bin);
		total += value;
		if (bin >= mWindowL && bin < mWindowR) {
			mMeasuredCharge += value;
		}
	}
	if (mVerbose) COUTP(Form("Integrated              %f (%f)", mMeasuredCharge, total));
}

vector<TH1F*> PMTSimulation::WaveformSteps(vector<string> titles) {
	vector<TH1F *> saved_waveform_hists;
	while(true) {

		vector<TH1F *> waveform_hists(titles.size());
		for (int i=0; i<titles.size(); i++) {
			delete gDirectory->FindObject(titles[i].c_str());
		}

		Reset();
		InjectLaserPhotons();
		if (GetLaserPhotons() == 0) continue;
		waveform_hists[0] = (TH1F*)GetWaveform()->Clone(titles[0].c_str());
		ConvertPhotons();
		if (GetPhotoElectrons() == 0) continue;
		waveform_hists[1] = (TH1F*)GetWaveform()->Clone(titles[1].c_str());
		InjectNSBPhotoelectrons();
		if (mNSBElectrons == 0) continue;
		waveform_hists[2] = (TH1F*)GetWaveform()->Clone(titles[2].c_str());
		Crosstalk();
		if (GetCrosstalkElectrons() == 0) continue;
		waveform_hists[3] = (TH1F*)GetWaveform()->Clone(titles[3].c_str());

		delete gDirectory->FindObject("backup");
		TH1F* backup = (TH1F*)GetWaveform()->Clone("backup");
		DynodeChain();
		waveform_hists[4] = (TH1F*)GetWaveform()->Clone(titles[4].c_str());
		delete gDirectory->FindObject("waveform");
		mContainerHist = (TH1F*)backup->Clone("waveform");

		FirstDynodeScattering();
		if (GetScatteredElectrons() == 0) continue;
		DynodeChain();
		waveform_hists[5] = (TH1F*)GetWaveform()->Clone(titles[5].c_str());
		ConvertToVoltage();
		waveform_hists[6] = (TH1F*)GetWaveform()->Clone(titles[6].c_str());
		AnalogueNoise();
		waveform_hists[7] = (TH1F*)GetWaveform()->Clone(titles[7].c_str());
		Digitise();
		waveform_hists[8] = (TH1F*)GetWaveform()->Clone(titles[8].c_str());
		saved_waveform_hists = waveform_hists;
		COUTP("Finished stage 1");
		break;
	}
	return saved_waveform_hists;
}
