//
// Created by Jason Watson on 30/09/15.
//

#include "Filepath.h"
#include <charge_resolution_plotter.h>

// TODO: option to list possible branches (automatically if branch empty/does not match a possibility)

int main(int argc, char *argv[]) {
	START();
	string help_message = Form(
			  "%s [-f {input_filepaths}] [OPTIONS] \n"
						 "  -- program to plot camera image from a TTree                                 \n\n"
						 "Options:        Arguments:        Description:                                 \n"
						 " -h | --help                       show the help text                          \n"
						 " -f              [input_filepaths] path to the input root file (or txt file,   \n"
						 "                                     which will be converted)                  \n"
						 "                                     multiple arugments and wildcards are      \n"
						 "                                     accepted                                  \n"
					    " -v                                plot true charge versus measured charge     \n"
					    "                                     instead of charge resolution              \n"
					    " -m              [max true charge] maximum number of photoelectrons explored   \n"
					    "                                     for the true charge (default=1000)        \n"
					    " -S              [output_name]     save a png for this event                   \n"
					    "                                     (does not display graphics)               \n"
					    " -P              [output_name]     save a pdf for this event                   \n"
					    "                                     (does not display graphics)               \n"
					    " -R              [output_name]     save a root file for this event             \n"
					    "                                     (does not display graphics)               \n",
			  argv[0]);

	// Define variables;
	set<fs::path> input_filepath_set;
	bool variation_plot = false;
	bool save_png = false;
	bool save_pdf = false;
	bool save_root = false;
	string output_filename = "Charge_Resolution";
	uint32_t max_npe = 2000;

	// Check for required arguments
	bool input_filepath_f = false;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			std::cout << help_message << endl;
			return 1;
		}
		if (strcmp(argv[i], "-f") == 0) {
			while(i+1 < argc && string(argv[i + 1]).find("-") != 0) {
				input_filepath_set.insert(argv[i + 1]);
				input_filepath_f = true;
				i++;
			}
		}
		if (strcmp(argv[i], "-v") == 0) {
			variation_plot = true;
		}
		if (strcmp(argv[i], "-S") == 0) {
			save_png = true;
			output_filename = "charge_resolution";
			if (i + 1 != argc && string(argv[i + 1]).find("-") != 0) {
				output_filename = argv[i + 1];
			}
		}
		if (strcmp(argv[i], "-P") == 0) {
			save_pdf = true;
			output_filename = "charge_resolution";
			if (i + 1 != argc && string(argv[i + 1]).find("-") != 0) {
				output_filename = argv[i + 1];
			}
		}
		if (strcmp(argv[i], "-R") == 0) {
			save_root = true;
			output_filename = "charge_resolution";
			if (i + 1 != argc && string(argv[i + 1]).find("-") != 0) {
				output_filename = argv[i + 1];
			}
		}
		if (strcmp(argv[i], "-m") == 0) {
			if (i + 1 != argc && string(argv[i + 1]).find("-") != 0) {
				max_npe = (uint32_t) atoi(argv[i + 1]);
			}
		}
	}

	// Required options
//	if (!input_filepath_f) {
//		std::cout << Print::Level() <<
//		"[arg][error] Required argument not specified: [input_filepaths]" << endl;
//		std::cout << help_message << endl;
//		return 1;
//	}

	set<fs::path> input_rootfile_set;
	vector<Filepath_ptr> filepathV;
	for (fs::path path : input_filepath_set) {
		auto filepath = FilepathLoader::Load(path);
		input_rootfile_set.insert(filepath->GetInput());
		filepathV.push_back(filepath);
	}

	if (variation_plot) {
		if (!save_png && !save_pdf && !save_root) {
			TApplication *rootapp = new TApplication("example", 0, 0);
			charge_variation_plotter(filepathV, save_png, save_pdf, save_root, max_npe);
			gPad->Update();
			rootapp->Run();
		}
		else {
			charge_variation_plotter(filepathV, save_png, save_pdf, save_root, max_npe);
		}
	}
	else {
		if (!save_png && !save_pdf && !save_root) {
			TApplication *rootapp = new TApplication("example", 0, 0);
			charge_resolution_plotter(filepathV, save_png, save_pdf, save_root, output_filename, max_npe);
			gPad->Update();
			rootapp->Run();
		}
		else {
			charge_resolution_plotter(filepathV, save_png, save_pdf, save_root, output_filename, max_npe);
		}
	}

//	if (!save_png) {
//		TApplication *rootapp = new TApplication("example", 0, 0);
//		old_charge_resolution_plotter(input_rootfile_set, save_png, output_filename, max_npe);
//		gPad->Update();
//		rootapp->Run();
//	}
//	else {
//		old_charge_resolution_plotter(input_rootfile_set, save_png, output_filename, max_npe);
//	}

	END();
	return 0;
}

