//
//  Commands.cpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Commands.hpp"

#include "Command.hpp"

namespace Commander
{
	Commands::~Commands()
	{
	}
	
	IteratorT Commands::parse(IteratorT begin, IteratorT end)
	{
		if (begin != end) {
			auto pair = _fields.find(*begin);

			if (pair == _fields.end())
				pair = _fields.find("");

			if (pair != _fields.end()) {
				_command = pair->second;

				begin = pair->second->parse(begin, end);
			}
		}

		return begin;
	}

	void Commands::invoke()
	{
		if (_command)
			_command->invoke();
	}
}
