//
//  Variable.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 3/9/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

namespace Commander
{
	enum class Specified {
		UNSET, DEFAULT, SET
	};
	
	template <typename ValueT>
	class Variable
	{
	public:
		Variable() {}
		Variable(const ValueT & initial, Specified specified = Specified::DEFAULT) : _value(initial), _specified(specified) {}
		
		auto & specified() const noexcept {return _specified;}
		
		auto & value() const noexcept {return _value;}
		auto & value() noexcept {return _value;}
		
		void set(const ValueT & value, Specified specified = Specified::SET) {
			_value = value;
			_specified = specified;
		}
		
		explicit operator bool() {return _specified != Specified::UNSET;}
		auto & operator*() const noexcept {return _value;}
		
	protected:
		ValueT _value;
		Specified _specified = Specified::UNSET;
	};
}
