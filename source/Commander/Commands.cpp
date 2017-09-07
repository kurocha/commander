//
//  Commands.cpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Commands.hpp"

#include "Command.hpp"

#include <iostream>

namespace Commander
{
	Commands::~Commands()
	{
	}
	
	IteratorT Commands::parse(IteratorT begin, IteratorT end)
	{
		if (begin != end) {
			// We extract the command name if possible:
			auto pair = _fields.find(*begin);
			
			if (pair != _fields.end()) {
				_command = pair->second;
				++begin;
			}
			
			// A command with an empty name assumes whatever was specified.
			pair = _fields.find("");
			
			if (pair != _fields.end()) {
				_command = pair->second;
				_command->set_name(*begin);
				++begin;
			}
		}
		
		if (_command) {
			begin = _command->parse(begin, end);
		}
		
		return begin;
	}
	
	void Commands::print_usage(std::ostream & output) const noexcept
	{
		output << "<command>";
	}
	
	void Commands::print_command_usage(std::ostream & output, std::size_t level) const noexcept
	{
		output << std::string(level, '\t');
		
		print_usage(output);
		
		output << ' ';
		
		auto size = _fields.size();
		
		if (size == 0) {
			output << "Is unavailable." << std::endl;
		} else if (size == 1) {
			auto front = _fields.begin();
			output << "Must be " << front->first << '.' << std::endl;
		} else {
			output << "Must be one of ";
			bool first = true;
			
			for (auto & field : _fields) {
				if (!first) output << ", ";
				else first = false;
				
				output << field.first;
			}
			
			output << '.';
		}
		
		if (_command) {
			// TODO: Fix this to use Variable..
			output << " Default: " << _command->name() << ".";
		}
	}
	
	void Commands::print_full_usage(std::ostream & output, std::size_t level) const noexcept
	{
		if (level == 0) {
			
		} else {
			print_command_usage(output, level);
		}
		
		output << std::endl;
		
		for (auto & field : _fields) {
			output << std::endl;
			field.second->print_full_usage(output, level);
		}
	}
	
	void Commands::invoke()
	{
		if (_command)
			_command->invoke();
	}
}
