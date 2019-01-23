//
// Created by Jason Watson on 08/04/2016.
//

#include "PulseSpectrumFit.h"

double_t gaussianFunction(Double_t *x, Double_t *par) {
	return par[0] * (ROOT::Math::normal_pdf(x[0], par[2], par[1]));
}

double_t risingedgeFunction(Double_t *x, Double_t *par) {
	return (par[3] * // scaling parameter
	        (ROOT::Math::normal_pdf(x[0], ((sqrt(1)) * par[5]),
	                                (1 * par[4])))); // normal dist for dynodes
}

double_t pbnFunction(Double_t *x, Double_t *par, uint i, uint k) {
	return (par[3] * // scaling parameter
	        (ROOT::Math::poisson_pdf(i, par[6])) *// poisson distribution of incoming photons
	        (ROOT::Math::binomial_pdf(k, par[7], i)) * // binomial for quantum efficiency
	        (ROOT::Math::normal_pdf(x[0], ((sqrt(k)) * par[5]),
	                                (k * par[4])))); // normal dist for dynodes
}

double_t pbnNSBFunction(Double_t *x, Double_t *par, uint i, uint k) {
	return (par[3] * // scaling parameter
	        (ROOT::Math::poisson_pdf(i, par[8])) *// poisson distribution of incoming photons
	        (ROOT::Math::binomial_pdf(k, par[7], i)) * // binomial for quantum efficiency
	        (ROOT::Math::normal_pdf(x[0], ((sqrt(k)) * par[5]),
	                                (k * par[4])))); // normal dist for dynodes
}

double_t pedrisingFunction(Double_t *x, Double_t *par) {
	double_t xtotal = gaussianFunction(x, par); // pedestal
	xtotal += risingedgeFunction(x, par); //rising edge
	return xtotal;
}

double_t lowPEFunction(Double_t *x, Double_t *par, int maxPhotons) {
	double_t xtotal = gaussianFunction(x, par); // pedestal
	for (uint i = 1; i <= maxPhotons; ++i) {
		for (uint k = i; k > 0; k--) {
			xtotal += pbnFunction(x, par, i, k);
		}
	}
	return xtotal;
}

double_t lowPENSBFunction(Double_t *x, Double_t *par, int maxPhotons) {
	double_t xtotal = gaussianFunction(x, par); // pedestal
	for (uint i = 1; i <= maxPhotons; ++i) {
		for (uint k = i; k > 0; k--) {
			xtotal += pbnFunction(x, par, i, k);
			xtotal += pbnNSBFunction(x, par, i, k);
		}
	}
	return xtotal;
}

double_t pbnGaussianFunction(Double_t *x, Double_t *par, uint i, uint k) {
	return (par[0]
	        * ((1/(sqrt(par[3])*sqrt(2*M_PI)))*exp(-pow((i-par[3]),2)/(2*par[3])))// Photon dist
	        * ((1/(sqrt(par[4]*(1-par[4])*i)*sqrt(2*M_PI)))*exp(-pow((k-(i*par[4])),2)/(2*(par[4]*(1-par[4])*i))))// Quantum efficiency
	        * (ROOT::Math::normal_pdf(x[0], ((sqrt(k)) * par[2]), (k * par[1])))); // normal from dynodes
}

double_t highPEFunction(Double_t *x, Double_t *par) {
	double_t xtotal = 0;
	for (int i = (int)par[5]; i <= par[6]; ++i)
	{
		for (int k = i; k> 0; k--)
		{
			// approximate poisson with normal dist
			// approx binomial with normal distribution
			xtotal += pbnGaussianFunction(x, par, i, k);
		}
	}


	return xtotal;
}

void PulseSpectrumFit::Init() {
	mXmin = 0;
	mXmax = 0;
	mMaxPhotons = 20; // TODO: change to user specified
	mPedRisingEdgeFit = nullptr;
	mLowPEFit = nullptr;
	mHighInitialFit = nullptr;
	mHighFit = nullptr;
	memset(mPedRisingEdgePar, 0, sizeof mPedRisingEdgePar);
	memset(mLowPEPar, 0, sizeof mLowPEPar);
	memset(mHighInitialPar, 0, sizeof mHighInitialPar);
	memset(mHighPar, 0, sizeof mHighPar);
	memset(mCalibPar, 0, sizeof mCalibPar);
	mPEMap.clear();

	gStyle->SetOptFit(1112);
	gStyle->SetOptStat(0);
}

void PulseSpectrumFit::FitPedRisingEdge() {
	mPedRisingEdgeSpectrum = (TH1F*) mSpectrum->Clone("PedRisingEdge");

	mPedRisingEdgeFit = new TF1("pedrisingFit", pedrisingFunction, mXmin, 60, 6);
	mPedRisingEdgeFit->SetParameter(0, 2E5); // Pedestal Scale
	mPedRisingEdgeFit->FixParameter(1, 0);   // Pedestal Mean
	mPedRisingEdgeFit->SetParameter(2, 10);  // Pedestal stddev
	mPedRisingEdgeFit->SetParameter(3, 2E5); // Normal Scale
	mPedRisingEdgeFit->SetParameter(4, 45);  // Normal Mean
	mPedRisingEdgeFit->SetParameter(5, 20);  // Normal stddev

	mPedRisingEdgeFit->SetParName(0, "Pedestal scale ");
	mPedRisingEdgeFit->SetParName(1, "Pedestal mean  ");
	mPedRisingEdgeFit->SetParName(2, "Pedestal stddev");
	mPedRisingEdgeFit->SetParName(3, "Scale          ");
	mPedRisingEdgeFit->SetParName(4, "Gaussian mean  ");
	mPedRisingEdgeFit->SetParName(5, "Gaussian stddev");

	mPedRisingEdgeSpectrum->Fit("pedrisingFit", "0");
	mPedRisingEdgeFit->GetParameters(mPedRisingEdgePar);
}

void PulseSpectrumFit::FitLowPE() {
	mLowPESpectrum = (TH1F*) mSpectrum->Clone("LowPE");

	FitPedRisingEdge();
	auto lowPELambda = [this](Double_t *x, Double_t *par) {
		 return lowPEFunction(x, par, mMaxPhotons);
	};
	mLowPEFit = new TF1("lowPEFit", lowPELambda, mXmin, mXmax, 9);
	mLowPEFit->SetParameter(0, mPedRisingEdgePar[0]); // Pedestal scale
	mLowPEFit->FixParameter(1, mPedRisingEdgePar[1]); // Pedestal mean
	mLowPEFit->SetParameter(2, mPedRisingEdgePar[2]); // Pedestal stddev
	mLowPEFit->SetParameter(3, mPedRisingEdgePar[3]); // Scale
	mLowPEFit->SetParameter(4, mPedRisingEdgePar[4]); // Gaussian mean
	mLowPEFit->SetParameter(5, mPedRisingEdgePar[5]); // Gaussian stddev
	mLowPEFit->SetParameter(6, 1);                    // Lambda (Poisson mean)
	mLowPEFit->FixParameter(7, 0.35);                 // Quantum Efficiency
	mLowPEFit->FixParameter(8, 0);                    // NSB rate

	mLowPEFit->SetParName(0, "Pedestal scale ");
	mLowPEFit->SetParName(1, "Pedestal mean  ");
	mLowPEFit->SetParName(2, "Pedestal stddev");
	mLowPEFit->SetParName(3, "Scale          ");
	mLowPEFit->SetParName(4, "Gaussian mean  ");
	mLowPEFit->SetParName(5, "Gaussian stddev");
	mLowPEFit->SetParName(6, "Lambda         ");
	mLowPEFit->SetParName(7, "QE             ");
	mLowPEFit->SetParName(8, "NSB            ");

	mLowPESpectrum->Fit("lowPEFit", "0");
	mLowPEFit->GetParameters(mLowPEPar);

	mPEMap.clear();
	for (uint k=1; k <= mMaxPhotons; k++) {
		auto pbnLambda = [k, this](Double_t *x, Double_t *par) {
			 double_t xtotal = 0;
			 for (uint i = 1; i <= mMaxPhotons; ++i) {
				 xtotal += pbnFunction(x, par, i, k); // normal dist for dynodes
			 }
			 return xtotal;
		};
		TF1 *gaussian = new TF1("gaussian", pbnLambda, mXmin, mXmax, 9);
		gaussian->SetParameters(mLowPEPar);
		mPEMap[k] = gaussian;
	}
	TF1 *pedestal = new TF1("pedestal", gaussianFunction, mXmin, mXmax, 9);
	pedestal->SetParameters(mLowPEPar);
	mPEMap[0] = pedestal;
}

void PulseSpectrumFit::FitHighPE() {
	mHighInitialSpectrum = (TH1F*) mSpectrum->Clone("HighInitial");

	mHighInitialFit = new TF1("highInitialFit", gaussianFunction, mXmin, mXmax, 3);
	mHighInitialFit->SetParameter(0, 2E6); // Scale
	mHighInitialFit->SetParameter(1, mSpectrum->GetMean()); // Mean
	mHighInitialFit->SetParameter(2, mSpectrum->GetStdDev());    // Stddev

	mHighInitialFit->SetParName(0, "Scale ");
	mHighInitialFit->SetParName(1, "Mean  ");
	mHighInitialFit->SetParName(2, "Stddev");

	mHighInitialSpectrum->Fit("highInitialFit", "0");
	mHighInitialFit->GetParameters(mHighInitialPar);

	mHighSpectrum = (TH1F*) mSpectrum->Clone("High");

	mHighFit = new TF1("highFit", highPEFunction, mXmin, mXmax, 7);
	double lambdaGuess = mHighInitialPar[1]/ (mCalibPar[7]*mCalibPar[4]);
	int lower = int(lambdaGuess - (3)*sqrt(lambdaGuess));
	int upper = int(lambdaGuess + (3)*sqrt(lambdaGuess));

	mHighFit->SetParameter(0, 2E6);          // Gaussian scale
	mHighFit->SetParameter(1, mCalibPar[4]); // Gaussian mean
	mHighFit->SetParameter(2, mCalibPar[5]); // Gaussian stddev
	mHighFit->SetParameter(3, lambdaGuess);  // Lambda (Poisson mean)
	mHighFit->FixParameter(4, mCalibPar[7]); // Quantum Efficiency
	mHighFit->FixParameter(5, lower);        // lower limit for scanning over incoming photons
	mHighFit->FixParameter(6, upper);        // upper limit for scanning over incoming photons

	mHighFit->SetParName(0, "Gaussian scale ");
	mHighFit->SetParName(1, "Gaussian mean  ");
	mHighFit->SetParName(2, "Gaussian stddev");
	mHighFit->SetParName(3, "Lambda         ");
	mHighFit->SetParName(4, "QE             ");
	mHighFit->SetParName(5, "lower          ");
	mHighFit->SetParName(6, "high           ");

	mHighSpectrum->Fit("highFit", "0");
	mHighFit->GetParameters(mHighPar);

	mPEMap.clear();
	for (uint k=1; k <= (uint)mHighPar[6]; k++) {
		auto pbnGaussianLambda = [k, this](Double_t *x, Double_t *par) {
			 double_t xtotal = 0;
			 for (uint i = (uint)mHighPar[5]; i <= (uint)mHighPar[6]; ++i) {
				 xtotal += pbnGaussianFunction(x, par, i, k); // normal dist for dynodes
			 }
			 return xtotal;
		};
		TF1 *gaussian = new TF1("gaussian", pbnGaussianLambda, mXmin, mXmax, 9);
		gaussian->SetParameters(mHighPar);
		mPEMap[k] = gaussian;
	}
}

void PulseSpectrumFit::DrawPedRisingEdge(fs::path output) {
	TCanvas *canvas = new TCanvas("cPedRisingEdge", "cPedRisingEdge", 3000, 2000);

	mPedRisingEdgeSpectrum->Draw("E");

	TF1 *pedestal = new TF1("pedestal", gaussianFunction, mXmin, mXmax, 6);
	pedestal->SetParameters(mPedRisingEdgePar);
	pedestal->SetNpx(1000);
	pedestal->SetLineWidth(2);
	pedestal->SetLineColor(kRed);
	pedestal->Draw("same");

	TF1 *risingedge = new TF1("risingedge", risingedgeFunction, mXmin, mXmax, 6);
	risingedge->SetParameters(mPedRisingEdgePar);
	risingedge->SetNpx(500);
	risingedge->SetLineWidth(2);
	risingedge->SetLineColor(kBlue);
	risingedge->Draw("same");

	mPedRisingEdgeFit->SetNpx(500);
	mPedRisingEdgeFit->SetLineWidth(2);
	mPedRisingEdgeFit->SetLineColor(kMagenta);
	mPedRisingEdgeFit->Draw("same");

	mPedRisingEdgeSpectrum->SetTitle("PedRisingEdge");
	mPedRisingEdgeSpectrum->SetXTitle("Measured Charge (ADC)");
	mPedRisingEdgeSpectrum->SetYTitle("Frequency");
	mPedRisingEdgeSpectrum->GetXaxis()->SetTitleOffset(1.4);
	mPedRisingEdgeSpectrum->GetYaxis()->SetTitleOffset(1.4);

	if (boost::filesystem::create_directories(output.parent_path()))
		COUTP("[directory][new] " << output);
	canvas->SaveAs(output.c_str());
	COUTP("[file][output] " << output);
}

void PulseSpectrumFit::DrawLowPE(fs::path output) {
	TCanvas *canvas = new TCanvas(output.c_str(), output.c_str(), 3000, 2000);
	mLowPESpectrum->Draw("E");

	TF1 *pedestal = new TF1("pedestal", gaussianFunction, mXmin, mXmax, 9);
	pedestal->SetParameters(mLowPEPar);
	pedestal->SetNpx(1000);
	pedestal->SetLineWidth(2);
	pedestal->SetLineColor(kRed);
	pedestal->Draw("same");

	for (uint k=1; k <= mMaxPhotons; k++) {
		auto pbnLambda = [k, this](Double_t *x, Double_t *par) {
			 double_t xtotal = 0;
			 for (uint i = 1; i <= mMaxPhotons; ++i) {
				 xtotal += pbnFunction(x, par, i, k); // normal dist for dynodes
			 }
			 return xtotal;
		};
		TF1 *gaussian = new TF1("gaussian", pbnLambda, mXmin, mXmax, 9);
		gaussian->SetParameters(mLowPEPar);
		gaussian->SetNpx(1000);
		gaussian->SetLineWidth(2);
		gaussian->SetLineColor(kBlue);
		gaussian->Draw("same");
	}

	mLowPEFit->SetNpx(1000);
	mLowPEFit->SetLineWidth(2);
	mLowPEFit->SetLineColor(kMagenta);
	mLowPEFit->Draw("same");

	mLowPESpectrum->SetTitle("LowPE");
	mLowPESpectrum->SetXTitle("Measured Charge (ADC)");
	mLowPESpectrum->SetYTitle("Frequency");
	mLowPESpectrum->GetXaxis()->SetTitleOffset(1.4);
	mLowPESpectrum->GetYaxis()->SetTitleOffset(1.4);

	if (boost::filesystem::create_directories(output.parent_path()))
		COUTP("[directory][new] " << output);
	canvas->SaveAs(output.c_str());
	COUTP("[file][output] " << output);
}

void PulseSpectrumFit::DrawHighInitial(fs::path output){
	TCanvas *canvas = new TCanvas("cHighInitialPE", "cHighInitialPE", 3000, 2000);
	mHighInitialSpectrum->Draw("E");

	mHighInitialFit->SetNpx(1000);
	mHighInitialFit->SetLineWidth(2);
	mHighInitialFit->SetLineColor(kMagenta);
	mHighInitialFit->Draw("same");

	mHighInitialSpectrum->SetTitle("HighInitial");
	mHighInitialSpectrum->SetXTitle("Measured Charge (ADC)");
	mHighInitialSpectrum->SetYTitle("Frequency");
	mHighInitialSpectrum->GetXaxis()->SetTitleOffset(1.4);
	mHighInitialSpectrum->GetYaxis()->SetTitleOffset(1.4);

	if (boost::filesystem::create_directories(output.parent_path()))
		COUTP("[directory][new] " << output);
	canvas->SaveAs(output.c_str());
	COUTP("[file][output] " << output);
}

void PulseSpectrumFit::DrawHigh(fs::path output){
	TCanvas *canvas = new TCanvas("cHighPE", "cHighPE", 3000, 2000);
	mHighSpectrum->Draw("E");

	mHighFit->SetNpx(1000);
	mHighFit->SetLineWidth(2);
	mHighFit->SetLineColor(kMagenta);
	mHighFit->Draw("same");

	for (uint k=1; k <= (int)mHighPar[6]; k++) {
		auto pbnGaussianLambda = [k, this](Double_t *x, Double_t *par) {
			 double_t xtotal = 0;
			 for (uint i = (uint)mHighPar[5]; i <= (int)mHighPar[6]; ++i) {
				 xtotal += pbnGaussianFunction(x, par, i, k); // normal dist for dynodes
			 }
			 return xtotal;
		};
		TF1 *gaussian = new TF1("gaussian", pbnGaussianLambda, mXmin, mXmax, 9);
		gaussian->SetParameters(mHighPar);
		gaussian->SetNpx(1000);
		gaussian->SetLineWidth(2);
		gaussian->SetLineColor(kBlue);
		gaussian->Draw("same");
	}

	mHighSpectrum->SetTitle("High");
	mHighSpectrum->SetXTitle("Measured Charge (ADC)");
	mHighSpectrum->SetYTitle("Frequency");
	mHighSpectrum->GetXaxis()->SetTitleOffset(1.4);
	mHighSpectrum->GetYaxis()->SetTitleOffset(1.4);

	if (boost::filesystem::create_directories(output.parent_path()))
		COUTP("[directory][new] " << output);
	canvas->SaveAs(output.c_str());
	COUTP("[file][output] " << output);
}

float PulseSpectrumFit::GetTrueCharge(float x) {
	double sum = 0;
	for (auto& PEFit_pair : mPEMap) {
		uint pe = PEFit_pair.first;
		TF1* PEFit = PEFit_pair.second;
		sum += PEFit->Eval(x);
	}
	if (sum==0) THROW("mPEMap appears to be empty");
	map<uint,double> probM;
	for (auto& PEFit_pair : mPEMap) {
		uint pe = PEFit_pair.first;
		TF1* PEFit = PEFit_pair.second;
		probM[pe] = PEFit->Eval(x)/sum;
	}
	gRandom = new TRandom3(0);
	double p0 = gRandom->Uniform();
	float true_pe = -1;
	double current_p = 0;
	for (auto p_pair : probM) {
		uint pe = p_pair.first;
		double p = current_p + p_pair.second;
		if (p0 > current_p && p0 <= p) {
			true_pe = pe;
			break;
		}
		else current_p = p;
	}
	if (true_pe == -1) THROW("true_pe not set, p0 = " << p0);
	return true_pe;
}

float PulseSpectrumFit::ConvertMeasuredCharge(float x) {
	return x/(float)mCalibPar[4];
}