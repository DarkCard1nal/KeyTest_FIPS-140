# KeyTest_FIPS-140
C++ Module (library) for for testing FIPS-140 cryptography keys.
____
# installation:

`#include "SPBlockSynEncrypt.h"`

# Opportunities:

Class Methods:

`static bool MonobitTest(const std::string key, const size_t min, const size_t max)` __- a method checks the 'key' for monobitality, the test is considered passed (returns true) if the number of identical bits falls within the range ('min', 'max'), the default values are 'min' = 9654, 'max' = 10346.__

`static bool MaxSeriesLengthTest(const std::string key, const size_t max)` __- a method checks the 'key' for the maximum length of a series of bits (a sequence of one (or zero) bits, which is framed on both sides by zero (or one) bits), the test is considered passed (returns true) if the maximum length of such series of bits does not exceed 'max', the default values are 'max' = 36.__

`static bool Poker4Test(const std::string key, const double min, const double max)` __- a method checks the 'key' for the Poker test for blocks of 4 bits (checking whether sequences of 4 bits each appear approximately as many times as expected in a random sequence), the test is considered passed if the output coefficient of the Poker test is within the range ('min', 'max'), the default values are 'min' = 1.03, 'max' = 57.4.__

`static bool MaxNumOfSeriesLengthTest(const std::string key, std::vector<std::pair<size_t, size_t>> arr)` __- a method checks whether the number of zeros and ones in all series of the 'key' sequence is the same as in the random 'arr' sequence. To do this, you need to count the number of all series of ones/zeros of length 1, 2, 3, 4, 5, 6 (and more) and check each number if it falls within the corresponding interval, the test is considered passed if the number in all series of the sequence is within the ranges ['min', 'max'] of the corresponding 'arr'. By default, it is set to 'key' of 2500 characters (which is 20000 bits) 'arr' = {{2267, 2733}, {1079, 1421}, {502, 748}, {223, 402}, {90 , 223}, {90, 223}}. 'arr' has the structure std::vector<std::pair<size_t, size_t>> {{min, max}, {min, max}, ... }.__

> _A static method checks whether the number of zeros and ones in all series of the 'key' sequence is the same as in the random 'arr' sequence. To do this, you need to count the number of all series of ones/zeros of length 1, 2, 3, 4, 5, 6 (and more) and check each number if it falls within the corresponding interval, the test is considered passed if the number in all series of the sequence is within the ranges ['min', 'max'] of the corresponding 'arr'. By default, it is set to 'key' of 2500 characters (which is 20000 bits) 'arr' = {{2267, 2733}, {1079, 1421}, {502, 748}, {223, 402}, {90 , 223}, {90, 223}}. 'arr' has the structure std::vector<std::pair<size_t, size_t>> {{min, max}, {min, max}, ... }, where arr[i] is the length of the series i -1 consisting of the minimum (inclusive) and maximum (inclusive) element, and the last element arr[last] is the length of the sums of the series (last -1) + (last) + (last +1) +. ..., the number of elements in 'arr' must be greater than 0, each element of 'arr' must have a min and max value, otherwise the behavior is unpredictable (may lead to unknown errors)_

| index in 'arr' | Length of the series | Suitable interval (min - max) |
|:---------------:|:---------------:|:---------------:|
| 0 | 1 | 2267 – 2733 |
| 1 | 2 | 1079 – 1421 |
| 2 | 3 | 502 – 748 |
| 3 | 4 | 223 – 402 |
| 4 | 5 | 90 – 223 |
| 5 | 6+ | 90 – 223 |

`static std::string randomKey(const size_t count)` __- a method for generating pseudo-random keys of length (number of characters) 'count', returns the generated string key. This method does not guarantee the randomness of the generated key, use the MaxNumOfSeriesLengthTest(), Poker4Test(), MaxSeriesLengthTest(), MonobitTest() methods to check for randomness.__

#### More information about algorithms and methods in the comments of 'SPBlockSynEncrypt.h'
____
# Examples and tests in examples.cpp

## An example of a program call:
```c++
std::string randomKey = KeyTest_FIPS140::randomKey(2500);

if (KeyTest_FIPS140::MonobitTest(key, 9654, 10346))
	std::cout << "MonobitTest is passed" << std::endl;
else
	std::cout << "MonobitTest has failed" << std::endl;

if (KeyTest_FIPS140::MaxSeriesLengthTest(key))
	std::cout << "MaxSeriesLengthTest is passed" << std::endl;
else
	std::cout << "MaxSeriesLengthTest has failed" << std::endl;

if (KeyTest_FIPS140::Poker4Test(key))
	std::cout << "Poker4Test is passed" << std::endl;
else
	std::cout << "Poker4Test has failed" << std::endl;

if (KeyTest_FIPS140::MaxNumOfSeriesLengthTest(key))
	std::cout << "MaxNumOfSeriesLengthTest is passed" << std::endl;
else
	std::cout << "MaxNumOfSeriesLengthTest has failed" << std::endl;


```
## The result of the program call:
```c++
MonobitTest is passed
MaxSeriesLengthTest is passed
Poker4Test is passed
MaxNumOfSeriesLengthTest is passed
```
