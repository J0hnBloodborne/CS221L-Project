#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

class FileSystemNode{
public:
    string name;
    bool isFile;
    map<string, FileSystemNode*> children;
    int size; // For file size in bytes or any unit.
    
    FileSystemNode(string nodeName, bool file = false, int fileSize = 0) : name(nodeName), isFile(file), size(fileSize) {}
};

class FileSystemTree{
private:
    FileSystemNode* root;

    void dfsHelper(FileSystemNode* node, int depth){
        if (!node) {return;}

        for(int i = 0; i < depth; ++i) {cout << "  ";}
        cout << (node->isFile ? node->name : node->name + "/") << endl;

        if(!node->isFile){
            for(auto& child : node->children) {dfsHelper(child.second, depth + 1);}
        }
    }

    void deleteNode(FileSystemNode* node){
        if (!node) {return;}

        for(auto& child : node->children) {deleteNode(child.second);}
        delete node;
    }

    // Helper function to calculate directory size.
    int calculateDirectorySize(FileSystemNode* node){
        if (!node) return 0;
        if (node->isFile) return node->size;

        int totalSize = 0;
        for (auto& child : node->children) {
            totalSize += calculateDirectorySize(child.second);
        }
        return totalSize;
    }

public:
    FileSystemTree() {root = new FileSystemNode("root", false);}
    ~FileSystemTree() {deleteNode(root);}

    //  Traversal functions.
    void dfs(){dfsHelper(root, 0);}
    void bfs(){
        queue<FileSystemNode*> q;
        q.push(root);

        while(!q.empty()){
            FileSystemNode* current = q.front();
            q.pop();

            cout << (current->isFile ? current->name : current->name + "/") << endl;

            if (!current->isFile){
                for(auto& child : current->children) {q.push(child.second);}
            }
        }
    }

    //  Adding file(directory).
    void insert(const vector<string>& path, bool isFile, int fileSize = 0) {
        FileSystemNode* current = root;
        for (size_t i = 0; i < path.size(); ++i) {
            const string& part = path[i];
            if (current->children.find(part) == current->children.end()) {
                current->children[part] = new FileSystemNode(part, i == path.size() - 1 && isFile, fileSize);
            }
            current = current->children[part];
        }
    }

    // Deletion: Remove a file or directory
    bool remove(const vector<string>& path) {
        FileSystemNode* current = root;
        FileSystemNode* parent = nullptr;
        string key = "";

        for (const string& part : path) {
            if (current->children.find(part) == current->children.end()){
                cout << "Path not found: ";
                for (const auto& p : path) {cout << "/" << p;}
                cout << endl;
                return false;
            }
            parent = current;
            current = current->children[part];
            key = part;
        }

        if (parent && !key.empty()){
            deleteNode(current);
            parent->children.erase(key);
            return true;
        }

        return false;
    }

    // Search: Find a file or directory by name
    bool search(const string& name, FileSystemNode* node = nullptr){
        if (!node) node = root;
        if (node->name == name) {return true;}

        for (auto& child : node->children) {
            if (search(name, child.second)) {return true;}
        }

        return false;
    }

    int getDirectorySize(const vector<string>& path) {
        FileSystemNode* current = root;
        for (const string& part : path) {
            if (current->children.find(part) == current->children.end()) {
                cout << "Path not found." << endl;
                return -1;
            }
            current = current->children[part];
        }
        return calculateDirectorySize(current);
    }
};

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
