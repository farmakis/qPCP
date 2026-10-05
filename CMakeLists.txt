project( QPCP_LIB )

# This library is only intended to be built as part of the CloudCompare
# build tree (added as a submodule under CloudCompare/libs). It relies on
# CCCoreLib, which is built by CloudCompare/libs/qCC_db/extern and must
# already exist as a target by the time this subdirectory is processed.
add_library( ${PROJECT_NAME} STATIC )

add_subdirectory( include )
add_subdirectory( src )

target_link_libraries( ${PROJECT_NAME}
	PUBLIC
		CCCoreLib
)

target_compile_features( ${PROJECT_NAME} PUBLIC cxx_std_11 )

set_target_properties( ${PROJECT_NAME} PROPERTIES
	POSITION_INDEPENDENT_CODE ON
)

# Optional OpenMP support (used by OMPNumThreads.h / CutPursuit for parallelism)
if( NOT TARGET OpenMP::OpenMP_CXX )
	find_package( OpenMP QUIET )
endif()
if( TARGET OpenMP::OpenMP_CXX )
	target_link_libraries( ${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX )
else()
	message( STATUS "qPCP: OpenMP not found - building without parallelism" )
endif()
