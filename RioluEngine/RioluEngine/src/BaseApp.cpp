#include "BaseApp.h"
#include <ECS/Actor.h>

/**
 * @file BaseApp.cpp
 * @brief Implements the BaseApp class which manages the main application loop.
 */

 /// Destructor de la clase BaseApp.
 /// Actualmente no hace nada porque los recursos se limpian en `destroy()`.
BaseApp::~BaseApp() {}

/// Ejecuta el bucle principal de la aplicación.
///
/// Inicializa, ejecuta el ciclo de eventos, actualiza y renderiza.
/// Finalmente libera recursos.
/// @return int 0 si la ejecución fue exitosa.
int BaseApp::run() {
    if (!init()) {
        ERROR("BaseApp", "run", "Initializes result on a false statement", "check method validations");
    }

    while (m_windowPtr->isOpen()) {
        m_windowPtr->handleEvents();
        update();
        render();
    }

    destroy();
    return 0;
}

/// Inicializa los recursos de la aplicación.
///
/// Crea la ventana, una figura base y un actor con forma de círculo que se moverá entre waypoints.
/// @return true si la inicialización fue exitosa.
bool BaseApp::init() {
    // Crear ventana
    m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "Onigiri Engine");
    if (!m_windowPtr) {
        ERROR("BaseApp", "init", "Failed to create window pointer, check memory allocation");
        return false;
    }

    // Crear figura estática amarilla
    m_shapePtr = EngineUtilities::MakeShared<CShape>();
    if (m_shapePtr) {
        m_shapePtr->createShape(ShapeType::CIRCLE);
        m_shapePtr->setFillColor(sf::Color::Yellow);
        m_shapePtr->setPosition(200.f, 150.f);
    }

    // Crear actor con componente CShape y Transform
    m_ACircle = EngineUtilities::MakeShared<Actor>("Circle Actor");
    if (m_ACircle) {
        auto shape = m_ACircle->getComponent<CShape>();
        auto transform = m_ACircle->getComponent<Transform>();

        shape->createShape(CIRCLE);
        shape->setFillColor(sf::Color::Red);
        transform->setPosition(sf::Vector2f(100.f, 150.f));

        // Waypoints de navegación
        m_waypoints = {
          {400.f, 150.f},
          {700.f, 300.f},
          {1000.f, 150.f},
          {1200.f, 500.f}
        };
    }

    return true;
}

/// Actualiza el estado de la aplicación.
///
/// Lógica de navegación del actor entre waypoints.
void BaseApp::update() {
    if (!m_windowPtr.isNull()) {
        m_windowPtr->update();
    }

    if (!m_ACircle.isNull() && !m_waypoints.empty()) {
        m_ACircle->update(m_windowPtr->deltaTime.asSeconds());

        sf::Vector2f currentPos = m_ACircle->getComponent<Transform>()->getPosition();
        sf::Vector2f targetPos = m_waypoints[m_currentWaypointIndex];

        float dx = targetPos.x - currentPos.x;
        float dy = targetPos.y - currentPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < 10.0f) {
            m_currentWaypointIndex = (m_currentWaypointIndex + 1) % m_waypoints.size();
        }

        m_ACircle->getComponent<Transform>()->seek(
            m_waypoints[m_currentWaypointIndex],
            200.0f,
            m_windowPtr->deltaTime.asSeconds(),
            10.0f
        );
    }
}

/// Renderiza el frame actual.
///
/// Limpia la pantalla, dibuja las figuras y muestra el resultado.
void BaseApp::render() {
    if (!m_windowPtr) return;

    m_windowPtr->clear();

    if (m_shapePtr) {
        m_shapePtr->render(m_windowPtr);
    }

    if (!m_ACircle.isNull()) {
        m_ACircle->render(m_windowPtr);
    }

    m_windowPtr->display();
}

/// Libera recursos utilizados.
///
/// Gracias al uso de punteros inteligentes, la limpieza es automática.
void BaseApp::destroy() {
    // No se requiere código explícito debido al uso de smart pointers.
}
