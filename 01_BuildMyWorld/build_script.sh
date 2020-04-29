MYDIR=$(pwd)
echo ${MYDIR}
mkdir build
cd build/
cmake ../
make
export GAZEBO_PLUGIN_PATH="${GAZEBO_PLUGIN_PATH}:${MYDIR}/build"
cd ../world
gazebo myworld
