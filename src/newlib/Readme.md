This folder contains essential files to port newlib

Docker build downloads newlib source and copies files in this folder to the proper places, then builds.

unfortunately, I could not find a better way to modify configuration files, 
thus keeping the hand-modified versions of them in the repository.
This method must be abandoned. 
It is ugly and most likely coupled to a specific version of newlib. 
