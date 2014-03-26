#define _CRT_SECURE_NO_WARNINGS

#include "rn_base64.h"
#include "Base64.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

const int big_number = 1024 * 1024 * 16;

int main(int, const char*[])
{
	std::vector<char> bytes(big_number);

	// generated a random set of 1 million bytes
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<> uid(0, 255);
	std::generate(bytes.begin(), bytes.end(), [&]()
	{
		return uid(dre);
	});

	// run Rene Nyffenegger base64 encoder over 16 million characters
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(&bytes[0]), bytes.size());
	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "René Nyffenegger encode elapsed time: " << elapsed_seconds.count() << "s\n";


	// run my library encoder over 16 million characters
	start = std::chrono::system_clock::now();
	std::string encoded_string;
	std::for_each(bytes.cbegin(), bytes.cend(), encoder::encode(std::back_inserter(encoded_string)));
	end = std::chrono::system_clock::now();

	elapsed_seconds = end - start;
	std::cout << "Graham Reeds encode elapsed time: " << elapsed_seconds.count() << "s\n";

	// Compare
	std::cout << "The encoded files are " << std::string((encoded_string.compare(encoded) == 0) ? "identical" : "different") << "!\n";


	// now use Rene Nyffenegger base64 decoder to decode those same 16 million characters
	start = std::chrono::system_clock::now();
	std::string decoded = base64_decode(encoded);
	end = std::chrono::system_clock::now();

	elapsed_seconds = end - start;
	std::cout << "René Nyffenegger decode elapsed time: " << elapsed_seconds.count() << "s\n";


	// run my library decoder over 16 million characters
	start = std::chrono::system_clock::now();
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string)));
	end = std::chrono::system_clock::now();

	elapsed_seconds = end - start;
	std::cout << "Graham Reeds decode elapsed time: " << elapsed_seconds.count() << "s\n";

	// Compare
	std::cout << "The decoded files are " << std::string((decoded_string.compare(decoded) == 0) ? "identical" : "different") << "!\n";

	return 0;
}

