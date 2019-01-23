//
// Created by Lucy Martin on 22/03/16.
//

#include "fitForJason.h"

#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <TMath.h>
#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include <TRandom.h>
#include <TPad.h>
#include <TDirectory.h>
#include <TROOT.h>

// take the output from previously saved monte carlos and fit to it


///////////////////////////////////

double_t fittingFunction(Double_t *x, Double_t *par)
{

    int nMax = 42;

    double_t xtotal = par[3]*(ROOT::Math::normal_pdf(x[0], par[5], par[4])); // pedestal


    xtotal += (par[2] * // scaling parameter

               (ROOT::Math::normal_pdf(x[0], ((sqrt(1)) * par[0]), (1 * par[1])))); // normal dist for dynodes



    return xtotal;
}

//////////////////////////////////

double_t fittingFunction2(Double_t *x, Double_t *par) {

    int nMax = 42;

    double_t xtotal = par[6] * (ROOT::Math::normal_pdf(x[0], par[5], par[4])); // pedestal


    for (int i = 1; i <= nMax; ++i) {

        for (int k = i; k > 0; k--) {

            xtotal += (par[3] * // scaling parameter
                       (ROOT::Math::poisson_pdf(i,par[2]))*// poisson distribution of incoming photons
                       (ROOT::Math::binomial_pdf(k, par[7],i)) * // binomial for quantum efficiency
                       (ROOT::Math::normal_pdf(x[0], ((sqrt(k)) * par[0]), (k * par[1])))); // normal dist for dynodes


            // then add in nsb fitting for when its turned on:

            xtotal += (par[3] * // scaling
                       (ROOT::Math::poisson_pdf(i,par[8]))*// poisson for incoming nsb photons
                       (ROOT::Math::binomial_pdf(k, par[7],i)) *// binomial
                       (ROOT::Math::normal_pdf(x[0], ((sqrt(k)) * par[0]), (k * par[1])))); // normal dist for dynodes



        }


    }

    return xtotal;
}

///////////////////////////////////////

double_t fittingFunction1(Double_t *x, Double_t *par)
{
    double_t xtotal = par[2]*(ROOT::Math::normal_pdf(x[0], par[0], par[1]));
    return xtotal;
}

//////////////////////////////////////////

double_t fittingFunction4(Double_t *x, Double_t *par)
{

    double_t xtotal = 0;

    for (int i = par[5]; i <= par[6]; ++i)
    {

        for (int k = i; k> 0; k--)
        {

            // approximate poisson with normal dist
            // approx binomial with normal distribution
            xtotal += (par[3]
                       * ((1/(sqrt(par[2])*sqrt(2*M_PI)))*exp(-pow((i-par[2]),2)/(2*par[2])))// Photon dist
                       * ((1/(sqrt(par[4]*(1-par[4])*i)*sqrt(2*M_PI)))*exp(-pow((k-(i*par[4])),2)/(2*(par[4]*(1-par[4])*i))))// Quantum efficiency
                       * (ROOT::Math::normal_pdf(x[0], ((sqrt(k)) * par[0]), (k * par[1])))); // normal from dynodes

        }

    }


    return xtotal;
}


///////////////////////////////////////
// actual fit bit
///////////////////////////////////////

void fitForJason()
{
    // first find the max of the distribution, if is is greater than a certain value switch to the higher energy case
    // where distributions can be approximated with gaussians, this value is approx 20 pe.

    TFile *f = new TFile("pulse_simulation3photonnoapnoise3.root");

    TH1F *pulse = (TH1F*)f->Get("h1");


    double xAxisLimit = pulse->GetXaxis()->GetXmax();

    pulse->SetTitle("Spectrum of outputted voltage for incoming photons");
    pulse->GetXaxis()->SetTitle("Voltage/ V");
    pulse->GetYaxis()->SetTitle("Frequancy");

    pulse->Draw("E");


    double binEstimate = pulse->GetMaximumBin();
    double maxEstimate = binEstimate*xAxisLimit/100;
    cout << maxEstimate << endl;


    if (maxEstimate < 0.02) {


        TF1 *fitFcn = new TF1("fitFcn", fittingFunction, 0., xAxisLimit, 6);
        fitFcn->SetNpx(500);
        fitFcn->SetLineWidth(2);
        fitFcn->SetLineColor(kMagenta);

        // for lower energy CTA MaPMT case an initial fit is needed or system can't cope.

        Double_t fitpar[6];

        fitFcn->SetParameter(0, 0.00107);
        //fitFcn->SetParLimits(0, 0, 0.002);
        fitFcn->SetParameter(1, 0.0046);
        //fitFcn->SetParLimits(1, 0.003, 0.007);
        fitFcn->SetParameter(2, 2);
        //fitFcn->SetParLimits(2, 0.05, 5);
        fitFcn->SetParameter(3, 5);
        //fitFcn->SetParLimits(3, 0.6, 5);
        fitFcn->SetParameter(4, 0);
        fitFcn->FixParameter(4, 0);
        fitFcn->SetParameter(5, 0.0015);
        fitFcn->SetParLimits(5, 0, 0.005);


        pulse->Fit("fitFcn", "L", "", 0., 0.007);
        fitFcn->GetParameters(fitpar);
        //gr->Draw("AL");
        std::cout << fitFcn->GetChisquare() << endl;
        std::cout << fitFcn->GetNDF() << endl;
        std::cout << fitFcn->GetProb() << endl;
        //std::cout<<fitFcn->GetL()<<endl;


        TH1F *pulse2 = (TH1F *) f->Get("h1");

        TCanvas *c2 = new TCanvas("c2", "fit2", 200, 10, 700, 500);

        pulse2->Draw("E");

        TF1 *fitFcn2 = new TF1("fitFcn2", fittingFunction2, 0., xAxisLimit, 9);
        fitFcn2->SetNpx(500);
        fitFcn2->SetLineWidth(2);
        fitFcn2->SetLineColor(kMagenta);

        Double_t fitpar2[9];

        // par[2] is lambda, par[0] is standard deviation, par[1] is mean, par[3] is multiplication constant,
        // par[4] is pedestal mean, par[5] is the pedestal standard deviation, par[6] is multiplication for pedestal.
        // par[7] is the QE, par[8] is the rate of nsb

        fitFcn2->SetParameter(0, fitpar[0]);
        //fitFcn2->SetParLimits(0, fitpar[0] - 0.0005, fitpar[0] + 0.0005);
        fitFcn2->SetParameter(1, fitpar[1]);
        //fitFcn2->SetParLimits(1, fitpar[1] - 0.0005, fitpar[1] + 0.0005);
        fitFcn2->SetParameter(2, 3);
        //fitFcn2->SetParLimits(2, 3, 3);
        fitFcn2->SetParameter(3, fitpar[2]);
        //fitFcn2->FixParameter(3, fitpar[2]);
        fitFcn2->SetParameter(4, 0);
        fitFcn2->FixParameter(4, 0);
        fitFcn2->SetParameter(5, fitpar[5]);
        fitFcn2->SetParLimits(5, fitpar[5] - 0.0005, fitpar[5] + 0.0005);
        fitFcn2->SetParameter(6, fitpar[3]);
        //fitFcn2->FixParameter(6, fitpar[3]);
        fitFcn2->SetParameter(7, 0.35);
        fitFcn2->SetParLimits(7, 0.35, 0.35);
        fitFcn2->SetParameter(8, 0);
        fitFcn2->FixParameter(8, 0);



        //pulse2->Fit("fitFcn2", "L");
        pulse2->Fit("fitFcn2");
        fitFcn2->GetParameters(fitpar2);
        //gr->Draw("AL");
        std::cout << fitFcn2->GetChisquare() << endl;
        std::cout << fitFcn2->GetNDF() << endl;
        std::cout << fitFcn2->GetProb() << endl;
        //std::cout<<fitFcn->GetL()<<endl;


        std::vector<int> peDistribution;
        for (int i = 0; i <= 1000000; i++) {
            peDistribution.push_back(gRandom->Binomial((gRandom->PoissonD(fitpar2[2])), fitpar2[7]));

        }


        double limitc3 = fitpar[2] * 3;

        TH1F *peDist = new TH1F("peDist", "pe peak", 100, 0., limitc3);
        TCanvas *c3 = new TCanvas("c3", "pe dist", 200, 10, 700, 500);
        for (int i = 0; i < peDistribution.size(); i++) {
            peDist->Fill(peDistribution[i]);
        }

        for (int i = 0; i < peDistribution.size(); i++) {
            peDist->SetBinContent(i, (peDist->GetBinContent(i)) / 1000000);
        }


        peDist->SetTitle("Distribution of electrons after photocathode");
        peDist->GetXaxis()->SetTitle("no. of electrons");
        peDist->GetYaxis()->SetTitle("frequancy");
        peDist->DrawCopy();

        double fitInfo[8] = {fitpar2[0], fitpar2[1] ,fitpar2[2] ,fitpar2[3], fitpar2[7], fitpar2[4], fitpar2[5], fitpar2[6] };

        ofstream fout("fitInfoArray.txt"); //opening an output stream for file test.txt
        /*checking whether file could be opened or not. If file does not exist or don't have write permissions, file
      stream could not be opened.*/

        if(fout.is_open())
        {
            //file opened successfully so we are here
            cout << "File Opened successfully!!!. Writing data from array to file" << endl;

            for(int i = 0; i<8 ; i++)
            {
                fout << fitInfo[i] << endl; //writing ith character of array in the file
            }
            cout << "Array data successfully saved into the file fitInfo.txt" << endl;
        }
        else //file could not be opened
        {
            cout << "File could not be opened." << endl;
        }


    }

    else
    {
        TF1 *fitFcn1 = new TF1("fitFcn1", fittingFunction1, 0., xAxisLimit, 3);
        fitFcn1->SetNpx(500);
        fitFcn1->SetLineWidth(2);
        fitFcn1->SetLineColor(kMagenta);

        Double_t fitpar1[3];

        fitFcn1->SetParameter(0, 0.03);
        //fitFcn1->SetParLimits(0, 0.03, 0.03);
        fitFcn1->SetParameter(1, 0.03);
        //fitFcn1->SetParLimits(1, 0.03, 0.03);
        fitFcn1->SetParameter(2, 1);

        pulse->Fit("fitFcn1");
        fitFcn1->GetParameters(fitpar1);
        //gr->Draw("AL");
        std::cout<<fitFcn1->GetChisquare()<<endl;
        std::cout<<fitFcn1->GetNDF()<<endl;
        std::cout<<fitFcn1->GetProb()<<endl;


        TH1F *pulse2 = (TH1F*)f->Get("h1");

        TCanvas *c2 = new TCanvas("c2", "fit2", 200, 10, 700, 500);
        pulse2->Draw("E");

        // then the mean of the gaussian is first approximation of lambda*0.35. So is mean and also variance of the poisson distribution.
        // can use this to give estimate of values to loop through, eg, 3 standard deviations


        TF1 *fitFcn2 = new TF1("fitFcn3", fittingFunction4, 0., xAxisLimit, 7);
        fitFcn2->SetNpx(500);
        fitFcn2->SetLineWidth(2);
        fitFcn2->SetLineColor(kMagenta);

        // parameter 2 if the guess of the mean of the gaussian. par[1]/ 0.35 = lambda
        double lambdaGuess = fitpar1[1]/ (0.35*0.005);
        int lower = lambdaGuess - (3)*sqrt(lambdaGuess);
        int upper = lambdaGuess + (3)*sqrt(lambdaGuess);

        Double_t fitpar2[7];

        fitFcn2->SetParameter(0, 0.0035);
        //fitFcn2->SetParLimits(0, 0.0035, 0.0035);
        fitFcn2->SetParameter(1, 0.003);
        //fitFcn2->SetParLimits(1, 0.003, 0.003);
        fitFcn2->SetParameter(2, 20);
        //fitFcn2->SetParLimits(2, 0, 5);
        fitFcn2->SetParameter(3, 100);
        //fitFcn2->SetParLimits(3, 0.6, 5);
        fitFcn2->SetParameter(4, 0.35);
        fitFcn2->FixParameter(4, 0.35);
        fitFcn2->SetParameter(5, lower); //lower limit for scanning over incoming photons
        fitFcn2->FixParameter(5, lower);
        fitFcn2->SetParameter(6, upper); // upper limit for scanning over incoming photons
        fitFcn2->FixParameter(6, upper);


        pulse2->Fit("fitFcn3");
        fitFcn2->GetParameters(fitpar2);
        //gr->Draw("AL");
        std::cout<<fitFcn2->GetChisquare()<<endl;
        std::cout<<fitFcn2->GetNDF()<<endl;
        std::cout<<fitFcn2->GetProb()<<endl;
        //std::cout<<fitFcn->GetL()<<endl;


        std::vector<int> peDistribution;
        for (int i = 0; i<=1000000; i++)
        {
            peDistribution.push_back(gRandom->Binomial((gRandom->PoissonD(fitpar2[2])), fitpar2[4]));

        }

        double limitc3 = fitpar2[2]*3;

        TH1F *peDist = new TH1F("peDist", "pe peak", 100, 0., limitc3);
        TCanvas *c3 = new TCanvas("c3", "pe dist", 200, 10, 700, 500);
        for (int i = 0; i < peDistribution.size(); i++)
        {
            peDist->Fill(peDistribution[i]);
        }

        for (int i = 0; i < peDistribution.size(); i++)
        {
            peDist->SetBinContent(i, (peDist->GetBinContent(i))/1000000);
        }


        peDist->SetTitle("Distribution of electrons after photocathode");
        peDist->GetXaxis()->SetTitle("no. of electrons");
        peDist->GetYaxis()->SetTitle("frequancy");
        peDist->DrawCopy();

        double fitInfo[8] = {fitpar2[0], fitpar2[1] ,fitpar2[2] ,fitpar2[3], fitpar2[4], 0, 0, 0 };

        ofstream fout("fitInfoArray.txt"); //opening an output stream for file test.txt
        /*checking whether file could be opened or not. If file does not exist or don't have write permissions, file
      stream could not be opened.*/

        if(fout.is_open())
        {
            //file opened successfully so we are here
            cout << "File Opened successfully!!!. Writing data from array to file" << endl;

            for(int i = 0; i<8 ; i++)
            {
                fout << fitInfo[i] << endl; //writing ith character of array in the file
            }
            cout << "Array data successfully saved into the file fitInfo.txt" << endl;
        }
        else //file could not be opened
        {
            cout << "File could not be opened." << endl;
        }


    }
}