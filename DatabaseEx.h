/*
  DataBaseEx.h - Library for database code.
  Created by Frank Pedersen 2018 dec. 18
*/
#ifndef DatabaseEx_h
#define DatabaseEx_h
#include <newSdFat.h>
#include "Arduino.h"
#include <SPI.h>
//#define CARD_CS 16
//#define USE_SDIO 1
//#define SPI0 SPI

class databaseEx
{

	
  public:
  
//----main database struct to hold records------------
// note this struct is 44 bytes long with only 42 used
struct mainDB
{
  uint32_t  	brn; 		
  uint16_t	unit;		
  uint16_t  	cyn; 		
  uint16_t  	dom; 		
  uint16_t  	yer;  		
  char  	mth[6]; 	
  char  	uer[12];	
  char  	cnt[12];	
  
};


//------------------define vars----------------------------
	SdFatSdioEX sdEx;
	//SdFat  	sdEx;
	File  	sdfile;      // File object
	
	bool	getSize(char* xName);
	void 	recvOneChar();
	void 	recvOneByte();
	void 	printresult(char* xName);
	bool 	chkscan();	
	
	char 	receivedChar;
	char  	fname[14]; 	// even # of bytes big enough to hold 8.3 filename and terminator
	char	reason[20];
	byte 	flag;
	
	int 	startSd();
	uint32_t scanNum;
	uint32_t count;
	uint32_t count1;
	uint16_t receivedNum;
	int 	openCreate(char* xName);
	int 	openRead(char* xName);
	int 	openScan(char* xName);
	
	boolean fnd = false;
	boolean haveData = false;
	
	//struct  mainDB  example; 	// creates space for struct example in SRAM
	struct  mainDB  copyto; 	// creates space for struct read
	
  private:
   
};

#endif
