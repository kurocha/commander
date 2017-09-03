//
//  Option.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Variable.hpp"
#include "Options.hpp"
#include "Flags.hpp"

#include "OptionTraits.hpp"

#include <iostream>

namespace Commander
{
	template <typename ValueT, typename _TraitsT = OptionTraits<ValueT>>
	class Option : public Field, public Variable<ValueT>
	{
	public:
		using TraitsT = _TraitsT;
		
		Option(Options & options, Flags flags, std::string description, ValueT initial, Specified specified = Specified::DEFAULT) : Field(options, description), Variable<ValueT>::Variable(initial, specified), _flags(flags)
		{
			for (auto & key : flags.keys())
				options.insert(key, this);
		}
		
		Option(Options & options, Flags flags, std::string description) : Option(options, flags, description, ValueT(), Specified::UNSET)
		{
		}
		
		virtual ~Option() {}
		
		virtual IteratorT parse(IteratorT begin, IteratorT end)
		{
			auto value = TraitsT::parse(begin, end);
			
			TraitsT::assign(this, value);
			this->_specified = Specified::SET;
			
			return begin;
		}
		
		auto & flags() const noexcept {return _flags;}
		
		virtual void print_usage(std::ostream & output) const noexcept
		{
			TraitsT::print_usage(this, output);
		}
		
		virtual void print_value(std::ostream & output) const noexcept
		{
			TraitsT::print_value(this->_value, output);
		}
		
		virtual void print_description(std::ostream & output) const noexcept
		{
			Field::print_description(output);
			
			switch(this->_specified) {
				case Specified::UNSET:
					output << " Unset.";
					break;
				case Specified::DEFAULT:
					output << " Default: "; print_value(output);
					break;
				case Specified::SET:
					output << " Set: "; print_value(output);
					break;
			}
		}
		
	protected:
		Flags _flags;
	};
}
