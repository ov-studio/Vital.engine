#ifndef vEngine_VERSION_DEFINED
#define vEngine_VERSION_DEFINED

namespace wi::version
{
	long GetVersion();
	// major features
	int GetMajor();
	// minor features, major bug fixes
	int GetMinor();
	// minor bug fixes, alterations
	int GetRevision();
	const char* GetVersionString();
}

#endif // vEngine_VERSION_DEFINED
