function(get_subdirectory_targets _TARGETS _SUBDIRECTORY)
    get_property(SUBDIRS DIRECTORY "${_SUBDIRECTORY}" PROPERTY SUBDIRECTORIES)
    foreach(SUBDIR IN LISTS SUBDIRS)
        get_subdirectory_targets(${_TARGETS} "${SUBDIR}")
    endforeach()
    get_property(SUBTARGETS DIRECTORY "${_SUBDIRECTORY}" PROPERTY BUILDSYSTEM_TARGETS)
    set(${_TARGETS} ${${_TARGETS}} ${SUBTARGETS} PARENT_SCOPE)
endfunction()

function(add_subdirectory_to_folder _SUBDIR _FOLDER)
    add_subdirectory(${_SUBDIR} ${ARGN})
    get_subdirectory_targets(SUBDIR_TARGTES "${_SUBDIR}")
    foreach(SUBDIR_TARGET IN LISTS SUBDIR_TARGTES)
        set_target_properties(
            ${SUBDIR_TARGET}
            PROPERTIES
                FOLDER "${_FOLDER}"
        )
    endforeach()
endfunction()

add_subdirectory_to_folder("googletest" "external/googletest")
