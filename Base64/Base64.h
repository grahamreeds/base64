#pragma once

namespace
{
	template< class Container >
	class encoder_
	{
	public:
		encoder_(Container c) : ref_(c) { }
		~encoder_() { }
		void operator()(unsigned char byte)	{ }
	private:
		Container& ref_;
	};
}

template< class Container >
encoder_<Container> encoder(Container& c)
{
	return encoder_<Container>(c);
}
