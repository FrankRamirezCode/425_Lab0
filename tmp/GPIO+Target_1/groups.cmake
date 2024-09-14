# groups.cmake

# group main
add_library(Group_main OBJECT
  "${SOLUTION_ROOT}/main.c"
)
target_include_directories(Group_main PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_main PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_main PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_main PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group src
add_library(Group_src OBJECT
  "${SOLUTION_ROOT}/GPIO.c"
  "${SOLUTION_ROOT}/SysTick_Delay.c"
)
target_include_directories(Group_src PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_src PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_src PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_src PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group inc
add_library(Group_inc INTERFACE)
target_include_directories(Group_inc INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${SOLUTION_ROOT}/.
)
target_compile_definitions(Group_inc INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
