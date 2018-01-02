
// Temporary cruft to make MSVC happy, doesn't do anything.
#ifdef WIN32

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

	__declspec(dllexport) void __cdecl temp()
	{
	}

#ifdef __cplusplus
}
#endif

#endif