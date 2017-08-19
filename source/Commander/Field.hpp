//
//  Field.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Table.hpp"

namespace Commander
{
	class Field
	{
		Table & _table;
		std::string _description;

	public:
		Field(Table & table, std::string description) : _table(table), _description(description)
		{
			_table.append(this);
		}
		
		virtual ~Field();
		
		virtual IteratorT parse(IteratorT begin, IteratorT end)
		{
			return begin;
		}

		virtual void invoke() {}

		virtual void print_usage(std::ostream & output) const noexcept = 0;

		//virtual const std::string & usage(Output::Lines & lines) const noexcept = 0;
	};

}
