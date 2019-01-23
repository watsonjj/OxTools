//
// Created by Jason Watson on 23/10/15.
//

#include <timeseries_plotter.h>


void timeseries_plotter(TTree* ttree, std::string output_directory) {

	// Set vector for branches of interest
	std::vector<std::string> branches = {"fPulseHeight", "fPulseArea", "fPulsePos"};

//	// Get ttree totals
//	uint32_t num_events = ttree->GetMaximum("fEventIndex") + 1;
//	uint32_t num_pixels = ttree->GetMaximum("fPixelID") + 1;

	uint32_t event_index;
	uint64_t event_timestamp;
	int pixel_id;
	int module_id;

	// Create holder map
	std::map<std::string, float> branch_holder;

	// Set branches for ttree
	ttree->SetBranchAddress("fEventIndex", &event_index);
	ttree->SetBranchAddress("fEventTimestamp", &event_timestamp);
	ttree->SetBranchAddress("fPixelId", &pixel_id);
	ttree->SetBranchAddress("fModuleId", &module_id);

	// Create map of graphs for each branch
	std::map<std::string, std::map<int, TGraph*>> graph_map;

	for (auto it : branches) {
		ttree->SetBranchAddress(it.c_str(), &branch_holder[it]);
	}

	// Create map for events: [branch][module][event]=average value for that module
	std::map<std::string,std::map<int,std::map<uint32_t,float>>> branch_map;
	std::map<std::string,std::map<int,std::map<uint32_t,int>>> branch_map_counter;

	// Create map to avoid duplicate entries (produced by inactive modules)
	std::map<int,std::map<int,bool>> bool_entry_map;

	// Fill event information
	cout << ttree->GetEntries() << endl;
	for (uint32_t i = 0; i < ttree->GetEntries(); i++) {
		ttree->GetEntry(i);

//		// Make sure and entry does not already exists (temp fix for unresponsive module filling 0)
		if (!bool_entry_map[event_index][pixel_id]) {
			for (auto it:branches) {
				branch_map[it][module_id][event_index] += branch_holder[it];
				branch_map_counter[it][module_id][event_index] += 1;
			}
			bool_entry_map[event_index][pixel_id] = true;
		}
	}

	std::cout << "[file] Creating diagnostic output directory: " << output_directory << std::endl;
	const int dir_err = system(("mkdir -p " + output_directory).c_str());
	if (-1 == dir_err) {
		std::cout << ("[file][error] Creating directory failed") << std::endl;
		exit(1);
	}

	std::cout << "[plot] Plotting diagnostic timeseries" << std::endl;
	TCanvas *c1 = new TCanvas("c1","c1",1000, 600);
	TPad *Ppad1 = (TPad *) c1->GetPad(0);
	Ppad1->SetRightMargin(0.2);

	std::string output_filepath;
	std::string output_filename;
	for (auto& branch_pair : branch_map) {
		TMultiGraph* mg = new TMultiGraph();
		TLegend* leg = new TLegend(0.81, 0.20, 0.99, 0.80);

		std::string current_branch = branch_pair.first;
		std::cout << current_branch << std::endl;

		// Build output paths
		output_filename = current_branch + "_timeseries";
		output_filepath = output_directory + "/" + output_filename;

		// Create array for colors
		int color_array[7] = {kRed,kOrange,kGreen,kCyan,kBlue,kMagenta,kGray+3};
		int marker_array[9] = {1,2,3,4,5,6,7,8,9};

		for (auto& module_pair : branch_pair.second) {
			int current_module = module_pair.first;
			std::cout << current_module << std::endl;
			graph_map[current_branch][current_module] = new TGraph();
			for (auto& event_pair : module_pair.second) {
				uint32_t current_event = event_pair.first;
				std::cout << current_event << std::endl;
				std::cout << "div " <<  branch_map_counter[current_branch][current_module][current_event] << std::endl;
				float module_average_value = event_pair.second/branch_map_counter[current_branch][current_module][current_event];

				// Enter point into graph
				int current_point = graph_map[current_branch][current_module]->GetN();
				graph_map[current_branch][current_module]->SetPoint(current_point, current_event, module_average_value);
			}

			// Style Graph
			graph_map[current_branch][current_module]->SetMarkerStyle(
					  (Style_t) marker_array[current_module%9]);
			graph_map[current_branch][current_module]->SetMarkerColor(
					  (Color_t) color_array[current_module%7]);
			graph_map[current_branch][current_module]->SetLineColor(
					  (Color_t) color_array[current_module%7]);
			graph_map[current_branch][current_module]->SetTitle(std::to_string(current_module).c_str());

			if (graph_map[current_branch][current_module]->GetN()>0) {
				leg->AddEntry(graph_map[current_branch][current_module], std::to_string(current_module).c_str(), "pl");
				mg->Add(graph_map[current_branch][current_module]);
			}
		}

		std::cout << __LINE__ << std::endl;

		// Draw Multigraph
		mg->SetTitle(output_filepath.substr(output_filepath.find("cameradata_run")).c_str());
		mg->Draw("ALP");
		mg->GetXaxis()->SetTitle("Entry Index");
		mg->GetYaxis()->SetTitle(current_branch.c_str());

		// Draw Legend
		leg->SetNColumns(3);
		leg->SetHeader("Module ID");
		leg->SetBorderSize(0);
		leg->Draw();
		std::cout << __LINE__ << std::endl;

		// Save graph
		c1->SaveAs((output_filepath + ".pdf").c_str());
	}
}


