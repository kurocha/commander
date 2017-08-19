//
//  Many.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Field.hpp"

namespace Commander
{
	template <typename ValueT = std::string>
	class Many : public Field
	{
		std::vector<ValueT> _value;

	public:
		using Field::Field;

		virtual IteratorT parse(IteratorT begin, IteratorT end)
		{
			while (begin != end) {
				if (begin->at(0) == '-') break;

				_value.push_back(*begin);

				++begin;
			}

			return begin;
		}

		auto & value() const {return _value;}
	};
}
