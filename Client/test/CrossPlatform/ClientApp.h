#ifndef __CEF3SimpleSample__ClientHandler__
#define __CEF3SimpleSample__ClientHandler__

#include "Vendors/cef/include/cef_app.h"
#include "Vendors/cef/include/cef_client.h"

class ClientApp : public CefApp, public CefRenderProcessHandler {
public:
ClientApp();

CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override
{
	return this;
}

void OnWebKitInitialized() override;

IMPLEMENT_REFCOUNTING(ClientApp);
};

#endif /* defined(__CEF3SimpleSample__ClientHandler__) */
