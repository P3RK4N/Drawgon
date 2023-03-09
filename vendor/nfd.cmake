add_library(nfd)

target_sources(
   nfd
      PRIVATE
         "${Drawgon_SOURCE_DIR}/vendor/nfd/src/nfd_common.c"

         "${Drawgon_SOURCE_DIR}/vendor/nfd/src/include/nfd.h"
         "${Drawgon_SOURCE_DIR}/vendor/nfd/src/nfd_common.h"
         "${Drawgon_SOURCE_DIR}/vendor/nfd/src/common.h"
)

if(WIN32)

   target_sources(
      nfd
         PRIVATE
            "${Drawgon_SOURCE_DIR}/vendor/nfd/src/nfd_win.cpp"
   )

elseif(APPLE)

target_sources(
   nfd
      PRIVATE
         "${Drawgon_SOURCE_DIR}/vendor/nfd/src/nfd_cocoa.cpp"
)

elseif(UNIX)

target_sources(
   nfd
      PRIVATE
         "${Drawgon_SOURCE_DIR}/vendor/nfd/src/nfd_zenity.cpp"
)

else()

   message(FATAL_ERROR "Unsupported platform!")

endif()

target_compile_definitions(
   nfd
      PRIVATE "DNDEBUG"
)

target_include_directories(
   nfd
      PUBLIC "${Drawgon_SOURCE_DIR}/vendor/nfd/src/include"
)