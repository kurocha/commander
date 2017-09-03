//
//  OptionTraits.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 3/9/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Parser.hpp"

#include <iostream>

namespace Commander
{
	template <typename ValueT>
	struct OptionTraits
	{
		ValueT parse(IteratorT & begin, IteratorT end) const
		{
			if (begin != end) {
				return *begin++;
			} else {
				throw ArgumentError("Reached end of input!", begin);
			}
		}
		
		template <typename OptionT>
		void assign(OptionT * option, const ValueT & value) const
		{
			option->set(value);
		}
		
		void print_value(const ValueT & value, std::ostream & output) const
		{
			output << value;
		}
		
		template <typename OptionT>
		void print_usage(const OptionT * option, std::ostream & output) const
		{
			output << '[' << option->flags() << " <value>]";
		}
	};
	
	template<>
	struct OptionTraits<bool>
	{
		bool parse(IteratorT & begin, IteratorT end) const
		{
			return true;
		}
		
		template <typename OptionT>
		void assign(OptionT * option, const bool & value) const
		{
			option->set(value);
		}
		
		void print_value(const bool & value, std::ostream & output) const
		{
			output << (value ? "yes" : "no");
		}
		
		template <typename OptionT>
		void print_usage(const OptionT * option, std::ostream & output) const
		{
			output << '[' << option->flags() << ']';
		}
	};
	
	template <typename ValueT>
	struct OptionTraits<std::vector<ValueT>> : public OptionTraits<ValueT>
	{
		using OptionTraits<ValueT>::OptionTraits;
		
		ValueT parse(IteratorT & begin, IteratorT end) const
		{
			return OptionTraits<ValueT>::parse(begin, end);
		}
		
		template <typename OptionT>
		void assign(OptionT * option, const ValueT & value) const
		{
			// If the user sets something, we clear all the default values.
			if (option->specified() == Specified::DEFAULT) {
				option->value().clear();
			}
			
			option->value().push_back(value);
		}
		
		void print_value(const std::vector<ValueT> & value, std::ostream & output) const
		{
			output << '{';
			bool first = true;
			for (const auto & item : value) {
				if (first) first = false;
				else output << ", ";
				
				OptionTraits<ValueT>::print_value(item, output);
			}
			output << '}';
		}
		
		template <typename OptionT>
		void print_usage(const OptionT * option, std::ostream & output) const
		{
			OptionTraits<ValueT>::print_usage(option, output);
			output << '*';
		}
	};
}
