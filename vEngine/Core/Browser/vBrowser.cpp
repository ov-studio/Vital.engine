#include "Core/Browser/vBrowser.h"


namespace wi::browser
{
    Client* g_instance = NULL;
    HWND g_mainWindowHandle;

    Client::Client()
    {
        DCHECK(!g_instance);
        g_instance = this;
    }
    Client::~Client()
    {
        g_instance = NULL;
    }

    // Client Helpers
    Client* Client::GetInstance()
    {
        return g_instance;
    }
    void Client::SetMainWindowHandle(HWND windowHandle)
    {
        g_mainWindowHandle = windowHandle;
    }
    HWND Client::GetMainWindowHandle()
    {
        return g_mainWindowHandle;
    }
}

/*

SDKCefApp::SDKCefApp()
{
}

namespace wi::browser
{
    void create(HWND CWindow)
    {
        CefBrowserSettings browserSettings;
        browserSettings.windowless_frame_rate = 60;
        browserSettings.javascript_access_clipboard = cef_state_t::STATE_DISABLED;
        browserSettings.javascript_dom_paste = cef_state_t::STATE_DISABLED;
        browserSettings.webgl = cef_state_t::STATE_ENABLED;

        CefWindowInfo windowInfo;
        windowInfo.SetAsWindowless(NULL);

        CefBrowserHost::CreateBrowser(windowInfo, nullptr, "https://www.google.com", browserSettings, nullptr, nullptr);

        CefRefPtr<SDKCefApp> app(new SDKCefApp);

        // Initialize CEF.
        CefMainArgs main_args(GetModuleHandle(nullptr));
    	CefSettings settings;
        settings.no_sandbox = true;
        settings.background_color = 0xFF161923;
        CefInitialize(main_args, settings, app.get(), nullptr);

    }
}
*/