# database1
CD database
I have written this simple database type code to handle saving data and searching for the data as needed.
It works well with arduino, the data base is saved to the SD card.
Use the struct in your code, just change the data fields to suit your needs.
This is just what works for my needs.

//----main database struct to hold records------------
// note this struct is 44 bytes long with only 42 used

struct mainDB
{
  uint32_t  	brn;      //4 bytes 0-3
  uint16_t		unit;   
  uint16_t  	cyn;
  uint16_t  	dom; 	    //day of month	8-9
  uint16_t  	yer;  		//year 10-11
  char  		mth[6]; 		//month	12-17
};

Change it in DatabaseEx.h and add the same to your main code before setup.
Hope its useful.
