//
// Created by Laurel Kaye on 16/02/2016.
//

#include <hillas_plots.h>



void hillas_plotter(Filepath_ptr input_fp, Filepath_ptr input_fp2, string branch_name, string branch_name2,
                           bool save_images){
    START();

    //Select required branch
    const set<string> hillas_branch = {branch_name};
    const set<string> hillas_branch2 = {branch_name2};

    //Build run
    Run_ptr hillas_run = input_fp->Read();
    Run_ptr hillas_run2 = input_fp2->Read();

    //set up output location
    if (save_images) input_fp->CreateOutputDirectory();

    //set relevant values
    int num_events = hillas_run->GetMaxEventNum();
    int num_events2 = hillas_run2->GetMaxEventNum();
    int num_cameras = hillas_run->GetNumCameras();
    int num_cameras2 = hillas_run2->GetNumCameras();
    int num_parameters = 9;
    HillasPlot h_plots; //this will contain vectors and histograms
    HillasPlot h_plots2;

    // Create canvas
    TCanvas* canvas;
    TPad* pad;
    canvas = new TCanvas(Form("Hillas_Parameters"), "Parameter Canvas", 3000, 2000);
    canvas->Divide(int(ceil(sqrt(num_parameters))), int(ceil(sqrt(num_parameters))));
    pad = (TPad *) canvas->GetPad(0);
    pad->SetRightMargin(0.2);



  //First Loop through events

    Progress progress(num_events, "Looping over events : ");
    int progress_i = 0;

    for (uint32_t current_event = 0; current_event < num_events; current_event++) {
        progress.Print(current_event);

        //Loop over cameras
        int camera_index = 0;
        double RMS_intensity=0;
        for (auto &camera_pair : hillas_run->GetCameraMap()) {
            auto &camera = camera_pair.second;
            int current_camera = camera.GetCameraId();
            Event &event = camera.GetEvent(current_event);
            //Make tailcuts
            event.Tailcut(3, 9, branch_name, true);
	        /*
	         * !!!   Laurel - This is the new way to get tailcuts
	         * the last argument is a bool, if true it multiplies the first two arguments by the rms of the image
	         */



            //Calculate Hillas Parameters
            HillasParameter* parameters;
            parameters = event.GetHillasParameter(branch_name);
            //fill histograms
            fill_histograms(h_plots, parameters);

        }

    }


    //Second Loop through events
    Progress progress2 (num_events2, "Looping over events : ");
    int progress_i2 = 0;

    for (uint32_t current_event = 0; current_event < num_events2; current_event++) {
        progress2.Print(current_event);

        //Loop over cameras
        int camera_index = 0;
        for (auto &camera_pair2 : hillas_run2->GetCameraMap()) {
            auto &camera2 = camera_pair2.second;
            int current_camera = camera2.GetCameraId();
            Event &event2 = camera2.GetEvent(current_event);
            //Make tailcuts
	        event2.Tailcut(15, 60, branch_name, true);
	        /*
	         * !!!   Laurel - This is the new way to get tailcuts
	         * the last argument is a bool, if true it multiplies the first two arguments by the rms of the image
	         */


            //Calculate Hillas Parameters
            HillasParameter* parameters2;
            parameters2 = event2.GetHillasParameter(branch_name2);
            //fill histograms
            fill_histograms(h_plots2, parameters2);

        }

    }

    draw_histograms(h_plots, canvas);
    draw_second_histograms(h_plots2, canvas);
    cout <<"histograms have been drawn"<< endl;



    // There is almost surely a more efficient way of writing this part- need to think of function that can iterate through each histo
    cout << "Parameter" << "\t" << "Cutoff" << std::setw(12) << "Quality Factor" << "\t" << "Top/Bottom" << endl;
    QualityFactor QF_width;
    QF_width= calculateQF(h_plots.width_histo, h_plots2.width_histo);
    cout<<"width       " << "\t" << QF_width.cutoff << std::setw(12) << QF_width.quality_factor;
    if (QF_width.bottom_bool)
        cout << "\t" << "bottom cut" << endl;
    else
        cout << "\t" << "top cut" << endl;
    draw_cutoff(canvas,h_plots.width_histo,1,QF_width.cutoff);
    QualityFactor QF_length;
    QF_length= calculateQF(h_plots.length_histo, h_plots2.length_histo);
    cout<<"length      " << "\t" << QF_length.cutoff <<std::setw(12)<< QF_length.quality_factor;
    if (QF_length.bottom_bool)
        cout << "\t" << "bottom cut" << endl;
    else
        cout << "\t" << "top cut" << endl;
    draw_cutoff(canvas,h_plots.length_histo,2,QF_length.cutoff);
    QualityFactor QF_intensity;
    QF_intensity= calculateQF(h_plots.intensity_histo, h_plots2.intensity_histo);
    cout<<"intensity   " << "\t" << QF_intensity.cutoff << std::setw(12) << QF_intensity.quality_factor;
    if (QF_intensity.bottom_bool)
        cout << "\t" << "bottom cut" << endl;
    else
        cout << "\t" << "top cut" << endl;
    draw_cutoff(canvas,h_plots.intensity_histo,3,QF_intensity.cutoff);
    QualityFactor QF_phi;
    QF_phi= calculateQF(h_plots.phi_histo, h_plots2.phi_histo);
    cout<<"phi         " << "\t" << QF_phi.cutoff << std::setw(12) << QF_phi.quality_factor;
    if (QF_phi.bottom_bool)
        cout << "\t" << "bottom cut" << endl;
    else
        cout << "\t" << "top cut" << endl;
    draw_cutoff(canvas,h_plots.phi_histo,4,QF_phi.cutoff);
    QualityFactor QF_azwidth;
    QF_azwidth= calculateQF(h_plots.azwidth_histo, h_plots2.azwidth_histo);
    cout<<"azwidth     " << "\t" << QF_azwidth.cutoff << std::setw(12) << QF_azwidth.quality_factor;
    if (QF_azwidth.bottom_bool)
        cout << "\t" << "bottom cut" << endl;
    else
        cout << "\t" << "top cut" << endl;
    draw_cutoff(canvas,h_plots.azwidth_histo,5,QF_azwidth.cutoff);
    QualityFactor QF_asymmetry;
    QF_asymmetry= calculateQF(h_plots.asymmetry_histo, h_plots2.asymmetry_histo);
    cout<<"asymmetry   " << "\t" << QF_asymmetry.cutoff << std::setw(12) << QF_asymmetry.quality_factor;
    if (QF_asymmetry.bottom_bool)
        cout << "\t" << "bottom cut" << endl;
    else
        cout << "\t" << "top cut" << endl;
    draw_cutoff(canvas,h_plots.asymmetry_histo,6,QF_asymmetry.cutoff);
    QualityFactor QF_aspect_ratio;
    QF_aspect_ratio= calculateQF(h_plots.aspect_ratio_histo, h_plots2.aspect_ratio_histo);
    cout<<"aspect ratio " << "\t" << QF_aspect_ratio.cutoff << std::setw(12) << QF_aspect_ratio.quality_factor;
    if (QF_aspect_ratio.bottom_bool)
        cout << "\t" << "bottom cut" << endl;
    else
        cout << "\t" << "top cut" << endl;
    draw_cutoff(canvas,h_plots.aspect_ratio_histo,7,QF_aspect_ratio.cutoff);
    QualityFactor QF_miss;
    QF_miss= calculateQF(h_plots.miss_histo, h_plots2.miss_histo);
    cout<<"miss        " << "\t" << QF_miss.cutoff << std::setw(12) << QF_miss.quality_factor;
    if (QF_miss.bottom_bool)
        cout << "\t" << "bottom cut" << endl;
    else
        cout << "\t" << "top cut" << endl;
    draw_cutoff(canvas,h_plots.miss_histo,8,QF_miss.cutoff);
    QualityFactor QF_distance;
    QF_distance= calculateQF(h_plots.distance_histo, h_plots2.distance_histo);
    cout<<"distance    " << "\t" << QF_distance.cutoff << std::setw(12) << QF_distance.quality_factor;
    if (QF_distance.bottom_bool)
        cout << "\t" << "bottom cut" << endl;
    else
    cout << "\t" << "top cut" << endl;
    draw_cutoff(canvas,h_plots.distance_histo,9,QF_distance.cutoff);



    if (save_images) {
        fs::path save_name = input_fp->GetRunIdentifier()       //TODO:: add second root file name in the saved file
                             + "_" + branch_name
                             + "_" + branch_name2 + "_plots"
                             + ".png";

        fs::path save_path = input_fp->GetOutputDirectory() / save_name;
        canvas->SaveAs(save_path.c_str());

        COUTP("[file][output] " << save_path);

        canvas->Clear("D");
    }
    cout << "All done, still working." <<endl;

}

void fill_histograms(HillasPlot plots, HillasParameter* h_parameters){
    double width = h_parameters->GetWidth();
    double length = h_parameters->GetLength();
    double intensity = h_parameters->GetIntensity();
    double phi = h_parameters->GetPhi();
    double azwidth = h_parameters->GetAzwidth();
    double asymmetry = h_parameters->GetAsymmetry();
    double aspect_ratio = length/width;
    double miss = h_parameters->GetMiss();
    double distance = h_parameters->GetDistance();


    plots.width_histo->Fill(width);
    plots.length_histo->Fill(length);
    plots.intensity_histo->Fill(intensity);
    plots.phi_histo->Fill(phi);
    plots.azwidth_histo->Fill(azwidth);
    plots.asymmetry_histo->Fill(asymmetry);
    plots.aspect_ratio_histo->Fill(aspect_ratio);
    plots.miss_histo->Fill(miss);
    plots.distance_histo->Fill(distance);



}

void draw_histograms(HillasPlot plots,TCanvas* canvas1) {

    canvas1->cd(1);
    plots.width_histo->SetFillColorAlpha(kAzure, 0.6);
    plots.width_histo->SetLineColor(kAzure);
    plots.width_histo->Draw();
    canvas1->cd(2);
    plots.length_histo->SetFillColorAlpha(kAzure, 0.6);
    plots.length_histo->SetLineColor(kAzure);
    plots.length_histo->Draw();
    canvas1->cd(3);
    plots.intensity_histo->SetFillColorAlpha(kAzure, 0.6);
    plots.intensity_histo->SetLineColor(kAzure);
    plots.intensity_histo->Draw();
    canvas1->cd(4);
    plots.phi_histo->SetFillColorAlpha(kTeal, 0.6);
    plots.phi_histo->SetLineColor(kTeal);
    plots.phi_histo->Draw();
    canvas1->cd(5);
    plots.azwidth_histo->SetFillColorAlpha(kTeal, 0.6);
    plots.azwidth_histo->SetLineColor(kTeal);
    plots.azwidth_histo->Draw();
    canvas1->cd(6);
    plots.asymmetry_histo->SetFillColorAlpha(kTeal, 0.6);
    plots.asymmetry_histo->SetLineColor(kTeal);
    plots.asymmetry_histo->Draw();
    canvas1->cd(7);
    plots.aspect_ratio_histo->SetFillColorAlpha(kSpring, 0.6);
    plots.aspect_ratio_histo->SetLineColor(kSpring);
    plots.aspect_ratio_histo->Draw();
    canvas1->cd(8);
    plots.miss_histo->SetFillColorAlpha(kSpring, 0.6);
    plots.miss_histo->SetLineColor(kSpring);
    plots.miss_histo->Draw();
    canvas1->cd(9);
    plots.distance_histo->SetFillColorAlpha(kSpring, 0.6);
    plots.distance_histo->SetLineColor(kSpring);
    plots.distance_histo->Draw();
}

void draw_second_histograms(HillasPlot plots,TCanvas* canvas1){
    //second set of plots
    canvas1->cd(1);
    plots.width_histo->SetFillColorAlpha(kRed, 0.6);
    plots.width_histo->SetLineColor(kRed);
    plots.width_histo->Draw("same");
    canvas1->cd(2);
    plots.length_histo->SetFillColorAlpha(kRed, 0.6);
    plots.length_histo->SetLineColor(kRed);
    plots.length_histo->Draw("same");
    canvas1->cd(3);
    plots.intensity_histo->SetFillColorAlpha(kRed, 0.6);
    plots.intensity_histo->SetLineColor(kRed);
    plots.intensity_histo->Draw("same");
    canvas1->cd(4);
    plots.phi_histo->SetFillColorAlpha(kMagenta, 0.6);
    plots.phi_histo->SetLineColor(kMagenta);
    plots.phi_histo->Draw("same");
    canvas1->cd(5);
    plots.azwidth_histo->SetFillColorAlpha(kMagenta, 0.6);
    plots.azwidth_histo->SetLineColor(kMagenta);
    plots.azwidth_histo->Draw("same");
    canvas1->cd(6);
    plots.asymmetry_histo->SetFillColorAlpha(kMagenta, 0.6);
    plots.asymmetry_histo->SetLineColor(kMagenta);
    plots.asymmetry_histo->Draw("same");
    canvas1->cd(7);
    plots.aspect_ratio_histo->SetFillColorAlpha(kViolet, 0.6);
    plots.aspect_ratio_histo->SetLineColor(kViolet);
    plots.aspect_ratio_histo->Draw("same");
    canvas1->cd(8);
    plots.miss_histo->SetFillColorAlpha(kViolet, 0.6);
    plots.miss_histo->SetLineColor(kViolet);
    plots.miss_histo->Draw("same");
    canvas1->cd(9);
    plots.distance_histo->SetFillColorAlpha(kViolet, 0.6);
    plots.distance_histo->SetLineColor(kViolet);
    plots.distance_histo->Draw("same");

}

QualityFactor calculateQF (TH1F* gamma_histos, TH1F* cr_histos)
{
    QualityFactor QF1;

    QF1.x_min = gamma_histos->GetXaxis()->GetXmin();
    QF1.x_max = gamma_histos->GetXaxis()->GetXmax();
    QF1.num_bins = gamma_histos->GetXaxis()->GetNbins();
    QF1.increment = (QF1.x_max-QF1.x_min)/QF1.num_bins;
    QF1.N_g_t = 11;      //gamma_histos->GetEntries();
    QF1.N_cr_t = 11;     // cr_histos->GetEntries();
    QF1.top_bool=false;
    QF1.bottom_bool=false;
    QF1.cutoff=0;
    QF1.quality_factor=0;

    double quality_factor, gamma_fraction, cr_fraction;
    double v_qf_top[QF1.num_bins];          //cut from above
    double v_qf_bottom[QF1.num_bins];       //cut from below
    int array_size_top =0;
    int array_size_bottom=0;


    //Cut from below
    for (double current_bin_number = 0; current_bin_number<QF1.num_bins; current_bin_number++)
    {
        QF1.N_g_a = 0;
        QF1.N_cr_a = 0;
        //calculate number of gamma/cr under number

        for (double current_loop_bin = 0; current_loop_bin <= current_bin_number; current_loop_bin++) {
            int gamma_content, cr_content;
            gamma_content = gamma_histos->GetBinContent(current_loop_bin);
            cr_content = cr_histos->GetBinContent(current_loop_bin);
            QF1.N_g_a += gamma_content;
            QF1.N_cr_a += cr_content;
            //cout << current_loop_bin << "\t" << QF1.N_g_a << "\t" << QF1.N_cr_a << endl;
        }
        float N_g_a = QF1.N_g_a;
        //cout << current_bin_number << "\t" << QF1.N_g_a << "\t" << N_g_a << "\t"  << QF1.N_cr_a << endl;

        //calculate QF
        if (QF1.N_cr_a==0)
        {
            QF1.N_cr_a=0.1;      //this should prevent infinite results (though in reality, the QF would be infinite)- make sure it is sensible
        }
        quality_factor = QF1.N_g_a/QF1.N_g_t/(pow((QF1.N_cr_a/QF1.N_cr_t),-0.5));    //*(pow(cr_fraction,-0.5));
        v_qf_bottom[array_size_bottom]=quality_factor;

        QF1.qf_map[quality_factor] = gamma_histos->GetXaxis()->GetBinCenter(current_bin_number);        //TODO:: make this vector pair instead of map, otherwise it will rewrite entries with same QF
        array_size_bottom++;

        //cout << "Current QF for bottom cutoff at bin " << current_bin_number << " =  " << quality_factor << endl;
    }

    //cut from above
    for (double current_bin_number = QF1.num_bins; current_bin_number>= 0; current_bin_number -=1)
    {
        QF1.N_g_a =0;
        QF1.N_cr_a =0;
        //calculate number of gamma/cr under number
        for (double current_x = QF1.num_bins; current_x >= current_bin_number; current_x -= 1 )
        {
            int gamma_content, cr_content;
            gamma_content = gamma_histos->GetBinContent(current_x);
            cr_content = cr_histos->GetBinContent(current_x);
            QF1.N_g_a += gamma_content;
            QF1.N_cr_a += cr_content;

        }

        //calculate QF
        gamma_fraction= QF1.N_g_a/QF1.N_g_t;

        if (QF1.N_cr_a==0)
        {
            QF1.N_cr_a=0.01;      //this should prevent infinite results (though in reality, the QF would be infinite)- make sure it is sensible
        }
        else
        {
            cr_fraction= QF1.N_cr_a/QF1.N_cr_t;
        }


        quality_factor = gamma_fraction*(pow(cr_fraction,-0.5));
        v_qf_top[array_size_top]=quality_factor;
        QF1.qf_map[quality_factor] = current_bin_number;        //TODO:: make this vector pair instead of map, otherwise it will rewrite entries with same QF
        array_size_top++;

    }

    //part of function that pulls the maximum quality factor
    double current_qf = 0, max_qf_top = 0, max_qf_bottom=0, max_qf=0;
    for (int i = 0; i < array_size_bottom; i++ ) {
        current_qf = v_qf_bottom[i];
        if (current_qf > max_qf_bottom) {
            max_qf_bottom = current_qf;
        }
    }

    for (int i = 0; i < array_size_top; i++ )
    {
        current_qf= v_qf_top[i];
        if (current_qf>max_qf_top) {
            max_qf_top=current_qf;
        }
    }

    //Now pick whether to do a bottom or top cut
    if (max_qf_bottom>max_qf_top)
    {
        QF1.bottom_bool=true;
        max_qf=max_qf_bottom;
    }
    else
    {
        QF1.top_bool=true;
        max_qf=max_qf_top;
    }


    //get the cutoff value for the maximum quality factor
    QF1.quality_factor=max_qf;
    double cutoff_bin=QF1.qf_map[QF1.quality_factor];

    QF1.cutoff= gamma_histos->GetBinCenter(cutoff_bin);        //TODO:: make this vector pair instead of map

    return QF1;

}

void draw_cutoff (TCanvas* canvas1, TH1F* histo, int canvas_number, double cut)
{
    Float_t ymax = histo->GetMaximum();
    canvas1->cd(canvas_number);
    TLine *line = new TLine(cut,0,cut,8);
    line->SetLineColor(kRed);
    line->Draw("SAME");
}

//void make_QF_cutoff (TH1F* plot_1, )