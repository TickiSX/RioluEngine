#pragma once

#include "../Prerequisites.h"
#include "Entity.h"
#include "CShape.h"
#include "Transform.h"

/**
 * @file Actor.h
 * @brief Declares the Actor class which represents an active entity in the game world.
 */

 /**
  * @class Actor
  * @brief Represents an active entity in the game world that can have components, be updated, rendered, and destroyed.
  * Inherits from Entity.
  */
class Actor : public Entity {
public:
    /**
     * @brief Default constructor for Actor.
     */
    Actor() = default;

    /**
     * @brief Constructor that initializes the Actor with a name.
     * @param actorName Name to assign to the actor.
     */
    Actor(const std::string& actorName);

    /**
     * @brief Default virtual destructor for Actor.
     */
    virtual ~Actor() = default;

    /**
     * @brief Method called when the Actor starts. Can be used to initialize components.
     */
    void start() override;

    /**
     * @brief Method called every frame to update the Actor's state.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;

    /**
     * @brief Renders the Actor to the provided window.
     * @param window Shared pointer reference to the window where the actor is rendered.
     */
    void render(const EngineUtilities::TSharedPointer<Window>& window) override;

    /**
     * @brief Method called to destroy the Actor and clean up resources.
     */
    void destroy() override;

    /**
     * @brief Retrieves a component of the specified type if it exists on the Actor.
     * @tparam T Type of the component to find.
     * @return Shared pointer to the component of type T if found; nullptr otherwise.
     */
    template <typename T>
    EngineUtilities::TSharedPointer<T> getComponent();

private:
    /**
     * @brief Name of the actor.
     */
    std::string m_name = "Actor";
};

/**
 * @brief Template implementation of getComponent.
 * @tparam T Type of component to find.
 * @return Shared pointer to the component of type T if found; nullptr otherwise.
 */
template <typename T>
inline EngineUtilities::TSharedPointer<T> Actor::getComponent() {
    for (auto& component : components) {
        EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
        if (specificComponent) {
            return specificComponent;
        }
    }
    return EngineUtilities::TSharedPointer<T>();
}
