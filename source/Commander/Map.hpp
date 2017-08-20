//
//  Map.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Field.hpp"

#include <map>
#include <string>

namespace Commander
{
	template <typename FieldT = Field>
	class Map : public Field, public Table
	{
	protected:
		std::map<std::string, FieldT *> _fields;

	public:
		Map(Table & table, std::string description = "") : Field(table, description) {}
		virtual ~Map() {}
		
		void insert(std::string key, FieldT * option)
		{
			_fields.insert({key, option});
		}
		
		virtual IteratorT parse(IteratorT begin, IteratorT end)
		{
			while (begin != end) {
				auto pair = _fields.find(*begin);

				if (pair != _fields.end()) {
					begin = pair->second->parse(++begin, end);
				} else {
					break;
				}
			}

			return begin;
		}
	};

}
