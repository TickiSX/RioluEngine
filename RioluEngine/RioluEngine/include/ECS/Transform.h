#pragma once

/**
 * @file Transform.h
 * @brief Declares the Transform component, managing position, rotation, and scale.
 */

#include <SFML/System/Vector2.hpp>
#include "ECS/Component.h"

class Window;

/**
 * @class Transform
 * @brief Component storing position, rotation, and scale data for an entity.
 */
class Transform : public Component {
public:
    /**
     * @brief Default constructor initializes position, rotation, and scale.
     */
    Transform()
        : Component(ComponentType::TRANFORM),
        m_position(0.f, 0.f),
        m_rotation(0.f, 0.f),
        m_scale(1.f, 1.f) {
    }

    /**
     * @brief Default virtual destructor.
     */
    virtual ~Transform() = default;

    // ECS lifecycle overrides

    /**
     * @brief Initialize component (no deltaTime needed).
     */
    void start() override;

    /**
     * @brief Update component every frame (empty).
     * @param deltaTime Time since last frame.
     */
    void update(float deltaTime) override {}

    /**
     * @brief Render component (no rendering required).
     * @param window Shared pointer to render window.
     */
    void render(const EngineUtilities::TSharedPointer<Window>& window) override {}

    /**
     * @brief Cleanup resources (no action required).
     */
    void destroy() override {}

    // Setters

    void setPosition(const sf::Vector2f& position) { m_position = position; }
    void setRotation(const sf::Vector2f& rotation) { m_rotation = rotation; }
    void setScale(const sf::Vector2f& scale) { m_scale = scale; }

    // Getters

    sf::Vector2f getPosition() const { return m_position; }
    sf::Vector2f getRotation() const { return m_rotation; }
    sf::Vector2f getScale() const { return m_scale; }

private:
    sf::Vector2f m_position;
    sf::Vector2f m_rotation;
    sf::Vector2f m_scale;
};
