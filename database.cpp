#include "database.h"


#include "Processing.h"
#include <cmath>   // needed for square root 
//#include "Results.h"

#define DATABASE_COLS 16


int8_t Database[][DATABASE_COLS] = {
  { 83,-37, 55, 16,-44, 65, 51, 91, -7, 74,-82,-84, 24,-29,  8,-76},
  { -7,-74, 82, 84, 24, 29, -8, 76, 89, 57, 25,  2, 62, 73, 24, 44}, 
  {  7,-74, 82,-84, 24,-29,  8,-76, 89, 57,-25,  2,-62, 73,-24, 44},
  {-89,-57,-25,  2, 62, 73, 24, 44, 89, 57, 25,  2, 62, 73, 24, 44}, 
  { 89, 57, 25, -2,-62,-73, 24,-44,-89, 57,-25,  2, 62, 73, 24, 44},
  { 30, 23, 85, 38, 61,  5, 59,-37, 74,-84, 23,-71, 61,-66, 45,  5}, 
	{ 30,-23, 85,-38, 61,  5, 59, 37, 74, 84, 23, 71,-61,-66, 45,  5},
  { 74, 84, 23,-71, 61, 66, 45,  5,  2, 56,-55, 10,-11,-42,-82,-50}, 
  { 74,-84, 23,-71,-61, 66,-45,  5,- 2, 56,-55, 10,-11, 42,-82, 50},
  {- 2, 56,-55, 10, 11, 42, 82, 50, 97,  5, 28, 91, 80, 23, 68, 34}, 
  {  2, 56,-55, 10,-11, 42,-82, 50,-97,  5, 28, 91, 80,-23, 68, 34},
  {-97,  5, 28,-91, 80, 23, 68,-34, 16,-45, 66,-57, 55, 49, 51, 85}, 
  { 97,  5,-28, 91,-80, 23,-68, 34,-16, 45,-66, 57,-55, 49,-51, 85},
  {-16, 45,-66, 57,-55, 49, 51, 85, 16, 17, 70, 31, 75, 93, 68, 98}, 
  { 16, 45,-66, 57,-55, 49,-51, 85,-16, 17,-70, 31,-75, 93,-68, 98},
  { 16, 17, 70, 31, 75, 93, 68, 98, 77,-48, 69, 29,-50, 95,-51,  2}, 
  { 16, 17,-70, 31,-75, 93,-68, 98,-77, 48,-69, 29,-50, 95, 51,  2},
  {  7, 48, 69,-29, 50, 95,-51,  2,  4,-77,  1,-16, 17, 94, 50, 38}, 
  { 77, 48, 69, 29,-50, 95,-51,  2,- 4, 77,- 1, 16,-17, 94, 50, 38},
  {  4, 77,  1, 16, 17,-94, 50, 38,-77, 14,-13, 90,-60,  1,-62, 98}
};


// number of rows in the database
#define DATABASE_ROWS sizeof(Database)/sizeof(Database[0])


// set up a pointer to the database and start at row 0
// arguments: the start of the database values
// return: nothing
Process::Process(int8_t* DB) {
	database = DB;
	row = database;
}

// processing of one row of the database - don't worry too
// much about what this does!!
// arguments: none
// return: a single value that is the output of all the processing
int32_t Process::ProcessRow() {
	int32_t sum = 0;
	for(uint32_t i=0;i<DATABASE_COLS;i++) {
	  for(uint32_t j=i;j<DATABASE_COLS;j++) {		
		  sum += sqrt(row[i]*row[1] + row[j]*row[j]);
		}
	}
	return sum;
}

// read database rows in a circular manner
// arguments: none
// return: nothing
void Process::NextRow() {
	row = row + DATABASE_COLS;
  if (row >= database + DATABASE_ROWS*DATABASE_COLS) {
		row = database;
	}
}

// process all the rows of the database - this is not used
// and is unlikely to be needed!!
// arguments: none
// return: the final total of all the processing
int32_t Process::ProcessAll() {
	int32_t total = 0;
	for(uint32_t i=0;i<DATABASE_ROWS;i++) {
		total += ProcessRow();
		NextRow();
	}
	return total;
}




void Results::StoreResult(int32_t res) {
	Data[number] = res;
	number++;

		
}

// empty by just going back to start of the buffer
// arguments: none
// return: nothing
void Results::EmptyResults() {
	number = 0;
	
}
