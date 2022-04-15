#pragma once

#include "SaturnEngine/Core.h"
#include "Utils/String.h"
#include "Utils/File.h"

#include "rapidjson/document.h"
#include "rapidjson/encodings.h"

namespace SaturnEngine
{
	class SATURN_API ConfigSubsystem
	{
	public:
		explicit ConfigSubsystem(const String& path);
		ConfigSubsystem(const ConfigSubsystem& other) = delete;
		ConfigSubsystem(ConfigSubsystem&& other) = delete;
		~ConfigSubsystem();

		/**
		 * Returns a string value from the config file.
		 *
		 * If the requested value hasn't been found, the function returns the `defaultValue` parameter and saves that value with the provided name.
		 *
		 * @param name the name of the value requested
		 * @param defaultValue value to be returned when the requested one wasn't found
		 * @return a string value of the requested one
		 */
		String RequestString(const String& name, const String& defaultValue);
		/**
		 * Returns a 32-bit integer value from the config file.
		 *
		 * If the requested value hasn't been found, the function returns the `defaultValue` parameter and saves that value with the provided name.
		 *
		 * @param name the name of the value requested
		 * @param defaultValue value to be returned when the requested one wasn't found
		 * @return a 32-bit integer value of the requested one
		 */
		I32 RequestInt32(const String& name, I32 defaultValue);
		/**
		 * Returns a 64-bit integer value from the config file.
		 *
		 * If the requested value hasn't been found, the function returns the `defaultValue` parameter and saves that value with the provided name.
		 *
		 * @param name the name of the value requested
		 * @param defaultValue value to be returned when the requested one wasn't found
		 * @return a 64-bit integer value of the requested one
		 */
		I64 RequestInt64(const String& name, I64 defaultValue);
		/**
		 * Returns a 32-bit float value from the config file.
		 *
		 * If the requested value hasn't been found, the function returns the `defaultValue` parameter and saves that value with the provided name.
		 *
		 * @param name the name of the value requested
		 * @param defaultValue value to be returned when the requested one wasn't found
		 * @return a 32-bit float value of the requested one
		 */
		F32 RequestFloat32(const String& name, F32 defaultValue);
		/**
		 * Returns a 64-bit float value from the config file.
		 *
		 * If the requested value hasn't been found, the function returns the `defaultValue` parameter and saves that value with the provided name.
		 *
		 * @param name the name of the value requested
		 * @param defaultValue value to be returned when the requested one wasn't found
		 * @return a 64-bit float value of the requested one
		 */
		F64 RequestFloat64(const String& name, F64 defaultValue);
		/**
		 * Returns a boolean value from the config file.
		 *
		 * If the requested value hasn't been found, the function returns the `defaultValue` parameter and saves that value with the provided name.
		 *
		 * @param name the name of the value requested
		 * @param defaultValue value to be returned when the requested one wasn't found
		 * @return a boolean value of the requested one
		 */
		bool RequestBool(const String& name, bool defaultValue);

		//Singleton instance getter function. Present in every subsystem.
		static ConfigSubsystem* Get();

		ConfigSubsystem& operator=(const ConfigSubsystem& other) = delete;
		ConfigSubsystem& operator=(ConfigSubsystem&& other) = delete;

	private:
		static ConfigSubsystem* s_instance;

		File m_file;
		rapidjson::GenericDocument<rapidjson::UTF16LE<>> m_config;
	};
}

#define CONFIG_REQUEST_STRING(name, defaultValue) ConfigSubsystem::Get()->RequestString(name, defaultValue)
#define CONFIG_REQUEST_INT32(name, defaultValue) ConfigSubsystem::Get()->RequestInt32(name, defaultValue)
#define CONFIG_REQUEST_INT64(name, defaultValue) ConfigSubsystem::Get()->RequestInt64(name, defaultValue)
#define CONFIG_REQUEST_FLOAT32(name, defaultValue) ConfigSubsystem::Get()->RequestFloat32(name, defaultValue)
#define CONFIG_REQUEST_FLOAT64(name, defaultValue) ConfigSubsystem::Get()->RequestFloat64(name, defaultValue)
#define CONFIG_REQUEST_BOOL(name, defaultValue) ConfigSubsystem::Get()->RequestBool(name, defaultValue)
