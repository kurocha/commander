//
//  Table.cpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Table.hpp"

#include "Field.hpp"

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
}
