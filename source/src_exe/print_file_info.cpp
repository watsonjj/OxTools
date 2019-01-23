//
// Created by Jason Watson on 12/02/2016.
//

#include <initialise.h>
#include <Filepath.h>

int main(int argc, char *argv[]) {
	START();
	string help_message = Form(
"%s [-f {input_filepath}]                                                       \n"
"  -- program to print information about a file                                 \n\n"
"Options:        Arguments:        Description:                                 \n"
" -h | --help                       show the help text                          \n"
" -f              [input_filepath]  path to the file                            \n",
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

	// Run command
	filepath->Print();

	END();
	return 0;
}