//
// Created by Jason Watson on 16/09/15.
//

/*
 * 3b level of the OxTools entry structure.
 *
 * Each Pixel contains the properties of each of the 2048 pixel on a camera.
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

#ifndef OXTOOLS_PIXEL_H
#define OXTOOLS_PIXEL_H

#include <initialise.h>
#include <utilities.h>

typedef std::set<int> set_int;

class Pixel {
	 friend class Run;
	 friend class Camera;
private:
	 uint32_t mFileIndex;
	 int mPixelId;
	 int mModuleId;
	 int mModulePixelSlot; // Defined differently for readhess and libchec
	 double mXpix;
	 double mYpix;
	 double mZpix;
	 int mRow;
	 int mColumn;
	 int mCameraId;

	 set<int> mNeighbours;

public:
	 Pixel() {Reset();}

	 void Reset();
	 void SetTTreeWriteBranches(TTree *&output_TTree);
	 void SetOxToolsBranchAddress(TTree* input_tree);
	 void SetLibchecBranchAddress(TTree* input_tree);
	 void ParseReadhessLine(string txt_file_line);
	 void Clone(Pixel old);

	 GET(TTreeIndex, mFileIndex, uint32_t);
	 GET(PixelId, mPixelId, int);
	 GET(ModuleId, mModuleId, int);
	 GET(ModulePixelSlot, mModulePixelSlot, int);
	 GET(Xpix, mXpix, float);
	 GET(Ypix, mYpix, float);
	 GET(Zpix, mZpix, float);
	 GETSET(Row, mRow, int);
	 GETSET(Column, mColumn, int);
	 GET(Camera, mCameraId, int);
};

#endif //OXTOOLS_PIXEL_H
