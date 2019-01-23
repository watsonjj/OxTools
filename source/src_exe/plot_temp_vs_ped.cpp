//
// Created by Jason Watson on 15/05/2016.
//

#include "Filepath.h"

int main(int argc, char *argv[]) {
	START();
	string help_message = Form(
			  "%s [-f {input_filepath}] [-b {branch_name}] [-e {event_number} | -a] [OPTIONS] \n"
						 "  -- program to plot camera image from a TTree                                 \n\n"
						 "Options:        Arguments:          Description:                                 \n"
						 " -h | --help                         show the help text                          \n"
						 " -f              [input_filepath]    path to the root file (or txt file,         \n"
						 "                                       which will be converted)                  \n",
			  argv[0]);

	// Define variables;
	fs::path input_filepath;

	// Check for required arguments
	bool input_filepath_f = false;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			std::cout << help_message << endl;
			return 1;
		}
		if (strcmp(argv[i], "-f") == 0) {
			if (i + 1 != argc) {
				input_filepath = argv[i + 1];
				input_filepath_f = true;
			}
		}
	}

	// Required options
	if (!input_filepath_f) {
		std::cout << Print::Level() << "[arg][error] Required argument not specified: [input_filepath]" << endl;
		std::cout << help_message << endl;
		return 1;
	}

	// Load Filepath
	auto filepath = FilepathLoader::Load(input_filepath);
	Run_ptr run = filepath->Read();

	TCanvas* canvas = new TCanvas("Cc1", "Cc1", 2500, 1450);

	TGraph* graph = new TGraph();

	for (auto& camera_pair : run->GetCameraMap()) {
		auto& camera = camera_pair.second;
		for (auto& event_pair : camera.GetEventMap()) {
			auto& event = event_pair.second;
			for (auto& entry_pair : event.GetEntryMap()) {
				auto& entry = entry_pair.second;
				float ped = entry.GetBranchValue("fPed");
				float temp = entry.GetBranchValue("fTemp");
				int current_point = graph->GetN();
				graph->SetPoint(current_point, temp, ped);
			}
		}
	}

	graph->Draw("A");

	string filename = filepath->GetRunIdentifier() + "_TempVsPed.png";
	fs::path output_filepath = filepath->GetOutputDirectory() / filename;
	canvas->SaveAs(output_filepath.c_str());
	COUTP("[file][output] " << output_filepath);

	END();
	return 0;
}

