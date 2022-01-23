﻿#include "stdafx.h"

#include "ClientV8ExtensionHandler.h"

ClientV8ExtensionHandler::ClientV8ExtensionHandler(CefRefPtr<CefApp> app)
{
	this->app = app;
}

bool ClientV8ExtensionHandler::Execute(const CefString &name,
                                       CefRefPtr<CefV8Value> object,
                                       const CefV8ValueList &arguments,
                                       CefRefPtr<CefV8Value> &retval,
                                       CefString &exception)
{
	if ( name == "ChangeTextInJS" ) {
		if ( (arguments.size() == 1) && arguments[0]->IsString() ) {
			CefString text   = arguments[0]->GetStringValue();
			CefRefPtr<CefFrame> frame  =
				CefV8Context::GetCurrentContext()->GetBrowser()
				->
				GetMainFrame();
			std::string jscall = "ChangeText('";
			jscall += text;
			jscall += "');";
			frame->ExecuteJavaScript(jscall, frame->GetURL(), 0);
			/*
			 * If you want your method to return a value, just use
			 *  retval, like this:
			 * retval = CefV8Value::CreateString("Hello World!");
			 * you can use any CefV8Value, what means you can return
			 *  arrays, objects or whatever you can create with
			 *  CefV8Value::Create* methods
			 */
			return true;
		}
	}

	return false;
}
