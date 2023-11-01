#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>
#include "KeyTest_FIPS140.h"

//A function prints the string 'key' in binary format
void printBinaryString(std::string );
//A function prints the string 'key' in hex format
void printHexString(std::string );
//A function checks the 'key' of 2500 characters (which is 20000 bits) using the MaxNumOfSeriesLengthTest(), 
//Poker4Test(), MaxSeriesLengthTest(), MonobitTest() methods with the default arguments (these are the arguments for a 
//key of 2500 characters (which is 20000 bits)), returns true if all tests are successfully passed
bool checkAll2500(std::string );

int main()
{
	std::cout << "Starting the example and testing program!" << std::endl << std::endl;

	//All keys are 2500 characters in length (which is 20000 bits)
	
	// a key consists of the repetition of the characters 'a', true only MaxSeriesLengthTest().
	std::string badKey = std::string(2500, 'a');
	
	// a random key.
	std::string randomKey = KeyTest_FIPS140::randomKey(2500);
	
	std::cout << "Bad key(" << badKey.length() << "): " << std::endl;
	if (checkAll2500(badKey))
		std::cout << "Test Bad key is passed" << std::endl;
	else
		std::cout << "Test Bad key has failed" << std::endl;

	std::cout << std::endl <<  "Random key(" << badKey.length() << "): " << std::endl;
	if (checkAll2500(randomKey))
		std::cout << "Test Random key is passed" << std::endl;
	else
		std::cout << "Test Random key has failed" << std::endl;

	std::cout << std::endl << "End of the example and test program!" << std::endl;
}

//A function prints the string 'key' in binary format
void printBinaryString(std::string key)
{
	for (char c : key)
		std::cout << std::bitset<8>(c);

	std::cout << std::endl;
}

//A function prints the string 'key' in hex format
void printHexString(std::string key)
{
	for (char c : key)
		std::cout << std::hex << static_cast<int>(c);

	std::cout << std::endl;
}

//A function checks the 'key' of 2500 characters (which is 20000 bits) using the MaxNumOfSeriesLengthTest(), 
//Poker4Test(), MaxSeriesLengthTest(), MonobitTest() methods with the default arguments (these are the arguments for a 
//key of 2500 characters (which is 20000 bits)), returns true if all tests are successfully passed
bool checkAll2500(std::string key)
{
	bool flag = true;

	/* //Uncomment this to display the key in binary and hex format on the screen
	std::cout << "Key: " << key << std::endl;

	std::cout << "Key in binary: ";
		printBinaryString(key);

	std::cout << "Key in hex: ";
		printHexString(key);
	*/

	std::cout << "Start of all tests for this key!" << std::endl << std::endl;

	if (KeyTest_FIPS140::MonobitTest(key))
		std::cout << "MonobitTest is passed" << std::endl;
	else
	{
		std::cout << "MonobitTest has failed" << std::endl;
		flag = false;
	}

	if (KeyTest_FIPS140::MaxSeriesLengthTest(key))
		std::cout << "MaxSeriesLengthTest is passed" << std::endl;
	else
	{
		std::cout << "MaxSeriesLengthTest has failed" << std::endl;
		flag = false;
	}

	if (KeyTest_FIPS140::Poker4Test(key))
		std::cout << "Poker4Test is passed" << std::endl;
	else
	{
		std::cout << "Poker4Test has failed" << std::endl;
		flag = false;
	}

	if (KeyTest_FIPS140::MaxNumOfSeriesLengthTest(key))
		std::cout << "MaxNumOfSeriesLengthTest is passed" << std::endl;
	else
	{
		std::cout << "MaxNumOfSeriesLengthTest has failed" << std::endl;
		flag = false;
	}

	std::cout << std::endl << "Testing is finished for this key!" << std::endl;
	return flag;
}
