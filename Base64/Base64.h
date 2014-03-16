#pragma once
#include <string>

namespace
{
	struct base64
	{
		const std::string alphabet_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		const int shift_ = 6;
		const int mask_ = 0x3f;
		const int mod_ = 4;
		base64& operator=(const base64&) = delete;
	};

	struct base64url
	{
		const std::string alphabet_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
		const int shift_ = 6;
		const int mask_ = 0x3f;
		const int mod_ = 4;
		base64url& operator=(const base64url&) = delete;
	};

	struct base32
	{
		const std::string base32::alphabet_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
		const int shift_ = 5;
		const int mask_ = 0x1f;
		const int mod_ = 8;
		base32& operator=(const base32&) = delete;
	};

	const char pad = '=';


	template< class Container = std::string, typename Alphabet = base64 >
	class encoder : Alphabet
	{
	public:
		encoder(Container& c) 
			: ref_(c), bits_(0), bits_remaining_(0) { }
		~encoder() 
		{
			if (bits_remaining_ > 0)
			{
				bits_ = (bits_ << 8); // | 0x00;
				bits_remaining_ += 8;

				const int shift = bits_remaining_ - shift_;
				const int mask = mask_ << shift;
				const int index = (bits_ & mask) >> shift;

				const char out_byte = alphabet_[index];
				ref_.push_back(out_byte);
			}
			while (ref_.size() % mod_)
			{
				ref_.push_back(pad);
			}
		}
		encoder(encoder&& other) : ref_(other.ref_) {
		}

		void operator()(unsigned char byte)	
		{
			bits_ = (bits_ << 8) | byte;
			bits_remaining_ += 8;
			while (bits_remaining_ >= shift_)
			{
				const int shift = bits_remaining_ - shift_;
				const int mask = mask_ << shift;
				const int index = (bits_ & mask) >> shift;

				bits_ = bits_ & ~mask;
				bits_remaining_ -= shift_;

				const char out_byte = alphabet_[index];
				ref_.push_back(out_byte);
			}
		}

	private:
		encoder& operator=(const encoder&) = delete;
		encoder& operator=(const encoder&&) = delete;

		Container&	ref_;
		int			bits_;
		int			bits_remaining_;
	};
}

/*
template< class Container >
encoder_<Container> encoder(Container& c)
{
	return encoder_<Container>(c);
}
*/