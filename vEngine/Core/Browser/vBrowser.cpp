#include "Core/Browser/vBrowser.h"

SDKCefClient* g_instance = NULL;
HWND g_mainWindowHandle;

SDKCefClient::SDKCefClient()
	: is_closing_(false)
{
	DCHECK(!g_instance);
	g_instance = this;
}

SDKCefClient::~SDKCefClient()
{
	g_instance = NULL;
}

// static
SDKCefClient* SDKCefClient::GetInstance()
{
	return g_instance;
}
void SDKCefClient::SetMainWindowHandle(HWND handle)
{
	g_mainWindowHandle = handle;
}
HWND SDKCefClient::GetMainWindowHandle()
{
	return g_mainWindowHandle;
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

        CefRefPtr<SDKCefApp> app(new SDKCefApp);

        // Initialize CEF.

        CefMainArgs main_args(GetModuleHandle(nullptr));

    	CefSettings settings;

        settings.no_sandbox = true;

        settings.background_color = 0xFF161923;
    
        CefInitialize(main_args, settings, app.get(), nullptr);

        CefBrowserHost::CreateBrowser(windowInfo, nullptr, "https://www.google.com", browserSettings, nullptr, nullptr);
    }
}