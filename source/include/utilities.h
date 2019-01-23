//
// Created by Jason Watson on 14/09/15.
//

/*
 * A collection of generic functions that have use across not only this project, but are generic
 * enough to be used in other C++/ROOT projects.
 */

#ifndef OXTOOLS_UTILITIES_H
#define OXTOOLS_UTILITIES_H

#include <initialise.h>

string regex_extract(string input, string regex, bool return_empty = true);
bool check_TTree_branch_exists(TTree *tree, string branch_name);
long get_file_size(fs::path filepath);
string get_first_line(fs::path filepath);
void silence_root();
void print_TFile_contents(TFile* f);
string get_branch_type(string type);
void rainbow_palette();

/* Class to customise the print statements in this project to include a depth indicator (as dashes).
 * Is called by the macro COUTP */
class Print {
private:
	 static char dash;
	 static uint32_t global_print_level;
public:
	 static string Level () {return string(global_print_level, dash);}
	 static void LevelIncrease() {global_print_level++;}
	 static void LevelDecrease() {global_print_level--;}
};

/* Class to produce a progress indicator in loops, useful for long loops to know the program is
 *  still progressing */
class Progress {
private:
	 int m_milestone = 0;
	 float m_milestone_base = 10;
	 float m_progress = 0.0;
	 float m_percentage = 0.0;
	 float m_total = 0.0;
	 string m_message = "";
	 Progress() {}
	 void IncrementMilestone() { m_milestone++; }
	 void SetPosition(float new_position) { m_progress = new_position; }
	 void AppendPosition(float new_position) { m_progress += new_position; }
	 void UpdatePercentage() {
		 m_percentage = m_progress / m_total * 100;
	 }
	 void PrintPercentage() {
		 cout << Print::Level() << m_message << int(m_percentage) << "% complete... \r";
		 fflush(stdout);
	 }
	 void ConditionalPrintPercentage() {
		 if (m_percentage > m_milestone*m_milestone_base) {
			 PrintPercentage();
			 IncrementMilestone();
		 }
	 }
public:
	 Progress(float total, string message = "", float milestone_base = 10) {
		 m_total = total;
		 m_milestone_base = milestone_base;
		 m_message = message;
	 }
	 void Print(float new_position) {
		 SetPosition(new_position);
		 UpdatePercentage();
		 ConditionalPrintPercentage();
	 }
	 void AppendPrint(float new_position) {
		 AppendPosition(new_position);
		 UpdatePercentage();
		 ConditionalPrintPercentage();
	 }
};

class Table {
private:
	 vector<vector<string>> mInputVector; //[column][line]
	 vector<u_long> mColumnWidth;
	 u_long mNColumns;
	 u_long mNLines;
	 std::stringstream mBorder;
	 vector<string> mLineVector;

	 void FillEmptyCells() {
		 for (vector<string>& column : mInputVector){
			 long N = mNLines - column.size();
			 for (int i=0; i < N; i++ ) {
				 column.push_back("");
			 }
		 }
	 }

	 void SetColumnWidths() {
		 mColumnWidth.assign(mInputVector.size(),0);
		 for (int column = 0; column < mNColumns; column++) {
			 for (string entry : mInputVector[column]) {
				 if (mColumnWidth[column] < entry.size()) mColumnWidth[column] = entry.size();
			 }
			 mColumnWidth[column]++;
		 }
	 }

	 void SetBorder() {
		 for (u_long w : mColumnWidth) {
			 mBorder << "+" << string(w,'-');
		 }
		 mBorder << "+";
	 }

	 void SetLines() {
		 std::stringstream lineS;
		 for (int line = 0; line < mNLines; line++) {
			 for (int column = 0; column<mNColumns; column++) {
				 int w = (int)mColumnWidth[column];
				 lineS << "|" << std::setw(w) << std::left << mInputVector[column][line];
			 }
			 lineS << "|";
			 mLineVector.push_back(lineS.str());
			 lineS.str(std::string()); // Clear
		 }
	 }
public:
	 Table(vector<vector<string>> input) :
			   mInputVector(input),
			   mNColumns(input.size()),
			   mNLines(input[0].size())
	 {
		 for (vector<string> column : mInputVector)
			 if (column.size() > mNLines) mNLines = column.size();
		 FillEmptyCells();
		 SetColumnWidths();
		 SetBorder();
		 SetLines();
	 }

	 void Print() {
		 for (string line : mLineVector) {
			 cout << mBorder.str() << endl;
			 cout << line << endl;
		 }
		 cout << mBorder.str() << endl;
		 cout << endl;
	 }
};

#endif //OXTOOLS_UTILITIES_H
