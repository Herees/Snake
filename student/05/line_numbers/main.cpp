#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string input_nimi, output_nimi = "";
    cout << "Input file: ";
    getline(cin, input_nimi);
    cout << "Output file: ";
    getline(cin, output_nimi);

    ifstream input(input_nimi);
    if (! input) {
        cout << "Error! The file " << input_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        string row;
        ofstream output(output_nimi);
        for(unsigned int i = 1; getline(input, row); i++){
            output << i << " " << row << endl;
        }
        output.close();
        input.close();
    }
}
