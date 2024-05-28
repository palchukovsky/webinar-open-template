cmake_minimum_required(VERSION 3.5)

project(templates)

add_executable(motivation motivation.cpp)
add_executable(f_template funс_template.cpp)
add_executable(f_template_specialization func_template_specialization.cpp)
add_executable(template_val template_val.cpp)
add_executable(template_type template_type.cpp)
add_executable(policy policy.cpp)

set_target_properties(
    motivation
    f_template
    f_template_specialization
    template_val
    template_type
    policy
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)
