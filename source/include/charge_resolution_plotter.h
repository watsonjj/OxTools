//
// Created by Jason Watson on 01/10/15.
//

/*
 * Outputs a graph of the charge resolution of data taken in a run by a camera, compared to
 * the CTA requirements and goals. Multiple runs can be plotted onto the same graph.
 */

#ifndef OXTOOLS_CHARGE_RESOLUTION_PLOTTER_H
#define OXTOOLS_CHARGE_RESOLUTION_PLOTTER_H

#include <initialise.h>
#include "Filepath.h"

void charge_resolution_plotter(vector<Filepath_ptr>, bool save_png, bool save_pdf,
                               bool save_root, string output_name, int user_max_npe = 2000);
void print_charge_resolution_scores(vector<Filepath_ptr> filepathV, int user_max_npe);
void charge_variation_plotter(vector<Filepath_ptr> filepathV, bool save_png, bool save_pdf,
		                              bool save_root, int user_max_npe);

#endif //OXTOOLS_CHARGE_RESOLUTION_PLOTTER_H
