#include "func.h"

map<string, int> init(){
    map<string, int> commands;
    commands["invalid"] = 0;
    commands["--help"] = 1;
    commands["--exit"] = 2;
    commands["--run"] = 3;
    commands["--read"] = 4;
    commands["--cd"] = 5;

    cout << "\n==================================================================\n";
    cout << "Welcome to tri-compiler! Print --help to check available commands.";
    cout << "\n==================================================================\n";
    cout << "\nPrint --help to check available commands\n";

    return commands;
}

vector<string> split(string s, string separator){
    vector<string> output;
    string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(separator, pos)) != string::npos)
    {
        string substring( s.substr(prev_pos, pos-prev_pos) );
        output.push_back(substring);
        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word

    return output;
}

void run_txt(string filename){
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        return;
    }

    string language;
    getline(file, language);

    string code;
    string line;
    while (getline(file, line)) {
        code += line + "\n";
    }
    file.close();

    string tempFilename;
    string command;
    if (language == "C++") {
        tempFilename = "temp.cpp";
        ofstream file1(tempFilename);
        file1 << code;
        file1.close();
        command = "g++ " + tempFilename + " -o temp.out && ./temp.out";
    } else if (language == "Python") {
        tempFilename = "temp.py";
        ofstream file1(tempFilename);
        file1 << code;
        file1.close();
        command = "python3 " + tempFilename;
    } else if (language == "Kotlin") {
        tempFilename = "temp.kt";
        ofstream file1(tempFilename);
        file1 << code;
        file1.close();
        command = "kotlin " + tempFilename + " -include-runtime -d temp.jar && java -jar temp.jar";
    } else {
        cout << "Error: unsupported language " << language << endl;
        return;
    }

    int result = system(command.c_str());
    if (result != 0) {
        cout << "Error: command failed with exit code " << result << endl;
        return;
    }

    cout << "\nProgram executed successfully" << endl;
}

void run(string flag, string filename){
    string r;
    if (flag == "-py")
        r = "python3 " + filename;
    if (flag == "-c")
        r = "g++ " + filename + " -o temp.out && ./temp.out";
    if (flag == "-kt")
        r = "kotlin " + filename + " -include-runtime -d temp.jar && java -jar temp.jar";

    int result = system(r.c_str());
    if (result != 0) {
        cout << "Error: command failed with exit code " << result << endl;
        return;
    }

    cout << "\nProgram executed successfully" << endl;
}