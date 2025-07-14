#include "BaseApp.h"
#include <ECS/Actor.h>

/**
 * @file BaseApp.cpp
 * @brief Implements the BaseApp class which manages the main application loop.
 */

BaseApp::~BaseApp() {
}

int BaseApp::run() {
    if (!init()) {
        ERROR("BaseApp", "run", "Initialization failed", "Exiting application");
        return -1;
    }

    while (m_windowPtr->isOpen()) {
        m_windowPtr->handleEvents();
        update();
        render();
    }

    destroy();
    return 0;
}

bool BaseApp::init() {
    m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "Onigiri Engine");
    if (!m_windowPtr) {
        ERROR("BaseApp", "init", "Failed to create window pointer, check memory allocation");
        return false;
    }

    m_shapePtr = EngineUtilities::MakeShared<CShape>();
    if (m_shapePtr) {
        m_shapePtr->createShape(ShapeType::CIRCLE);
        m_shapePtr->setFillColor(sf::Color::Yellow);
        m_shapePtr->setPosition(200.f, 150.f);
    }

    // Create Circle Actor
    m_ACircle = EngineUtilities::MakeShared<Actor>("Circle Actor");
    if (m_ACircle) {
        auto shape = m_ACircle->getComponent<CShape>();
        if (shape) {
            shape->createShape(CIRCLE);
            shape->setFillColor(sf::Color::Red);
        }

        auto transform = m_ACircle->getComponent<Transform>();
        if (transform) {
            transform->setPosition(sf::Vector2f(100.f, 150.f));
        }
    }

    return true;
}

void BaseApp::update() {
    if (!m_ACircle.isNull()) {
        m_ACircle->update(0);
    }
}

void BaseApp::render() {
    if (!m_windowPtr) {
        return;
    }

    m_windowPtr->clear();

    if (m_shapePtr) {
        m_shapePtr->render(m_windowPtr);
    }

    if (!m_ACircle.isNull()) {
        m_ACircle->render(m_windowPtr);
    }

    m_windowPtr->display();
}

void BaseApp::destroy() {
    // Smart pointers will clean up automatically.
}
