set(EJFF_SRC_ROOT_DIR "${PROJECT_SOURCE_DIR}/src/ejff")

set(EJFF_SOURCES
    "${EJFF_SRC_ROOT_DIR}/gpu/resources/buffer.cpp"
    "${EJFF_SRC_ROOT_DIR}/gpu/resources/command_buffer.cpp"
    "${EJFF_SRC_ROOT_DIR}/gpu/resources/copy_pass.cpp"
    "${EJFF_SRC_ROOT_DIR}/gpu/resources/graphics_pipeline.cpp"
    "${EJFF_SRC_ROOT_DIR}/gpu/resources/render_pass.cpp"
    "${EJFF_SRC_ROOT_DIR}/gpu/resources/sampler.cpp"
    "${EJFF_SRC_ROOT_DIR}/gpu/resources/shader.cpp"
    "${EJFF_SRC_ROOT_DIR}/gpu/resources/texture.cpp"
    "${EJFF_SRC_ROOT_DIR}/gpu/resources/transfer_buffer.cpp"
    "${EJFF_SRC_ROOT_DIR}/gpu/resources/vertex.cpp"
    "${EJFF_SRC_ROOT_DIR}/gpu/device.cpp"
    "${EJFF_SRC_ROOT_DIR}/application.cpp"
    "${EJFF_SRC_ROOT_DIR}/main.cpp"
    "${EJFF_SRC_ROOT_DIR}/surface.cpp"
    "${EJFF_SRC_ROOT_DIR}/window.cpp"
)