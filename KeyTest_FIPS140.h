#pragma once
#include <string>
#include <vector>
#include <bitset>
#include <utility>
#include <random>

class KeyTest_FIPS140
{
public:
	//A static method checks the 'key' for monobitality, the test is considered passed (returns true) if the number of 
	//identical bits falls within the range ('min', 'max'), the default values are 'min' = 9654, 'max' = 10346.
	static bool MonobitTest(const std::string key, const size_t min = 9654, const size_t max = 10346)
	{
		size_t count = 0;

		for (char c : key)
		{
			std::bitset<8> bits(c);
			for (char i = 0; i < 8; i++)
			{
				if (bits[i])
					count++;
			}
		}
		
		if (count > min && count < max)
			return true;

		return false;
	}

	//A static method checks the 'key' for the maximum length of a series of bits (a sequence of one (or zero) bits, 
	//which is framed on both sides by zero (or one) bits), the test is considered passed (returns true) if the 
	//maximum length of such series of bits does not exceed 'max', the default values are 'max' = 36.
	static bool MaxSeriesLengthTest(const std::string key, const size_t max = 36)
	{
		size_t count = 0;
		bool series = 0;

		for (char c : key)
		{
			std::bitset<8> bits(c);
			for (char i = 0; i < 8; i++)
			{
				if (bits[i] == series)
					count++;
				else
				{
					if (count > max)
						return false;

					count = 1;
					series = !series;
				}
			}
		}

		return true;
	}

	//A static method checks the 'key' for the Poker test for blocks of 4 bits (checking whether sequences of 4 bits each 
	//appear approximately as many times as expected in a random sequence), the test is considered passed if the output 
	//coefficient of the Poker test is within the range ('min', 'max'), the default values are 'min' = 1.03, 'max' = 57.4.
	static bool Poker4Test(const std::string key, const double min = 1.03, const double max = 57.4)
	{
		size_t counts[16] = {0};
		size_t sum = 0;
		double result;
		char blocks[2];
		char j;
		bool i;

		for (char c : key)
		{
			blocks[0] = (c >> 4) & 0xF;
			blocks[1] = c & 0xF;
			
			i = 0;
			do
			{
				for (j = 0; j < 16; j++)
				{
					if (blocks[i] == j)
						counts[j]++;
				}

				i = !i;
			} while (i);
		}

		for (j = 0; j < 16; j++)
			sum += counts[j] * counts[j];

		result = (double) (16 * sum) / (key.length() * 2) - (key.length() * 2);
		
		if (result > min && result < max)
			return true;

		return false;
	}

	//A static method checks whether the number of zeros and ones in all series of the 'key' sequence is the same as in 
	//the random 'arr' sequence. To do this, you need to count the number of all series of ones/zeros of 
	//length 1, 2, 3, 4, 5, 6 (and more) and check each number if it falls within the corresponding interval, the test is 
	//considered passed if the number in all series of the sequence is within the ranges ['min', 'max'] of the corresponding 
	//'arr'. By default, it is set to 'key' of 2500 characters (which is 20000 bits) 'arr' = {{2267, 2733}, {1079, 1421}, 
	//{502, 748}, {223, 402}, {90 , 223}, {90, 223}}. 'arr' has the structure std::vector<std::pair<size_t, size_t>> 
	//{{min, max}, {min, max}, ... }, where arr[i] is the length of the series i -1 consisting of the minimum (inclusive) 
	//and maximum (inclusive) element, and the last element arr[last] is the length of the sums of the series 
	//(last -1) + (last) + (last +1) +. ..., the number of elements in 'arr' must be greater than 0, each element of 'arr' 
	//must have a min and max value, otherwise the behavior is unpredictable (may lead to unknown errors).
	static bool MaxNumOfSeriesLengthTest(const std::string key, std::vector<std::pair<size_t, size_t>> arr =
			{{2267, 2733}, {1079, 1421}, {502, 748}, {223, 402}, {90 , 223}, {90, 223}})
	{
		std::vector<size_t> counts0(arr.size(), 0);
		std::vector<size_t> counts1(arr.size(), 0);
		size_t count = 0;
		bool series = 0;

		for (char c : key)
		{
			std::bitset<8> bits(c);
			for (char i = 0; i < 8; i++)
			{
				if (bits[i] == series)
					count++;
				else
				{
					if (count > 0)
					{
						if (count < arr.size())
						{
							if (series)
								counts1[count - 1]++;
							else
								counts0[count - 1]++;
						}
						else
						{
							if (series)
								counts1.back()++;
							else
								counts0.back()++;
						}
					}

					count = 1;
					series = !series;
				}
			}
		}

		for (size_t i = 0; i < arr.size(); i++)
		{
			if (counts0[i] < std::min(arr[i].second, arr[i].first) || counts0[i] > std::max(arr[i].second, arr[i].first))
				return false;
		}

		for (size_t i = 0; i < arr.size(); i++)
		{
			if (counts1[i] < std::min(arr[i].second, arr[i].first) || counts1[i] > std::max(arr[i].second, arr[i].first))
				return false;
		}

		return true;
	}

	//A static method for generating pseudo-random keys of length (number of characters) 'count', returns the generated string 
	//key. This method does not guarantee the randomness of the generated key, use the MaxNumOfSeriesLengthTest(), 
	//Poker4Test(), MaxSeriesLengthTest(), MonobitTest() methods to check for randomness.
	static std::string randomKey(const size_t count)
	{
		std::string key(count, 0);
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(1, 255);

		for (size_t i = 0; i < count; i++)
		{
			key[i] = static_cast<char>(dist(mt));
		}

		return key;
	}

};

