/*
  databaseEx.cpp - Library for Steri-Logicial code.
  Created by Frank Pedersen 2018 dec. 18
  All Rights Reserved. Alpah Micro Tech Inc.
  added new struct at 44 bytes as -mainDB-
*/

#include "Arduino.h"

#include "databaseEx.h" 


//===================start====================================== 
bool databaseEx::getSize(char* xName){
		
	if(!sdfile.isOpen()){
		sdEx.begin();
	}	
		sdfile = sdEx.open(xName, O_RDWR);
		
		if ( !sdfile ) return 0;	//added this 24-oct		
		count1 = ((sdfile.size()/44));
		sdfile.close();
		return 1;	
}

//-------------------------------------------------------------- 

int databaseEx::startSd(){
	
	flag = sdEx.begin(); // test if card is recognized 
	return 1;
}

//--------------------------------------------------------------
//--this is only used during serial testing/debuging--

void databaseEx::recvOneChar() {
 if (Serial.available() > 0) {
	receivedChar = Serial.read();
	haveData = true;
	}
}

void databaseEx::recvOneByte() {
 while (Serial.available() > 0) {
	receivedNum = Serial.parseInt();
	haveData = true;		
	}
}

// ========== sdEx open/create file to write ============================ 
int databaseEx::openCreate(char* xName) {
	
	if(!sdfile.isOpen()){
		sdEx.begin();
	}
	
	sdfile = sdEx.open(xName, O_RDWR | O_CREAT | O_AT_END );
  
  if ( !sdfile )
  {
    strcpy(reason, "openCreate failed");
    return 0; //  FAILED to open
  }

// ------------ sdEx write struct to file ----------------------------
// this file will only contain 1 struct although it could hold many
// since opening a file that already exists for write will start at the end
//

  count = sdfile.write((byte*) &copyto, sizeof(copyto));
  
  if ( count != sizeof( mainDB ))
  {
    
	sdfile.close(); // write fail
    return 0; //  FAILED to write!
  }

  sdfile.close(); // write success
  return 1;
}
// ========== end function and sdEx close file ==========================


// ========== sdEx open file to read ====================================

int databaseEx::openRead(char* xName) {
  sdfile = sdEx.open( xName, O_READ ); // try to open it
  
   if ( !sdfile ) // if not found, notify and change state
	{
		return 0; //  FAILED to open!
	}
	  
    if ( !sdfile.seek(receivedNum*44))
	{
    
		sdfile.close();
		return 0; //  FAILED to seek!
	}
  
// --- sdEx read file to struct ---

	sdfile.read((byte*) &copyto, sizeof(copyto));
 
	sdfile.close(); // close the open file
	return 1;
}
// ========== function end and sdEx close file ==========================


// ========== sdEx scan file for barcode ====================================

int databaseEx::openScan(char* xName) {
	
	if(!sdfile.isOpen()){
		sdEx.begin();
	}
		
	sdfile = sdEx.open( xName, O_READ ); // try to open it
  
	if ( !sdfile ) {// if not found, notify and change state
  
		strcpy(reason, "openScan failed");
	
		return 0; //  FAILED to open!
	}
	   
	for(uint32_t xb =0; xb <= count1; xb++){
		
		
		sdfile.read((byte*) &copyto, sizeof(copyto));
		
		if(scanNum == copyto.brn) {
			sdfile.close(); // close the open file
			fnd = true;
			return 1;
			break;			
		}		
		sdfile.seek(xb*44);		
	} 
	fnd = false;
	sdfile.close(); // close the open file
	return 0;		// file not found	
}
// ========== function end and sdEx close file ==========================


// ========== print retrieved data ====================================
void databaseEx::printresult(char* xName){ //function not in use
      //return 1; 

}


//=======================check scan number===========================
bool databaseEx::chkscan(){
	if(scanNum == copyto.brn){
	
		fnd = true;
		return 1;
		}
	else{
		fnd = false;
		return 0;
	}
}
//========================end========================================