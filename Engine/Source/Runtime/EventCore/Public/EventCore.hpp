/**
 * EventCore.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_MODULE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_MODULE_H_

#include "EventCoreAPI.hpp"


#include "ClientEvent.hpp"
#include "ControllerAxisEvent.hpp"
#include "ControllerButtonEvent.hpp"
#include "ControllerEvent.hpp"
#include "EngineEvent.hpp"
#include "EngineGameLoadEvent.hpp"
#include "EnginePostRenderEvent.hpp"
#include "EnginePreRenderEvent.hpp"
#include "EngineRenderEvent.hpp"
#include "EngineTickEvent.hpp"
#include "Event.hpp"
#include "EventDispatcher.hpp"
#include "KeyboardEvent.hpp"
#include "MouseButtonEvent.hpp"
#include "MouseEvent.hpp"
#include "MouseMovedEvent.hpp"
#include "MouseScrolledEvent.hpp"
#include "PeripheralEvent.hpp"
#include "SystemEvent.hpp"
#include "WindowCloseEvent.hpp"
#include "WindowContentScaleEvent.hpp"
#include "WindowCreatedEvent.hpp"
#include "WindowEvent.hpp"
#include "WindowFocusEvent.hpp"
#include "WindowMaximizeEvent.hpp"
#include "WindowMinimizeEvent.hpp"
#include "WindowPositionEvent.hpp"
#include "WindowRefreshEvent.hpp"
#include "WindowResizeEvent.hpp"
#include "WindowUpdateEvent.hpp"

#ifdef ENGINE_API
    #undef ENGINE_API
#endif

#endif