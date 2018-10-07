# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(MUGEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/mugen)
set(MUGEN_AST_SRC
${MUGEN_DIR}/Ast/Ast.cpp
${MUGEN_DIR}/Ast/AstManager.cpp
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (mugen_ast_module ${MUGEN_AST_SRC})
