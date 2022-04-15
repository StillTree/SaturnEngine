#include "Management/ConfigSubsystem.h"
#include "Management/LogSubsystem.h"

#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

namespace SaturnEngine
{
	ConfigSubsystem* ConfigSubsystem::s_instance = nullptr;

	ConfigSubsystem::ConfigSubsystem(const String& path)
		: m_file(path), m_config()
	{
		ST_ASSERT(!s_instance, L"You can't create a second instance of ConfigManager!")
		s_instance = this;

		m_config.Parse(m_file.ReadText().Pointer());
		if(!m_config.IsObject())
		{
			ST_WARN(L"Configuration file empty, incorrectly formatted or not found.");
			m_config.SetObject();
		}

		ST_DEBUG(L"ConfigSubsystem initialized successfully");
		ST_CLEAR_ERROR();
	}

	ConfigSubsystem::~ConfigSubsystem()
	{
		rapidjson::GenericStringBuffer<rapidjson::UTF16LE<>, rapidjson::MemoryPoolAllocator<>> buffer(&m_config.GetAllocator());
		rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF16LE<>, rapidjson::MemoryPoolAllocator<>>,
		        rapidjson::UTF16LE<>, rapidjson::UTF16LE<>> writer(buffer);
		writer.SetIndent(L'\t', 1);
		m_config.Accept(writer);

		m_file.WriteText(buffer.GetString());
		ST_DEBUG(L"Config subsystem shut down successfully.");
	}

	String ConfigSubsystem::RequestString(const String& name, const String& defaultValue)
	{
		if(!m_config.HasMember(name.Pointer()))
		{
			ST_WARN(L"Could not find the \"{0}\" member in the configuration file.", name.Pointer());
			auto& allocator = m_config.GetAllocator();
			m_config.AddMember(rapidjson::GenericValue<rapidjson::UTF16LE<>>(name.Pointer(), allocator),
					rapidjson::GenericValue<rapidjson::UTF16LE<>>(defaultValue.Pointer(), allocator),
					allocator);

			return defaultValue;
		}

		return m_config[name.Pointer()].GetString();
	}

	I32 ConfigSubsystem::RequestInt32(const String& name, I32 defaultValue)
	{
		if(!m_config.HasMember(name.Pointer()))
		{
			ST_WARN(L"Could not find the \"{0}\" member in the configuration file.", name.Pointer());
			auto& allocator = m_config.GetAllocator();
			m_config.AddMember(rapidjson::GenericValue<rapidjson::UTF16LE<>>(name.Pointer(), allocator),
					rapidjson::GenericValue<rapidjson::UTF16LE<>>(defaultValue), allocator);

			return defaultValue;
		}

		return m_config[name.Pointer()].GetInt();
	}

	I64 ConfigSubsystem::RequestInt64(const String& name, I64 defaultValue)
	{
		if(!m_config.HasMember(name.Pointer()))
		{
			ST_WARN(L"Could not find the \"{0}\" member in the configuration file.", name.Pointer());
			auto& allocator = m_config.GetAllocator();
			m_config.AddMember(rapidjson::GenericValue<rapidjson::UTF16LE<>>(name.Pointer(), allocator),
					rapidjson::GenericValue<rapidjson::UTF16LE<>>(defaultValue), allocator);

			return defaultValue;
		}

		return m_config[name.Pointer()].GetInt64();
	}

	F32 ConfigSubsystem::RequestFloat32(const String& name, F32 defaultValue)
	{
		if(!m_config.HasMember(name.Pointer()))
		{
			ST_WARN(L"Could not find the \"{0}\" member in the configuration file.", name.Pointer());
			auto& allocator = m_config.GetAllocator();
			m_config.AddMember(rapidjson::GenericValue<rapidjson::UTF16LE<>>(name.Pointer(), allocator),
					rapidjson::GenericValue<rapidjson::UTF16LE<>>(defaultValue), allocator);

			return defaultValue;
		}

		return m_config[name.Pointer()].GetFloat();
	}

	F64 ConfigSubsystem::RequestFloat64(const String& name, F64 defaultValue)
	{
		if(!m_config.HasMember(name.Pointer()))
		{
			ST_WARN(L"Could not find the \"{0}\" member in the configuration file.", name.Pointer());
			auto& allocator = m_config.GetAllocator();
			m_config.AddMember(rapidjson::GenericValue<rapidjson::UTF16LE<>>(name.Pointer(), allocator),
					rapidjson::GenericValue<rapidjson::UTF16LE<>>(defaultValue), allocator);

			return defaultValue;
		}

		return m_config[name.Pointer()].GetDouble();
	}

	bool ConfigSubsystem::RequestBool(const String& name, bool defaultValue)
	{
		if(!m_config.HasMember(name.Pointer()))
		{
			ST_WARN(L"Could not find the \"{0}\" member in the configuration file.", name.Pointer());
			auto& allocator = m_config.GetAllocator();
			m_config.AddMember(rapidjson::GenericValue<rapidjson::UTF16LE<>>(name.Pointer(), allocator),
					rapidjson::GenericValue<rapidjson::UTF16LE<>>(defaultValue), allocator);

			return defaultValue;
		}

		return m_config[name.Pointer()].GetBool();
	}

	ConfigSubsystem* ConfigSubsystem::Get()
	{
		return s_instance;
	}
}
