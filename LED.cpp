#include <iostream> 
#include <string.h> 


#include "LED.h" 


#include <cmath>   // needed for square root 




//int8_t Database[][DATABASE_COLS] = {
//  { 83,-37, 55, 16,-44, 65, 51, 91, -7, 74,-82,-84, 24,-29,  8,-76},
//  { -7,-74, 82, 84, 24, 29, -8, 76, 89, 57, 25,  2, 62, 73, 24, 44}, 
//  {  7,-74, 82,-84, 24,-29,  8,-76, 89, 57,-25,  2,-62, 73,-24, 44},
//  {-89,-57,-25,  2, 62, 73, 24, 44, 89, 57, 25,  2, 62, 73, 24, 44}, 
//  { 89, 57, 25, -2,-62,-73, 24,-44,-89, 57,-25,  2, 62, 73, 24, 44},
//  { 30, 23, 85, 38, 61,  5, 59,-37, 74,-84, 23,-71, 61,-66, 45,  5}, 
//	{ 30,-23, 85,-38, 61,  5, 59, 37, 74, 84, 23, 71,-61,-66, 45,  5},
//  { 74, 84, 23,-71, 61, 66, 45,  5,  2, 56,-55, 10,-11,-42,-82,-50}, 
//  { 74,-84, 23,-71,-61, 66,-45,  5,- 2, 56,-55, 10,-11, 42,-82, 50},
//  {- 2, 56,-55, 10, 11, 42, 82, 50, 97,  5, 28, 91, 80, 23, 68, 34}, 
//  {  2, 56,-55, 10,-11, 42,-82, 50,-97,  5, 28, 91, 80,-23, 68, 34},
//  {-97,  5, 28,-91, 80, 23, 68,-34, 16,-45, 66,-57, 55, 49, 51, 85}, 
//  { 97,  5,-28, 91,-80, 23,-68, 34,-16, 45,-66, 57,-55, 49,-51, 85},
//  {-16, 45,-66, 57,-55, 49, 51, 85, 16, 17, 70, 31, 75, 93, 68, 98}, 
//  { 16, 45,-66, 57,-55, 49,-51, 85,-16, 17,-70, 31,-75, 93,-68, 98},
//  { 16, 17, 70, 31, 75, 93, 68, 98, 77,-48, 69, 29,-50, 95,-51,  2}, 
//  { 16, 17,-70, 31,-75, 93,-68, 98,-77, 48,-69, 29,-50, 95, 51,  2},
//  {  7, 48, 69,-29, 50, 95,-51,  2,  4,-77,  1,-16, 17, 94, 50, 38}, 
//  { 77, 48, 69, 29,-50, 95,-51,  2,- 4, 77,- 1, 16,-17, 94, 50, 38},
//  {  4, 77,  1, 16, 17,-94, 50, 38,-77, 14,-13, 90,-60,  1,-62, 98}
//};

  //volatile bool IP_flag = false;

// define the LEDs
LEDs LED[NUM_LEDs] = {LED8,LED6,LED4,LED3,LED5,LED7,LED9,LED10};

// interrupt service routine called when button pressed
void HAL_GPIO_EXTI_Callback(uint16_t); 

// indicates when input is received


// configure an LED by connecting to a specific pin
LEDs::LEDs(uint16_t _bit_pattern) {
	bit_pattern = _bit_pattern;
	off();
}

// turn on an LED
// arguments: none
// return: nothing
void LEDs::on()
{
  GPIOE->ODR = GPIOE->ODR | (uint16_t) bit_pattern;
}

// turn off an LED
// arguments: none
// return: nothing
void LEDs::off()
{
  GPIOE->ODR = GPIOE->ODR & ~((uint16_t) bit_pattern);
}

// toggle an LED 
// arguments: none
// return: nothing
void LEDs::toggle()
{
  GPIOE->ODR = GPIOE->ODR ^ ((uint16_t) bit_pattern);
}


//------------------------------------------------------

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

//------------------------------------------------------------------------

void Results::StoreResult(int32_t res) {
	Data[number] = res;
	number++;

		if (res > 500){
			LED[2].on();  //bottom right blue blue leds
			LED[6].on();
		}
		else if (res == 0){
			LED[0].on();    // orange leds
			LED[4].on();
		}  //end of reacting part
}

// empty by just going back to start of the buffer
// arguments: none
// return: nothing
void Results::EmptyResults() {
	number = 0;
	LED[1].toggle();
	  LED[5].toggle();
	
	LED[2].off();    //blue leds
			LED[6].off();
		  LED[0].off();    // orange leds
			LED[4].off();	
}

//------------------------------------------------------------------------

//// Interrupt service routine for handling Port A interrupts
//// arguments: the pin generating the input
//// return: nothing
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{	
//	 if(GPIO_Pin == GPIO_PIN_0) { // check the user button has generated the interrupt
//   //GPIOE->ODR = GPIOE->ODR ^ (uint16_t) LED10;  // toggle red LED at top of board
//		IP_flag = true;
//  }
//	
//}

// This function handles the system tick timer interrupt
// arguments : none
// return: nothing
void SysTick_Handler(void)
{
  //GPIOE->ODR = GPIOE->ODR ^ (uint16_t) LED3;  // toggle red LED at bottom of board - 
 
//include system repeat speed and delete speed as variables that area called by adress to make sure the numbers truly change
}


//------------------------------------------



void changespeed::speed(int counting, int* placeholder){

	if ( counting % 2 ==0) {
		*placeholder = 500;
			LED[3].on();  //red
		LED[7].on();
		
	}
	else {
		*placeholder = 250;
		 LED[3].off();  //BLUE LEFT
		LED[7].off();
	}
	
	//return *placeholder; //need to double check that the counting value will stick around each time the function is called
}




