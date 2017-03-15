cmake_minimum_required(VERSION 3.0)
project(sdl_barebones)

include_directories(include $ENV{SDL2_ROOT}/include
							C:/Users/Public/Documents/Programming/Libraries/SDL2_ttf-2.0.12/include)
file(GLOB sources src/*.*)

add_executable(game ${sources})
target_link_libraries(game $ENV{SDL2_ROOT}/lib/x86/sdl2.lib C:/Users/Public/Documents/Programming/Libraries/SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.lib)

add_custom_command(TARGET game POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy
					$ENV{SDL2_ROOT}/lib/x86/sdl2.dll
					$<TARGET_FILE_DIR:game>
					)

add_custom_command(TARGET game POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy
					C:/Users/Public/Documents/Programming/Libraries/SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.dll
					$<TARGET_FILE_DIR:game>
					)

add_custom_command(TARGET game POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy
					C:/Users/Public/Documents/Programming/Libraries/SDL2_ttf-2.0.12/lib/x86/libfreetype-6.dll
					$<TARGET_FILE_DIR:game>
					)

add_custom_command(TARGET game POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy
					C:/Users/Public/Documents/Programming/Libraries/SDL2_ttf-2.0.12/lib/x86/zlib1.dll
					$<TARGET_FILE_DIR:game>
					)

add_custom_command(TARGET game POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${PROJECT_SOURCE_DIR}/images
					$<TARGET_FILE_DIR:game>
					)

add_custom_command(TARGET game POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${PROJECT_SOURCE_DIR}/fonts
					$<TARGET_FILE_DIR:game>
					)