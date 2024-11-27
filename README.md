# sorting-visualizer
Provides a graphical visualization of currently 3 sorting algorithms: insertion sort, mergesort, and quicksort.

Created by Caleb Hansen in Fall 2024 using [SFML](https://www.sfml-dev.org/index.php).
## Building
If you use Linux, install SFML's dependencies using your system package manager. On Ubuntu and other Debian-based distributions you can use the following commands:
   ```
   sudo apt update
   sudo apt install \
       libxrandr-dev \
       libxcursor-dev \
       libudev-dev \
       libfreetype-dev \
       libopenal-dev \
       libflac-dev \
       libvorbis-dev \
       libgl1-mesa-dev \
       libegl1-mesa-dev
   ```

   You also must install CMake. After this, run the following commands in the root directory of the project to build the executable:

   ```
   cmake -B build
   cmake --build build
   ```

Alternatively, almost all popular IDEs have integrated CMake support.
