//
// Created by Jason Watson on 10/09/15.
//

/* TODO ideas:
 * option to print list of branches
*/

#include <camera_image_plotter.h>


void camera_image_plotter(Filepath_ptr input_fp, string branch_name,
                          uint32_t event_requested, std::pair<float,float> tailcut_values,
                          bool all_events, bool save_images, bool hillas_p,
                          int camera_requested, bool source, bool rms_f) {

	START();

	//Build run
	Run_ptr run = input_fp->Read();

	//Check branch exists
	run->CheckBranchesExist({branch_name});

	// Convert from source id
	uint32_t source_event = 0;
	if (source && !all_events) {
		source_event = event_requested;
		event_requested = run->GetCorrespondingEventId(event_requested);
	}

	// Check we are not out of range
	if (event_requested > run->GetMaxEventNum())
		THROW("Requested event out of range");

	// Set up output
	if (all_events) {
		fs::path delete_name = input_fp->GetRunIdentifier() + "_" + branch_name + "_image.gif";
		fs::path delete_path = input_fp->GetOutputDirectory() / delete_name;
		fs::remove(delete_path); // delete previous gif
	}
	if (save_images) input_fp->CreateOutputDirectory();

	// Find the number of cameras that will be plotted
	int num_cameras = run->GetNumCamerasWithEvent(event_requested);
	if (all_events) num_cameras = run->GetNumCameras();
	if (camera_requested>0 && !all_events) num_cameras = 1;

	// Print setup
	COUTP("[branch] " << branch_name);
	COUTP("[camera][loop] " << num_cameras);
	if (all_events) COUTP("[events][loop] " << run->GetMaxEventNum()+1);
	else COUTP("[event] " << event_requested);

	// Create canvas
	TCanvas* canvas;
	canvas = new TCanvas(Form("Camera"), "Camera Canvas", 3000, 2000);
	canvas->Divide(int(ceil(sqrt(num_cameras))), int(ceil(sqrt(num_cameras))));

	//Loop over event numbers
	uint32_t num_events = run->GetMaxEventNum()+1;
//	uint32_t num_events = 5;
	Progress progress(num_events, "Looping over events : ");
	int progress_i = 0;

	for (uint32_t current_event = 0; current_event < num_events; current_event++) {
		if (!all_events && current_event != event_requested) continue;
		progress.Print(current_event);

		//Loop over cameras
		int camera_index = 0;
		for (auto &camera_pair : run->GetCameraMap()) {
			auto &camera = camera_pair.second;
			int current_camera = camera.GetCameraId();
			if (camera_requested>0 && !all_events && current_camera != camera_requested) continue;


			// When plotting all_events, plot blank for empty cameras
			if (!run->CheckEventExists(current_camera, current_event) && !all_events) continue;
			canvas->cd(++camera_index);
			gPad->SetRightMargin(0.2);

			// Get the event's camera image
			TH2F* camera_image;
			TH2F* camera_image_tailcuts;
			double RMS_intensity;
			TEllipse* ellipse;
			if (run->CheckEventExists(current_camera, current_event)) {
				float min = run->GetEventBranchMin(current_event, branch_name);
				float max = run->GetEventBranchMax(current_event, branch_name);
				Event &event = camera.GetEvent(current_event);
				if (tailcut_values.first > 0 || tailcut_values.second > 0)
				{
					event.Tailcut(tailcut_values.first, tailcut_values.second, branch_name, rms_f);
				}
				camera_image = event.GetCameraImage(branch_name);
				camera_image->GetZaxis()->SetRangeUser(min, max);

				//Draw histograms/make tailcuts
				camera_image->Draw("colz"); // TODO: look at DrawCopy
//				camera.GetPixelIdTH2F()->Draw("same text");
				if (hillas_p) {
					event.GetHillasParameter(branch_name)->Draw();
				}
			}
			else {
				camera_image = camera.GetBaseCameraTH2F();
				camera_image->Draw("col");
			}
			camera.DrawPixelOutline();
			camera.PlotMarker(0,0);
			string title = Form("[IMAGE] Camera [RUN] %s [CAMERA] %d [EVENT] %d",
			                    input_fp->GetRunIdentifier().c_str(), current_camera,
			                    current_event);
			if (source && !all_events) title += Form(" [SOURCE_EVENT] %d",source_event);
			camera_image->SetTitle(title.c_str());
		}
		gPad->Update();
		// Save to file
		if (save_images) {
			string save_name = input_fp->GetRunIdentifier()
			                     + "_e" + std::to_string(current_event)
			                     + "_" + branch_name + "_image"
			                     + ".png";
			if (all_events && current_event<num_events-1) // TODO: check how i made gif in libchec
				save_name = input_fp->GetRunIdentifier()
	                     + "_" + branch_name + "_image"
	                     + ".gif+300";
			else if (all_events) {
				save_name = input_fp->GetRunIdentifier()
				            + "_" + branch_name + "_image"
				            + ".gif+600";
			}
			fs::path save_path = input_fp->GetOutputDirectory() / save_name;
			canvas->SaveAs(save_path.c_str());
			if (!(all_events && current_event<num_events-1)) {
				COUTP("[file][output] " << save_path);
			}
			canvas->Clear("D");
		}
	}
	END();
}

void basic_camera_image_plotter(Filepath_ptr input_fp, string branch_name,
                         uint32_t event_requested) {

	//Select required branches
	const set<string> branch_set = {branch_name};

	//Build run
	Run_ptr run = input_fp->Read();

	int camera_requested = 0;
	if (!run->CheckEventExists(camera_requested, event_requested)) exit(0);

	// Loop over cameras
	Camera &camera = run->GetCamera(camera_requested);

	// Create Histogram
	int num_rows = camera.GetNumRows();
	int num_columns = camera.GetNumColumns();
	TH2F *Hhist0 = new TH2F("camera_image", "camera_image", num_columns, 0, num_columns, num_rows, 0, num_rows);

	// Create canvas
	TCanvas* canvas= new TCanvas(Form("Camera"), "Camera Canvas", 3000, 2000);

	// Get event
	Event &event = camera.GetEvent(event_requested);

	// Fill Histogram
	for (auto &entry_pair : event.GetEntryMap()) {
		auto &entry = entry_pair.second;
		int pixel = entry.GetPixelId();
		int row = camera.GetPixel(pixel).GetRow();
		int column = camera.GetPixel(pixel).GetColumn();
		float bin_content = entry.GetBranchValue("fPulseHeight");
		Hhist0->SetBinContent(column + 1, row + 1, bin_content);

	}


	// Draw
	Hhist0->Draw("colz");
	camera.DrawPixelOutline();
	fs::path save_name = "example.png";
	fs::path save_path = input_fp->GetOutputDirectory() / save_name;
	canvas->SaveAs(save_path.c_str());
}
