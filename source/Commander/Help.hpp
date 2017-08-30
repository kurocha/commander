//
//  Help.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 30/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Option.hpp"

namespace Commander
{
	class Help : public Option<bool>
	{
	public:
		Help(Options & options, const Field * top);
		virtual ~Help();
		
		virtual void invoke();
	
	protected:
		const Field * _top;
	};
}
