#include "UnitTest++.h"
#include "Base64.h"
#include <algorithm>

TEST(CheckEncoderHandlesZeroByteString)
{
	const std::string unencoded_string("");
	std::string encoded_string;
	std::for_each(unencoded_string.cbegin(), unencoded_string.cend(), encoder(encoded_string));
	CHECK_EQUAL(0U, encoded_string.size());
	CHECK_EQUAL("", encoded_string);
}
