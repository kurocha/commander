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

namespace Commander
{
	template <typename ValueT>
	class Option : public Field
	{
		Flags _flags;
		ValueT _value;

	public:
		Option(Options & options, Flags flags, std::string description, ValueT initial = ValueT()) : Field(options, description), _flags(flags), _value(initial)
		{
			for (auto & key : flags.keys())
				 options.insert(key, this);
		}

		virtual ~Option() {}

		virtual IteratorT parse(IteratorT begin, IteratorT end)
		{
			if (begin != end) {
				// consume the value
				_value = *begin;

				++begin;
			}

			return begin;
		}

		virtual void print_usage(std::ostream & output) const noexcept
		{
			output << _flags << ' ' << "[value]";
		}

		auto flags() const noexcept {return _flags;}
		auto value() const noexcept {return _value;}
	};

	template <>
	class Option<bool> : public Field
	{
		Flags _flags;
		bool _value = false;

	public:
		Option(Options & options, Flags flags, std::string description) : Field(options, description), _flags(flags)
		{
			for (auto & key : flags.keys())
				options.insert(key, this);
		}

		virtual ~Option() {}

		virtual IteratorT parse(IteratorT begin, IteratorT end)
		{
			_value = true;

			return begin;
		}

		virtual void print_usage(std::ostream & output) const noexcept
		{
			output << '[' << _flags << ']';
		}

		auto flags() const noexcept {return _flags;}
		auto value() const noexcept {return _value;}
	};
}
