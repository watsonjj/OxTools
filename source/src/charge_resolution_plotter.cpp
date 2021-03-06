//
// Created by Jason Watson on 01/10/15.
//

#include "charge_resolution_plotter.h"


void charge_resolution_plotter(vector<Filepath_ptr> filepathV, bool save_png, bool save_pdf,
                               bool save_root, string output_name, int user_max_npe) {
	START();

	string trueNPE_branch = "fTrueNPE";
	string measuredNPE_branch = "fPulseArea";
	set<string> branchV = {trueNPE_branch, measuredNPE_branch};

	// Create TFile (for when saving to root file)
	fs::path input_directory = filepathV[0]->GetInputDirectory();
	fs::path r_save_name = output_name + ".root";
	fs::path r_save_path = input_directory / "charge_resolution" / r_save_name;
	TFile* f;
	if (save_root) {
		if (boost::filesystem::create_directories(r_save_path.parent_path()))
			COUTP("[directory][new] "<< r_save_path);
		f = new TFile(r_save_path.c_str(),"recreate");
	}

	// Create canvas
	COUTP("[canvas] Creating canvas");
	TCanvas *canvas = new TCanvas("Cc1", "Cc1", 2500, 1450);
	canvas->Divide(2);
	TPad *Ppad1 = (TPad *) canvas->GetPad(1);
	TPad *Ppad2 = (TPad *) canvas->GetPad(2);
	Ppad1->SetRightMargin(0.2);
	Ppad1->SetLogy();


	// Create array for colors
	Style_t color_array[4] = {kBlue, kMagenta, kGray + 3, kOrange};
	Style_t marker_array[6] = {5, 8, 21, 22, 23, 33};

	TMultiGraph *mgB = new TMultiGraph("benchmarks","benchmarks");
	TMultiGraph *mgB_scaled = new TMultiGraph("benchmarks_scaled","benchmarks_scaled");
	TMultiGraph *mg = new TMultiGraph("chargeres","chargeres");
	TMultiGraph *mg_scaled = new TMultiGraph("chargeres_scaled","chargeres_scaled");
	TLegend *leg = new TLegend(0.81, 0.80-0.025*(filepathV.size()+3), 0.99, 0.80);

	ChargeResolutionBenchmarks benchmarks(user_max_npe);

	int i = 0;
	for (auto& filepath : filepathV) {
		Run_ptr run = filepath->Read();
		int max_npe = (user_max_npe == 0) ? (int)run->GetBranchMax(trueNPE_branch) : user_max_npe;
		ChargeResolution* chargeResHolder = run->GetChargeResolution(trueNPE_branch,
		                                                             measuredNPE_branch,
		                                                             benchmarks,
		                                                             max_npe);

		TGraphErrors* g = chargeResHolder->GetChargeResolutionGraph();
		TGraphErrors* gS = chargeResHolder->GetChargeResolutionScaledGraph();

		// Style Graph
		g->SetMarkerStyle(marker_array[i % 6]);
		g->SetMarkerColor(color_array[i % 4]);
		g->SetMarkerSize(1);
		g->SetLineColor(color_array[i % 4]);
		g->SetTitle(std::to_string(i).c_str());
		gS->SetMarkerStyle(marker_array[i % 6]);
		gS->SetMarkerColor(color_array[i % 4]);
		gS->SetMarkerSize(1);
		gS->SetLineColor(color_array[i % 4]);
		gS->SetTitle(std::to_string(i).c_str());

		// Fill Multigraph
		COUTP("[TGraph] Appending to multigraph");
		if (g->GetN() > 0) {
			leg->AddEntry(g, filepath->GetRunIdentifier().c_str(), "pl");
			mg->Add(g);
			mg_scaled->Add(gS);
		}
		i++;
	}


	// Get Requirement and Goal
	TGraph* g_R = benchmarks.GetRequirementGraph();
	TGraph* g_RS = benchmarks.GetRequirementScaledGraph();
	TGraph* g_G = benchmarks.GetGoalGraph();
	TGraph* g_GS = benchmarks.GetGoalScaledGraph();
	TGraph* g_P = benchmarks.GetPoissonGraph();
	TGraph* g_PS = benchmarks.GetPoissonScaledGraph();

	leg->AddEntry(g_R, "Requirement", "l");
	leg->AddEntry(g_G, "Goal", "l");
	leg->AddEntry(g_P, "Poisson Limit", "l");
	mgB->Add(g_R);
	mgB->Add(g_G);
	mgB->Add(g_P);
	mgB_scaled->Add(g_RS);
	mgB_scaled->Add(g_GS);
	mgB_scaled->Add(g_PS);

	// Draw Multigraph
	COUTP("[TGraph] Drawing multigraphs");
	canvas->cd(1);
	mgB->SetTitle(output_name.c_str());
	mgB->Draw("A");
	mgB->GetXaxis()->SetTitle("Log_{10}(True Charge (Q_{True}) (p.e.))");
	mgB->GetXaxis()->SetTitleSize(0.02);
	mgB->GetXaxis()->SetTitleOffset(1.3);
	mgB->GetXaxis()->SetLabelSize(0.02);
	mgB->GetXaxis()->SetRangeUser(0,110);
	mgB->GetYaxis()->SetTitle("Fractional Charge Resolution #sigma_{Q}/Q_{True}(p.e.)");
	mgB->GetYaxis()->SetTitleSize(0.02);
	mgB->GetYaxis()->SetTitleOffset(1.5);
	mgB->GetYaxis()->SetLabelSize(0.02);
	mg->Draw("P");
	mgB->Draw("L"); // Draw on top

	// Draw Legend
	leg->SetNColumns(1);
	leg->SetHeader("Run");
//	leg->SetTextSize(0.02);
	leg->Draw();

	// Draw Multigraph
	canvas->cd(2);
	mgB_scaled->SetTitle("");
	mgB_scaled->Draw("A");
	mgB_scaled->GetXaxis()->SetTitle("Log_{10}(True Charge (Q_{True}) (p.e.))");
	mgB_scaled->GetXaxis()->SetTitleSize(0.02);
	mgB_scaled->GetXaxis()->SetTitleOffset(1.3);
	mgB_scaled->GetXaxis()->SetLabelSize(0.02);
	mgB_scaled->GetYaxis()->SetTitle("Fractional Charge Resolution #sigma_{Q}/Q_{True}(p.e.) (Relative to Goal)");
	mgB_scaled->GetYaxis()->SetTitleSize(0.02);
	mgB_scaled->GetYaxis()->SetTitleOffset(1.5);
	mgB_scaled->GetYaxis()->SetLabelSize(0.02);
	mg_scaled->Draw("P");
	mgB_scaled->Draw("L"); // Draw on top

	if (save_png) {
		fs::path save_name = output_name + ".png";
		fs::path save_path = input_directory / "charge_resolution" / save_name;
		if (boost::filesystem::create_directories(save_path.parent_path()))
			COUTP("[directory][new] "<< save_path);
		canvas->SaveAs(save_path.c_str());
		COUTP("[file][output] " << save_path);
	}
	if (save_pdf) {
		fs::path save_name = output_name + ".pdf";
		fs::path save_path = input_directory / "charge_resolution" / save_name;
		if (boost::filesystem::create_directories(save_path.parent_path()))
			COUTP("[directory][new] "<< save_path);
		canvas->SaveAs(save_path.c_str());
		COUTP("[file][output] " << save_path);
	}
	if (save_root) {
		f->cd();
		if (boost::filesystem::create_directories(r_save_path.parent_path()))
			COUTP("[directory][new] "<< r_save_path);
		canvas->Write();
	}

	print_charge_resolution_scores(filepathV, user_max_npe);

	END();
}

void print_charge_resolution_scores(vector<Filepath_ptr> filepathV, int user_max_npe) {
	START();

	string trueNPE_branch = "fTrueNPE";
	string measuredNPE_branch = "fPulseArea";
	set<string> branchV = {trueNPE_branch, measuredNPE_branch};

	double low1 = 0;
	double low2 = 4;
	double high1 = low2;
	double high2 = 20;

	std::stringstream lowcut1;
	std::stringstream lowcut2;
	std::stringstream highcut1;
	std::stringstream highcut2;
	lowcut1 << low1;
	lowcut2 << low2;
	highcut1 << high1;
	if (user_max_npe > high2) highcut2 << high2;
	else highcut2 << user_max_npe;
	if (user_max_npe == 0) highcut2.str("user_max_npe");

	// Score Vectors
	vector<vector<string>> score_vector = {{"Run"},
	                                       {"Low ( " + lowcut1.str() + "<Q<=" + lowcut2.str() + " )"},
	                                       {"Low Rank"},
	                                       {"High ( " + highcut1.str() + "<Q<=" + highcut2.str() + " )"},
	                                       {"High Rank"},
	                                       {"Overall"},
	                                       {"Overall Rank"}};
	vector<vector<double>> value_vector = {{},{},{}};
	vector<vector<string>> rank_vector = {{},{},{}};
	double min_low = DBL_MAX, min_high = DBL_MAX, min_total = DBL_MAX;
	string best_low, best_high, best_total;
	double max_low = -DBL_MAX, max_high = -DBL_MAX, max_total = -DBL_MAX;
	string worst_low, worst_high, worst_total;

	ChargeResolutionBenchmarks benchmarks(user_max_npe);

	for (auto& filepath : filepathV) {
		Run_ptr run = filepath->Read();
		int max_npe = (user_max_npe == 0) ? (int)run->GetBranchMax(trueNPE_branch) : user_max_npe;
		ChargeResolution* chargeResHolder = run->GetChargeResolution(trueNPE_branch,
		                                                             measuredNPE_branch,
		                                                             benchmarks, max_npe);

		// Scores
		map<string,double> scores = chargeResHolder->GetScores(low1,low2,high1,high2);
		score_vector[0].push_back(filepath->GetRunIdentifier());
		score_vector[1].push_back(std::to_string(scores["low"]));
		score_vector[3].push_back(std::to_string(scores["high"]));
		score_vector[5].push_back(std::to_string(scores["overall"]));
		value_vector[0].push_back(scores["low"]);
		value_vector[1].push_back(scores["high"]);
		value_vector[2].push_back(scores["overall"]);
		if (min_low > scores["low"]) {
			min_low = scores["low"];
			best_low = filepath->GetRunIdentifier();
		}
		if (min_high > scores["high"]) {
			min_high = scores["high"];
			best_high = filepath->GetRunIdentifier();
		}
		if (min_total > scores["overall"]) {
			min_total = scores["overall"];
			best_total = filepath->GetRunIdentifier();
		}

		if (max_low < scores["low"]) {
			max_low = scores["low"];
			worst_low = filepath->GetRunIdentifier();
		}
		if (max_high < scores["high"]) {
			max_high = scores["high"];
			worst_high = filepath->GetRunIdentifier();
		}
		if (max_total < scores["overall"]) {
			max_total = scores["overall"];
			worst_total = filepath->GetRunIdentifier();
		}
	}

	// Rank each run
	for (int i=0; i<value_vector.size(); i++) {
		for (double current : value_vector[i]) {
			int position = 0;
			for (double compare : value_vector[i]) {
				if (current > compare) position++;
			}
			position++;
			rank_vector[i].push_back(std::to_string(position));
		}
	}
	for (string rank: rank_vector[0]) score_vector[2].push_back(rank);
	for (string rank: rank_vector[1]) score_vector[4].push_back(rank);
	for (string rank: rank_vector[2]) score_vector[6].push_back(rank);

	score_vector[0].push_back("BEST: ");
	score_vector[1].push_back(best_low);
	score_vector[3].push_back(best_high);
	score_vector[5].push_back(best_total);
	score_vector[0].push_back("WORST: ");
	score_vector[1].push_back(worst_low);
	score_vector[3].push_back(worst_high);
	score_vector[5].push_back(worst_total);

	COUTP("[chargeres][scores] : ");
	Table score_table(score_vector);
	score_table.Print();

	END();
}

void charge_variation_plotter(vector<Filepath_ptr> filepathV, bool save_png, bool save_pdf,
                              bool save_root, int user_max_npe) {

	START();

	string trueNPE_branch = "fTrueNPE";
	string measuredNPE_branch = "fPulseArea";
	set<string> branchV = {trueNPE_branch, measuredNPE_branch};

	ChargeResolutionBenchmarks benchmarks(user_max_npe);

	for (auto& filepath : filepathV) {

		// Create TFile (for when saving to root file)
		string r_save_name = filepath->GetRunIdentifier()
		                     + "_ChargeVariation"
		                     + ".root";
		fs::path r_save_path = filepath->GetOutputDirectory() / r_save_name;
		TFile* f;
		if (save_root) {
			if (boost::filesystem::create_directories(r_save_path.parent_path()))
				COUTP("[directory][new] "<< r_save_path);
			f = new TFile(r_save_path.c_str(),"recreate");
		}

		// Create canvas
		COUTP("[canvas] Creating canvas");
		TCanvas *canvas = new TCanvas("Cc1", "Cc1", 1500, 1500);
		TPad *Ppad1 = (TPad *) canvas->GetPad(0);
		Ppad1->SetRightMargin(0.2);
		Ppad1->SetLogz();
		Ppad1->SetGrid();

		Run_ptr run = filepath->Read();
		int max_npe = (user_max_npe == 0) ? (int)run->GetBranchMax(trueNPE_branch) : user_max_npe;
		ChargeResolution* chargeResHolder = run->GetChargeResolution(trueNPE_branch,
		                                                             measuredNPE_branch,
		                                                             benchmarks, max_npe);


		rainbow_palette();
		TH2F* hist = chargeResHolder->GetVariationHist();
		hist->GetXaxis()->SetTitle("log_{10} Q_{True}");
		hist->GetYaxis()->SetTitle("log_{10} Q_{Measured}");
		hist->GetXaxis()->SetTitleSize(0.02);
		hist->GetYaxis()->SetTitleSize(0.02);
		hist->GetXaxis()->SetTitleOffset(2);
		hist->GetYaxis()->SetTitleOffset(2);
		hist->SetTitle(filepath->GetRunIdentifier().c_str());
		hist->Draw("colz");

		TLine* line = new TLine(log10(1),log10(1),log10(max_npe),log10(max_npe));
		line->SetLineStyle(9);
		line->SetLineColor(kMagenta);
		line->SetLineWidth(2);
		line->Draw("same");

		if (save_png) {
			fs::path save_name = filepath->GetRunIdentifier()
			                     + "_ChargeVariation"
			                     + ".png";
			fs::path save_path = filepath->GetOutputDirectory() / save_name;
			filepath->CreateOutputDirectory();
			canvas->SaveAs(save_path.c_str());
				COUTP("[file][output] " << save_path);
			canvas->Clear("D");
		}
		if (save_pdf) {
			fs::path save_name = filepath->GetRunIdentifier()
			                     + "_ChargeVariation"
			                     + ".pdf";
			fs::path save_path = filepath->GetOutputDirectory() / save_name;
			filepath->CreateOutputDirectory();
			canvas->SaveAs(save_path.c_str());
			COUTP("[file][output] " << save_path);
			canvas->Clear("D");
		}
		if (save_root) {
			f->cd();
			canvas->Write();
		}
	}
	END();
}
