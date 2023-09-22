project(cmd)

file(GLOB_RECURSE EXAMPLES "*.cpp")
foreach (EXAMPLE_FILE ${EXAMPLES})
    get_filename_component(EXAMPLE ${EXAMPLE_FILE} NAME_WE)
    add_executable("example-${EXAMPLE}" ${EXAMPLE_FILE})
endforeach ()
