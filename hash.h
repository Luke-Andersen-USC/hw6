#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				unsigned long long w[5];
				//unsigned int power = 0;
				
				for(unsigned int i = 0; i < 5; i++)
				{
					w[i] = 0;
				}
				
				std::string copy(k);

				int wWalk = 4;

				while(!copy.empty())
				{
					if(copy.size() <= 6)
					{
						w[wWalk] = baseConversion(copy);
						//std::cout << wWalk << ": " << w[wWalk] << std::endl;
						copy.erase();
					}
					else
					{
						std::string frag(copy.substr(copy.size()-6,6));

						w[wWalk] = baseConversion(frag);

						copy = copy.substr(0,copy.size()-6);
					}
					wWalk--;
				}

				//std::cout << std::endl;
				//std::cout << "GOTHERE!" << std::endl;

				for(int i = 0; i < 5; i++)
				{
					//std::cout << "w[" << i << "]: " << w[i] << std::endl;
				}
				


				HASH_INDEX_T total = 0;
				for(unsigned int i = 0; i < 5; i++)
				{
					//std::cout << "INHERE!" << std::endl;
					//std::cout << "Adding: " << rValues[i] << " * " << w[i] << std:: endl;
					total += rValues[i] * w[i];
				}

				//std::cout << "REACHEND!" << std::endl;
				//std::cout << total << std::endl;

				return total;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				if('a' <= letter && letter <= 'z')
				{
					//std::cout << "letter: " << letter << std::endl;
					//std::cout << (int)letter - 97 << std::endl;
					return (int)letter - 97;
				}
				else if('A' <= letter && letter <= 'Z')
				{
					//std::cout << "letter here?: " << letter << std::endl;
					//std::cout << (int)letter - 65 << std::endl;
					return (int)letter - 65;
				}
				else
				{
					//std::cout << "letter here!: " << letter << std::endl;
					// << (int)letter - 22 << std::endl;
					return (int)letter - 22;
				}
    }

		long long baseConversion(std::string& k) const
		{

			//std::cout << "string k: " << k << std::endl;
			long long total = letterDigitToNumber(k[0]);

			//std::cout << "KBEGIN: " << k[0] << std::endl;

			

			//std::cout << "Total Start: " << total << std::endl;

			for(unsigned int i = 1; i < k.size(); ++i)
			{
				total *= 36;
				total += letterDigitToNumber(k[i]);
			}

			//std::cout << "Total End: " << total << std::endl;
			return total;
			
		}



    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
