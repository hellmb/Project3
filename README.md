# Project 3

This project is solved by implementing the forward Euler algorithm and the velocity Verlet algorithm. We created a class structure in C++ to solve all the exercises, and made python files to read data from the class files, before plotting our results. The programs runs as follows:

## main.cpp
Takes an input argument from command line. The argument differ from 1 to 5: 
- 1: Runs the Earth-Sun system (related python file: `eart_sun.py`)
- 2: Finds the escaping velocity of a planet around the Sun (related python file: `escape_velocity.py`)
- 3: Runs the three-body problem with the Sun, Earth and Jupiter (related python file: `jupiter_mass.py`). In this part of the program, you need to manually change the mass of Jupiter by adding lines that are commented out.
- 4: Creates a complete solar system, including Pluto (related python file: `plot_solarsystem.py`)
- 5: Finds the perihelion of Mercury (related python file: `mercury_perihelion.py`). In this part of the program, the force that is not used in the `verlet.cpp` file, needs to be manually commented out. This also applies to main, where you need to comment out the filename not used.

## Python files
- `earth_sun.py`: reads data from the textfile *positions.txt*.
- `escape_velocity.py`: reads data from the textfile *positions_escape.txt*.
- `jupiter_mass.py`: reads data from the textfile *positions_3body.txt*. In this program you need to manually change what the title of the plot will be, by adding lines about Jupiter's mass that are commented out.
- `plot_solarsystem.py`: reads data from the textfile *positions_system.txt*.
- `mercury_perihelion.py`: reads data from the textfile *perihelion_angle_GR.txt* and *perihelion_angle_pure.txt*. In this program you need to manually change between using a pure Newtonian solution or a general relativistic correction to the Newtonian force. This is done by changing which filename you excert the data from, by adding / commenting out the filename lines.
