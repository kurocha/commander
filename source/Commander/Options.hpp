//
//  Options.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Map.hpp"

namespace Commander
{
	class Options : public Map<>
	{
	public:
		using Map::Map;
		virtual ~Options();
		
		virtual void print_usage(std::ostream & output) const noexcept;
	};
}
