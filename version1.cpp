#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

/*
  Version1 includes:
  - Binary to Decimal
  - Decimal to Binary
 */

void reverseString(std::string& str)
{
  for (int i = 0; i < str.length() / 2; i++)
  {
    std::swap(str[i], str[str.length() - i - 1]); //Swaps every character with each other, so if the string is abcde, then it first waps a with e, then b with d, etc.
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
}

int main()
{ 
  int choice = 0;
  printf("1. Binary to Decimal\n");
  printf("2. Decimal to Binary\n");
  printf("3. Hexadecimal to Decimal\n");
  printf("4. Decimal to Hexadecimal\n");
  printf("5. Hexadecimal to Binary\n");
  printf("6. Binary to Hexadecimal\n");
  printf(": ");
  std::cin >> choice;
  
  if (choice == 1)
  {
    int firstMethodOutput = 0; //Store the result of BinaryToDecimal
    int secondMethodOutput = 0; //Store the result of BinaryToDecimal2
    int binaryNum = 0; //Binary number that the user will enter
    
    printf("Enter the binary number: ");
    std::cin >> binaryNum; //Ask for user input into the variable binaryNum
  
    Conversion::BinaryToDecimal(binaryNum, firstMethodOutput);
    Conversion::BinaryToDecimal2(binaryNum, secondMethodOutput);

    printf("First binary method: Decimal number = %d\n", firstMethodOutput);
    printf("Second binary method: Decimal Number = %d\n", secondMethodOutput);
  }

  else if (choice == 2)
  {
    int decimalNum = 0; //Store the decimal number to convert
    std::string output = ""; //Store the binary output, Can later convert it to int using std::stoi()
    
    printf("Enter the decimal number: ");
    std::cin >> decimalNum;
    Conversion::DecimalToBinary(decimalNum, output);
    std::cout << "Binary equivalent: " << output << std::endl;
  }
  
  return 0;
}
