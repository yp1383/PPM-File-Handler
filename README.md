# assignment-1-yp1383

Write a Image class that will handle different type of PPM files
P2, P3, P5, P6

Take P3 for example!

Frist we have two P3 type images:

![image](https://github.com/nyu-cs-cy-6533-fall-2020/assignment-1-yp1383/blob/master/images/Mandrill.jpg)

and

![image](https://github.com/nyu-cs-cy-6533-fall-2020/assignment-1-yp1383/blob/master/images/tandon_stacked_color.jpg)

There are several functions in image.cpp:  
  
Basic: loadPPM and savePPM.    
1. addPPM
2. additionPPM
3. subtractPPM
4. multiByScalePPM
5. gamma_corrected
6. alphaCompositingPPM

Let's see what these functions do!!!


addPPM:  
  
addPPM("out_file.ppm", image1, image2);  
    
![image](https://github.com/nyu-cs-cy-6533-fall-2020/assignment-1-yp1383/blob/master/images/add.jpg)  
  
  
  
additionPPM:  
  
additionPPM("out_file.ppm", image1, image2);
  
![image](https://github.com/nyu-cs-cy-6533-fall-2020/assignment-1-yp1383/blob/master/images/addition.jpg)  
  

subtractPPM:  
   
subtractPPM("out_file.ppm", image1, image2);
  
![image](https://github.com/nyu-cs-cy-6533-fall-2020/assignment-1-yp1383/blob/master/images/subtract.jpg)   
  
multiByScalePPM:    
  
multiByScalePPM("out_file.ppm", image1, scale);
   
![image](https://github.com/nyu-cs-cy-6533-fall-2020/assignment-1-yp1383/blob/master/images/multi.jpg)  
  
   
gamma_corrected for(4.f):  
  
gamma_corrected(4.f, image1);  
    
![image](https://github.com/nyu-cs-cy-6533-fall-2020/assignment-1-yp1383/blob/master/images/first.jpg)  
  
gamma_corrected for(0.25f):  
  
gamma_corrected(0.25f, image1);  
  
![image](https://github.com/nyu-cs-cy-6533-fall-2020/assignment-1-yp1383/blob/master/images/second.jpg)  
  
  
Which proof that gamma correction is not linear  
Just for extra fun, let's run it one more time!  
  
gamma_corrected for(0.25f):  
  
gamma_corrected(0.25f, image1);
  
![image](https://github.com/nyu-cs-cy-6533-fall-2020/assignment-1-yp1383/blob/master/images/third.jpg)  
  
  
  
alphaCompositing:  
  
alphaCompositingPPM("out_file", image1, alpha1, image2, alpha2)
  
![image](https://github.com/nyu-cs-cy-6533-fall-2020/assignment-1-yp1383/blob/master/images/alpha.jpg)  
  
