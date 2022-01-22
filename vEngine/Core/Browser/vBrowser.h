#pragma once
#include "Vendors/cef/include/cef_app.h"
#include "Vendors/cef/include/cef_browser.h"
#include "Vendors/cef/include/cef_client.h"
#include "Vendors/cef/include/cef_render_handler.h"
#include "Vendors/cef/include/cef_life_span_handler.h"
#include "Vendors/cef/include/cef_context_menu_handler.h"
#include "Vendors/cef/include/cef_resource_request_handler.h"
#include "Vendors/cef/include/cef_parser.h"
#include "Vendors/cef/include/cef_task.h"
#include "Vendors/cef/include/cef_scheme.h"

#include "Vendors/cef/include/cef_browser.h"
#include "Vendors/cef/include/cef_command_line.h"
#include "Vendors/cef/include/views/cef_browser_view.h"
#include "Vendors/cef/include/views/cef_window.h"
#include "Vendors/cef/include/wrapper/cef_helpers.h"
#include "Vendors/cef/include/wrapper/cef_closure_task.h"

class SDKCefClient : public CefClient,
	public CefDisplayHandler,
	public CefLifeSpanHandler,
	public CefLoadHandler,
	public CefRequestHandler,
	public CefResourceRequestHandler
{
public:
	explicit SDKCefClient();
	~SDKCefClient();

	// Provide access to the single global instance of this object.
	static SDKCefClient* GetInstance();

	static void SetMainWindowHandle(HWND handle);
	static HWND GetMainWindowHandle();

	// CefClient methods:
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override
	{
		return this;
	}
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override
	{
		return this;
	}
	virtual CefRefPtr<CefRequestHandler> GetRequestHandler() override
	{
		return this;
	}
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override
	{
		return this;
	}

    /*
	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;

	// CefDisplayHandler methods:
	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
		const CefString& title) override;

	// CefLifeSpanHandler methods:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

	// CefLoadHandler methods:
	virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override;

	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		ErrorCode errorCode,
		const CefString& errorText,
		const CefString& failedUrl) override;

	virtual CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool is_navigation, bool is_download, const CefString& request_initiator, bool& disable_default_handling) override
	{
		return this;
	}

	// Request that all existing browser windows close.
	void CloseAllBrowsers(bool force_close);

	bool IsClosing() const
	{
		return is_closing_;
	}
    */

	CefRefPtr<CefBrowser> GetBrowser();

private:
	// Platform-specific implementation.
	void PlatformTitleChange(CefRefPtr<CefBrowser> browser,
		const CefString& title);

	// List of existing browser windows. Only accessed on the CEF UI thread.
	typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
	BrowserList browser_list_;

	bool is_closing_;

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(SDKCefClient);
};

class SDKCefApp : public CefApp, public CefBrowserProcessHandler/*, public CefRenderProcessHandler*/
{
public:
	typedef std::function<CefRefPtr<CefV8Value>(const CefV8ValueList&, CefString&)> TV8Handler;

	SDKCefApp();

	// CefApp methods:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
		override
	{
		return this;
	}

	//virtual void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) override;

	// CefBrowserProcessHandler methods:
	//virtual void OnContextInitialized() override;

private:
	int m_v8Callbacks;

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(SDKCefApp);
};

/*
class SDKWindowDelegate : public CefWindowDelegate
{
public:
	explicit SDKWindowDelegate(CefRefPtr<CefBrowserView> browser_view, const std::wstring& placementKey);
	explicit SDKWindowDelegate(CefRefPtr<CefBrowserView> browser_view, const std::wstring& placementKey, const std::string& forceWindowTitle);

	void OnWindowCreated(CefRefPtr<CefWindow> window) override;
	void OnWindowDestroyed(CefRefPtr<CefWindow> window) override;

	bool CanClose(CefRefPtr<CefWindow> window) override;

	CefSize GetMinimumSize(CefRefPtr<CefView> view) override;

private:
	void LoadPlacement(CefRefPtr<CefWindow> window);
	void SavePlacement(CefRefPtr<CefWindow> window);

private:
	std::string forcedWindowTitle;
	std::wstring placementRegistryKey;
	CefRefPtr<CefBrowserView> browser_view_;

	IMPLEMENT_REFCOUNTING(SDKWindowDelegate);
	DISALLOW_COPY_AND_ASSIGN(SDKWindowDelegate);
};

class SDKSubViewDelegate : public CefBrowserViewDelegate
{
public:
	SDKSubViewDelegate();

	virtual CefRefPtr<CefBrowserViewDelegate> GetDelegateForPopupBrowserView(CefRefPtr<CefBrowserView> browser_view, const CefBrowserSettings& settings, CefRefPtr<CefClient> client, bool is_devtools);

	virtual bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view, CefRefPtr<CefBrowserView> popup_browser_view, bool is_devtools);

private:
	IMPLEMENT_REFCOUNTING(SDKSubViewDelegate);
	DISALLOW_COPY_AND_ASSIGN(SDKSubViewDelegate);
};
*/

namespace wi::browser
{
    void create(HWND CWindow);
}