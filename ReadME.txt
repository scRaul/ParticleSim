Brute Force Particle Collision Simulator

Prerequisite: pnmtopng command 

TO BUILD executable open the terminal :

1. Change directory into the PPM4 directory 

       $ cd /path_to_PPM4_folder


2. Run make 

       $ make


TO RUN a simulation : 

1. Execute the sim.exe with 2 arguments, first # of particles
And second # of frames 
	
	$ ./sim 50 600

  (If no arguments provided default simulation will be of 
50 particles for 300 frames)

TO VIEW options: 

 1. Open up screen.html, after a bit of flickering, sim play smooth
 2. Use a video editing software to make a video of png images in img folder

MAKE CLEAN removes executable and backup files: 
	
	$ make clean 

MAKE FRESH deletes all .png files in img/ forder

	$ make fresh



