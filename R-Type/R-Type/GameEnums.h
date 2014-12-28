#pragma once

namespace	RType
{

	namespace	HUD
	{
		enum
		{
			LIFE_TEXT,
			SHIELD_TEXT,
			LIFEBAR,
			SHIELDBAR,
			BOSS_LIFEBAR,
			SCORE,
			WEAPON_1,
			WEAPON_2,
			WEAPON_3,
			MAX
		};
	};

	namespace	Player
	{
		enum
		{
			SHIP,
			ENGINE_1,
			ENGINE_2,
			WEAPON_1,
			WEAPON_2,
			MAX
		};
	};

	namespace	GameBackground
	{
		enum
		{
			DEFAULT,
			REVERSED,
			MAX
		};
	};

	namespace	MainMenu
	{
		enum
		{
			CONNECT,
			EXIT,
			BACKGROUND,
			TITLE,
			MAX
		};
	};

	namespace	LobbyMenu
	{
		enum
		{
			BACKGROUND,
			TEXT,
			LOAD_ICON,
			MAX
		};
	};

	namespace	PauseMenu
	{
		enum
		{
			CONTINUE,
			EXIT,
			FILTER,
			MAX
		};
	};

	namespace	EndMenu
	{
		enum
		{
			RESULT,
			FILTER,
			SCORE,
			EXIT,
			MAX
		};
	}

	namespace	Projectile
	{
		enum
		{
			MISSILE,
			LASER
		};
	}

}