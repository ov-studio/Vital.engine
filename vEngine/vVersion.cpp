#include "vVersion.h"

#include <string>

namespace wi::version
{
    const int major = 1;
    const int minor = 0;
    const int revision = 0;

    const std::string version_string = std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(revision);

    int GetMajor()
    {
        return major;
    }

    int GetMinor()
    {
        return minor;
    }

    int GetRevision()
    {
        return revision;
    }

    const char* GetVersionString()
    {
        return version_string.c_str();
    }
}
