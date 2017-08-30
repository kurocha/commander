//
//  Option.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Options.hpp"
#include "Flags.hpp"

#include <iostream>

namespace Commander
{
	template <typename ValueT>
	class GenericOption : public Field
	{
	public:
		GenericOption(Options & options, Flags flags, std::string description, ValueT initial = ValueT()) : Field(options, description), _flags(flags), _value(initial)
		{
			for (auto & key : flags.keys())
				options.insert(key, this);
		}
		
		virtual ~GenericOption() {}
		
		auto flags() const noexcept {return _flags;}
		auto value() const noexcept {return _value;}
		
		auto operator*() {return _value;}
		
		virtual void print_usage(std::ostream & output) const noexcept
		{
			output << '[' << this->_flags << " <value>]";
		}
		
	protected:
		Flags _flags;
		ValueT _value;
	};
	
	template <typename ValueT = std::string>
	class Option : public GenericOption<ValueT>
	{
	public:
		using GenericOption<ValueT>::GenericOption;
		virtual ~Option() {}
	};
	
	template <>
	class Option<std::string> : public GenericOption<std::string>
	{
	public:
		using GenericOption<std::string>::GenericOption;
		virtual ~Option() {}
		
		virtual IteratorT parse(IteratorT begin, IteratorT end)
		{
			if (begin != end) {
				// consume the value
				this->_value = *begin;

				++begin;
			}

			return begin;
		}
	};
	
	template <>
	class Option<bool> : public GenericOption<bool>
	{
	public:
		using GenericOption<bool>::GenericOption;
		virtual ~Option() {}

		virtual IteratorT parse(IteratorT begin, IteratorT end)
		{
			this->_value = true;

			return begin;
		}

		virtual void print_usage(std::ostream & output) const noexcept
		{
			output << '[' << this->_flags << ']';
		}
	};
}
