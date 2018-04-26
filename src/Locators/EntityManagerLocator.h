#pragma once

#include <assert.h>

class EntityManager;
class EntityManagerLocator
{
public:
	EntityManagerLocator() = delete;

	static void provide(EntityManager& entityManager)
	{
		m_entityManager = &entityManager;
	}

	static EntityManager& get()
	{
		assert(m_entityManager);
		return *m_entityManager;
	}

private:
	static EntityManager* m_entityManager;
};