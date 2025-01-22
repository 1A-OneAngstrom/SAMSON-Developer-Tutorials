#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {

    // we expect the program name plus two arguments: input file path and output file path
    if (argc != 3) {

        std::cerr << "Usage: " << argv[0] << " <input-file> <output-file>\n";
        return 1;

    }

    // retrieve the paths from the command-line arguments
    std::string inputFilePath = argv[1];
    std::string outputFilePath = argv[2];

    unsigned int numberOfAtoms;
    
    // open the input file
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {

        std::cerr << "Error: could not open input file: " << inputFilePath << "\n";
        return 1;

    }
    
    // open the output file
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {

        std::cerr << "Error: could not open output file: " << outputFilePath << "\n";
        return 1;

    }

    // read the number of atoms
    
    std::string line;
    std::getline(inputFile, line);
    std::stringstream firstLineParser(line);
    firstLineParser >> numberOfAtoms;
    
    if (!numberOfAtoms) {
    
        outputFile << "No atoms" << std::endl;
        return 0;
    
    }
    
    // read the coordinates of the atoms and update the barycenter
    
    double x_c = 0.0, y_c = 0.0, z_c = 0.0;
    
    while (std::getline(inputFile, line)) {
    
        std::stringstream lineParser(line);
        
        double x = 0.0, y = 0.0, z = 0.0;
        
        lineParser >> x >> y >> z;
        
        x_c += x;
        y_c += y;
        z_c += z;
    
    }
    
    x_c /= (double)numberOfAtoms;
    y_c /= (double)numberOfAtoms;
    z_c /= (double)numberOfAtoms;
    
    outputFile << x_c << "A " << y_c << "A " << z_c << "A" << std::endl;
    
    return 0;

}
