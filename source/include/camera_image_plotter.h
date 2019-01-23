//
// Created by Jason Watson on 10/09/15.
//

/*
 * Outputs an image of the 2D histogram of the camera face, with the pixels coloured corresponding
 * to the intensity of the branch value specified.
 */

#ifndef OXTOOLS_CAMERA_IMAGE_PLOTTER_H
#define OXTOOLS_CAMERA_IMAGE_PLOTTER_H

#include <initialise.h>
#include <Filepath.h>

void camera_image_plotter(Filepath_ptr input_fp, string branch_name,
                          uint32_t event_requested, std::pair<float,float> tailcut_values,
                          bool all_events = false, bool save_images = false,
                          bool hillas_p = false, int camera_requested = -1, bool source = false, bool rms_f = false);
void basic_camera_image_plotter(Filepath_ptr input_fp, string branch_name,
                                uint32_t event_requested);

#endif //OXTOOLS_CAMERA_IMAGE_PLOTTER_H
