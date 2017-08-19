//
//  Table.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Parser.hpp"

namespace Commander
{
	class Field;
	
	class Table
	{
		std::vector<Field *> _ordered;

	public:
		virtual void append(Field * field)
		{
			_ordered.push_back(field);
		}

		IteratorT parse(IteratorT begin, IteratorT end);

		virtual void invoke();
	};
}
