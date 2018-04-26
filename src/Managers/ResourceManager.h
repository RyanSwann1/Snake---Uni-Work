#pragma once

#include <string>
#include <unordered_map>
#include <assert.h>
#include <utility>

template <class Resource>
class ResourceManager
{
public:
	ResourceManager()
		: m_resources()
	{

	}
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	void unloadAllResources()
	{
		m_resources.clear();
	}

	void addResource(std::string&& name)
	{
		assert(m_resources.find(name) == m_resources.cend());
		m_resources.emplace(std::move(name), loadResourceFromFile(name));
	}

	const Resource& getResource(const std::string& name) const
	{
		auto cIter = m_resources.find(name);
		//if(cIter != )
		assert(cIter != m_resources.cend());
		return cIter->second;
	}

protected:
	virtual Resource loadResourceFromFile(const std::string& fileName) const = 0;

private:
	std::unordered_map<std::string, Resource> m_resources;
};