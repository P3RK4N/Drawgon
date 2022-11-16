include "Dependencies.lua"

workspace "Tigraf"
   architecture "x64"
   startproject "Tigraf-ConsoleApp"
   configurations { "Debug", "Release", "Dist" }
   flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
   include "vendor/premake"
   include "Tigraf-Engine/vendor/glfw"
   include "Tigraf-Engine/vendor/glad"
--     include "GCEngine/vendor/imgui"
--     include "GCEngine/vendor/yaml-cpp"
--     include "GCEngine/vendor/Box2D"
group ""

group "Core"
   include "Tigraf-ConsoleApp"
   include "Tigraf-GUI"
   include "Tigraf-Engine"
group ""