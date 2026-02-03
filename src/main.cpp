#include <iostream>
#include <chrono>
#include <string>

#include "TRA/ecs/world.hpp"
#include "TRA/ecs/component.hpp"
#include "TRA/ecs/tag.hpp"

constexpr size_t LOOP_COUNT = 10;
constexpr uint32_t ENTITY_COUNT = 1000000;
constexpr size_t COMPONENTS_PER_ENTITY = 5;

using namespace tra;

TRA_ECS_REGISTER_TAG(IsAliveTag)

TRA_ECS_REGISTER_COMPONENT(PositionComponent,
	float m_x = 0;
	float m_y = 0;
)

TRA_ECS_REGISTER_COMPONENT(VelocityComponent,
	float m_x = 0;
	float m_y = 0;
)

TRA_ECS_REGISTER_COMPONENT(DataComponent,
	std::string m_name;
	int m_gold = 9999;

	DataComponent(const std::string& _name) : m_name(_name) {}
)

TRA_ECS_REGISTER_COMPONENT(HealthComponent,
	int m_health = 100;
)

TRA_ECS_REGISTER_COMPONENT(DamageComponent,
	int m_damage = 0;
)

int main()
{
	std::chrono::high_resolution_clock mainClock;
	std::chrono::time_point start = mainClock.now();
	std::chrono::time_point end = mainClock.now();

	long long createEntityDuration = 0;
	long long addComponentDuration = 0;
	long long getComponentDuration = 0;
	long long setComponentDuration = 0;
	long long removeComponentDuration = 0;
	long long destroyEntityDuration = 0;

	std::vector<ecs::Entity> entities;
	entities.resize(ENTITY_COUNT, ecs::NULL_ENTITY);


	for (size_t i = 0; i < LOOP_COUNT; i++)
	{
		ecs::World ecsWorld;

		//////////////////////////////////////////////////////////////

		start = mainClock.now();

		for (size_t i = 0; i < ENTITY_COUNT; i++)
		{
			entities[i] = ecsWorld.createEntity();
		}

		end = mainClock.now();

		createEntityDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

		//////////////////////////////////////////////////////////////

		start = mainClock.now();

		for (size_t i = 0; i < ENTITY_COUNT; i++)
		{
			ecsWorld.addComponent(entities[i], ecs::PositionComponent{});
			ecsWorld.addComponent(entities[i], ecs::VelocityComponent{});
			ecsWorld.addComponent(entities[i], ecs::DataComponent{"Player-" + std::to_string(i)});
			ecsWorld.addComponent(entities[i], ecs::HealthComponent{});
			ecsWorld.addComponent(entities[i], ecs::DamageComponent{});
		}

		end = mainClock.now();

		addComponentDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

		//////////////////////////////////////////////////////////////

		start = mainClock.now();

		for (size_t i = 0; i < ENTITY_COUNT; i++)
		{
			ecsWorld.getComponent<ecs::PositionComponent>(entities[i]);
			ecsWorld.getComponent<ecs::VelocityComponent>(entities[i]);
			ecsWorld.getComponent<ecs::DataComponent>(entities[i]);
			ecsWorld.getComponent<ecs::HealthComponent>(entities[i]);
			ecsWorld.getComponent<ecs::DamageComponent>(entities[i]);
		}

		end = mainClock.now();

		getComponentDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

		//////////////////////////////////////////////////////////////

		start = mainClock.now();

		for (size_t i = 0; i < ENTITY_COUNT; i++)
		{
			ecsWorld.setComponent(entities[i], ecs::PositionComponent{});
			ecsWorld.setComponent(entities[i], ecs::VelocityComponent{});
			ecsWorld.setComponent(entities[i], ecs::DataComponent{ "Player-" + std::to_string(i) });
			ecsWorld.setComponent(entities[i], ecs::HealthComponent{});
			ecsWorld.setComponent(entities[i], ecs::DamageComponent{});
		}

		end = mainClock.now();

		setComponentDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

		//////////////////////////////////////////////////////////////

		start = mainClock.now();

		for (size_t i = 0; i < ENTITY_COUNT; i++)
		{
			ecsWorld.removeComponent<ecs::DamageComponent>(entities[i]);
			ecsWorld.removeComponent<ecs::HealthComponent>(entities[i]);
			ecsWorld.removeComponent<ecs::DataComponent>(entities[i]);
			ecsWorld.removeComponent<ecs::VelocityComponent>(entities[i]);
			ecsWorld.removeComponent<ecs::PositionComponent>(entities[i]);
		}

		end = mainClock.now();

		removeComponentDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

		//////////////////////////////////////////////////////////////

		start = mainClock.now();

		for (size_t i = 0; i < ENTITY_COUNT; i++)
		{
			ecsWorld.destroyEntity(entities[i]);
		}

		end = mainClock.now();

		destroyEntityDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

		//////////////////////////////////////////////////////////////
	}

	std::cout << "Result:" << std::endl;
	std::cout << std::endl;
	std::cout << "Average time to create an entity: " << std::to_string(createEntityDuration / LOOP_COUNT / ENTITY_COUNT) << " nanoseconds" << std::endl;
	std::cout << std::endl;
	std::cout << "Average time to add a component to an entity: " << std::to_string(addComponentDuration / LOOP_COUNT / COMPONENTS_PER_ENTITY / ENTITY_COUNT) << " nanoseconds" << std::endl;
	std::cout << std::endl;
	std::cout << "Average time to get a component to an entity: " << std::to_string(getComponentDuration / LOOP_COUNT / COMPONENTS_PER_ENTITY / ENTITY_COUNT) << " nanoseconds" << std::endl;
	std::cout << std::endl;
	std::cout << "Average time to set a component to an entity: " << std::to_string(setComponentDuration / LOOP_COUNT / COMPONENTS_PER_ENTITY / ENTITY_COUNT) << " nanoseconds" << std::endl;
	std::cout << std::endl;
	std::cout << "Average time to remove a component to an entity: " << std::to_string(removeComponentDuration / LOOP_COUNT / COMPONENTS_PER_ENTITY / ENTITY_COUNT) << " nanoseconds" << std::endl;
	std::cout << std::endl;
	std::cout << "Average time to destroy an entity: " << std::to_string(destroyEntityDuration / LOOP_COUNT / ENTITY_COUNT) << " nanoseconds" << std::endl;

	return 0;
}