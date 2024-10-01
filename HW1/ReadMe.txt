DIP HW1 313510171

There're two ways to run this code:

-- Run by command: Self defined command with different options(option can be stacked)
1. $make
2. $./HW1 <option 1> <option 2> ... <option N> <input> <output>

<Options>:
  -f: Flip the image
  -r: Do quantization resolution, require a bit num value (2/4/6)
  -c: Crop the image (Later key in the parameters)


e.g.  $./HW1 -f input/input1.bmp output/output.bmp
      $./HW1 -f -r 2 -c input/input2.bmp output/output.bmp



-- Run by shell script(Recommanded): Generate all the requirment image for HW1
1. $chmod +x run
2. $./run 




Directory:
/input : contain input images input1.bmp, input2.bmp
/output: contain output images
/inc   : header files
/src   : source files