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


MAKE CLEAN removes executable and backup files: 
	
	$ make clean 

MAKE FRESH deletes all .png files in img/ forder

	$ make fresh



