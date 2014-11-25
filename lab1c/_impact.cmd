setMode -bs
setMode -bs
setCable -port auto
Identify 
identifyMPM 
assignFile -p 5 -file "/homes/ugrad/billlipeng/ecen449/lab1c/jackpot.bit"
Program -p 5 
setMode -bs
deleteDevice -position 1
deleteDevice -position 1
deleteDevice -position 1
deleteDevice -position 1
deleteDevice -position 1
setMode -ss
setMode -sm
setMode -hw140
setMode -spi
setMode -acecf
setMode -acempm
setMode -pff
setMode -bs
