//WSC318 Coursework

//Unfortunatly due to a multitude of errors experienced with the step of splitting my code into
//application layer i have had to leave all of my classes in the 'main' source file.
//i have included notes as to the layer that i planned each of my classes and their function definitions to go into

#include <cmath>   // needed for square root 
extern "C" { 
	#include "gpio_setup.h"  // set up input/output ports and interrupts
}
#include "database.h"  // the database data is read from here



//this would be included in the application layer
// carry out simple processing of data obtained from the database
class Process {
 public:
	Process(int8_t*);      // initialize the addresses pointing to the database
	int32_t ProcessRow();  // data processing of the current row
  void NextRow();        // change 'row' to point to the next database row
 	int32_t ProcessAll();  // data processing of all the rows in turn
 private:
	int8_t* database;  // address of the start of the database
  int8_t* row;       // address of current database row being processed
};

//this would be included in the application layer
// access an area of memory that keeps the results of the processing
class Results {
 public:
	Results() {number = 0;}      // initial location is the start of the 'Data' data store
	void StoreResult(int32_t);   // put an item in the data store
  void EmptyResults();         // reset to point to the start of the data store
 private:
	int32_t Data[DATABASE_ROWS];  // space to store results of processing each row
  uint32_t number;              // current entry being accessed in the 'Data' data store
};

//this would be included in the device layer
// specify LED actions and access through a bit pattern mask 
class LEDs {
	public:
	  LEDs (uint16_t);   // set up the bit pattern mask specifying the LED pin 
  	void on();
    void off();
    void toggle();
	private:
		uint16_t bit_pattern;  // the bit pattern mask specifying the LED pin
};



//this would be included in the application layer
class changespeed {
	public:
		void speed(int,int*);
	
	private:
		int x = 0;
	
};



//this would be included in the device layer
// number of LEDs on the board
#define NUM_LEDs 8

//this would be included in the device layer
// define the LEDs
LEDs LED[NUM_LEDs] = {LED8,LED6,LED4,LED3,LED5,LED7,LED9,LED10};

//this would be included in the device layer
// interrupt service routine called when button pressed
void HAL_GPIO_EXTI_Callback(uint16_t); 

//this would be included in the application layer
// indicates when input is received
volatile bool IP_flag = false;

// perform an example run of the processing and then run a loop to light LEDs
// and respond to the button presses
int main(void)
{
	
	
	
	// initialize the GPIO for the input/output of ports and set up interrupts
	gpio_setup();
	
  // timer interrupt frequency in 10ths of a microsecond (do not exceed 0xFFFFFF)
  SysTick_Config(2500); // this needs to be kept at 1000000 or system tick handler shits itself and doesnt flash :(

	
  // define objects for processing the database values and storing
	// the results of the calculations
	Process P(*Database);
  Results R;
	changespeed S;
	
	//CURRENTLY 05/01/2022 i was working on (and wasted a bunch of time on) trying to get the board to react to x being a number, tommrow try and get the two functions to react apropriatly using x
	int Placeholder = 0;
	int* ptr = &Placeholder;
	int county = 0;
	
	
while (1)  {	
	
	LED[2].off();  //bottom right blue blue leds
			LED[6].off();
		LED[0].off();    // orange leds
			LED[4].off();	
	
	while(IP_flag == true){
	////////////////////////////LED[5].toggle();  //green LEFT
				
		
		S.speed(county,ptr); // this will change the operation speed of processing
		if (Placeholder == 2500 ){
	  LED[3].off();  //BLUE LEFT
		LED[7].off();
		}
		if (Placeholder == 5000 ){
		LED[3].on();  //BLUE LEFT
		LED[7].on();
			//make red = 3 and 7
		}
		IP_flag = false;
		county = county +1;
	
}
	//-----------------------
	
	//while(!IP_flag) {
	
	SysTick_Config(Placeholder); // change processing speed to 1
		
	////////////LED[1].toggle();  //green led right  - atm this is turning off and on because each time the code runs through with a press of the button it is toggeling off and on
		
	// perform processing and store the results
	uint32_t total = P.ProcessAll();
	for(uint8_t i=0;i<DATABASE_ROWS; i++) {
		total = P.ProcessRow();
	  R.StoreResult(total);
    P.NextRow();
	//processing part (prewritten)

		
		//Section to react to the result of process which is 'total'
		if (total > 500){
			LED[2].on();  //bottom right blue blue leds
			LED[6].on();
		}
		else if (total == 0){
			LED[0].on();    // orange leds
			LED[4].on();
		}  //end of reacting part
		else
		//THIS EXCERSIE SHOWS ME THAT ALOT OF NUMBER ARE BEING PROCESSED ALL THE TIME, IT SHOWS THIS BY ONLY REACTING TO THE VERY RARE AND INFREQUENT OUTLIERS (WHICH IS STILL PRETTY DAM REQUENT)
		
		
		R.EmptyResults();	//clearresults - i might not have to do anything with this as changing the processing speed would therefor change the deleting speed 
	//led 1 and 5
	
	//------------------
//	LED[0].toggle();  // top right orange - this was to check that my code was reaching the end
	county = county +1;  // ready to be moved into rest of code
	
}

}}



//this would be included in the application layer
void changespeed::speed(int counting, int* placeholder){

	if ( counting % 2 ==0) {
		*placeholder = 5000;
	}
	else {
		*placeholder = 2500;
	}
	
	//return *placeholder; //need to double check that the counting value will stick around each time the function is called
}


//this would be included in the application layer
// set up a pointer to the database and start at row 0
// arguments: the start of the database values
// return: nothing
Process::Process(int8_t* DB) {
	database = DB;
	row = database;
}

//this would be included in the application layer
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

//this would be included in the application layer
// read database rows in a circular manner
// arguments: none
// return: nothing
void Process::NextRow() {
	row = row + DATABASE_COLS;
  if (row >= database + DATABASE_ROWS*DATABASE_COLS) {
		row = database;
	}
}

//this would be included in the application layer
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

//this would be included in the application layer
// add a result to the next location in memory
// arguments: the value to add to the memory area
// return: nothing
void Results::StoreResult(int32_t res) {
	Data[number] = res;
	number++;
}

//this would be included in the application layer
// empty by just going back to start of the buffer
// arguments: none
// return: nothing
void Results::EmptyResults() {
	number = 0;
	LED[1].toggle();
	LED[5].toggle();
}


//this would be included in the device layer
// configure an LED by connecting to a specific pin
LEDs::LEDs(uint16_t _bit_pattern) {
	bit_pattern = _bit_pattern;
	off();
}


//this would be included in the device layer
// turn on an LED
// arguments: none
// return: nothing
void LEDs::on()
{
  GPIOE->ODR = GPIOE->ODR | (uint16_t) bit_pattern;
}


//this would be included in the device layer
// turn off an LED
// arguments: none
// return: nothing
void LEDs::off()
{
  GPIOE->ODR = GPIOE->ODR & ~((uint16_t) bit_pattern);
}


//this would be included in the device layer
// toggle an LED 
// arguments: none
// return: nothing
void LEDs::toggle()
{
  GPIOE->ODR = GPIOE->ODR ^ ((uint16_t) bit_pattern);
}




//this would be included in the device driver layer
// Interrupt service routine for handling Port A interrupts
// arguments: the pin generating the input
// return: nothing
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{	
	 if(GPIO_Pin == GPIO_PIN_0) { // check the user button has generated the interrupt
   //GPIOE->ODR = GPIOE->ODR ^ (uint16_t) LED10;  // toggle red LED at top of board
		IP_flag = true;
  }
	
}


//This would be placed into my device driver layer
// This function handles the system tick timer interrupt
// arguments : none
// return: nothing
void SysTick_Handler(void)
{
  //GPIOE->ODR = GPIOE->ODR ^ (uint16_t) LED3;  // toggle red LED at bottom of board - 
 
//include system repeat speed and delete speed as variables that area called by adress to make sure the numbers truly change
}