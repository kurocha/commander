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
	enum class Specified {
		UNSET, DEFAULT, SET
	};
	
	template <typename T>
	struct OptionTraits
	{
		static T parse(IteratorT & begin, IteratorT end)
		{
			if (begin != end) {
				return begin++;
			} else {
				throw ArgumentError("Reached end of input!", begin);
			}
		}
		
		static void assign(T & value, T & value, Specified specified)
		{
			option->set_value(value);
		}
		
		static void print_value(const T & value, std::ostream & output)
		{
			output << value;
		}
		
		template <typename OptionT>
		static void print_usage(const OptionT * option, std::ostream & output)
		{
			output << '[' << option->flags() << " <value>]";
		}
	};
	
	template<>
	struct OptionTraits<bool>
	{
		static bool parse(IteratorT & begin, IteratorT end)
		{
			return true;
		}
		
		template <typename OptionT>
		static void assign(OptionT * option, T & value)
		{
			option->set_value(value);
		}
		
		static void print_value(const bool & value, std::ostream & output)
		{
			output << (value ? "yes" : "no");
		}
		
		template <typename OptionT>
		static void print_usage(const OptionT * option, std::ostream & output)
		{
			output << '[' << option->flags() << ']';
		}
	};
	
	template<typename T, typename TraitsT = OptionsTraits<T>>
	struct OptionTraits<std::vector<T>>
	{
		void assign(OptionT * option, T & value)
		{
			if (option->specified() == Specified::DEFAULT) {
				option->value().clear();
			}
			
			option->value().push_back(value);
		}
		
		static void print_value(const std::vector<T> & value, std::ostream & output)
		{
			output << '{';
			bool first = true;
			for (const auto & item : value) {
				if (first) first = false;
				else output << ", ";
				
				OptionTraits<T>::print(value, output);
			}
			output << '}';
		}
		
		template <typename OptionT>
		static void print_usage(const OptionT * option, std::ostream & output)
		{
			output << '[' << option->flags() << " <value>]*";
		}
	};
	
	template <typename T, typename TraitsT = OptionsTraits<T>>
	class Option : public Field
	{
	public:
		Option(Options & options, Flags flags, std::string description, ValueT initial, Specified specified = Specified::DEFAULT) : Field(options, description), _flags(flags), _specified(specified), _value(initial)
		{
			for (auto & key : flags.keys())
				options.insert(key, this);
		}
		
		virtual ~Option() {}
		
		
	protected:
		Flags _flags;

		Specified _specified = Specified::UNSET;
		ValueT _value;
	};
	
	template <typename ValueT, typename TraitsT = SingleValue<ValueT>>
	class Option : public Field
	{
	public:
		Option(Options & options, Flags flags, std::string description, ValueT initial, Specified specified = Specified::DEFAULT) : Field(options, description), _flags(flags), _specified(specified), _value(initial)
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
			if (begin != end) {
				_value = *begin;
			}
			
			return begin;
		}
		
		explicit operator bool() {return _specified != Specified::UNSET;}
		
		auto & flags() const noexcept {return _flags;}
		auto & value() const noexcept {return _value;}
		
		auto operator*() {return _value;}
		
		virtual void print_usage(std::ostream & output) const noexcept
		{
			TraitsT::print_usage(this, output);
		}
		
		virtual void print_value(std::ostream & output) const noexcept
		{
			TraitsT::print_value(_value, output);
		}
		
		virtual void print_description(std::ostream & output) const noexcept
		{
			Field::print_description(output);
			
			switch(_specified) {
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
		
		Specified _specified = Specified::UNSET;
		ValueT _value;
	};
	
	template <typename ValueT>
	virtual IteratorT Option<ValueT>::parse(IteratorT begin, IteratorT end)
	{
		_value = TraitsT::parse(begin, end);
		_specified = Specified::SET;
		
		return begin;
	}
	
	template <typename ValueT>
	virtual IteratorT Option<std::vector<ValueT>>::parse(IteratorT begin, IteratorT end)
	{
		auto value = TraitsT::parse(begin, end);
		
		if (_specified == Specified::DEFAULT) {
			_value.clear();
		}
		
		_value.push_back(value);
		_specified = Specified::SET;
		
		return begin;
	}
}
