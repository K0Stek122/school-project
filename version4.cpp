#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <ncurses.h>
#include <sstream>

#include "ascii.h"
/*
  This version adds all the user-friendly things that were explained in version3.
 */

void reverseString(std::string& str)
{
  for (int i = 0; i < str.length() / 2; i++)
  {
    std::swap(str[i], str[str.length() - i - 1]);
  }
}

int GetDigitsInInteger(int num)
{
  int i = 0;
  while (num != 0)
  {
    num = num / 10;
    i++;
  }
  return i;
}

void upper(std::string& str)
{
  std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

namespace Conversion
{
  void BinaryToDecimal(int binaryNum, int& decimalNum)
  {
    /* initializing all the variables */
    int remainder = 0;
    int i = 1; //This variable determines what value we multiply the remainder by
    /* End of variable initialization */
  
    while (binaryNum != 0) //Goes through the binary numbers one by one, until binary is == 0
      {
	remainder = binaryNum % 10; //Gets the ramainder of the binary number, it is needed so that then we can multiply it by the overall sum
	decimalNum = decimalNum + (remainder * i);  //adds the (remainder * i) to the decimal sum, it will do that until we run out of numbers
	i = i * 2; //doubles i, This is a different way of calculating binary numbers, it is explained in full below
	binaryNum = binaryNum / 10; //divides it by ten so that one unit is gone from the number, and the next one is calculated, this is done until binary number is equal to 0
      }
    /*
      The method that is used here:
      let's say you want to convert 1100110 to a decimal, so we do the following:
      (0 * 2) + 0 = 0
      (0 * 2) + 1 = 1
      (1 * 2) + 1 = 3
      (3 * 2) + 0 = 6
      (6 * 2) + 0 = 12
      (12 * 2) + 1 = 25
      (25 * 2) + 1 = 51
      so we go through each bit, add it to our sum (which is equal to sum * 2) and that is our answer !
      it is a different way than it is normally though, but i consider this way more useful when actually programming.
      Advantages of this method is that it can convert any binary number, while the function CalculateToBinary2 can only convert numbers that are up to 8 bits.
    */
  }

  void BinaryToDecimal2(int binaryNum, int& decimalNum)
  {
    //This method however uses the power of 2 timetable to calculate the binary number
    int sum = 0; //The decimal answer
    int digits = GetDigitsInInteger(binaryNum); //Get how many digits there is in the binary number

    std::string binaryStr = std::to_string(binaryNum); //convert the binary to a string, in order to iterate over it
    for (int i = 0; i < digits; i++)
      {
	decimalNum += (binaryStr[i] - '0') * (pow(2, (digits -i) - 1)); //the binary digits are taken in order, from the most significant bit to least significant bit, each one is multiplied by 2 to the power of the calculated number. It is then added to the final answer
      }

    /*
      The method used here is more common:
      the first bit is taken, and it is multiplied by the appropiate power of 2. for example:
      firstBit * 2**0
      secondBit * 2**1
      thirdBit * 2**2
      etc...
      all of this is added together and that is our answer !
    */
  }

  void DecimalToBinary(int decimalNum, std::string& binaryStr)
  {
    while (decimalNum != 0) //While decimalNum is not equal to 0, we divide it by 2 and store the remainder, remainders read backwards is our binary number.
      {
	binaryStr += std::to_string(decimalNum % 2);
	decimalNum = ceil(decimalNum / 2);
      }

    reverseString(binaryStr);
  }

  void HexToDecimal(std::string hexNum, int& output)
  {
    upper(hexNum); //we make the hex number uppercase, in order for it to match our hex numbers
    std::vector<int> parsedHex; //We will store our decimal equivalent in this array, so for example, if we're converting 12C, then this array will store: [1, 2, 12], because C == 12 in decimal
    for (const char c : hexNum) //we're iterating over characters in the hex number, in order to convert them into decimal equivalent
    {
      //we check with if statements what number the digit is
      if (c == 'A')
	parsedHex.push_back(10);
      else if (c == 'B')
	parsedHex.push_back(11);
      else if (c == 'C')
	parsedHex.push_back(12);
      else if (c == 'D')
	parsedHex.push_back(13);
      else if (c == 'E')
	parsedHex.push_back(14);
      else if (c == 'F')
	parsedHex.push_back(15);
      else if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '0')
      {
	std::string s;
	std::stringstream ss;
	ss << c;
	ss >> s;
	parsedHex.push_back(std::stoi(s)); //if it does not match any hex digits, it will just convert it to int (std::stoi) and push it into the parsedHex vector
      }
      
    }

    std::reverse(parsedHex.begin(), parsedHex.end()); //reverses the array, when converting hex to decimal, we go from right to left, therefore we reverse the array

    for (int i = 0; i < parsedHex.size(); i++)
    {
      output += parsedHex[i] * (pow(16, i)); //this is the calculation done in order to convert it to decimal, it is explained in detail below
    }
      /*
    So this method does the following thing:
    if we want to convert 12C to decimal,
    it takes the digits one by one and does that calculation:
    12 * (16**0) = 12 <- 12 because C is equivalent to 12 in decimal
    2 * (16**1) = 32
    1 * (16**2) = 256
    12 + 32 + 256 = 300
    therefore, 0x12C == 300
   */
  }

  void DecimalToHex(int decimal, std::string& output)
  {
    std::vector<int> remainders; //we will store all the remainders here

    while (decimal != 0) //until decimal == 0, we divide it by 16 and get the remainder and store it in the array
    {
      remainders.push_back(decimal % 16);
      decimal = ceil(decimal / 16);
    }

    std::reverse(remainders.begin(), remainders.end()); //we reverse the string, same as with converting Hex to Decimal, we read the number backwards
    for (int i : remainders) //iterate over the remainders, and for each one add the hex equivalent of a number, so if remainder is 12, it will add 'C' to the output
    {
      if (i < 10) //If the number is less than 10, we don't need to convert it to a character
      {
	output += std::to_string(i);
      }
      else //however if it is, then we add the character
      {
	if (i == 10)
	  output += 'A';
	else if (i == 11)
	  output += 'B';
	else if (i == 12)
	  output += 'C';
	else if (i == 13)
	  output += 'D';
	else if (i == 14)
	  output += 'E';
	else if (i == 15)
	  output += 'F';
      }
    }
  }

  void HexToBinary(std::string hex, std::string& output)
  {
    std::string currentBinary = ""; //This will store the temporary binary number that we convert
    int currentDecimal = 0; //This will store the temporary decimal number that we convert
    std::vector<char> hexNums(hex.begin(), hex.end()); //we split the hex number into an array of characters
    for (int i = 0; i < hexNums.size(); i++) //we iterate over all the characters
    {
      /*
	For each character we're converting it to decimal, then to binary, and we add it to the output, repeat until we run out of characters
       */
      Conversion::HexToDecimal(std::string(1, hexNums[i]), currentDecimal);
      Conversion::DecimalToBinary(currentDecimal, currentBinary);
      output += currentBinary;
      currentBinary = "";
      currentDecimal = 0;
    }
  }

  void BinaryToHex(std::string binary, std::string& output)
  {
    int tempDecimal = 0; //This will store the temporary decimal number that we convert
    std::string tempHex = ""; //This will store the temporary hex number that we convert
    std::vector<std::string> byte;
    // We split the binary number into array of four binary numbers
    for (size_t i = 0; i < binary.size(); i += 4)
    {
      byte.push_back(binary.substr(i, 4));
    }

    //we iterate of the arrays of fours
    for (short int j = 0; j < byte.size(); j++)
    {
      /*
	For each group of 4 we're converting them to decimal, then to hex and we add this to the output
      */
      Conversion::BinaryToDecimal(std::stoi(byte[j]), tempDecimal);
      Conversion::DecimalToHex(tempDecimal, tempHex);
      output += tempHex;
      tempDecimal = 0;
      tempHex = "";
    }
  }
}

int main()
{
  ascii::init_scr(true);

  int pointerY = 1;
  
  std::string decimal = "";
  std::string binary = "";
  std::string hex = "";
  
  while (true)
  {
    char c = getch();
    if (c == 66 && pointerY < 3) //DOWN
    {
      pointerY++;
    }
    if (c == 65 && pointerY > 1) //UP
    {
      pointerY--;
    }
    if (c == 10) //ENTER
    {
      decimal = "";
      hex = "";
      binary = "";
      while (true)
      {
	char c = getch();
	switch(pointerY)
	{
	case 1:
	  decimal += c;
	  break;
	case 2:
	  if (c == '1' || c == '0')
	    binary += c;
	  break;
	case 3:
	  hex += c;
	  break;
	}
	refresh();
	if (c == 10)
	  break;
      }
      
      if (pointerY == 1) //DECIMAL INPUT
      {
	Conversion::DecimalToBinary(std::stoi(decimal), binary);
	Conversion::DecimalToHex(std::stoi(decimal), hex);
      }
      else if (pointerY == 2) //BINARY INPUT
      {
	int tempDecimal = 0;
	Conversion::BinaryToDecimal(std::stoi(binary), tempDecimal);
	decimal = std::to_string(tempDecimal);
	Conversion::BinaryToHex(binary, hex);
      }
      else if (pointerY == 3) //HEX INPUT
      {
	int tempDecimal = 0;
	Conversion::HexToDecimal(hex, tempDecimal);
	decimal = std::to_string(tempDecimal);
	Conversion::HexToBinary(hex, binary);
      }
      
    }
    
    WINDOW* win = ascii::print_window(5, 50, 1, 1);
    ascii::print("Decimal: ", 2, 1, win);
    ascii::print(decimal.c_str(), 10, 1, win);
    
    ascii::print("Binary: ", 2, 2, win);
    ascii::print(binary.c_str(), 10, 2, win);
    
    ascii::print("Hex: ", 2, 3, win);
    ascii::print(hex.c_str(), 10, 3, win);
    
    ascii::print(">", 1, pointerY, win);

    refresh();
    wrefresh(win);
  }

  ascii::end_scr();
  
  return 0;
}
