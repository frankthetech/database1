/*
  DataBaseEx.h - Library for Steri-Logicial code.
  Created by Frank Pedersen 2018 dec. 18
  All Rights Reserved. Alpah Micro Tech Inc.
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
  uint32_t  	brn; 		//bar code num	0-3
  uint16_t		unit;		//sterlizer id 1 or 2	4-5
  uint16_t  	cyn; 		//cycle num	6-7
  uint16_t  	dom; 	//day of month	8-9
  uint16_t  	yer;  		//year 10-11
  char  		mth[6]; 		//month	12-17
  char  		uer[12];		//user	18-29
  char  		cnt[12];		//contents	30-41
  
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
	char  fname[14]; 	// even # of bytes big enough to hold 8.3 filename and terminator
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