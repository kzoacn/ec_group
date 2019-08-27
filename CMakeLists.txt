cmake_minimum_required (VERSION 2.8.11)
project (ecgroup)
set(NAME "ec_group")

include(cmake/common.cmake)
include(cmake/source_of_randomness.cmake)
include(cmake/threading.cmake)

find_package(OpenSSL REQUIRED)
find_package(relic REQUIRED)
find_package(GMP REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${RELIC_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${GMP_INCLUDE_DIR})


# Installation
set(sources
ec_group/group.cpp
)

add_library(${NAME} SHARED ${sources})

install(DIRECTORY emp-tool DESTINATION include/)
install(DIRECTORY cmake/ DESTINATION cmake/)
install(TARGETS ${NAME} DESTINATION lib)

# Test cases
macro (add_test _name)
	add_test_with_lib(${_name} "${NAME}")
endmacro()

add_test(ot)
