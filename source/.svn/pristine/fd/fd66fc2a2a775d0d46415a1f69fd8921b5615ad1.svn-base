//
// Created by Jason Watson on 06/04/2016.
//

#include <initialise.h>
#include <Filepath.h>

void pixel_position_plotter(Filepath_ptr input_fp);

int main(int argc, char *argv[]) {
	START();
	string help_message = Form(
"%s [-f {input_filepath}] [-b {branch_name}] [-e {event_number} | -a] [OPTIONS] \n"
"  -- program to plot camera image from a TTree                                 \n\n"
"Options:        Arguments:          Description:                                 \n"
" -h | --help                         show the help text                          \n"
" -f              [input_filepath]    path to the root file (or txt file,         \n",
argv[0]);
	/// TODO: create algorithm to add new branches containing user created pulse height and pulse area

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

	// Run command
	TApplication *rootapp = new TApplication("example", 0, 0); // Allows graphics to be seen when using g++
	pixel_position_plotter(filepath);
	gPad->Update();
	rootapp->Run();

	END();
	return 0;
}

void pixel_position_plotter(Filepath_ptr input_fp) {

	//Build run
	Run_ptr run = input_fp->Read();

	Camera camera = run->GetCamera(0);

	TCanvas* canvas = new TCanvas("Cc1", "Cc1", 2500, 1450);
	TGraph* graph = new TGraph();
	for (auto& pixel_pair : camera.GetPixelMap()) {
		auto& pixel = pixel_pair.second;
		int current_point = graph->GetN();
		graph->SetPoint(current_point, pixel.GetXpix(), pixel.GetYpix());
	}

	graph->Draw("A*");
}