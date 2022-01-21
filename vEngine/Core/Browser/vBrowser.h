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

namespace wi::browser
{
    void create(HWND CWindow);
}