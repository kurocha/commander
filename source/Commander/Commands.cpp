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
			auto pair = _fields.find(*begin);

			if (pair == _fields.end())
				pair = _fields.find("");

			if (pair != _fields.end()) {
				_command = pair->second;
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
			output << "No commands available." << std::endl;
		} else if (size == 1) {
			auto front = _fields.begin();
			output << "Only " << front->first << '.' << std::endl;
		} else {
			output << "One of ";
			bool first = true;
			
			for (auto & field : _fields) {
				if (!first) output << ", ";
				else first = false;
				
				output << field.first;
			}
			
			output << '.';
		}
		
		if (_command) {
			output << " Default: " << _command->name() << ".";
		}
	}
	
	void Commands::print_full_usage(std::ostream & output, std::size_t level) const noexcept
	{
		if (level == 0) {
			
		} else {
			print_command_usage(output, level);
		}
		
		//output << std::endl;
		
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
