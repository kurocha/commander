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
	public:
		Field(Table & table, std::string description) : _table(table), _description(description)
		{
			_table.append(this);
		}
		
		virtual ~Field();
		
		Field(const Field &) = delete;
		
		template <typename ArgumentsT>
		bool parse(const ArgumentsT & arguments)
		{
			return parse(arguments.begin(), arguments.end()) == arguments.begin();
		}
		
		virtual IteratorT parse(IteratorT begin, IteratorT end)
		{
			return begin;
		}

		virtual void invoke() {}

		virtual void print_usage(std::ostream & output) const noexcept = 0;
		
		virtual void print_full_usage(std::ostream & output, std::size_t level = 0) const noexcept;
		
		virtual void print_description(std::ostream & output) const noexcept;
		
	protected:
		Table & _table;
		std::string _description;
	};
}
