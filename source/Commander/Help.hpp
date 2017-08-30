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
		using Option<bool>::Option;
		virtual ~Help();
		
		virtual void invoke();
	};
}
