#include <iostream>
#include <dirent.h>  // For directory operations
#include <sys/stat.h>  // For stat() to check file type
#include <fstream>   // For file operations
#include <string>
#include <sstream>
#include<unordered_map>
#include<vector>
#include<algorithm>
using namespace std;

unordered_map<string,vector<pair<string,int> > >wordMap;
void calculateWordFrequencies(const string content,string fileName) {

     string line=content;
    vector<string>wordList;
    string words;
    int n;
    unordered_map<string,int>wordFreq;
    n=line.size();
                cout<<n<<endl;
            for(int i=0;i<n;i++){
                if(line[i]==' '){
                    wordList.push_back(words);
                    words="";
                }else{
                    words += line[i];
                }
            }
            wordList.push_back(words);


    for( string newWord : wordList){
        wordFreq[newWord]++;
    }
    for(auto pair : wordFreq){
        wordMap[pair.first].push_back(make_pair(fileName,pair.second));

    }

}

int main() {
    string path = "C:\\Users\\hp\\Documents\\stories\\stories";  // Specify your folder path here
    DIR* dir;
    struct dirent* entry;

    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
                string fileName = entry->d_name;

            // Skip directories (., .., etc.)
            if (fileName == "." || fileName == "..") {
                continue;  // Skip special entries
            }

                string fullPath = path + "/" + fileName;

            struct stat fileStat;
            if (stat(fullPath.c_str(), &fileStat) == 0) {
                // Check if it's a regular file
                if (S_ISREG(fileStat.st_mode)) {
                        cout << "Reading file: " << fileName << endl;

                        ifstream file(fullPath);
                    if (file.is_open()) {
                            ostringstream ss;
                        ss << file.rdbuf();
                            string content = ss.str();

                        calculateWordFrequencies(content, fileName);
                        file.close();
                    } else {
                        cerr << "Unable to open file: " << fileName << endl;
                    }

                        cout << "---------------------------------\n";
                }
            }
        }
        closedir(dir);
    } else {
        cerr << "Could not open directory: " << path << endl;
    }

      string user_input;
      cin>>user_input;
      auto x=wordMap[user_input];
     sort(x.begin(), x.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;  // Compare by the integer (second element)
     });
       for (const auto& p : x) {
            cout << "  Pair: (" << p.first << ", " << p.second << ")\n";  // Print the pair (string, int)
        }

    return 0;
}
