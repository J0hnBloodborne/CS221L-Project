#include<bits/stdc++.h>
//<iostream>       // For input/output stream
//<string>         // For string handling
//<vector>         // For working with vectors
//<unordered_map>  // For unordered_map (e.g., used for children map)
//<unordered_set>  // For unordered_set (e.g., used for visited nodes)
//<algorithm>      // For algorithms like std::remove_if
#include "fileSystem.hpp"

using namespace std;

// Helper function to split user input into a vector of path components
vector<string> splitPath(string& path){
    vector<string> result;
    int start = 0, end = 0;
    while((end = path.find('/', start)) != string::npos){
        result.push_back(path.substr(start, end - start));
        start = end + 1;
    }
    if (start < path.length()) {result.push_back(path.substr(start));}
    return result;
}

void displayMenu(){
    cout << "\nFile System Manager - Menu" << endl;
    cout << "1. Display File System (DFS)" << endl;
    cout << "2. Add File/Directory" << endl;
    cout << "3. Delete File/Directory" << endl;
    cout << "4. Search for File/Directory" << endl;
    cout << "5. Get Directory Size" << endl;
    cout << "6. Add Symbolic Link" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
}

int runner(){
    FileSystemTree fs;

    while(true){
        displayMenu();

        int choice;
        cin >> choice;
        cin.ignore(); // Ignore leftover newline character

        switch (choice){
            case 1:{
                cout << "\nFile System (DFS Traversal):" << endl;
                fs.dfs();
                break;
            }
            case 2:{
                cout << "\nEnter the path to add (e.g., 'home/user/docs'): ";
                string pathInput;
                getline(cin, pathInput);
                vector<string> path = splitPath(pathInput);

                cout << "Is this a file? (1 for Yes, 0 for No): ";
                bool isFile;
                cin >> isFile;

                int fileSize = 0;
                if (isFile) {
                    cout << "Enter the size of the file in bytes: ";
                    cin >> fileSize;
                }

                fs.insert(path, isFile, fileSize);
                cout << "Added successfully." << endl;
                break;
            }
            case 3:{
                cout << "\nEnter the path to delete (e.g., 'home/user/docs'): ";
                string pathInput;
                getline(cin, pathInput);
                vector<string> path = splitPath(pathInput);

                if (fs.remove(path)) {cout << "Deleted successfully." << endl;} 
                else {cout << "Failed to delete. Path not found." << endl;}
                break;
            }
            case 4:{
                cout << "\nEnter the name of the file/directory to search: ";
                string name;
                getline(cin, name);

                if (fs.search(name)) {cout << "Found '" << name << "' in the file system." << endl;} 
                else {cout << "'" << name << "' not found in the file system." << endl;}
                break;
            }
            case 5:{
                cout << "\nEnter the path to calculate size (e.g., 'home/user'): ";
                string pathInput;
                getline(cin, pathInput);
                vector<string> path = splitPath(pathInput);

                int size = fs.getDirectorySize(path);
                if (size != -1) {cout << "Total size: " << size << " bytes." << endl;}
                break;
            }
            case 6:{
                // Adding symbolic link
                cout << "\nEnter the source path for the symbolic link (e.g., 'home/user/docs'): ";
                string sourcePathInput;
                getline(cin, sourcePathInput);
                vector<string> sourcePath = splitPath(sourcePathInput);

                cout << "Enter the target path for the symbolic link (e.g., 'home/user/target'): ";
                string targetPathInput;
                getline(cin, targetPathInput);
                vector<string> targetPath = splitPath(targetPathInput);

                if (fs.addSymbolicLink(sourcePath, targetPath)) {
                    cout << "Symbolic link added successfully." << endl;
                } else {
                    cout << "Failed to add symbolic link." << endl;
                }
                break;
            }
            case 7:{
                cout << "Exiting File System Manager. Goodbye!" << endl;
                return 0;
            }
            default:{
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }
}