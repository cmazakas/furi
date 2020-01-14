function(furi_add_test test_name)
  add_executable(${test_name} "${test_name}.cpp")

  target_link_libraries(${test_name} PRIVATE furi)
  set_target_properties(${test_name} PROPERTIES FOLDER "Test")

  if (MSVC)
    target_link_libraries(${test_name} PRIVATE Boost::disable_autolinking)
  endif()

  add_test(${test_name} ${test_name})
endfunction()
