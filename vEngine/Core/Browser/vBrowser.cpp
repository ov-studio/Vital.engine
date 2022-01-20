#include "Core/Browser/vBrowser.h"

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
        windowInfo.SetAsWindowless(CWindow);

        CefBrowserHost::CreateBrowser(windowInfo, nullptr, "https://www.google.com", browserSettings, nullptr, nullptr);
    }
}