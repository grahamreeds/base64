#include "UnitTest++.h"
#include "Base64.h"
#include <algorithm>
#include <functional>
#include <vector>
//*
TEST(CheckEncoderHandlesZeroByteString)
{
	const std::string unencoded_string("");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::back_inserter(encoded_string)));
	CHECK_EQUAL(0U, encoded_string.size());
	CHECK_EQUAL("", encoded_string);
}

TEST(CheckEncoderEncodesExactlyOneByte)
{
	const std::string unencoded_string("F");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::back_inserter(encoded_string)));
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("Rg==", encoded_string);
}

TEST(CheckEncoderEncodesTwoBytes)
{
	const std::string unencoded_string("Fo");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::back_inserter(encoded_string)));
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("Rm8=", encoded_string);
}

TEST(CheckEncoderEncodesThreeBytes)
{
	const std::string unencoded_string("Foo");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::back_inserter(encoded_string)));
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("Rm9v", encoded_string);
}

TEST(CheckEncoderEncodesFourBytes)
{
	const std::string unencoded_string("Foob");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::back_inserter(encoded_string)));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("Rm9vYg==", encoded_string);
}

TEST(CheckEncoderEncodesFourBytesWithAlternateAlphabet)
{
	const std::string unencoded_string("Foob");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base64url>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("Rm9vYg==", encoded_string);
}

TEST(CheckBase32EncoderEncodesExactlyOneByte)
{
	const std::string unencoded_string("F");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base32>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("IY======", encoded_string);
}

TEST(CheckBase32EncoderEncodesTwoBytes)
{
	const std::string unencoded_string("Fo");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base32>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("IZXQ====", encoded_string);
}

TEST(CheckBase16EncoderEncodesExactlyOneByte)
{
	const std::string unencoded_string("F");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base16>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(2U, encoded_string.size());
	CHECK_EQUAL("46", encoded_string);
}

TEST(CheckBase16EncoderEncodesTwoBytes)
{
	const std::string unencoded_string("Fo");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base16>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("466F", encoded_string);
}


TEST(CheckDecoderThrowsOnInvalidAlphabetCharacters)
{
	const std::string encoded_string(",.");
	std::string decoded_string;
	CHECK_THROW(std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string))), std::runtime_error);
}
//*/
TEST(CheckDecoderCanBeForcedToIgnoreInvalidAlphabetCharacters)
{
	const std::string encoded_string(",.");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode<base64, invalid_data_allow<base64>>(std::back_inserter(decoded_string)));
	CHECK_EQUAL(0U, decoded_string.size());
	CHECK_EQUAL("", decoded_string);
}

TEST(CheckDecoderHandlesZeroByteString)
{
	const std::string encoded_string("");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string)));
	CHECK_EQUAL(0U, decoded_string.size());
	CHECK_EQUAL("", decoded_string);
}

TEST(CheckDecoderDecodesExactlyOneByte)
{
	const std::string encoded_string("Rg==");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string)));
	CHECK_EQUAL(1U, decoded_string.size());
	CHECK_EQUAL("F", decoded_string);
}

TEST(CheckDecoderDecodesTwoBytes)
{
	const std::string encoded_string("Rm8=");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string)));
	CHECK_EQUAL(2U, decoded_string.size());
	CHECK_EQUAL("Fo", decoded_string);
}

TEST(CheckDecoderDecodesThreeBytes)
{
	const std::string encoded_string("Rm9v");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string)));
	CHECK_EQUAL(3U, decoded_string.size());
	CHECK_EQUAL("Foo", decoded_string);
}

TEST(CheckDecoderDecodesFourBytes)
{
	const std::string encoded_string("Rm9vYg==");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string)));
	CHECK_EQUAL(4U, decoded_string.size());
	CHECK_EQUAL("Foob", decoded_string);
}
//*/
TEST(CheckDecoderDecodesExactlyOneByteOfBase32)
{
	const std::string encoded_string("IY======");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode<base32>(std::back_inserter(decoded_string)));
	CHECK_EQUAL(1U, decoded_string.size());
	CHECK_EQUAL("F", decoded_string);
}

TEST(CheckDecoderCanDecodesTwoBytesOfBase32)
{
	const std::string encoded_string("IZXQ====");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode<base32>(std::back_inserter(decoded_string)));
	CHECK_EQUAL(2U, decoded_string.size());
	CHECK_EQUAL("Fo", decoded_string);
}
/*
TEST(CheckDecoderFailsWhenPresentedWithPaddingCharactersTooSoon)
{
const std::string encoded_string("R===");
std::string decoded_string;
std::for_each(encoded_string.cbegin(), encoded_string.cend(), decoder<std::string, base64, invalid_data_allow<base64>>(decoded_string));
CHECK_EQUAL(0U, decoded_string.size());
CHECK_EQUAL("", decoded_string);
}
*/