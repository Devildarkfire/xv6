#!/bin/bash


#cd student_modified_files
#for i in $(ls -d */)
#ConnorMahlbacher/  FanruoGu/    kaichenzhang/    Oliver_Zhang/       WillElliott_has_all/  ziyue_zhou/ danielwhite/       Junda_An/    KaitlynHuynh/  Rui_Hou/  yangchenYeHw4/ ericnubbe/  JunzhaoSun/  Kevin_Rochford/  TimLesch_has_make/  YvonneSanchez/

#done: ConnorMahlbacher

for i in FanruoGu    kaichenzhang    Oliver_Zhang       WillElliott_has_all  ziyue_zhou danielwhite  Junda_An    KaitlynHuynh  Rui_Hou  yangchenYeHw4 ericnubbe  JunzhaoSun  Kevin_Rochford  TimLesch_has_make  YvonneSanchez

do		
	echo ----$i-----------------------------------------------------------
	
	rm -rf xv6-public
	cp -r xv6-public-org/ xv6-public/
	
	cp student_modified_files/$i/* xv6-public/ ####there could be a problem if students include their makefiles which do not make the testcases 

	python3 helper.py

	mkdir actual_output/$i -p
	cp xv6-public/out*.txt actual_output/$i
	
done




