#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <cctype>

using namespace std; //no lib, dependency runs from shell and piped

string exec(string command) {
   char buffer[128];
   string result = "";

   FILE* pipe = _popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   while (!feof(pipe)) {

      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   _pclose(pipe);
   return result;
}

string get_PID(string s) {
    size_t pos = 0;
    std::string token;
    int count = 0;
    while ((pos = s.find(",")) != std::string::npos) {
        token = s.substr(0, pos);
        if (count == 5)
        {
            return token.substr(1, token.length() - 2);
        };
        s.erase(0, pos + 1);
        count++;
    }
    return "";
}

int main() {
   string process = exec("tasklist /fi \"IMAGENAME eq blackops3.exe \"");
   if (process.find("BlackOps3.exe") != string::npos) 
   {
      string csv = exec("tasklist /fo csv /fi \"IMAGENAME eq blackops3.exe \""); // grab csv containing PID
      string pid = get_PID(csv);
      string dll_list = exec(".\\dep\\listdlls " + pid);
      cout << dll_list << "\n";
      cout << csv;
      system("pause");
   } else {
      system("clear");
      cout << "Black Ops III Not Detected";
   };
};