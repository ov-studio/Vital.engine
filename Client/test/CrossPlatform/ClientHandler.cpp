#include "stdafx.h"
#include "ClientHandler.h"

#include "Vendors/cef/include/cef_app.h"
#include "Vendors/cef/include/cef_base.h"
#include "Vendors/cef/include/cef_client.h"
#include "Vendors/cef/include/cef_command_line.h"
#include "Vendors/cef/include/cef_frame.h"
#include "Vendors/cef/include/cef_web_plugin.h"

ClientHandler::ClientHandler()
{
}

bool ClientHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	return false;
}

void ClientHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	if (!m_Browser.get()) {
		// We need to keep the main child window, but not popup windows
		m_Browser     = browser;
		m_BrowserHandle = browser->GetHost()->GetWindowHandle();
	}
}

void ClientHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	if (m_BrowserHandle == browser->GetHost()->GetWindowHandle()) {
		// Free the browser pointer so that the browser can be destroyed
		m_Browser = nullptr;
	}
}
