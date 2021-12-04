# cmake \
# -DCMAKE_PREFIX_PATH="/qt5-amiga" \
# -DCMAKE_FIND_ROOT_PATH="/opt/adtools" \
# -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY \
# -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY \
# -DCMAKE_SYSTEM_NAME="AmigaOS" \
# -DCMAKE_SYSTEM_PROCESSOR="PowerPC" \
# -DCMAKE_C_COMPILER="ppc-amigaos-gcc" \
# -DCMAKE_CXX_COMPILER="ppc-amigaos-g++" \
# -DCMAKE_ASM_COMPILER="ppc-amigaos-as" \
# -DCMAKE_MAKE_PROGRAM="make" \
# -DCMAKE_CXX_FLAGS_INIT="-mcrt=newlib -athread=native" \
# -DCMAKE_C_FLAGS_INIT="-mcrt=newlib" \
# -DUNIX=1 -DAMIGA=1 \
# -DCMAKE_INSTALL_PREFIX="/qt5-amiga" \
# -DQT_HOST_PATH="/usr/local/Qt-6.2.0" \
# -DQT_QMAKE_TARGET_MKSPEC=amiga-g++ \
# -DQT_FEATURE_thread=OFF \
# -DQT_FEATURE_network=OFF \
# -DQT_FEATURE_glib=OFF \
# -DQT_FEATURE_libudev=OFF \
# -DQT_FEATURE_evdev=OFF \
# ../amiga-test-qt6

cmake -DCMAKE_PREFIX_PATH="/qt5-amiga" \
-DCMAKE_FIND_ROOT_PATH="/opt/adtools" \
-DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY \
-DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY \
-DCMAKE_SYSTEM_NAME="Generic" \
-DCMAKE_SYSTEM_PROCESSOR="PowerPC" \
-DCMAKE_C_COMPILER="ppc-amigaos-gcc" \
-DCMAKE_CXX_COMPILER="ppc-amigaos-g++" \
-DCMAKE_ASM_COMPILER="ppc-amigaos-as" \
-DCMAKE_MAKE_PROGRAM="make" \
-DCMAKE_CXX_FLAGS_INIT="-mcrt=newlib -athread=native" \
-DCMAKE_C_FLAGS_INIT="-mcrt=newlib" \
-DUNIX=1 -DAMIGA=1 \
-DCMAKE_INSTALL_PREFIX="/qt5-amiga" \
-DQT_HOST_PATH="/usr/local/Qt-6.2.0" \
-DQT_QMAKE_TARGET_MKSPEC=amiga-g++ \
-DQT_FEATURE_thread=ON \
-DQT_FEATURE_network=ON \
-DQT_FEATURE_glib=OFF \
-DQT_FEATURE_libudev=OFF \
-DQT_FEATURE_evdev=OFF \
-DQT_FEATURE_concurrent=ON \
-DQT_FEATURE_sql=ON \
-DQT_FEATURE_future=ON \
-DQT_FEATURE_process=OFF \
-DQT_FEATURE_processenvironment=OFF \
-DQT_BUILD_TOOLS_WHEN_CROSSCOMPILING=false \
-DCMAKE_EXE_LINKER_FLAGS="-athread=native" \
../amiga-test-qt6/

# cmake \
# -DCMAKE_PREFIX_PATH="/usr/local/Qt-6.2.0" \
# -DCMAKE_INSTALL_PREFIX="/usr/local/Qt-6.2.0" \
# ..