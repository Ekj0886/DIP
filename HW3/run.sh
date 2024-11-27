make
echo "\n<Task 1>" 
./HW3 --ShadesGrey 10 input/input1.bmp output/output1_1.bmp
./HW3 --ShadesGrey 10 input/input2.bmp output/output2_1.bmp
./HW3 --ShadesGrey 5 input/input3.bmp output/output3_1.bmp
./HW3 --ShadesGrey 2 input/input4.bmp output/output4_1.bmp
echo "\n<Task 2>" 
./HW3 --lumin 0.7 --Saturate 1.1 -s 0.5 output/output1_1.bmp output/output1_2.bmp
./HW3 --lumin 0.6 --Saturate 1.5 -s 0.2 output/output2_1.bmp output/output2_2.bmp
./HW3 --lumin 0.65 --Saturate 2.0 -s 0.5 output/output3_1.bmp output/output3_2.bmp
./HW3 --lumin 1.2 --Saturate 1.4 -s 0.5 output/output4_1.bmp output/output4_2.bmp
echo "\n<Task 3>"
./HW3 --Warm output/output1_2.bmp output/output1_3.bmp
./HW3 --Warm output/output2_2.bmp output/output2_3.bmp
./HW3 --Warm output/output3_2.bmp output/output3_3.bmp
./HW3 --Warm output/output4_2.bmp output/output4_3.bmp
./HW3 --Cold output/output1_2.bmp output/output1_4.bmp
./HW3 --Cold output/output2_2.bmp output/output2_4.bmp
./HW3 --Cold output/output3_2.bmp output/output3_4.bmp
./HW3 --Cold output/output4_2.bmp output/output4_4.bmp