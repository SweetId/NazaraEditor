#pragma once

#include <NazaraUtils/Prerequisites.hpp>

#ifndef NAZARAEDITOR_CORE_CONFIG_HPP
#define NAZARAEDITOR_CORE_CONFIG_HPP

#if !defined(NAZARAEDITOR_STATIC)
#ifdef NAZARAEDITOR_CORE_BUILD
#define NAZARAEDITOR_CORE_API NAZARA_EXPORT
#else
#define NAZARAEDITOR_CORE_API NAZARA_IMPORT
#endif
#else
#define NAZARAEDITOR_CORE_API
#endif

namespace Nz
{
	enum StretchMode
	{
		Fill,
		KeepAspectRatio
	};
}

#endif // NAZARAEDITOR_CORE_CONFIG_HPP
