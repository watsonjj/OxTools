//
// Created by Jason Watson on 14/09/15.
//

#include <sys/stat.h>
#include "utilities.h"
#include <TLeaf.h>

char Print::dash = '-';
uint32_t Print::global_print_level = 0;


string regex_extract(string input, string regex, bool return_empty) {
	string output = boost::regex_replace(
			  input,
			  boost::regex(regex), // ("[^0-9]*([0-9]+).*"),
			  string("\\1"));
	if (strcmp(output.c_str(), input.c_str()) == 0) {
		if (return_empty) output = "";
		else output = input;
	}
	return output;
}

bool check_TTree_branch_exists(TTree *tree, string branch_name) {
	std::stringstream ss;
	auto old_buf = std::cout.rdbuf(ss.rdbuf()); //change the underlying buffer and save the old buffer
	tree->GetListOfBranches()->ls(); //->Print(); //all the std::cout goes to ss
	std::cout.rdbuf(old_buf); //reset
	return ss.str().find("\t" + branch_name + "\t") != string::npos;
}

long get_file_size(fs::path filepath) {
	struct stat stat_buf;
	int rc = stat(filepath.c_str(), &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}

string get_first_line(fs::path filepath) {
	string line;
	std::ifstream file;
	file.open(filepath.c_str());
	getline(file, line);
	file.close();
	return line;
}

void silence_root()
{
	gErrorIgnoreLevel = kWarning;
	return;
}

void print_TFile_contents(TFile* f) {
	TIter nextkey( f->GetListOfKeys() );
	TKey *key;
	vector<TObject*> tree_holder;
	while ((key = (TKey*)nextkey())) {
		TObject *obj = (TObject *) key->ReadObj();
		if (obj->IsA()->InheritsFrom(TTree::Class())) {
			tree_holder.push_back(obj);
		}
		else {
			COUTP("[TFile][contents] " << obj->IsA()->GetName() << " - " <<
			      obj->GetName() << " - " << obj->GetTitle());
		}
	}
	for (TObject* obj : tree_holder) {
		TTree* tree = (TTree *) f->Get(obj->GetName());
		COUTP("[TFile][contents] " << obj->IsA()->GetName() << " - " <<
		      obj->GetName() << " - " << obj->GetTitle() << " - Entries=" << tree->GetEntries());
		TObjArray *branch_list = (TObjArray*) tree->GetListOfBranches()->Clone();
		branch_list->SetOwner(kFALSE);

		vector<string> branchV{"Branch"};
		vector<string> typeV{"Type"};
		vector<string> minV{"Min"};
		vector<string> maxV{"Max"};

		for(int i = 0; i < branch_list->GetEntries(); ++i) {
			string name = branch_list->At(i)->GetName();
			string type = get_branch_type(branch_list->At(i)->GetTitle());
			std::stringstream firstS;
			std::stringstream minS;
			std::stringstream maxS;
			minS << tree->GetMinimum(name.c_str());
			maxS << tree->GetMaximum(name.c_str());

			branchV.push_back(name);
			typeV.push_back(type);
			minV.push_back(minS.str());
			maxV.push_back(maxS.str());
		}
		Table table({branchV,typeV,minV,maxV});
		table.Print();
	}
}

string get_branch_type(string type) {
	switch(type.back())
	{
		case 'C': return "string";
		case 'B': return "Char_t";
		case 'b': return "UChar_t";
		case 'S': return "Short_t";
		case 's': return "UShort_t";
		case 'I': return "Int_t";
		case 'i': return "UInt_t";
		case 'F': return "Float_t";
		case 'D': return "Double_t";
		case 'L': return "Long64_t";
		case 'l': return "ULong64_t";
		case 'O': return "Bool_t";
		default: return "UNKNOWN";
	}
}

void rainbow_palette() {
	// Define gradient color palette
	const Int_t NRGBs = 5;
	const Int_t NCont = 255;
	Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
	Double_t red[NRGBs] = {0.00, 0.00, 0.87, 1.00, 0.51};
	Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
	Double_t blue[NRGBs] = {0.51, 1.00, 0.12, 0.00, 0.00};
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
}