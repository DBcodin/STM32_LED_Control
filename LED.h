//# include <iostream>
//extern "C" { 
//	#include "gpio_setup.h"  // set up input/output ports and interrupts
//}

//// number of LEDs on the board
//#define NUM_LEDs 8


//// specify LED actions and access through a bit pattern mask 
//class LEDs {     //LED FILES
//	public:
//	  LEDs (uint16_t);   // set up the bit pattern mask specifying the LED pin 
//  	void on();
//    void off();
//    void toggle();
//	private:
//		uint16_t bit_pattern;  // the bit pattern mask specifying the LED pin
//};

////-----------------------------------------------------------------------------------------------------
//// carry out simple processing of data obtained from the database
//class Process {// main files
// public:
//	Process(int8_t*);      // initialize the addresses pointing to the database
//	int32_t ProcessRow();  // data processing of the current row
//  void NextRow();        // change 'row' to point to the next database row
// 	int32_t ProcessAll();  // data processing of all the rows in turn
//  
// private:
//	int8_t* database;  // address of the start of the database
//  int8_t* row;       // address of current database row being processed
// 
//};

////------------------------


//class Results {  // main files
// public:
//	Results() {number = 0;}      // initial location is the start of the 'Data' data store
//	void StoreResult(int32_t);   // put an item in the data store
//  void EmptyResults();         // reset to point to the start of the data store

// private:
//	int32_t Data[DATABASE_ROWS];  // space to store results of processing each row
//  uint32_t number;              // current entry being accessed in the 'Data' data store
//};

# include <iostream>
extern "C" { 
	#include "gpio_setup.h"  // set up input/output ports and interrupts
}

// number of LEDs on the board
#define NUM_LEDs 8

// specify LED actions and access through a bit pattern mask 
class LEDs {     //LED FILES
	public:
	  LEDs (uint16_t);   // set up the bit pattern mask specifying the LED pin 
  	void on();
    void off();
    void toggle();
	private:
		uint16_t bit_pattern;  // the bit pattern mask specifying the LED pin
};

//-----------------------------------------------------------------------------------------------------
// carry out simple processing of data obtained from the database
class Process {// main files
 public:
	Process(int8_t*);      // initialize the addresses pointing to the database
	int32_t ProcessRow();  // data processing of the current row
  void NextRow();        // change 'row' to point to the next database row
 	int32_t ProcessAll();  // data processing of all the rows in turn
  
 private:
	int8_t* database;  // address of the start of the database
  int8_t* row;       // address of current database row being processed
 
};

//------------------------


class Results {  // main files
 public:
	Results() {number = 0;}      // initial location is the start of the 'Data' data store
	void StoreResult(int32_t);   // put an item in the data store
  void EmptyResults();         // reset to point to the start of the data store

 private:
	int32_t Data[DATABASE_ROWS];  // space to store results of processing each row
  uint32_t number;              // current entry being accessed in the 'Data' data store
};


//--------------------------------------------------

class changespeed {  //changespeed files
	public:
		void speed(int,int*);
	void setspeed(int speedplaceholder){numspeed = speedplaceholder;}
	int getspeed()const {return numspeed;}
	
	private:
		
	int numspeed;
	  
};



////--------------------------------------------------

//class changespeed {  //changespeed files
//	public:
//		void speed(int,int*);
//	void setspeed(int speedplaceholder){numspeed = speedplaceholder;}
//	int getspeed()const {return numspeed;}
//	
//	private:
//		
//	int numspeed;
//	  
//};




