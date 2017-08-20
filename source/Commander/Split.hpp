//
//  Split.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Field.hpp"
#include <vector>

namespace Commander
{
	template <typename ValueT = std::string>
	class Split : public Field
	{
		std::vector<ValueT> _value;

	public:
		virtual ~Split() {}
		
		IteratorT parse(IteratorT begin, IteratorT end)
		{
			if (begin != end) {
				_value = *begin;
				++begin;
			}

			return begin;
		}

		virtual void print_usage(std::ostream & output) const noexcept
		{
			output << "-- <" << "value" << "...>";
		}
		
		auto & value() const noexcept {return _value;}
	};
}
