//
// Created by Jason Watson on 18/09/15.
//

#include "Entry.h"

uint32_t Entry::sIdGenerator = 0;
string Entry::sInvestigation = "";

void Entry::Reset() {
	mFileIndex = 0;
	mEventId = 0;
	mSourceEventId = 0;
	mEventTimestamp = 0;
	mCameraId = 0;
	mPixelId = 0;

	mBranchValueMap.clear();
	mEventIdMap.clear();
}

void Entry::ResetStatic() {
	sIdGenerator = 0;
	sInvestigation = "";
}

void Entry::SetOxtoolsBranchAddress(TTree* input_TTree) {
	input_TTree->SetBranchAddress("fEventIndex", &mEventId);
	input_TTree->SetBranchAddress("fSourceEventIndex", &mSourceEventId);
	input_TTree->SetBranchAddress("fEventTimestamp", &mEventTimestamp);
	input_TTree->SetBranchAddress("fCameraId", &mCameraId);
	input_TTree->SetBranchAddress("fPixelId", &mPixelId);
	input_TTree->SetBranchAddress("fPulseHeight", &mBranchValueMap["fPulseHeight"]);
	input_TTree->SetBranchAddress("fPulseArea", &mBranchValueMap["fPulseArea"]);
	input_TTree->SetBranchAddress("fPulsePosition", &mBranchValueMap["fPulsePosition"]);
	input_TTree->SetBranchAddress("fTrueNPE", &mBranchValueMap["fTrueNPE"]);
}

void Entry::SetLibchecBranchAddress(TTree* input_TTree) {
	input_TTree->SetBranchAddress("fEventIndex", &mEventId);
	input_TTree->SetBranchAddress("fEventTimestamp", &mEventTimestamp);
	input_TTree->SetBranchAddress("fPeakHeight", &mBranchValueMap["fPulseHeight"]);
	input_TTree->SetBranchAddress("fPeakArea", &mBranchValueMap["fPulseArea"]);
	input_TTree->SetBranchAddress("fPeakPos", &mBranchValueMap["fPulsePosition"]);
}

void Entry::SetTTreeWriteBranches(TTree *&output_TTree) {
	output_TTree->Branch("fInvestigation", &sInvestigation, "fInvestigation/C");
	output_TTree->Branch("fEventIndex", &mEventId, "fEventIndex/i");
	output_TTree->Branch("fSourceEventIndex", &mSourceEventId, "fSourceEventIndex/i");
	output_TTree->Branch("fEventTimestamp", &mEventTimestamp, "fEventTimestamp/l");
	output_TTree->Branch("fCameraId", &mCameraId, "fCameraId/I");
	output_TTree->Branch("fPixelId", &mPixelId, "fPixelId/I");
	output_TTree->Branch("fPulseHeight", &mBranchValueMap["fPulseHeight"], "fPulseHeight/F");
	output_TTree->Branch("fPulseArea", &mBranchValueMap["fPulseArea"], "fPulseArea/F");
	output_TTree->Branch("fPulsePosition", &mBranchValueMap["fPulsePosition"], "fPulsePosition/F");
	output_TTree->Branch("fTrueNPE", &mBranchValueMap["fTrueNPE"], "fTrueNPE/F");
}

void Entry::ParseReadhessLine(string txt_file_line) {
	std::istringstream iss(txt_file_line);
	string context;
	iss >> context;
	iss >> sInvestigation;
	iss >> mSourceEventId;
	iss >> mEventTimestamp;
	iss >> mCameraId;
	iss >> mPixelId;
	iss >> mBranchValueMap["fPulseHeight"];
	iss >> mBranchValueMap["fPulseArea"];
	iss >> mBranchValueMap["fPulsePosition"];
	iss >> mBranchValueMap["fTrueNPE"];
	if (!mEventIdMap.count(mSourceEventId)) {
		mEventIdMap[mSourceEventId] = sIdGenerator++;;
	}
	mEventId = mEventIdMap[mSourceEventId];
}

void Entry::Clone(Entry old) {
	sInvestigation = old.sInvestigation;
	mEventId = old.mEventId;
	mSourceEventId = old.mSourceEventId;
	mEventTimestamp = old.mEventTimestamp;
	mCameraId = old.mCameraId;
	mPixelId = old.mPixelId;
	mBranchValueMap["fPulseHeight"] = old.mBranchValueMap["fPulseHeight"];
	mBranchValueMap["fPulseArea"] = old.mBranchValueMap["fPulseArea"];
	mBranchValueMap["fPulsePosition"] = old.mBranchValueMap["fPulsePosition"];
	mBranchValueMap["fTrueNPE"] = old.mBranchValueMap["fTrueNPE"];
}