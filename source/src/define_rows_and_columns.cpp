/*
 * define_rows_and_columns.cpp
 *
 *  Created on: 4 Sep 2015
 *      Author: Jason
 */

#include <define_rows_and_columns.h>

void define_rows_and_columns(Run_ptr run, int num_pixels) {
	for (auto& camera_pair : run->GetCameraMap()) {
		auto& camera = camera_pair.second;
		auto& pixel_map = camera.GetPixelMap();
		PixelInformation pixel_arrays;
		pixel_arrays.num_pixels = (int) num_pixels;
		for (auto& pixel_pair : pixel_map) {
			auto& pixel = pixel_pair.second;
			pixel_arrays.pixel[pixel.GetPixelId()] = pixel.GetPixelId();
			pixel_arrays.xpix[pixel.GetPixelId()] = pixel.GetXpix();
			pixel_arrays.ypix[pixel.GetPixelId()] = pixel.GetYpix();
		}
		define_rows_and_columns(&pixel_arrays);
		for (auto& pixel_pair : pixel_map) {
			auto& pixel = pixel_pair.second;
			pixel.SetRow(pixel_arrays.row[pixel.GetPixelId()]);
			pixel.SetColumn(pixel_arrays.column[pixel.GetPixelId()]);
		}
	}
}

void define_rows_and_columns(PixelInformation* camset) {
	START();
	cout << Print::Level() << "[ttree] Assigning rows and columns to pixels in TTree" << endl;

	// Setup variables
	int npix = camset->num_pixels;
	int i, j, nactpix = 0;
	int activated_pixel[H_MAX_PIX];
	double activated_xpix[H_MAX_PIX], activated_ypix[H_MAX_PIX];
	double adjacent_separation, transverse_separation = 0.0;
	double adjacent_position[H_MAX_PIX], transverse_position[H_MAX_PIX];
	double xpix_separation_test, ypix_separation_test;
   int line_already_stored = 0;
   double previous_adjacent_line_position, previous_transverse_line_position;
   int adjacent_is_on_same_row = 0;
   int max_num_transverse = 0, max_num_adjacent = 0;
   double adjacent_line_position[H_MAX_PIX], transverse_line_position[H_MAX_PIX];
   double previous_adjacent_position, previous_transverse_position;
   double tmp;
   double nearest_adjacent_separation, nearest_transverse_separation;
   for (i=0; i<npix; i++) {
   	activated_pixel[i] = -1;
   	activated_xpix[i] = 99999.9;
   	activated_ypix[i] = 99999.9;
   	adjacent_position[i] = 99999.9;
   	transverse_position[i] = 99999.9;
   	adjacent_line_position[i] = 99999.9;
   	transverse_line_position[i] = 99999.9;
   }

	// Recreate list of pixels as missing modules create errors in row calculation
	for (i=0;i<camset->num_pixels;i++) {
		if (camset->pixel[i] != -1) {
			activated_pixel[nactpix] = camset->pixel[i];
			activated_xpix[nactpix] = camset->xpix[i];
			activated_ypix[nactpix] = camset->ypix[i];
			nactpix++;
		}
	}

	// Find typical separation between pixels, and find the number of rows and columns
   xpix_separation_test = fabs(activated_xpix[0] - activated_xpix[1]);
   ypix_separation_test = fabs(activated_ypix[0] - activated_ypix[1]);
   if (xpix_separation_test > ypix_separation_test) {
   	//We are moving along x axis
   	adjacent_is_on_same_row = 1;
   	adjacent_separation = xpix_separation_test;
   	for (i=0; i<nactpix; i++) {
			adjacent_position[i] = activated_xpix[i];
			transverse_position[i] = activated_ypix[i];
   	}
   }
   else {
   	//We are moving along y axis
   	adjacent_is_on_same_row = 0;
   	adjacent_separation = ypix_separation_test;
   	for (i=0; i<nactpix; i++) {
			adjacent_position[i] = activated_ypix[i];
			transverse_position[i] = activated_xpix[i];
   	}
   }

   // Find transverse separation
   previous_adjacent_position = adjacent_position[0];
   previous_transverse_position = transverse_position[0];
   for (i=0; i<nactpix; i++) {
   	if (fabs(adjacent_position[i] - previous_adjacent_position) > adjacent_separation *2) {
   		//New row
   		transverse_separation = fabs(transverse_position[i] - previous_transverse_position);
   		break;
   	}
   	previous_adjacent_position = adjacent_position[i];
   	previous_transverse_position = transverse_position[i];
   }

   // Find number of rows and columns
   previous_transverse_position = 99999.9;
   previous_adjacent_position = 99999.9;
   for (i=0; i<nactpix; i++) {
   	line_already_stored = 0;
   	if (fabs(transverse_position[i] - previous_transverse_position) > transverse_separation *0.5) {
   		for (j=0;j<max_num_transverse;j++) {
   	   	if (fabs(transverse_position[i] - transverse_line_position[j]) < transverse_separation *0.5) {
   	   		//line already stored
   	   		line_already_stored = 1;
   	   	}
   		}
   		if (!line_already_stored) {
      		//New row (transverse)
      		transverse_line_position[max_num_transverse] = transverse_position[i];
      		max_num_transverse++;
   		}
   	}
   	previous_transverse_position = transverse_position[i];
		line_already_stored = 0;
   	if (fabs(adjacent_position[i] - previous_adjacent_position) > adjacent_separation *0.5) {
   		for (j=0;j<max_num_adjacent;j++) {
   	   	if (fabs(adjacent_position[i] - adjacent_line_position[j]) < adjacent_separation *0.5) {
   	   		//line already stored
   	   		line_already_stored = 1;
   	   	}
   		}
   		if (!line_already_stored) {
				//New column (adjacent)
				adjacent_line_position[max_num_adjacent] = adjacent_position[i];
				max_num_adjacent++;
   		}
   	}
   	previous_adjacent_position = adjacent_position[i];
   }

   // Rearrange lines into ascending order
   for (i=0; i<max_num_adjacent; i++) {
		for(j=0;j<max_num_adjacent-1;j++) {
			if(adjacent_line_position[j]>adjacent_line_position[j+1]) {
				tmp=adjacent_line_position[j];
				adjacent_line_position[j]=adjacent_line_position[j+1];
				adjacent_line_position[j+1]=tmp;
			}
		}
	}
   for (i=0; i<max_num_transverse; i++) {
		for(j=0;j<max_num_transverse-1;j++) {
			if(transverse_line_position[j]>transverse_line_position[j+1]) {
				tmp=transverse_line_position[j];
				transverse_line_position[j]=transverse_line_position[j+1];
				transverse_line_position[j+1]=tmp;
			}
		}
	}

   // Insert gaps between modules for empty rows and columns
   previous_adjacent_line_position = adjacent_line_position[0];
   for(i=0; i<max_num_adjacent; i++) {
		if (fabs(adjacent_line_position[i] - previous_adjacent_line_position) > adjacent_separation *1.5) {
			for(j=max_num_adjacent-1;j>=i;j--) {
				adjacent_line_position[j+1] = adjacent_line_position[j];
			}
			adjacent_line_position[i] = previous_adjacent_line_position + adjacent_separation;
			max_num_adjacent++;
   	}
		previous_adjacent_line_position = adjacent_line_position[i];
   }
   previous_transverse_line_position = transverse_line_position[0];
   for(i=0; i<max_num_transverse; i++) {
	   if (fabs(transverse_line_position[i] - previous_transverse_line_position) > transverse_separation *1.5) {
			for(j=max_num_transverse-1;j>=i;j--) {
				transverse_line_position[j+1] = transverse_line_position[j];
			}
			transverse_line_position[i] = previous_transverse_line_position + transverse_separation;
			max_num_transverse++;
   	}
		previous_transverse_line_position = transverse_line_position[i];
   }

   // Assign pixels to nearest rows and columns
   for (i=0; i<nactpix; i++) {
   	nearest_adjacent_separation = 99999.9;
   	nearest_transverse_separation = 99999.9;
   	for (j=0; j<max_num_adjacent; j++) {
   		if (fabs(adjacent_position[i] - adjacent_line_position[j]) < nearest_adjacent_separation) {
   			nearest_adjacent_separation = fabs(adjacent_position[i] - adjacent_line_position[j]);
   			if (adjacent_is_on_same_row) {
   				camset->column[activated_pixel[i]] = j;

   			}
   			else {
   				camset->row[activated_pixel[i]] = j;
   			}
   		}
   	}
   	for (j=0; j<max_num_transverse; j++) {
   		if (fabs(transverse_position[i] - transverse_line_position[j]) < nearest_transverse_separation) {
   			nearest_transverse_separation = fabs(transverse_position[i] - transverse_line_position[j]);
   			if (adjacent_is_on_same_row) {
   				camset->row[activated_pixel[i]] = j;
			   }
   			else {
   				camset->column[activated_pixel[i]] = j;
   			}
   		}
   	}
   }
	cout << Print::Level() << "[ttree] Assignment Complete" << endl;
	END();
}