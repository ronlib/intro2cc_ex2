ECHO OFF

.\Debug\sch.exe DRR .\tests\inp1.txt out.txt 1 2
fc /W out.txt ./tests/out1_DRR_w1_q2.txt

.\Debug\sch.exe DRR .\tests\inp1.txt out.txt 3 2
fc /W out.txt ./tests/out1_DRR_w3_q2.txt

.\Debug\sch.exe DRR .\tests\inp2.txt out.txt 1 10
fc /W out.txt ./tests/out2_DRR_w1_q10.txt

.\Debug\sch.exe DRR .\tests\inp2.txt out.txt 8 10
fc /W out.txt ./tests/out2_DRR_w8_q10.txt

.\Debug\sch.exe DRR .\tests\inp3.txt out.txt 1 40
fc /W out.txt ./tests/out3_DRR_w1_q40.txt

.\Debug\sch.exe DRR .\tests\inp3.txt out.txt 30 40
fc /W out.txt ./tests/out3_DRR_w30_q40.txt

.\Debug\sch.exe RR .\tests\inp1.txt out.txt 1 0
fc /W out.txt ./tests/out1_WRR_w1_q0.txt

.\Debug\sch.exe RR .\tests\inp1.txt out.txt 3 0
fc /W out.txt ./tests/out1_WRR_w3_q0.txt

.\Debug\sch.exe RR .\tests\inp2.txt out.txt 1 0
fc /W out.txt ./tests/out2_WRR_w1_q0.txt

.\Debug\sch.exe RR .\tests\inp2.txt out.txt 8 0
fc /W out.txt ./tests/out2_WRR_w8_q0.txt

.\Debug\sch.exe RR .\tests\inp3.txt out.txt 1 0
fc /W out.txt ./tests/out3_WRR_w1_q0.txt

.\Debug\sch.exe RR .\tests\inp3.txt out.txt 30 0
fc /W out.txt ./tests/out3_WRR_w30_q0.txt




.\Debug\sch.exe DRR .\tests2\inp1.txt out.txt 1 2
fc /W out.txt ./tests2/out1_DRR_w1_q2.txt

.\Debug\sch.exe DRR .\tests2\inp1.txt out.txt 3 2
fc /W out.txt ./tests2/out1_DRR_w3_q2.txt

.\Debug\sch.exe DRR .\tests2\inp2.txt out.txt 1 10
fc /W out.txt ./tests2/out2_DRR_w1_q10.txt

.\Debug\sch.exe DRR .\tests2\inp2.txt out.txt 8 10
fc /W out.txt ./tests2/out2_DRR_w8_q10.txt

.\Debug\sch.exe DRR .\tests2\inp3.txt out.txt 1 40
fc /W out.txt ./tests2/out3_DRR_w1_q40.txt

.\Debug\sch.exe DRR .\tests2\inp3.txt out.txt 30 40
fc /W out.txt ./tests2/out3_DRR_w30_q40.txt

.\Debug\sch.exe RR .\tests2\inp1.txt out.txt 1 0
fc /W out.txt ./tests2/out1_WRR_w1_q0.txt

.\Debug\sch.exe RR .\tests2\inp1.txt out.txt 3 0
fc /W out.txt ./tests2/out1_WRR_w3_q0.txt

.\Debug\sch.exe RR .\tests2\inp2.txt out.txt 1 0
fc /W out.txt ./tests2/out2_WRR_w1_q0.txt

.\Debug\sch.exe RR .\tests2\inp2.txt out.txt 8 0
fc /W out.txt ./tests2/out2_WRR_w8_q0.txt

.\Debug\sch.exe RR .\tests2\inp3.txt out.txt 1 0
fc /W out.txt ./tests2/out3_WRR_w1_q0.txt

.\Debug\sch.exe RR .\tests2\inp3.txt out.txt 30 0
fc /W out.txt ./tests2/out3_WRR_w30_q0.txt