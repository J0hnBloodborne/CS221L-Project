#include <iostream>
#include "fileSystem.hpp"

using namespace std;

int main() {
    FileSystemTree fs;

    fs.insert({"home"}, false);
    fs.insert({"home", "user"}, false);
    fs.insert({"home", "user", "file1.txt"}, true);
    fs.insert({"home", "user", "file2.txt"}, true);
    fs.insert({"home", "docs"}, false);
    fs.insert({"home", "docs", "report.docx"}, true);
    fs.insert({"home", "user", "file1.txt"}, true, 500); // 500 bytes
    fs.insert({"home", "user", "file2.txt"}, true, 300);
    fs.insert({"home", "docs", "report.docx"}, true, 1500);

    cout << "DFS Traversal:" << endl;
    fs.dfs();

    cout << "\nBFS Traversal:" << endl;
    fs.bfs();

    cout << "\nSearching for 'file1.txt': " << (fs.search("file1.txt") ? "Found" : "Not Found") << endl;
    cout << "Searching for 'missing.txt': " << (fs.search("missing.txt") ? "Found" : "Not Found") << endl;

    cout << "\nDeleting 'file1.txt': " << (fs.remove({"home", "user", "file1.txt"}) ? "Deleted" : "Not Found") << endl;

    cout << "\nDFS Traversal After Deletion:" << endl;
    fs.dfs();

    cout << "Size of 'home/user': " << fs.getDirectorySize({"home", "user"}) << " bytes" << endl;
    cout << "Size of 'home': " << fs.getDirectorySize({"home"}) << " bytes" << endl;
}
