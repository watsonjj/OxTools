//
// Created by Jason Watson on 11/09/15.
//

#include "Filepath.h"

Filepath_ptr FilepathLoader::Load(fs::path input_filepath) {
	if (!fs::exists(input_filepath))
		THROW("Input file does not exist");
	Filepath temp_fp(input_filepath);
	if (temp_fp.mRoot) {
		RootFilepath temp_fpR(input_filepath);
		if (temp_fpR.GetTFile()->GetListOfKeys()->Contains("camera_data")) {
			COUTP("[file][Libchec] " << input_filepath);
			return LibchecFile_ptr(new LibchecFilepath(input_filepath));
		}
		else if (temp_fpR.GetTFile()->GetListOfKeys()->Contains("event") &&
				  temp_fpR.GetTFile()->GetListOfKeys()->Contains("pixel")) {
			COUTP("[file][OxRoot] " << input_filepath);
			return OxrootFile_ptr(new OxRootFilepath(input_filepath));
		}
//		else if (temp_fpR.GetTFile()->GetListOfKeys()->Contains("signalTree")) {
//			// TODO: HARM ttree
//		}
		else {
			COUTP("[file][Root] " << input_filepath);
			return RootFile_ptr(new RootFilepath(input_filepath));
		}
	}
	else if (temp_fp.mTxt) {
		TxtFilepath temp_fpT(input_filepath);
		if (get_first_line(temp_fp.GetInput()).find("!OX") != string::npos) {
			COUTP("[file][Readhess] " << input_filepath);
			return ReadhessFile_ptr(new ReadhessFilepath(input_filepath));
		}
		else {
			COUTP("[file][Txt] " << input_filepath);
			return TxtFile_ptr(new TxtFilepath(input_filepath));
		}
	}
	else {
		COUTP("[file] " << input_filepath);
		return Filepath_ptr(new Filepath(input_filepath));
	}
}

Filepath_ptr FilepathLoader::Create(fs::path input_filepath) {
	return OxrootFile_ptr(new OxRootFilepath(input_filepath));
}

void Filepath::Init() {
	mInput = "";
	mInputName = "";
	mInputDirectory = "";
	mInputStem = "";
	mInputExtension = "";
	mRoot = false;
	mOx = false;
	mTxt = false;
	mRunIdentifier = "";
	mOutputOxrootFilepath = "";
	mFileSize = 0;
	mRun = nullptr;
}

void Filepath::SetInput(fs::path input) {
	mInput = input;
	mInputName = input.filename();
	mInputDirectory = input.parent_path();
	mInputStem = input.stem();

	// Determine extension
	mInputExtension = input.extension();
	if (strcmp(mInputExtension.c_str(),".root") == 0) {
		mRoot = true;
		if (strcmp(mInputStem.extension().c_str(),".ox") == 0) {
			mOx = true;
			mInputStem = mInputStem.stem();
			mInputExtension = fs::path(".ox" + mInputExtension.string());
		}
	}
	else if (strcmp(mInputExtension.c_str(),".txt") == 0) {
		mTxt = true;
	}
	else THROW("Unknown file extension");

	SetRunIdentifier();
	mOutputOxrootFilepath = mInputDirectory / mRunIdentifier += ".ox.root";
}

void Filepath::SetRunIdentifier() {
	mRunIdentifier = regex_extract(mInputStem.string(), "cameradata_run([0-9]+.*)", false);
	if (mInput.string().find("cameradata_run") != string::npos)
		mRunIdentifier = "r" + mRunIdentifier;
}

void Filepath::CreateOutputDirectory() const{
	cout << mOutputDirectory << endl;
	if (boost::filesystem::create_directories(mOutputDirectory))
		COUTP("[directory][new] "<< mOutputDirectory);
}

void Filepath::Print() {
	COUTP("[filetype]        " << mType);
	COUTP("[filename]        " << mInputName.string());
	COUTP("[directory]       " << mInputDirectory.string());
}

void RootFilepath::Print() {
	Filepath::Print();
	print_TFile_contents(mTFile);
}