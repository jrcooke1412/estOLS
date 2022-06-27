# Joseph R Cooke III
# Brown University
# Center for Computation and Visualization
# HPC Technical Assignment
# estOLS program

# Starting from Ubuntu 18.04
FROM ubuntu:18.04

# Updating apt-get and installing dependencies and Armadillo
RUN apt-get update && apt-get install -y \
g++ \
cmake \
libopenblas-dev \
liblapack-dev \
libarpack2-dev \
libsuperlu-dev \
libarmadillo-dev

# Coping estOLS to image, and building estOLS
RUN mkdir estOLS
COPY main.cpp estOLS/main.cpp

# Setting the working directory to be estOLS
WORKDIR estOLS

# Building estOLS and moving application to bin so it is 
# accessible throughout the container
RUN g++ main.cpp -o estOLS -std=c++17 -O2 -larmadillo
RUN cp ./estOLS  /bin