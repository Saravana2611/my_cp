cmake_minimum_required(VERSION 3.14.4)

set(SRC_PATH "./")

project(my_copy C)

add_executable(${PROJECT_NAME} 
	${SRC_PATH}/main.c
	${SRC_PATH}/copy.c
	)
