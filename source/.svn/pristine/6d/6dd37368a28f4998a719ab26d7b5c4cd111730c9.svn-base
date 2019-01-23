#include "Filepath.h"
#include "PulseSpectrumFit.h"

int main(int argc, char *argv[]) {
	START();
	string help_message = Form(
			  "%s [-f {input_filepath}] [-b {branch}] [OPTIONS] \n"
						 "  -- program to plot camera image from a TTree                                 \n\n"
						 "Options:        Arguments:          Description:                                \n"
						 " -h | --help                         show the help text                         \n"
						 " -f              [input_filepath]    path to the root file (or txt file,        \n"
						 "                                       which will be converted)                 \n"
						 " -b              [branch]            name of the branch to plot in the zaxis    \n"
						 "                                       (colour axis)                            \n"
						 " -T                                  type of fitting (low, high or both)        \n"
					    " -c              [calib_filepath]    path to file for calibration (low pe file) \n"
					    " -R              [output_suffix]     update run with true charges and converted\n"
					    "                                       measured charge, save as a new file      \n"
			  ,argv[0]);
	/// TODO: create algorithm to add new branches containing user created pulse height and pulse area

	// Define variables;
	fs::path input_filepath;
	string branch;
	string type = "";
	fs::path calib_filepath;
	vector<string> allowed_types = {"low","high","both"};
	bool update_run = false;
	string output_suffix = "";

	// Check for required arguments
	bool input_filepath_f = false;
	bool branch_name_f = false;
	bool type_f = false;
	bool calib_filepath_f = false;

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
				branch = argv[i + 1];
				branch_name_f = true;
			}
		}
		if (strcmp(argv[i], "-T") == 0) {
			if (i + 1 != argc) {
				type = argv[i + 1];
				type_f = true;
			}
		}
		if (strcmp(argv[i], "-c") == 0) {
			if (i + 1 != argc) {
				calib_filepath = argv[i + 1];
				calib_filepath_f = true;
			}
		}
		if (strcmp(argv[i], "-R") == 0) {
			if (i + 1 != argc) {
				update_run = true;
				output_suffix = argv[i + 1];
			}
		}
	}

	// Required options
	if (!input_filepath_f) {
		std::cout << Print::Level() << "[arg][error] Required argument not specified: [input_filepath]" << endl;
		std::cout << help_message << endl;
		return 1;
	}
	if (!branch_name_f) {
		std::cout << Print::Level() << "[arg][error] Required argument not specified: [branch]" << endl;
		std::cout << help_message << endl;
		return 1;
	}
	if (!type_f) {
		std::cout << Print::Level() << "[arg][error] Required argument not specified: [type]" << endl;
		std::cout << help_message << endl;
		return 1;
	}

	if (std::none_of(std::begin(allowed_types), std::end(allowed_types),
	                 [type](string t){return (strcmp(type.c_str(), t.c_str())==0);})) {
		COUTP("[arg][error] Type not valid, possible types:");
		for (auto t : allowed_types) {
			cout << t << endl;
		}
		return 1;
	}

	bool calib_required = false;
	if (strcmp(type.c_str(), "low") == 0) {
		calib_required = false;
	}
	else if (strcmp(type.c_str(), "high") == 0) {
		calib_required = true;
	}
	else if (strcmp(type.c_str(), "both") == 0) {
		calib_required = true;
	}
	if (calib_required && !calib_filepath_f) {
		COUTP("[arg][error] Required argument not specified: [calib_file]");
		std::cout << help_message << endl;
		return 1;
	}

	// Load Filepath
	auto filepath = FilepathLoader::Load(input_filepath);
	Run_ptr run = filepath->Read();

	TH1F* calib_spectrum = nullptr;
	if (calib_filepath_f) {
		auto calib_file = FilepathLoader::Load(calib_filepath);
		Run_ptr calib_run = calib_file->Read();
		calib_spectrum = calib_run->GetSpectrum(branch);
	}

	if (!update_run) {
		string run_identifier = filepath->GetRunIdentifier() + "_";
		fs::path output = filepath->GetOutputDirectory() / run_identifier;
		PulseSpectrumFit fit(run->GetSpectrum(branch), type, output, calib_spectrum);
	}
	else {
		run->UpdateCharges(branch, type, calib_spectrum);
		string output_name = filepath->GetRunIdentifier() + "_" + output_suffix + ".ox.root";
		fs::path output = filepath->GetInputDirectory() / output_name;
		run->Write(output);
	}

	END();
	return 0;
}

