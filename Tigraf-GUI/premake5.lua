project "Tigraf-GUI"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   staticruntime "on"

   targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
   objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

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
      Includes["spdlog"]
   }

   links
   {
   }

   filter "system:windows"
      systemversion "latest"
      defines
      {
      }
      links
		{
		}


   filter "configurations:Debug"
      defines "TIGRAF_DEBUG"
      runtime "Debug"
      symbols "on"
      
      links
      {
      }

   filter "configurations:Release"
      defines "TIGRAF_RELEASE"
      runtime "Release"
      optimize "on"

      links
		{
		}

   filter "configurations:Dist"
      defines "TIGRAF_DIST"
      runtime "Release"
      optimize "on"

      links
		{
		}