# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(MATH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/math)
set(MATH_SRC
${MATH_DIR}/SGF_Angles.cpp
${MATH_DIR}/SGF_Complex.cpp
${MATH_DIR}/SGF_Lcp.cpp
${MATH_DIR}/SGF_Math.cpp
${MATH_DIR}/SGF_Matriz.cpp
${MATH_DIR}/SGF_Ode.cpp
${MATH_DIR}/SGF_Plane.cpp
${MATH_DIR}/SGF_Pluecker.cpp
${MATH_DIR}/SGF_Polynomial.cpp
${MATH_DIR}/SGF_Quat.cpp
${MATH_DIR}/SGF_Rotation.cpp
${MATH_DIR}/SGF_Simd_Generic.cpp
${MATH_DIR}/SGF_Vector.cpp
)

if( NOT ANDROID)
set(MATH_SRC
${MATH_SRC}
${MATH_DIR}/SGF_Simd.cpp
)
endif()
# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
add_library (math_module STATIC ${MATH_SRC})
target_link_libraries(math_module exceptions_module)
