#Automated Gigapixel Camera#
by Kyle Tingey and Reuben Fishback

#Goal#
Create a camera mount that will automatically pan and tilt across the horizon caputuring many images that can later be stitched together 
to form one large high-quality image.

#Background#
A gigapixel image is a digital image bitmap composed of one billion (109) pixels (picture elements), 1000 times the information captured 
by a 1 megapixel digital camera. Current technology for creating such very high-resolution images usually involves either making mosaics 
of a large number of high-resolution digital photographs or using a film negative as large as 12" 9" (30 cm 23 cm) up to 18" 9" (46 cm 23 
cm), which is then scanned with a high-end large-format film scanner with at least 3000 dpi resolution. Aims. Create a unique robotic 
camera mount that empowers most small digital cameras with the ability to capture gigapixel images. Methods. Two servos will position the 
camera controlled by the STM32F3 microcontroller. The camera will take a picture and then the servos will reposition, continuing until the
grid of photos is complete. The built in software works out how many photos your camera will need to take, hundreds or even thousands.  

#Hardware#
###Microcontroller: STM32F3 Nucleo board###

We chose this board because of its small size and similarities to the STM32F0 boards we were familiar with from lab.

###Servo Motors###
Camera mount needs two directions of control, the pan or left to right motion and the tilt or the up and down motion. 

Our design constraint for the pan was that it needed to rotate 360 degrees. To accomplish this we used a continuous servo. It was controlled with PWM. When the PWM was turned on the servo would rotate left or right depending on the duty cycle and stop when the PWM signal was suppressed.

For the tilt control we used a 180 degree traditional servo. After connecting the servo to our device we tested inputs to find an equation that would give us degrees in rotation for every tenth of a millisecond we changed the duty cycle.

###IR Led:###

We wanted to use two different cameras, a Nikon D60 and a Sony A6000. Each had a different IR trigger protocol. We used an IR Led to capture images hands free.

###Aluminum Mount:###

A custom pan-tilt mount was designed in CAD and cut from ¼” aluminum sheet using a waterjet.  This process included quite a bit of modeling that helped determine what size motors we would be able to use. Our system is rated for a camera/lens combination weighing up to 7.5 lbs, perfect for our use.  

###Power:###

The servos and our microcontroller required different power needs. The servos run on six volts while the STM board uses typically five. For the system to work properly we used one six volt pack to power the servos and another nine volt battery to power the STM board. During our testing we found that the five volt would turn the board on but it would not run our code. We referenced the data sheet and discovered that the board could be powered with nine volts.

#Software#

###IR Led:###

We used two timers and an interrupt for the IR led control. One timer controlled the carrier frequency of 40KHz and the other timer controlled the envelope signal. The timer was controlled on an interrupt. Every time the interrupt was triggered the program advanced one position in the array containing our sequence.

###Servos:###

Both servos were powered with six volts and had a duty cycle that ranged from 5% to 10% of the 20ms period.

#Stitching#

Once the completed mount and control was finished we took it on a test drive. Below is the image we were able to capture. It consists of a 3X4 grid. The image was stitched using Photoshop.

![alt text](https://github.com/ktingey/portfolio/blob/master/giga.pix/results/NikonD60PanoFromU.jpg)

#Demo#

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/iDO9gcb2CD4/0.jpg)](https://www.youtube.com/watch?v=iDO9gcb2CD4)
