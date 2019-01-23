//
// Created by Jason Watson on 16/09/15.
//

/*
 * 4th level of the OxTools entry structure.
 *
 * Each Entry is a summary of the 90ns readout for one of the 2048 pixels in the camera.
 *
 * When a new entry is added to an event, the min/max of the branches are updated.
 *
 * OxTools entry structure:
 * RUN1
 *  |-------------------------------|
 * CAMERA1                      CAMERA2...(xNumCamerasInArray)
 *  |   |-------------------|
 *  |  PIXEL1            PIXEL2...(x2048 pixels)
 *  |---------------|
 *  EVENT1         EVENT2...(xNumEventTriggersForCamera)
 *     |--------|
 *   ENTRY1   ENTRY2...(x2048 pixels)
 */

#ifndef OXTOOLS_ENTRY_H
#define OXTOOLS_ENTRY_H

#include <initialise.h>
#include <utilities.h>

class Entry {
	 friend class Run;
	 friend class Event;
	 friend class LibchecFilepath;
	 friend class PMTSimulation;
private:
	 static uint32_t sIdGenerator;
	 map<uint32_t,uint32_t> mEventIdMap; // Map for matching source Event ID with an incremental ID

	 static string sInvestigation;
	 uint32_t mFileIndex;
	 uint32_t mEventId;
	 uint32_t mSourceEventId;
	 uint64_t mEventTimestamp;
	 int mCameraId;
	 int mPixelId;
	 map<string,float> mBranchValueMap; /* When reading a .ox.root file, the entry values of branches
													 * specified in the branch vector (Run initialisation
													 * argument) are stored in this variable, where the string is
													 * the branch name */

public:
	 Entry() {Reset();}

	 void Reset();
	 static void ResetStatic();
	 void SetOxtoolsBranchAddress(TTree* input_TTree);
	 void SetLibchecBranchAddress(TTree* input_TTree);
	 void SetTTreeWriteBranches(TTree *&output_TTree);
	 void ParseReadhessLine(string txt_file_line);
	 void Clone(Entry old);

	 GETSTATIC(Investigation, sInvestigation, string);
	 GET(TTreeIndex, mFileIndex, uint32_t);

	 GETSET(EventId, mEventId, uint32_t);
	 GET(SourceEventId, mSourceEventId, uint32_t);
	 GET(EventTimestamp, mEventTimestamp, uint32_t);
	 GET(CameraId, mCameraId, uint32_t);
	 GET(PixelId, mPixelId, int);
	 GETMAPCONTENT(BranchValue, mBranchValueMap, float, string);
};

#endif //OXTOOLS_ENTRY_H
