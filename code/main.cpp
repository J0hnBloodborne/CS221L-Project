#include <iostream>
#include <string>
#include "fileSystem.hpp"

using namespace std;

int main() {
    FileSystemTree fs;

    // Insert directories and files
    fs.insert({"home"}, false);
    fs.insert({"home", "user"}, false);
    fs.insert({"home", "user", "file1.txt"}, true);
    fs.insert({"home", "user", "file2.txt"}, true);
    fs.insert({"home", "docs"}, false);
    fs.insert({"home", "docs", "report.docx"}, true);

    // Display the file system (DFS)
    cout << "DFS Traversal:" << endl;
    fs.dfs();

    // Display the file system (BFS)
    cout << "\nBFS Traversal:" << endl;
    fs.bfs();

    // Search for a file
    cout << "\nSearching for 'file1.txt': " << (fs.search("file1.txt") ? "Found" : "Not Found") << endl;
    cout << "Searching for 'missing.txt': " << (fs.search("missing.txt") ? "Found" : "Not Found") << endl;

    // Delete a file
    cout << "\nDeleting 'file1.txt': " << (fs.remove({"home", "user", "file1.txt"}) ? "Deleted" : "Not Found") << endl;

    // Display the file system again
    cout << "\nDFS Traversal After Deletion:" << endl;
    fs.dfs();

    return 0;
}
