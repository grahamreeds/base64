#pragma once
#include <string>

namespace
{

	struct base64
	{
		const std::string alphabet_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		const int shift_ = 6;
		const int mask_ = 0x3f;
		base64& operator=(const base64&) = delete;
	};

//	const std::string base64::alphabet_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	template< class Container = std::string, typename Alphabet = base64>
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

				const int shift = bits_remaining_ - 6;
				const int mask = 0x3f << shift;
				const int index = (bits_ & mask) >> shift;

				const char out_byte = alphabet_[index];
				ref_.push_back(out_byte);
			}

			while (ref_.size() % 4)
			{
				ref_.push_back('=');
			}

		}
		encoder(encoder&& other) : ref_(other.ref_) {
//			ref_.push_back('M');
		}

		void operator()(unsigned char byte)	
		{
			bits_ = (bits_ << 8) | byte;
			bits_remaining_ += 8;
			while (bits_remaining_ > 4)
			{
				const int shift = bits_remaining_ - 6;
				const int mask = 0x3f << shift;
				const int index = (bits_ & mask) >> shift;

				bits_ = bits_ & ~mask;
				bits_remaining_ -= 6;

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