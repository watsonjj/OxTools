//
// Created by Jason Watson on 07/03/2016.
//

#include "Filepath.h"
#include <define_rows_and_columns.h>

Run_ptr OxRootFilepath::Read() {
	if (!mRun) {
		START()

		mRun = std::make_shared<Run>(shared_from_this());

		Long64_t event_entries = mEventTTree->GetEntries();
		Long64_t pixel_entries = mPixelTTree->GetEntries();

		// Checks
		if (event_entries == 0) THROW("Event TTree is empty!");
		if (pixel_entries == 0) THROW("Pixel TTree is empty!");

		Pixel pixel_holder;
		pixel_holder.SetOxToolsBranchAddress(mPixelTTree);
		Progress progressP(pixel_entries, "Filling pixel information from TTree : ");
		for (uint32_t i = 0; i < pixel_entries; i++) {
			progressP.Print(i);
			mPixelTTree->GetEntry(i);
			mRun->AddPixel(i, pixel_holder);
		}

		Entry entry_holder;
		entry_holder.SetOxtoolsBranchAddress(mEventTTree);
		Progress progressE(event_entries, "Filling event information from TTree : ");
		for (uint32_t i = 0; i < event_entries; i++) {
			progressE.Print(i);
			mEventTTree->GetEntry(i);
			mRun->AddEntry(i, entry_holder);
		}

		mRun->SetStats();

		END()
	}
	return mRun;
}

Run_ptr LibchecFilepath::Read() {
	if (!mRun) {
		START()

		mRun = std::make_shared<Run>(shared_from_this());

		Long64_t entries = mTTree->GetEntries();

		// Checks
		if (entries == 0) THROW("TTree is empty!");

		Pixel pixel_holder;
		Entry entry_holder;
		pixel_holder.SetLibchecBranchAddress(mTTree);
		entry_holder.SetLibchecBranchAddress(mTTree);

		Progress progressP(entries, "Filling run information from TTree : ");
		for (uint32_t i = 0; i < entries; i++) {
			progressP.Print(i);
			mTTree->GetEntry(i);
			entry_holder.mPixelId = pixel_holder.GetPixelId();
			entry_holder.mSourceEventId = entry_holder.mEventId;
			mRun->AddPixel(i, pixel_holder);
			mRun->AddEntry(i, entry_holder);
		}

		define_rows_and_columns(mRun, 2048); // Hardcoded in-case of missing modules

		mRun->SetStats();

		END()
	}
	return mRun;
}

Run_ptr ReadhessFilepath::Read() {
	if (!mRun) {
		START()
		srand ((uint) time(NULL)); // random number to avoid problems with multiple instances
		string temp_name = "___temp___" + std::to_string(rand()) + ".root";
		fs::path temp_out = GetInputDirectory() / temp_name;
		TFile* f = new TFile(temp_out.c_str(),"recreate"); //avoid error
		if (!mPixelTTree || !mEventTTree) {

			// Create TTrees
			/*
			 * NOTE: for some reason it is faster to parse the txt file into a ttree
			 * then fill the Run structure from the ttree!
			 */

			mEventTTree = new TTree("event", "");
			mPixelTTree = new TTree("pixel", "");

			// Create holder objects for input to TTree
			Entry entry_holder;
			Pixel pixel_holder;

			// Set ttree addresses
			entry_holder.SetTTreeWriteBranches(mEventTTree);
			pixel_holder.SetTTreeWriteBranches(mPixelTTree);

			string line;
			std::ifstream file;
			file.open(mInput.c_str());

			int other_investigation = false;
			Progress progress(get_file_size(mInput), // TODO: put into Filepath
			                  "Parsing input file and filling TTrees : ");
			while(!file.eof()) {
				progress.AppendPrint(line.length());
				getline(file, line);
				if (line.find("CONTENTS") != string::npos) {
					continue;
				}
				else if (line.find("!OX-PIXEL") != string::npos) {
					pixel_holder.ParseReadhessLine(line);
					mPixelTTree->Fill();
				}
				else if (line.find("!OX-DATA") != string::npos) {
					if (line.find(Entry::GetInvestigation()) != string::npos) {
						entry_holder.ParseReadhessLine(line);
						mEventTTree->Fill();
					}
					else if (!other_investigation) {
						COUTP("[file][warning] Multiple investigations inside txt file "
								        "- Current investigation: " << Entry::GetInvestigation());
						other_investigation = true;
					}
				}
			}
			COUTP("[run][investigation] " << Entry::GetInvestigation());
			file.close();
		}

		mRun = std::make_shared<Run>(shared_from_this());

		Long64_t event_entries = mEventTTree->GetEntries();
		Long64_t pixel_entries = mPixelTTree->GetEntries();

		// Checks
		if (event_entries == 0) THROW("Event TTree is empty!");
		if (pixel_entries == 0) THROW("Pixel TTree is empty!");

		Pixel pixel_holder;
		pixel_holder.SetOxToolsBranchAddress(mPixelTTree);
		Progress progressP(pixel_entries, "Filling pixel information from TTree : ");
		for (uint32_t i = 0; i < pixel_entries; i++) {
			progressP.Print(i);
			mPixelTTree->GetEntry(i);
			mRun->AddPixel(i, pixel_holder);
		}

		Entry entry_holder;
		entry_holder.SetOxtoolsBranchAddress(mEventTTree);
		Progress progressE(event_entries, "Filling event information from TTree : ");
		for (uint32_t i = 0; i < event_entries; i++) {
			progressE.Print(i);
			mEventTTree->GetEntry(i);
			mRun->AddEntry(i, entry_holder);
		}

		mRun->SetStats();

		f->Close();
		delete f;
		if (!fs::remove(temp_out)) COUTP("[WARNING] temp file not deleted: " << temp_out);

		END()
	}
	return mRun;
}

Run_ptr OxRootFilepath::Join(set<fs::path> inputs) {
	START()

	mRun = std::make_shared<Run>(shared_from_this());
	uint32_t new_event_id = 0;

	for (auto input : inputs) {
		auto filepath = FilepathLoader::Load(input);
		Run_ptr run = filepath->Read();

		Progress progress(run->GetNumEventEntries()+run->GetNumPixelEntries(), "Extracting Run: ");
		uint32_t count = 0;
		for (auto& camera_pair : run->GetCameraMap()) {
			auto& camera = camera_pair.second;
			for (auto& pixel_pair : camera.GetPixelMap()) {
				auto& pixel = pixel_pair.second;
				mRun->AddPixel(0, pixel);
				progress.Print(count++);
			}
			for (auto& event_pair : camera.GetEventMap()) {
				auto& event = event_pair.second;
				for (auto& entry_pair : event.GetEntryMap()) {
					auto& entry = entry_pair.second;
					entry.SetEventId(new_event_id);
					mRun->AddEntry(0, entry);
					progress.Print(count++);
				}
				new_event_id++;
			}
		}
	}

	COUTP("[run] New run created");
	mRun->SetStats();

	END()
	return mRun;
}