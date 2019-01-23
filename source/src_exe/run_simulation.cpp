#include <simulation.h>
#include <Filepath.h>

int main(int argc, char *argv[])
{
	START();
	string help_message = Form(
"%s [-f {input_filepaths}] [OPTIONS] \n"
"  -- program to run a simulation of an MAPM                                  \n\n"
"Options:        Arguments:        Description:                                 \n"
" -h | --help                       show the help text                          \n"
" -f              [input_filepath]  path to the input file used to extract      \n"
"                                     camera geometry                           \n"
" -R              [output_filepath]  path to save the run                       \n"
" -n              [num_events]      number of events to simulate (default=1)    \n"
" -P              [photons]         mean number of photons per pixel to simulate\n"
"                                      (default=1)                              \n"
" -V                                run a single verbose simulation             \n"
" -D              [output_name]     output plots from the simulation as a png   \n",
			  argv[0]);

// Define variables;
	fs::path input_filepath;
	uint32_t num_events = 1;
	uint32_t num_photons = 1;
	bool single_verbose = false;
	bool draw = false;
	string output_filename = "simulation";
	fs::path run_output_filepath = "";

	// Check for required arguments
	bool input_filepath_f = false;
	bool create_run_f = false;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			std::cout << help_message << endl;
			return 1;
		}
		if (strcmp(argv[i], "-f") == 0) {
			if (i + 1 != argc && string(argv[i + 1]).find("-") != 0) {
				input_filepath = argv[i + 1];
				input_filepath_f = true;
			}
		}
		if (strcmp(argv[i], "-R") == 0) {
			create_run_f = true;
			if (i + 1 != argc && string(argv[i + 1]).find("-") != 0) {
				run_output_filepath = argv[i + 1];
			}
		}
		if (strcmp(argv[i], "-n") == 0) {
			if (i + 1 != argc && string(argv[i + 1]).find("-") != 0) {
				num_events = (uint32_t) atoi(argv[i + 1]);
			}
		}
		if (strcmp(argv[i], "-P") == 0) {
			if (i + 1 != argc && string(argv[i + 1]).find("-") != 0) {
				num_photons = (uint32_t) atoi(argv[i + 1]);
			}
		}
		if (strcmp(argv[i], "-V") == 0) {
			single_verbose = true;
		}
		if (strcmp(argv[i], "-D") == 0) {
			draw = true;
			if (i + 1 != argc && string(argv[i + 1]).find("-") != 0) {
				output_filename = argv[i + 1];
			}
		}
	}

	// Required options
	if (create_run_f && !input_filepath_f) {
		std::cout << Print::Level() <<
		"[arg][error] Required argument not specified: [input_filepaths]" << endl;
		std::cout << help_message << endl;
		return 1;
	}


	PMTSimulation simulation;

	simulation.SetVerbosity(0);
	simulation.GetConfig().SetNumEvents(num_events);
	simulation.GetConfig().SetMeanPhotonsPerPixel(num_photons);

	simulation.GetConfig().SetLaserActivated(true);
	simulation.GetConfig().SetNSBActivated(true);
	simulation.GetConfig().SetThermalActivated(true);
	simulation.GetConfig().SetCrosstalkActivated(true);
	simulation.GetConfig().SetLatepulseActivated(true);
	simulation.GetConfig().SetAnalogueNoiseActivated(true);
	simulation.GetConfig().SetDigitalNoiseActivated(true);

	if (create_run_f) {
		simulation.GetConfig().SetNSBActivated(false);
		simulation.GetConfig().SetThermalActivated(false);
		simulation.GetConfig().SetCrosstalkActivated(false);
		auto filepath = FilepathLoader::Load(input_filepath);
		simulation.Run(filepath,run_output_filepath);
	}
	if (single_verbose) {
		simulation.GetConfig().SetNumEvents(1);
		simulation.SetVerbosity(1);
		simulation.SingleRun();
	}
	if (draw) {
//		TApplication *rootapp = new TApplication("example", 0,0); // Allows graphics to be seen when using g++
		simulation.DrawRun(output_filename);
//		gPad->Update();
//		rootapp->Run();
	}

	END();
}




