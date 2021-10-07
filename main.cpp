#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

void reverseString(std::string& str)
{
  for (int i = 0; i < str.length() / 2; i++)
  {
    std::swap(str[i], str[str.length() - i - 1]);
  }
}

int GetDigitsInInteger(int num)
{
  int num_ = num;
  int i = 0;
  while (num_ != 0)
  {
    num_ = num_ / 10;
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
      else
      {
	parsedHex.push_back(std::stoi(&c)); //if it does not match any hex digits, it will just convert it to int (std::stoi) and push it into the parsedHex vector
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
}

int main()
{ 
  int choice = 0;
  printf("1. Binary to Decimal\n");
  printf("2. Decimal to Binary\n");
  printf("3. Hexadecimal to Decimal\n");
  printf("4. Decimal to Hexadecimal\n");
  printf(": ");
  std::cin >> choice;
  
  if (choice == 1)
  {
    int firstMethodOutput = 0;
    int secondMethodOutput = 0;
    int binaryNum = 0;
    
    printf("Enter the binary number: ");
    std::cin >> binaryNum;
  
    Conversion::BinaryToDecimal(binaryNum, firstMethodOutput);
    Conversion::BinaryToDecimal2(binaryNum, secondMethodOutput);

    printf("First binary method: Decimal number = %d\n", firstMethodOutput);
    printf("Second binary method: Decimal Number = %d\n", secondMethodOutput);
  }

  else if (choice == 2)
  {
    int decimalNum = 0;
    std::string output = "";
    
    printf("Enter the decimal number: ");
    std::cin >> decimalNum;
    Conversion::DecimalToBinary(decimalNum, output);
    std::cout << "Binary equivalent: " << output << std::endl;
  }

  else if (choice == 3)
  {
    int output = 0;
    std::string hex = "";
    printf("Enter hex number: ");
    std::cin >> hex;
    Conversion::HexToDecimal(hex, output);
    printf("The decimal equivalent is: %i\n", output);
    
  }

  else
  {
    int decimal = 0;
    std::string output = "";
    printf("Enter a decimal number: ");
    std::cin >> decimal;
    Conversion::DecimalToHex(decimal, output);
    std::cout << "The hex equivalent is: " << output << std::endl;
  }
  
  return 0;
}
