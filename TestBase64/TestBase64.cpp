#include "UnitTest++.h"
#include "Base64.h"
#include <algorithm>
#include <functional>

TEST(CheckEncoderHandlesZeroByteString)
{
	const std::string unencoded_string("");
	std::string encoded_string;
	{
		encoder<std::string> enc(encoded_string);
		std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), std::ref(enc));
	}
	CHECK_EQUAL(0U, encoded_string.size());
	CHECK_EQUAL("", encoded_string);
}

TEST(CheckEncoderEncodesExactlyOneByte)
{
	const std::string unencoded_string("F");
	std::string encoded_string;
	{
		encoder<std::string> enc(encoded_string);
		std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), std::ref(enc));
	}
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("Rg==", encoded_string);
}

TEST(CheckEncoderEncodesTwoBytes)
{
	const std::string unencoded_string("Fo");
	std::string encoded_string;
	{
		encoder<std::string> enc(encoded_string);
		std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), std::ref(enc));
	}
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("Rm8=", encoded_string);
}

TEST(CheckEncoderEncodesThreeBytes)
{
	const std::string unencoded_string("Foo");
	std::string encoded_string;
	{
		encoder<std::string> enc(encoded_string);
		std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), std::ref(enc));
	}
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("Rm9v", encoded_string);
}

TEST(CheckEncoderEncodesFourBytes)
{
	const std::string unencoded_string("Foob");
	std::string encoded_string;
	{
		encoder<std::string> enc(encoded_string);
		std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), std::ref(enc));
	}
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("Rm9vYg==", encoded_string);
}

/*
BASE32("") = ""

BASE32("f") = "MY======"

BASE32("fo") = "MZXQ===="
*/

/*
struct test_enc
{
	test_enc(std::string& ref) : ref_(ref) {
		ref_.push_back('C');
	}
	test_enc(const test_enc& other) : ref_(other.ref_) {
		ref_.push_back('U');
	}
	~test_enc() {
		ref_.push_back('D');
	}
	void operator()(const char byte) {
		ref_.push_back('O');
	}
	test_enc& operator=(const test_enc&) = delete;
	std::string& ref_;
};

TEST(CheckTestEncoderEncodesExactlyOneByte)
{
	const std::string unencoded_string("M");
	std::string encoded_string;
	{
		test_enc test_str(encoded_string);
		std::for_each(unencoded_string.begin(), unencoded_string.end(), std::ref(test_str));
	}
//	std::for_each(unencoded_string.begin(), unencoded_string.end(), std::ref(test_enc(encoded_string)));
//	std::for_each(unencoded_string.begin(), unencoded_string.end(), test_enc(encoded_string));
	CHECK_EQUAL(3U, encoded_string.size());
	CHECK_EQUAL("COD", encoded_string);
}
*/