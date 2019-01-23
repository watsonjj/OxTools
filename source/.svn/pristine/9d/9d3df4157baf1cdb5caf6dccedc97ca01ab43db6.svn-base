//
// Created by Laurel Kaye on 16/02/2016.
//
#include "Filepath.h"
#include <hillas_plots.h>

int main(int argc, char *argv[]) {
    START();
    string help_message = Form(
            "%s [-f {input_filepath}] [-b {branch_name}] [-e {event_number} | -a] [OPTIONS]   \n"
                    "  -- program to plot hillas parameters from a  TTree                             \n\n"
                    "Options:        Arguments:          Description:                                 \n"
                    " -h | --help                         show the help text                          \n"
                    " -f              [input_filepath]    path to the root file (or txt file,         \n"
                    "                                       which will be converted)                  \n"
                    " -b              [branch_name]       name of the branch to plot from which to    \n"
                    "                                       plot hillas                               \n"
                    " -S                                  save a png for this event                   \n"
                    "                                       (does not display graphics)               \n",
            argv[0]);

    //inputs stored here:
    fs::path input_filepath;
    fs::path input_filepath2;
    string branch_name;
    string branch_name2;
    bool save_images = false;

    //check for required arguments
    bool input_filepath_f = false;
    bool branch_name_f = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            std::cout << help_message << endl;
            return 1;
        }
        if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 != argc) {
                input_filepath = argv[i + 1];
                input_filepath2 = argv[i + 2];
                input_filepath_f = true;
            }
        }
        if (strcmp(argv[i], "-b") == 0) {
            if (i + 1 != argc) {
                branch_name = argv[i + 1];
                branch_name2 = argv[i + 2];
                branch_name_f = true;
            }
        }
        if (strcmp(argv[i], "-S") == 0) {
            save_images = true;
        }
    }

    // Required options
    if (!input_filepath_f) {
        std::cout << Print::Level() << "[arg][error] Required argument not specified: [input_filepath]" << endl;
        std::cout << help_message << endl;
        return 1;
    }
    if (!branch_name_f) {
        std::cout << Print::Level() << "[arg][error] Required argument not specified: [branch_name]" << endl;
        std::cout << help_message << endl;
        return 1;
    }


    // Load Filepath
    auto filepath = FilepathLoader::Load(input_filepath);
    auto filepath2 = FilepathLoader::Load(input_filepath2);
    

    // Run command
    if (!save_images) {
        TApplication *rootapp = new TApplication("example", 0, 0); // Allows graphics to be seen when using g++
        hillas_plotter(filepath, filepath2, branch_name, branch_name2, save_images);
        gPad->Update();
        rootapp->Run();
    }
    else {
        hillas_plotter(filepath, filepath2, branch_name, branch_name2, save_images);
    }

    END();
    return 0;
    
}