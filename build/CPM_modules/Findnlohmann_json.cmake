include("/Users/rjacksonxyz/workspace/client-cpp/build/cmake/CPM.cmake")
CPMAddPackage("NAME;nlohmann_json;GITHUB_REPOSITORY;nlohmann/json;VERSION;3.11.2;OPTIONS;JSON_BuildTests OFF")
set(nlohmann_json_FOUND TRUE)