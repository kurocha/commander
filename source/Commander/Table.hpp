//
//  Table.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Parser.hpp"

#include <iosfwd>

namespace Commander
{
	class Field;
	
	class Table
	{
	protected:
		std::vector<Field *> _ordered;

	public:
		virtual void append(Field * field)
		{
			_ordered.push_back(field);
		}
		
		bool empty() const noexcept {return _ordered.empty();}
		
		IteratorT parse(IteratorT begin, IteratorT end);
		bool parse(const ArgumentsT & arguments);
		
		virtual void invoke();
		
		virtual void print_usage(std::ostream &) const noexcept;
		virtual void print_full_usage(std::ostream &, std::size_t level = 0) const noexcept;
	};
}
