project "Tigraf-Engine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   staticruntime "on"

   targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
   objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

   pcheader "PCH.h"
   pcsource "src/PCH.cpp"

   files
   {
      "src/**.h",
      "src/**.cpp",

   }
      
   defines
   {
   }

   includedirs
   {
      "src",
      Includes["Tigraf-GUI"],
      Includes["spdlog"]
   }

   links
   {
      "Tigraf-GUI"
   }

   filter "system:windows"
      systemversion "latest"


   filter "configurations:Debug"
      defines "TIGRAF_DEBUG"
      runtime "Debug"
      symbols "on"

   filter "configurations:Release"
      defines "TIGRAF_RELEASE"
      runtime "Release"
      optimize "on"


   filter "configurations:Dist"
      defines "TIGRAF_DIST"
      runtime "Release"
      optimize "on"
