//
// Brown University 
// CCV 
// HPC Technical Assignment
// Author: Joseph R. Cooke III
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <armadillo>
#include <chrono>

using namespace std;
using namespace arma;

mat ReadXMAT(string xMAT_input){
    // Opening XMAT text file
    ifstream inputX;
    inputX.open(xMAT_input,ios::in);

    // Declaring storage matrix
    mat X;

    // Storing data from text file to storage matrix
    X.load(inputX, raw_ascii);

    // Closing input file
    inputX.close();

    // Returning filled matrix
    return X;
}

vec ReadyVEC(string yVEC_input){
    // Opening yVEC text file
    ifstream inputY;
    inputY.open(yVEC_input,ios::in);
    
    // Declaring storage vector
    vec Y;
    
    // Storing data from text file to storage vector
    Y.load(inputY, raw_ascii);
    
    // Closing input file
    inputY.close();
    
    // Returning filled vector
    return Y;
}

vec CalculateBeta(mat X, vec Y){
    // Declaration of matrix and vector variables
    mat XT, XTX;
    vec Beta;

    // Taking the transpose of the input matrix X
    XT = X.t();
    
    // Completing the matrix multiplication
    XTX = XT*X;
    
    // Calculating Beta
    Beta = (inv(XTX))*XT*Y;

    // Returning Beta
    return Beta;
}

void DataWrite(string output_name, vec Beta){
    // Opening output file
    ofstream outputData;
    outputData.open(output_name,ios::out);

    // Need to specify arma because size() exists in both namespaces
    // Setting bounds for for loop to save data
    int m = arma::size(Beta)[0];

    // Writing to output file
    for(int i = 0; i < m; i++){
        outputData << Beta[i] << endl;
    }

    // Closing output file
    outputData.close();
}

int main(int argc, char** argv){
    // Start elapse time
    auto start_time = chrono::high_resolution_clock::now();

    // Declaration of expected inputs from command line and print error if it is different
    if(argc == 6){cout << "Wrong number of inputs. Please use format estOLS -x XMAT -y yVEC -o beta \n"; return 1;}

    // Declaration of string variables for XMAT, yVEC, amd output text files
    string xMAT_input, yVEC_input, output_name;

    // Read in XMAT text file name and store it to a string
    if(strcmp(argv[1],"-x") == 0){xMAT_input = argv[2];}
    else{cout << "Wrong input: Please use -x XMAT \n"; return 1;}

    // Read in yVEC text file name and store it to a string
    if(strcmp(argv[3],"-y") == 0){yVEC_input = argv[4];}
    else{cout << "Wrong input: Please use -y yVec \n"; return 1;}

    // Read in output name and store it to a string
    if(strcmp(argv[5],"-o") == 0){output_name = argv[6];}
    else{cout << "Wrong input: Please use -o output \n"; return 1;}

    // Start timing for XMAT read in
    auto start_time_X_ReadIn = chrono::high_resolution_clock::now();
    // Reading in XMAT
    mat X = ReadXMAT(xMAT_input);
    // Stop timing for XMAT read in
    auto stop_time_X_ReadIn = chrono::high_resolution_clock::now();

    // Start timing for yVEC read in
    auto start_time_Y_ReadIn = chrono::high_resolution_clock::now();
    // Reading in yVec
    vec Y = ReadyVEC(yVEC_input);
    // Stop timing for yVEC read in
    auto stop_time_Y_ReadIn = chrono::high_resolution_clock::now();

    // Start timing for Beta calculation
    auto start_time_Calculation = chrono::high_resolution_clock::now();
    // Calculate Beta
    vec Beta = CalculateBeta(X, Y);
    // Stop timing for Beta Calculation
    auto stop_time_Calculation = chrono::high_resolution_clock::now();
    
    // Output to screen
    cout << Beta << endl;

    // Start timing for data write
    auto start_time_DataWrite = chrono::high_resolution_clock::now();
    // Writing data to text file
    DataWrite(output_name, Beta);
    // Stop timing for data write
    auto stop_time_DataWrite = chrono::high_resolution_clock::now();

    // Stop elapse timing
    auto stop_time = chrono::high_resolution_clock::now();

    // Calculate timing for each of the functions
    auto elapse_time_X_ReadIn = chrono::duration_cast<chrono::milliseconds>(stop_time_X_ReadIn - start_time_X_ReadIn);
    auto elapse_time_Y_ReadIn = chrono::duration_cast<chrono::milliseconds>(stop_time_Y_ReadIn - start_time_Y_ReadIn);
    auto elapse_time_Calculation = chrono::duration_cast<chrono::milliseconds>(stop_time_Calculation - start_time_Calculation); 
    auto elapse_time_DataWrite = chrono::duration_cast<chrono::milliseconds>(stop_time_DataWrite - start_time_DataWrite); 
    auto elapse_time = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time);

    // Output to screen the timing results in milliseconds.
    cout << "The elapse time was " << elapse_time.count() << " milliseconds" << endl;
    cout << "The elapse time for XMAT read in was " << elapse_time_X_ReadIn.count() << " milliseconds" << endl;
    cout << "The elapse time for yVEC read in was " << elapse_time_Y_ReadIn.count() << " milliseconds" << endl;
    cout << "The elapse time for estimator calculation was " << elapse_time_Calculation.count() << " milliseconds" << endl;
    cout << "The elapse time for data write was " << elapse_time_DataWrite.count() << " milliseconds" << endl;

    return 0;
}