//
//  One.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#inclue "Field.hpp"

namespace Commander
{
	template <typename ValueT = std::string>
	class One : public Field
	{
		ValueT _value;

	public:
		using Field::Field;

		virtual IteratorT parse(IteratorT begin, IteratorT end) {
			if (begin != end) {
				_value = *begin;
				++begin;
			}

			return begin;
		}

		auto & value() const {return _value;}
	};
}
