#ifndef vEngine_vVersion
    #define vEngine_vVersion
    namespace wi::version
    {
        long GetVersion();
        // Major version
        int GetMajor();
        // Minor version
        int GetMinor();
        // Revision version
        int GetRevision();
        const char* GetVersionString();
    }
#endif