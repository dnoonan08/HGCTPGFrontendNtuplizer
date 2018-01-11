#! /usr/bin/env bash

# setup Python 2.7 and ROOT 6
source /opt/rh/devtoolset-2/enable
source /opt/exp_soft/llr/root/v6.06.00-el6-gcc48/bin/thisroot.sh
export python_path=/opt/exp_soft/llr/python/2.7.10
if [ "x$(which python 2>/dev/null)" != "x"$python_path"/bin/python" ] ; 
then
  export PATH=$python_path/bin:$PATH
  export LD_LIBRARY_PATH=$python_path/lib:$LD_LIBRARY_PATH
fi

export CC_NTUPLE_BASE=`pwd`
