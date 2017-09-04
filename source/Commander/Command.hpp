//
//  Command.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Table.hpp"
#include "Commands.hpp"
#include "Options.hpp"
#include "Help.hpp"

namespace Commander
{
	class Command : public Field
	{
	public:
		Table table;

		Command(Commands & commands, std::string name = "", std::string description = "", bool initial = false) : Field(commands, description), _name(name)
		{
			commands.insert(name, this);
			
			if (initial)
				commands.set_command(this);
		}

		virtual ~Command();

		virtual IteratorT parse(IteratorT begin, IteratorT end);
		
		virtual void print_usage(std::ostream & output) const noexcept;
		
		virtual void print_full_usage(std::ostream & output, std::size_t level = 0) const noexcept;

		auto name() const noexcept {return _name;}

	protected:
		std::string _name;
	};
}
