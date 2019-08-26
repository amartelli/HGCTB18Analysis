#!/bin/bash

float_scale=2
function float_eval()
{
    local stat=0
    local result=0.0
    if [[ $# -gt 0 ]]; then
        result=$(echo "scale=$float_scale; $*" | bc -q 2>/dev/null)
        stat=$?
        if [[ $stat -eq 0  &&  -z "$result" ]]; then stat=1; fi
    fi
    echo $result
    return $stat
}

Par="Ele"
#DataType="Data"
DataType="MC"
#TagMC="BeamProf_v1"
TagMC="v2_withMCP_EMN_Angle"
TagData="v13"

En=( 20 30 50 80 100 120 200 250 300 )
#En=( 30 100 250 )

EnSize=${#En[@]}

if [ "$DataType" == "Data" ]
then 
    echo "running on Data..."
    echo "mkdir -p ${DataType}/${TagData}"
    mkdir -p ${DataType}/${TagData}
    TagDir="$TagData"
else 
    echo "running on MC..."
    echo "mkdir -p ${DataType}/${TagMC}"
    mkdir -p ${DataType}/${TagMC}
    TagDir="$TagMC"
fi

cp HGCTBAna.C  HGCTBAna.h  HGCTBAlgo.C main.C Makefile $DataType/$TagDir
cp *TEMPLATE* $DataType/$TagDir
cd $DataType/$TagDir

for (( iEn=0; iEn<${EnSize}; iEn++ ))
do
    echo ======================== Beam Energy ${En[$iEn]} GeV ====================

    sed s/'#Energy#'/${En[$iEn]}/ < EXEC_TEMPLATE.sh |
    sed s/'#DataType#'/${DataType}/ |
    sed s/'#Par#'/${Par}/ |
    sed s/'#TagData#'/${TagData}/ |
    sed s/'#TagMC#'/${TagMC}/ > exec_${Par}${En[$iEn]}GeV.sh
    echo created exec_${Par}${En[$iEn]}GeV.sh
    sed s/'#Energy#'/${En[$iEn]}/ < CONDOR_TEMPLATE.sub |
    sed s/'#Par#'/${Par}/ > condor_${Par}${En[$iEn]}GeV.sub
    echo created condor_${Par}${En[$iEn]}GeV.sub
    condor_submit condor_${Par}${En[$iEn]}GeV.sub
done
