//
//  Table.cpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Table.hpp"

#include "Field.hpp"

#include <iostream>

namespace Commander
{
	void Table::invoke()
	{
		for (auto field : _ordered)
			field->invoke();
	}

	IteratorT Table::parse(IteratorT begin, IteratorT end)
	{
		for (auto field : _ordered) {
			begin = field->parse(begin, end);
		}

		return begin;
	}
	
	void Table::print_usage(std::ostream & output) const noexcept
	{
		bool first = true;
		
		for (auto field : _ordered) {
			if (!first) output << ' ';
			else first = false;
			
			field->print_usage(output);
		}
	}
	
	void Table::print_full_usage(std::ostream & output, std::size_t level) const noexcept
	{
		for (auto field : _ordered) {
			field->print_full_usage(output, level);
		}
	}
}
