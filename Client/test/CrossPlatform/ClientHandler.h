#ifndef __CEFSimpleSample__ClientHandler__
#define __CEFSimpleSample__ClientHandler__

#include "Vendors/cef/include/cef_render_process_handler.h"
#include "Vendors/cef/include/cef_client.h"
#include "Vendors/cef/include/cef_v8.h"
#include "Vendors/cef/include/cef_browser.h"

class ClientHandler : public CefClient, public CefLifeSpanHandler, public CefRenderHandler {
public:
ClientHandler();

CefRefPtr<CefBrowser> GetBrowser()
{
	return m_Browser;
}

CefWindowHandle GetBrowserHwnd()
{
	return m_BrowserHandle;
}

// CefClient methods
virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override
{
	return this;
}

CefRefPtr<CefRenderHandler> GetRenderHandler() override
{
    return this;
};

// Virtual on CefLifeSpanHandler
virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

protected:
// The child browser window
CefRefPtr<CefBrowser> m_Browser;

// The child browser window handle
CefWindowHandle m_BrowserHandle;

// /
// Macro that provides a reference counting implementation for classes
// extending CefBase.
// /
IMPLEMENT_REFCOUNTING(ClientHandler);
};

#endif /* defined(__CEFSimpleSample__ClientHandler__) */
