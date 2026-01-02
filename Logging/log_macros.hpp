#pragma once
#include "logging.hpp"

#define LOG_ERROR(msg)   Logging::get().logError(msg)
#define LOG_WARNING(msg) Logging::get().logWarning(msg)
#define LOG_INFO(msg)    Logging::get().logInfo(msg)
#define LOG_DEBUG(msg)   Logging::get().logDebug(msg)
#define LOG_VERBOSE(msg) Logging::get().logVerbose(msg)