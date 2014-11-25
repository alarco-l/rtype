#pragma once

struct									MovementComponent
{
	MovementComponent(const float _velocity = 0.0f) : velocity(_velocity)
	{
	}

	float								velocity;
};