//
// Created by Laurel Kaye on 16/02/2016.
//

#ifndef OXTOOLS_HILLAS_PLOTS_H
#define OXTOOLS_HILLAS_PLOTS_H

#include <Event.h>
#include <initialise.h>
#include <Filepath.h>
#include <HillasParameter.h>





struct HillasPlot
{

    /*
    std::vector <double> v_width;
    std::vector <double> v_length;
    std::vector <double> v_intensity;
    std::vector <double> v_phi;
    std::vector <double> v_azwidth;
    std::vector <double> v_asymetry;
    std::vector <double> v_aspect_ratio;
    std::vector <double> v_miss;
    std::vector <double> v_distance;
     */

    TH1F *width_histo = new TH1F("width_histo","Width",30,0,1.5);
    TH1F *length_histo = new TH1F("length_histo","Length",30,0,3);
    TH1F *intensity_histo = new TH1F("intensity_histo","Intensity",30,0,15000);
    TH1F *phi_histo = new TH1F("phi_histo","Phi",30,-1.5,1.5);
    TH1F *azwidth_histo = new TH1F("azwidth_histo","Azwidth",30,0,3);
    TH1F *asymmetry_histo = new TH1F("asymmetry_histo","Asymmetry",30,0,2.5);
    TH1F *aspect_ratio_histo = new TH1F("aspect_ratio_histo","Aspect Ratio",30,0,4.4);
    TH1F *miss_histo = new TH1F("miss_histo","Miss",30,0,3);
    TH1F *distance_histo = new TH1F("distance_histo","Distance",30,0,4);


};

void hillas_plotter(Filepath_ptr input_fp, Filepath_ptr input_fp2, string branch_name, string branch_name2,
                    bool save_images);

void fill_histograms(HillasPlot plots, HillasParameter* h_parameters);
void draw_histograms(HillasPlot plots, TCanvas* canvas1);
void draw_second_histograms(HillasPlot plots, TCanvas* canvas1);


struct QualityFactor
{
    double x_min, x_max, increment;
    int num_bins;
    float N_g_t, N_g_a, N_cr_t, N_cr_a;
    double quality_factor, cutoff;
    std::map <double, double> qf_map;
    bool top_bool, bottom_bool;

};

QualityFactor calculateQF (TH1F* gamma_histos, TH1F* cr_histos);
void draw_cutoff (TCanvas* canvas1, TH1F* histo, int canvas_number, double cut);

#endif //OXTOOLS_HILLAS_PLOTS_H
