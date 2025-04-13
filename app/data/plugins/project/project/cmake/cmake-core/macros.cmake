# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

if(NOT COMMAND find_host_program)
	macro(find_host_program)
		find_program(${ARGN})
	endmacro()
endif()
