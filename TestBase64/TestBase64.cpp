#include "UnitTest++.h"
#include "Base64.h"
#include <algorithm>
#include <functional>

TEST(CheckEncoderHandlesZeroByteString)
{
	const std::string unencoded_string("");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder<std::string>(encoded_string));
	CHECK_EQUAL(0U, encoded_string.size());
	CHECK_EQUAL("", encoded_string);
}

TEST(CheckEncoderEncodesExactlyOneByte)
{
	const std::string unencoded_string("F");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder<std::string>(encoded_string));
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("Rg==", encoded_string);
}

TEST(CheckEncoderEncodesTwoBytes)
{
	const std::string unencoded_string("Fo");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder<std::string>(encoded_string));
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("Rm8=", encoded_string);
}

TEST(CheckEncoderEncodesThreeBytes)
{
	const std::string unencoded_string("Foo");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder<std::string>(encoded_string));
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("Rm9v", encoded_string);
}

TEST(CheckEncoderEncodesFourBytes)
{
	const std::string unencoded_string("Foob");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder<std::string>(encoded_string));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("Rm9vYg==", encoded_string);
}

TEST(CheckEncoderEncodesFourBytesWithAlternateAlphabet)
{
	const std::string unencoded_string("Foob");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder<std::string, base64url>(encoded_string));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("Rm9vYg==", encoded_string);
}

TEST(CheckBase32EncoderEncodesExactlyOneByte)
{
	const std::string unencoded_string("F");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder<std::string, base32>(encoded_string));
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("IY======", encoded_string);
}

TEST(CheckBase32EncoderEncodesTwoBytes)
{
	const std::string unencoded_string("Fo");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder<std::string, base32>(encoded_string));
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("IZXQ====", encoded_string);
}
