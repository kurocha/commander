//
//  Help.cpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 30/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Help.hpp"

namespace Commander
{
	Help::Help(Options & options, const Field * top) : Option<bool>(options, {"-h", "--help"}, "Print usage information."), _top(top)
	{
		
	}
	
	Help::~Help()
	{
	}
	
	void Help::invoke()
	{
		_top->print_full_usage(std::cerr);
	}
}
