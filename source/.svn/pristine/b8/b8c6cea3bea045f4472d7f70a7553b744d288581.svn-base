#include "Filepath.h"

int main(int argc, char *argv[]) {
	START()
	string help_message = Form(
"%s [-f {input_filepaths}] [OPTIONS]                                            \n"
"  -- combine runs into a single .ox.root file                                  \n\n"
"Options:        Arguments:        Description:                                 \n"
" -h | --help                       show the help text                          \n"
" -f              [input_filepaths]  path to the input files (accepts wildcards)\n"
" -o              [output_name]     name of the new file                        \n",
argv[0]);

	// Define variables
	set<fs::path> input_filepath_set;
	string output_name = "";

	// Create flags for required inputs
	bool input_filepath_f = false;
	bool output_name_f = false;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			cout << help_message << endl;
			exit(0);
		}
		if (strcmp(argv[i], "-f") == 0) {
			while(i+1 < argc && string(argv[i + 1]).find("-") != 0) {
				input_filepath_set.insert(argv[i + 1]);
				input_filepath_f = true;
				i++;
			}
		}
		if (strcmp(argv[i], "-o") == 0) {
			if (i + 1 != argc) {
				output_name = argv[i + 1];
				output_name_f = true;
			}
		}
	}
	if (!input_filepath_f) {
		COUTP("[arg][error] Required argument not specified: [input_filepath]");
		cout << help_message << endl;
		return 1;
	}

	auto first_file = FilepathLoader::Load(*input_filepath_set.begin());
	fs::path output_dir = first_file->GetInputDirectory();
	string name = output_name + ".ox.root";
	auto new_file = FilepathLoader::Create(output_dir / name);

	new_file->Join(input_filepath_set)->Write(new_file->GetInput());

	END();
	return 0;
}
