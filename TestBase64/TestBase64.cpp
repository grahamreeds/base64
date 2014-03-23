#include "UnitTest++.h"
#include "Base64.h"
#include <algorithm>
#include <functional>
#include <vector>

TEST(CheckEncoderHandlesZeroByteStrings)
{
	const std::string unencoded_string("");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::back_inserter(encoded_string)));
	CHECK_EQUAL(0U, encoded_string.size());
	CHECK_EQUAL("", encoded_string);
}

TEST(CheckEncoderEncodesExactlyOneByteOfBase64)
{
	const std::string unencoded_string("F");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::back_inserter(encoded_string)));
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("Rg==", encoded_string);
}

TEST(CheckEncoderEncodesTwoBytesOfBase64)
{
	const std::string unencoded_string("Fo");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::back_inserter(encoded_string)));
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("Rm8=", encoded_string);
}

TEST(CheckEncoderEncodesThreeBytesOfBase64)
{
	const std::string unencoded_string("Foo");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::back_inserter(encoded_string)));
	CHECK_EQUAL(4U, encoded_string.size());
	CHECK_EQUAL("Rm9v", encoded_string);
}

TEST(CheckEncoderEncodesFourBytesOfBase64)
{
	const std::string unencoded_string("Foob");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::back_inserter(encoded_string)));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("Rm9vYg==", encoded_string);
}

TEST(CheckEncoderEncodesFiveBytesOfBase64)
{
	const std::string unencoded_string("Fooba");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::back_inserter(encoded_string)));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("Rm9vYmE=", encoded_string);
}

TEST(CheckEncoderEncodesSixBytesOfBase64)
{
	const std::string unencoded_string("Foobar");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::back_inserter(encoded_string)));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("Rm9vYmFy", encoded_string);
}
/*
TEST(CheckEncoderCanInsertOneByteOfBase64ToString)
{
	const std::string unencoded_string("F");
	std::string encoded_string("AB");
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode(std::inserter(encoded_string, encoded_string.begin())));
	CHECK_EQUAL(6U, encoded_string.size());
	CHECK_EQUAL("ARg==B", encoded_string);
}
*/
TEST(CheckEncoderEncodesSixBytesWithAlternateAlphabet)
{
	const std::string unencoded_string("Foobar");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base64url>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("Rm9vYmFy", encoded_string);
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

TEST(CheckBase32EncoderEncodesThreeBytes)
{
	const std::string unencoded_string("Foo");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base32>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("IZXW6===", encoded_string);
}

TEST(CheckBase32EncoderEncodesFourBytes)
{
	const std::string unencoded_string("Foob");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base32>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("IZXW6YQ=", encoded_string);
}

TEST(CheckBase32EncoderEncodesFiveBytes)
{
	const std::string unencoded_string("Fooba");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base32>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("IZXW6YTB", encoded_string);
}

TEST(CheckBase32EncoderEncodesSixBytes)
{
	const std::string unencoded_string("Foobar");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base32>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(16U, encoded_string.size());
	CHECK_EQUAL("IZXW6YTBOI======", encoded_string);
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

TEST(CheckBase16EncoderEncodesThreeBytes)
{
	const std::string unencoded_string("Foo");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base16>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(6U, encoded_string.size());
	CHECK_EQUAL("466F6F", encoded_string);
}

TEST(CheckBase16EncoderEncodesFourBytes)
{
	const std::string unencoded_string("Foob");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base16>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(8U, encoded_string.size());
	CHECK_EQUAL("466F6F62", encoded_string);
}

TEST(CheckBase16EncoderEncodesFiveBytes)
{
	const std::string unencoded_string("Fooba");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base16>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(10U, encoded_string.size());
	CHECK_EQUAL("466F6F6261", encoded_string);
}

TEST(CheckBase16EncoderEncodesSixBytes)
{
	const std::string unencoded_string("Foobar");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder::encode<base16>(std::back_inserter(encoded_string)));
	CHECK_EQUAL(12U, encoded_string.size());
	CHECK_EQUAL("466F6F626172", encoded_string);
}

TEST(CheckDecoderThrowsOnInvalidAlphabetCharacters)
{
	const std::string encoded_string(",.");
	std::string decoded_string;
	CHECK_THROW(std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string))), std::runtime_error);
}

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

TEST(CheckDecoderDecodesExactlyOneByteOfBase64)
{
	const std::string encoded_string("Rg==");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string)));
	CHECK_EQUAL(1U, decoded_string.size());
	CHECK_EQUAL("F", decoded_string);
}

TEST(CheckDecoderDecodesTwoBytesOfBase64)
{
	const std::string encoded_string("Rm8=");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string)));
	CHECK_EQUAL(2U, decoded_string.size());
	CHECK_EQUAL("Fo", decoded_string);
}

TEST(CheckDecoderDecodesThreeBytesOfBase64)
{
	const std::string encoded_string("Rm9v");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string)));
	CHECK_EQUAL(3U, decoded_string.size());
	CHECK_EQUAL("Foo", decoded_string);
}

TEST(CheckDecoderDecodesFourBytesOfBase64)
{
	const std::string encoded_string("Rm9vYg==");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string)));
	CHECK_EQUAL(4U, decoded_string.size());
	CHECK_EQUAL("Foob", decoded_string);
}

TEST(CheckDecoderDecodesFiveBytesOfBase64)
{
	const std::string encoded_string("Rm9vYmE=");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string)));
	CHECK_EQUAL(5U, decoded_string.size());
	CHECK_EQUAL("Fooba", decoded_string);
}

TEST(CheckDecoderDecodesSixBytesOfBase64)
{
	const std::string encoded_string("Rm9vYmFy");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode(std::back_inserter(decoded_string)));
	CHECK_EQUAL(6U, decoded_string.size());
	CHECK_EQUAL("Foobar", decoded_string);
}

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

TEST(CheckDecoderDecodesExactlyOneByteOfBase16)
{
	const std::string encoded_string("46");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode<base16>(std::back_inserter(decoded_string)));
	CHECK_EQUAL(1U, decoded_string.size());
	CHECK_EQUAL("F", decoded_string);
}

TEST(CheckDecoderCanDecodesTwoBytesOfBase16)
{
	const std::string encoded_string("466F");
	std::string decoded_string;
	std::for_each(encoded_string.cbegin(), encoded_string.cend(), encoder::decode<base16>(std::back_inserter(decoded_string)));
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