#!/bin/bash

EXPECTED=expected_output

#for ACTUAL in actual_output/*
#ConnorMahlbacher/  FanruoGu/    kaichenzhang/    Oliver_Zhang/       WillElliott_has_all/  ziyue_zhou/ danielwhite/       Junda_An/    KaitlynHuynh/  Rui_Hou/  yangchenYeHw4/ ericnubbe/  JunzhaoSun/  Kevin_Rochford/  TimLesch_has_make/  YvonneSanchez/

#done: ConnorMahlbacher

#changed: TimLesch_has_make

#not compile at all: YvonneSanchez kaichenzhang

for ACTUAL in  FanruoGu    Oliver_Zhang       WillElliott_has_all  ziyue_zhou danielwhite  Junda_An    KaitlynHuynh  Rui_Hou  yangchenYeHw4 JunzhaoSun  Kevin_Rochford  TimLesch_no_make  ericnubbe
do

correct=0
total=0

for expected in $EXPECTED/*; do
    name=`basename $expected`
    actual=actual_output/$ACTUAL/$name
    total=$((total+1))
    echo "Comparing $expected and $actual"
    diff -w -B $expected $actual	
		if [ "$?" == "0" ]; then
			echo "Test Case Passed"
			correct=$((correct+1))
		else
			echo "Test Case Failed"
		fi
		echo ""
done
echo "Test Cases Passed: $correct"
echo "Test Cases Total: $total"


done

