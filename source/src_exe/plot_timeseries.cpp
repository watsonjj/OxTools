//
// Created by Jason Watson on 23/10/15.
//

#include "Filepath.h"
#include <timeseries_plotter.h>


int main(int argc, char *argv[]) {
	START();
	string help_message = Form(
			  "%s [-f {input_filepath}] [-b {branch_name}] [-e {event_number} | -a] [OPTIONS] \n"
						 "  -- program to plot camera image from a TTree                                 \n\n"
						 "Options:        Arguments:        Description:                                 \n"
						 " -h | --help                       show the help text                          \n"
						 " -f              [input_filepath]  path to the root file (or txt file,         \n"
						 "                                     which will be converted)                  \n"
						 " -b              [branch_name]     name of the branch to plot in the zaxis     \n"
						 "                                     (colour axis)                             \n"
						 " -e              [event_number]    event number to plot                        \n"
						 " -s                                save a png for this event                   \n"
						 "                                     (does not display graphics)               \n"
						 " -a                                save animated gif for all events            \n"
						 "                                     (does not display graphics)               \n",
			  argv[0]);

	// Define variables;
	fs::path input_filepath;
	string branch_name;
	uint32_t event = 0;
	bool save_images = false, all_events = false;

	// Check for required arguments
	bool input_filepath_f = false;
	bool branch_name_f = false;
	bool event_f = false;

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
		if (strcmp(argv[i], "-b") == 0) {
			if (i + 1 != argc) {
				branch_name = argv[i + 1];
				branch_name_f = true;
			}
		}
		if (strcmp(argv[i], "-e") == 0) {
			if (i + 1 != argc) {
				event = (uint32_t) atoi(argv[i + 1]);
				event_f = true;
			}
		}
		if (strcmp(argv[i], "-s") == 0) {
			save_images = true;
		}
		if (strcmp(argv[i], "-a") == 0) {
			event = 0;
			all_events = true;
			save_images = true;

		}
	}

	// Required options
//	if (!input_filepath_f) {
//		std::cout << Print::Level() << "[arg][error] Required argument not specified: [input_filepath]" << endl;
//		std::cout << help_message << endl;
//		return 1;
//	}
//	if (!branch_name_f) {
//		std::cout << Print::Level() << "[arg][error] Required argument not specified: [branch_name]" << endl;
//		std::cout << help_message << endl;
//		return 1;
//	}
//	if (!event_f && !all_events) {
//		std::cout << Print::Level() << "[arg][error] Required argument not specified: [event_number] or -a" << endl;
//		std::cout << help_message << endl;
//		return 1;
//	}
//
//	// Conflicts
//	if (event_f && all_events) {
//		std::cout << Print::Level() << "[arg][error] Argument conflict encountered!" << endl;
//		std::cout << Print::Level() << "[arg][error] -e not compatible with -a" << endl;
//		std::cout << help_message << endl;
//		return 1;
//	}

//	// Build Filepaths
//	Filepaths filepaths(input_filepath);
//
//	// Run command
//	//Convert from txt to root
//	if (!filepaths.IsOx()) {
//		std::cout << Print::Level() << "[file] Converting file to .ox.root file" << endl;
//		oxtools_ttree_converter(filepaths);
//		filepaths.Init(filepaths.GetOutput());
//	}

	TFile *rootFile = new TFile("~/Software/outputs/libCHEC/cameradata_run603_summary.root", "READ");
	TTree *ttree = (TTree *) rootFile->Get("camera_data");
	string output_directory = "~/Software/outputs/libCHEC/cameradata_run603_summary";

	if (!save_images) {
		TApplication *rootapp = new TApplication("example", 0, 0); // Allows graphics to be seen when using g++
		timeseries_plotter(ttree, output_directory);
		gPad->Update();
		rootapp->Run();
	}
	else {
		timeseries_plotter(ttree, output_directory);
	}

	END();
	return 0;
}

