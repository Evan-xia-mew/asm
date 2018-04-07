#include "util.h"

void main(){
	 char str1[5];
	 char str2[4];
	 int c2dResult;
	 char getRCResult;
	 char num;
	 char row=0, column=0;

	 //testing printHex
	 printHex(0xF); // should see 0x21
	 printHex(11);//should see B
	 printHex(0); //should see 0
	 
	 
	 //testing printChar
	 printChar('C'); //should see C
	 printChar('#'); //should see #
	 printChar('2'); //should see 2
	 
	 //testing printStr
	 str1[0]='T';
	 str1[1]='E';
	 str1[2]='S';
	 str1[3]='T';
	 str1[4]=0;
	 printStr(str1);//should see "TEST"

	 str1[0]='S';
	 str1[1]='1';
	 str1[2]='2';
	 str1[3]='C';
	 str1[4]=0;
	 printStr(str1);//should see "S12C"
	 
	 //testing convertToDecimal
	 
	 str2[0]='1';
	 str2[1]='2';
	 str2[2]='3';
	 str2[3]=0;
	 c2dResult = convertToDecimal(str2);
	 
	 if(c2dResult == 123){
	 	printHex(1);
	}else{
		  printHex(0);
	}
	 
	 str2[0]='3';
	 str2[1]='2';
	 str2[2]='1';
	 str2[3]=0;
	 c2dResult = convertToDecimal(str2);
	 	 if(c2dResult == 321){
	 	printHex(1);
	}else{
		  printHex(0);
	}
	
	//Testing convertToString
	
	 str2[0]='9';
	 str2[1]='9';
	 str2[2]='9';
	 str2[3]='9';
	 num =3;
	 convertToString(num, str2);
	 printStr(str2);
	
	 
	 str2[0]='9';
	 str2[1]='9';
	 str2[2]='9';
	 str2[3]='9';
	 num=53;
	 convertToString(num, str2);
	 printStr(str2);
	 
	 str2[0]='9';
	 str2[1]='9';
     str2[2]='9';
     str2[3]='9';
	 num=123;
	 convertToString(num, str2);
	 	 printStr(str2);
	 
	 //Testing getRowColumn
	 
	 getRCResult = getRowColumn(0x88, &row, &column);
	 if(getRCResult == -1){
	 			  printChar('F'); //Print F for test failed
				  }
				  else{
				  printChar('P'); //Print P for test passed
				  }
	 printHex(row);//should be 3
	 printHex(column);//should be 3
	 
	 getRCResult = getRowColumn(0x42, &row, &column);
	 	 if(getRCResult == -1){
	 			  printChar('F'); //Print F for test failed
				  }
				  else{
				  printChar('P'); //Print P for test passed
				  }
	 printHex(row);//should be 1
	 printHex(column);//should be 2
	 
	 //Testing getChar
	 

	 printChar(getChar(2,3));
	 printChar(getChar(0, 2));

	 
	 asm("swi");

}

EOF