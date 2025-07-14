#pragma once
#include "../Prerequisites.h"
#include "Component.h"

class Window;

/**
 * @class Entity
 * @brief Abstract base class representing a game entity with components.
 *
 * Entities manage components and define lifecycle methods for initialization, update, rendering, and cleanup.
 */
class Entity {
public:
    virtual ~Entity() = default;

    /**
     * @brief Initialize the entity.
     */
    virtual void start() = 0;

    /**
     * @brief Update the entity state.
     * @param deltaTime Time elapsed since last update.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Render the entity components.
     * @param window Shared pointer to the rendering window.
     */
    virtual void render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

    /**
     * @brief Cleanup resources used by the entity.
     */
    virtual void destroy() = 0;

    /**
     * @brief Add a component to the entity.
     * @tparam T Component type derived from Component.
     * @param component Shared pointer to the component.
     */
    template<typename T>
    void addComponent(EngineUtilities::TSharedPointer<T> component) {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        components.push_back(component.template dynamic_pointer_cast<Component>());
    }

    /**
     * @brief Retrieve a component of the specified type.
     * @tparam T Component type to retrieve.
     * @return Shared pointer to the component if found, nullptr otherwise.
     */
    template<typename T>
    EngineUtilities::TSharedPointer<T> getComponent() {
        for (auto& component : components) {
            auto specificComponent = component.template dynamic_pointer_cast<T>();
            if (specificComponent) {
                return specificComponent;
            }
        }
        return EngineUtilities::TSharedPointer<T>();
    }

protected:
    bool isActive = true; ///< Indicates whether the entity is active.
    uint32_t id = 0;      ///< Unique identifier for the entity.
    std::vector<EngineUtilities::TSharedPointer<Component>> components; ///< Components owned by the entity.
};