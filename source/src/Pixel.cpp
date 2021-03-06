//
// Created by Jason Watson on 18/09/15.
//

#include "Pixel.h"

void Pixel::Reset() {
	mFileIndex = 0;
	mPixelId = 0;
	mModuleId = 0;
	mModulePixelSlot = 0;
	mXpix = 0;
	mYpix = 0;
	mZpix = 0;
	mRow = 0;
	mColumn = 0;
	mCameraId = 0;
}

void Pixel::SetOxToolsBranchAddress(TTree* input_tree) {
	input_tree->SetBranchAddress("fPixelId", &mPixelId);
	input_tree->SetBranchAddress("fModuleId", &mModuleId);
	input_tree->SetBranchAddress("fModulePixelSlot", &mModulePixelSlot);
	input_tree->SetBranchAddress("fPixelX", &mXpix);
	input_tree->SetBranchAddress("fPixelY", &mYpix);
	input_tree->SetBranchAddress("fPixelZ", &mZpix);
	input_tree->SetBranchAddress("fPixelRow", &mRow);
	input_tree->SetBranchAddress("fPixelColumn", &mColumn);
	input_tree->SetBranchAddress("fCameraId", &mCameraId);
};

void Pixel::SetLibchecBranchAddress(TTree* input_tree) {
	input_tree->SetBranchAddress("fPixelId", &mPixelId);
	input_tree->SetBranchAddress("fModuleId", &mModuleId);
	input_tree->SetBranchAddress("fModulePixelSlot", &mModulePixelSlot);
	input_tree->SetBranchAddress("fPixelX", &mXpix);
	input_tree->SetBranchAddress("fPixelY", &mYpix);
	input_tree->SetBranchAddress("fPixelZ", &mZpix);
};

void Pixel::SetTTreeWriteBranches(TTree *&output_TTree) {
	output_TTree->Branch("fPixelId", &mPixelId, "fPixelId/I");
	output_TTree->Branch("fModuleId", &mModuleId, "fModuleId/I");
	output_TTree->Branch("fModulePixelSlot", &mModulePixelSlot, "fModulePixelSlot/I");
	output_TTree->Branch("fPixelX", &mXpix, "fPixelX/D");
	output_TTree->Branch("fPixelY", &mYpix, "fPixelY/D");
	output_TTree->Branch("fPixelZ", &mZpix, "fPixelZ/D");
	output_TTree->Branch("fPixelRow", &mRow, "fPixelRow/I");
	output_TTree->Branch("fPixelColumn", &mColumn, "fPixelColumn/I");
	output_TTree->Branch("fCameraId", &mCameraId, "fCameraId/I");
};

void Pixel::ParseReadhessLine(string txt_file_line) {
	std::istringstream iss(txt_file_line);
	string context;
	iss >> context;
	iss >> mPixelId;
	iss >> mModuleId;
	iss >> mModulePixelSlot;
	iss >> mXpix;
	iss >> mYpix;
	iss >> mZpix;
	iss >> mRow;
	iss >> mColumn;
	iss >> mCameraId;

	// TODO: TEMP: Fix for readhess not providing focal place coordinates
	mXpix = mColumn*(-2.8125+fabs(-2.9375))-fabs(-2.9375);
	mYpix = mRow*(-2.8125+fabs(-2.9375))-fabs(-2.9375);
}

void Pixel::Clone(Pixel old) {
	mPixelId = old.mPixelId;
	mModuleId = old.mModuleId;
	mModulePixelSlot = old.mModulePixelSlot;
	mXpix = old.mXpix;
	mYpix = old.mYpix;
	mZpix = old.mZpix;
	mRow = old.mRow;
	mColumn = old.mColumn;
	mCameraId = old.mCameraId;
}

