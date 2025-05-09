include("E:/C++/Tune/build/Desktop_Qt_6_9_0_MinGW_64_bit-Release/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Tune-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase;qtmultimedia")

qt6_deploy_runtime_dependencies(
    EXECUTABLE E:/C++/Tune/build/Desktop_Qt_6_9_0_MinGW_64_bit-Release/Tune.exe
    GENERATE_QT_CONF
)
