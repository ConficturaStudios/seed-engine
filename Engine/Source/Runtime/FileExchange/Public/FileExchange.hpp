/**
 * @file FileExchange.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_MODULE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_MODULE_H_

#include "FileExchangeAPI.hpp"


#include "File.hpp"
#include "FileBuffer.hpp"
#include "IniData.hpp"
#include "IniHandler.hpp"
#include "JsonData.hpp"
#include "JsonHandler.hpp"
#include "XmlData.hpp"
#include "XmlHandler.hpp"

#ifdef ENGINE_API
    #undef ENGINE_API
#endif

#endif