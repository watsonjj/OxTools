//
// Created by Jason Watson on 27/01/2016.
//

#include <initialise.h>
#include <thread>
#include <future>

double_t pbnFunction(Double_t *x, Double_t *par, uint i, uint k) {
	return (par[3] * // scaling parameter
	        (ROOT::Math::poisson_pdf(i,par[6]))*// poisson distribution of incoming photons
	        (ROOT::Math::binomial_pdf(k, par[7],i)) * // binomial for quantum efficiency
	        (ROOT::Math::normal_pdf(x[0], ((sqrt(k)) * par[5]), (k * par[4])))); // normal dist for dynodes
}

int main()
{
	int int_var = 42;
	int i =5, k=5;
	auto lambda_func = [i, k](Double_t *x, Double_t *par){return pbnFunction(x, par, i, k);};
	TF1 *pedestal2 = new TF1("pedestal2", lambda_func, 0, 10, 6);
	pedestal2->Draw();
}



