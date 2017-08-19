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

namespace Commander
{
	class Command : public Field
	{
	public:
		Table table;

		Command(Commands & commands, std::string name = "") : Field(commands), _name(name)
		{
			commands.insert(name, this);
		}

		virtual ~Command();

		virtual IteratorT parse(IteratorT begin, IteratorT end);

		virtual void invoke()
		{
			table.invoke();
		};

	protected:
		std::string _name;
	};

}
