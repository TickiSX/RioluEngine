#pragma once

/**
 * @file BaseApp.h
 * @brief Defines the BaseApp class which manages the main application loop and rendering.
 */

#include "Prerequisites.h"
#include <Window.h>
#include "CShape.h"  ///< Included to match the instructor's code
#include "ECS/Actor.h"

 /**
  * @class BaseApp
  * @brief Main application class that controls initialization, main loop,
  * rendering, and resource cleanup.
  */
class BaseApp {
public:
    /**
     * @brief Default constructor.
     */
    BaseApp() = default;

    /**
     * @brief Destructor that releases allocated resources.
     */
    ~BaseApp();

    /**
     * @brief Runs the application.
     *
     * Initializes the application, enters the main loop,
     * and calls update and render methods.
     *
     * @return Exit code of the application.
     */
    int run();

    /**
     * @brief Initializes the window and application objects.
     *
     * @return true if initialization succeeds, false otherwise.
     */
    bool init();

    /**
     * @brief Updates the application logic (called every frame).
     */
    void update();

    /**
     * @brief Renders all drawable objects on the screen.
     */
    void render();

    /**
     * @brief Releases all allocated resources and performs cleanup.
     */
    void destroy();

private:
    EngineUtilities::TSharedPointer<Window> m_windowPtr; ///< Pointer to the main window (Window class).
    EngineUtilities::TSharedPointer<CShape> m_shapePtr;  ///< Pointer to the shape component (CShape).
    EngineUtilities::TSharedPointer<Actor>  m_ACircle;   ///< Actor representing a circular shape.
};