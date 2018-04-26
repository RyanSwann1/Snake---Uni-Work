#pragma once

#include <Components\ComponentPosition.h>
#include <memory>

class ComponentSnakeTail : public ComponentBase
{
public:
	std::unique_ptr<ComponentPosition> m_position;
};