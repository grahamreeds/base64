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

	struct base32hex
	{
		const std::string alphabet_ = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
		const int shift_ = 5;
		const int mask_ = 0x1f;
		const int mod_ = 8;
		base32hex& operator=(const base32hex&) = delete;
	};

	struct base16
	{
		const std::string alphabet_ = "0123456789ABCDEF";
		const int shift_ = 4;
		const int mask_ = 0x0f;
		const int mod_ = 1;
		base16& operator=(const base16&) = delete;
	};

	const char pad = '=';


	template< class Container, typename Alphabet = base64>
	class encoder_ : Alphabet
	{
	public:
		encoder_(Container& ref)
			: ref_(ref), bits_(0), bits_remaining_(0) { }
		encoder_(encoder_&& other) 
			: ref_(other.ref_) { }
		~encoder_()
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
//		encoder_& operator=(const encoder_&) = delete;
//		encoder_& operator=(const encoder_&&) = delete;

		Container&	ref_;
		int			bits_;
		int			bits_remaining_;
	};

	template< typename Alphabet >
	struct invalid_data_throw : Alphabet
	{
		size_t is_valid(unsigned char ch) const
		{
			size_t pos = alphabet_.find(ch);
			if (pos == std::string::npos)
			{
				throw std::runtime_error("Invalid alphabet data in stream");
			}
			return pos;
		}
	};

	template< typename Alphabet >
	struct invalid_data_allow : Alphabet
	{
		size_t is_valid(unsigned char ch) const
		{
			return alphabet_.find(ch);
		}
	};


	template< class Container = std::string, typename Alphabet = base64, typename InvalidAlphabet = invalid_data_throw<Alphabet> >
	class decoder : InvalidAlphabet
	{
	public:
		decoder(Container& ref) 
			: ref_(ref), bits_(0), bits_remaining_(0) { }
		~decoder() 
		{ 
		}
		void operator()(unsigned char byte) 
		{
			if (byte != pad)
			{
				size_t indice = is_valid(byte);
				if (indice != std::string::npos)
				{
					bits_ = (bits_ << shift_) | indice;
					bits_remaining_ += shift_;

					while (bits_remaining_ >= 8)
					{
						const int shift = bits_remaining_ - 8;
						const int mask = 0xff << shift;
						const int index = (bits_ & mask) >> shift;

						bits_ = bits_ & ~mask;
						bits_remaining_ -= 8;

						ref_.push_back((char)index);
					}
				}
			}
		}
	private:
		decoder& operator=(const decoder&) = delete;
		decoder& operator=(const decoder&&) = delete;

		Container&	ref_;
		int			bits_;
		int			bits_remaining_;
	};

}


template< class Container, typename Alphabet = base64 >
encoder_<Container, Alphabet> encoder(Container& ref)
{
	return encoder_<Container, Alphabet>(ref);
}

//template< class Container, typename Alphabet = base64 >
//decoder_<Container, Alphabet> decoder(Container& ref)
//{
//	return decoder_<Container, Alphabet>(ref);
//}
