//
//  Commands.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Map.hpp"

namespace Commander
{
	class Command;
	
	class Commands : public Map<Command>
	{
		Command * _command = nullptr;

		void print_command_usage(std::ostream & output, std::size_t level) const noexcept;

	public:
		using Map::Map;
		
		virtual ~Commands();

		virtual IteratorT parse(IteratorT begin, IteratorT end);
		void set_command(Command * command) {_command = command;}

		virtual void print_usage(std::ostream & output) const noexcept;
		virtual void print_full_usage(std::ostream & output, std::size_t level = 0) const noexcept;

		virtual void invoke();

		auto value() const noexcept {return _command;}
	};
}
