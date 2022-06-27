# estOLS

* Author: Joseph R. Cooke III
* Brown University
* Center for Computation and Visualization
* HPC Technical Assignment
-----
estOLS is a C++ program to calculate the estimates from an ordinary least square calculation using matrix vector operations. 

Files contained in this directory:

- **benchmark** &emsp; &emsp; &nbsp; XMAT and yVEC text files used for the benchmark
- **doc** &emsp; &emsp; &emsp; &emsp; &emsp; &nbsp; File containing benchmark report
- **examples** &emsp; &emsp; &ensp; &nbsp; Example XMAT and yVEC input files
- **src** &emsp; &emsp; &emsp; &emsp; &emsp; &nbsp; File containing source to build estOLS
- **README.md** &emsp; &nbsp; &nbsp; This file which contains install and operating instructions
-----------------------------------------------------------------------------------------------------------
## **Installation instructions:**

estOLS requires the Armadillo science library for C++. To install Armadillo, the following dependances need to be installed g++, CMake, OpenBLAS, LAPACK, ARPACK, and SuperLU. These programs and libraries can be acquired and installed from apt-get with the following command inside of a terminal window:

`sudo apt-get install g++, cmake, libopenblas-dev, liblapack-dev, libarpack2-dev, libsuperlu-dev`

Enter the above command without quotations and it will ask you for your password and confirmation to install the packages. To install the Armadillo library use the following command:

`sudo apt-get install libarmadillo-dev`

Enter the above command without quotations and it will ask you for your password and confirmation to install the packages.

To compile and build estOLS, move to the /src directory in the estOLS folder and enter the following command without quotations in the terminal:

`g++ main.cpp -o elsOLS -std=c++17 -O2 -larmadillo`

To make elsOLS accessible anywhere in the terminal, enter the following command without quotations to copy the application to the bin directory:

`cp ./estOLS  /bin`

-----

## **Running estOLS natively:**

To run the application, have the built application "estOLS" in a folder with your XMAT and yVEC files or have it installed in the bin directory. 

Navigate to the location of the data in your terminal window and run the following command without quotations:

`./elsOLS -x X.txt -y Y.txt -o beta.txt`

where "X.txt" is the space or tab delimited X matrix text file, "Y.txt" is the Y vector in a text file, and "beta.txt" is the output file name. Examples of the input files can be found the the \examples directory in the estOLS program.

-----

## **Running estOLS in Docker:**

With Docker installed, open up a terminal window and navigate to the docker folder in the estOLS directory. Run the following command to build the docker container: 

`docker build -t est-ols .`

Locate the directory where your matrix and vector data is located in via a terminal window and use the "pwd" command in terminal to obtain the absolute path directory. In a terminal window with the docker directory open, run the following command in the estOLS directory with ABSOLUTE_DATA_LOCATION changed to the directory where the the matrix and vector data is stored:

`docker run -v "ABSOLUTE_DATA_LOCATION:/estOLS" -i -t est-ols /bin/bash`

With the docker container now open, navigate to the directory that contains the X matrix text file and Y vector in that terminal window and enter the following command in the terminal without quotations to run the estOLS program:

`./elsOLS -x X.txt -y Y.txt -o beta.txt`

where "X.txt" is the space or tab delimited X matrix text file, "Y.txt" is the Y vector in a text file, and "beta.txt" is the output file name.
