NXT Labyrinth Solver.
=========================================================
Nikos Papakonstantinou 2015
----------------------------

License
=========
NXT Labyrinth is free software; you can redistribute it and/or modify it 
under the terms
of the GNU General Public License as published by the Free Software Foundation;
either version 3, or (at your option) any later version.

NXT Labyrinth Solver is distributed in the  hope that  it will  be  useful, 
but  WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should  have received a copy of  the GNU General  Public License along with
NXT Labyrinth Solver; see the file LIECENCE.  If not, write to 
Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
USA.

General:
=========

NXT Labyrinth allows to an NXT Mindstorms to get out of a Labyrinth using the
"right hand rule". To use this firmware, you need two light sensors, one touch
sensor and two motors. The light sensors used as the right and left hand, the
touch sensor used for starting and stopping the NXT.

[Demo](https://dl.dropboxusercontent.com/u/6873550/MOV_0043.mp4)

Usage
=====

1) Build the NXT Mindstorms car and draw the Labyrinth.

2) Build the firmware

	make all

3) Download the firmware to Lego NXT Mindstorms

	make download

Optional:

4) Remove the object files

	make clean

5) Remove the elf and bin files

	make distclean
