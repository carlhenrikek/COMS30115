set(APP_NAME "starfield")
set(APP_MODULE_PATH "${PROJECT_SOURCE_DIR}/${APP_NAME}")
set(APP_SRC_PATH "${APP_MODULE_PATH}/Source")

file(GLOB APP_SOURCE_FILES "${APP_SRC_PATH}/*.cpp")

add_executable(${APP_NAME} ${APP_SOURCE_FILES})

include_directories(
    ${OPENGL_INCLUDE_PATH}
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TFF_INCLUDE_DIR}
)
target_link_libraries(${APP_NAME} 
    ${OPENGL_LIB}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
