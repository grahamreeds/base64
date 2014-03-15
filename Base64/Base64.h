#pragma once
#include <string>

namespace
{
	template< class Container = std::string>
	class encoder
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
		encoder& operator=(const encoder&) = delete;
	private:
		Container&	ref_;
		int			bits_;
		int			bits_remaining_;
		const std::string alphabet_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	};
}
/*
template< class Container >
encoder_<Container> encoder(Container& c)
{
	return encoder_<Container>(c);
}
*/