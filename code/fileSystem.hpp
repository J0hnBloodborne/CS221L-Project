#include<bits/stdc++.h>

//<map>            // For using map (e.g., to store children of directories)
//<vector>         // For working with vectors (e.g., for symbolic links)
//<unordered_set>  // For unordered_set (e.g., for visited nodes during traversal)

using namespace std;

class FileSystemNode{
public:
    string name;
    bool isFile;
    map<string, FileSystemNode*> children;
    int size;
    vector<FileSystemNode*> symbolicLinks; // To handle symbolic links
    
    FileSystemNode(string nodeName, bool file = false, int fileSize = 0) : name(nodeName), isFile(file), size(fileSize){}
};

class FileSystemTree{
private:
    FileSystemNode* root;

    void dfsHelper(FileSystemNode* node, int depth, unordered_set<FileSystemNode*>& visited){
        if (!node || visited.count(node)) return;
        
        visited.insert(node);

        for(int i = 0; i < depth; ++i) cout << "  ";
        cout << (node->isFile ? node->name : node->name + "/") << endl;

        for(auto& link : node->symbolicLinks){
            for(int i = 0; i < depth + 1; ++i) cout << "  ";
            cout << "-> " << link->name << (link->isFile ? "" : "/") << endl;
        }

        if(!node->isFile){
            for(auto& child : node->children) {dfsHelper(child.second, depth + 1, visited);}
        }
    }

    void deleteNode(FileSystemNode* node, unordered_set<FileSystemNode*>& visited){
        if (!node || visited.count(node)) return;
        
        visited.insert(node);

        for(auto& child : node->children) {
            deleteNode(child.second, visited);
        }

        node->symbolicLinks.clear();
        delete node;
    }

    // Helper function to calculate directory size.
    int calculateDirectorySize(FileSystemNode* node, unordered_set<FileSystemNode*>& visited){
        if (!node || visited.count(node)) return 0;

        visited.insert(node);
        if (node->isFile) return node->size;

        int totalSize = 0;
        for (auto& child : node->children) {
            totalSize += calculateDirectorySize(child.second, visited);
        }
        return totalSize;
    }

public:
    FileSystemTree() {root = new FileSystemNode("root", false);}
    ~FileSystemTree() {
        unordered_set<FileSystemNode*> visited;
        deleteNode(root, visited);
    }

    //  Traversal functions.
    void dfs(){
        unordered_set<FileSystemNode*> visited;
        dfsHelper(root, 0, visited);
    }

    //  Adding file(directory).
    void insert(vector<string>& path, bool isFile, int fileSize = 0){
        FileSystemNode* current = root;
        for (size_t i = 0; i < path.size(); ++i){
            string& part = path[i];
            if (current->children.find(part) == current->children.end()){
                current->children[part] = new FileSystemNode(part, i == path.size() - 1 && isFile, fileSize);
            }
            current = current->children[part];
        }
    }
	 
	bool addSymbolicLink(vector<string>& sourcePath, vector<string>& targetPath){
        FileSystemNode* source = root;
        FileSystemNode* target = root;

        for (string& part : sourcePath){
            if (source->children.find(part) == source->children.end()){
                cout << "Source path not found." << endl;
                return false;
            }
            source = source->children[part];
        }

        for (string& part : targetPath){
            if (target->children.find(part) == target->children.end()){
                cout << "Target path not found." << endl;
                return false;
            }
            target = target->children[part];
        }

        if (find(source->symbolicLinks.begin(), source->symbolicLinks.end(), target) != source->symbolicLinks.end()){
            cout << "Symbolic link already exists." << endl;
            return false;
        }

        // Add symbolic link
        source->symbolicLinks.push_back(target);
        return true;
    }
 	
    // Deletion: Remove a file or directory
    bool remove(vector<string>& path) {
	    FileSystemNode* current = root;
	    FileSystemNode* parent = nullptr;
	    string key = "";
	
	    for (string& part : path) {
	        if (current->children.find(part) == current->children.end()) {
	            cout << "Path not found: ";
	            for (string& p : path) { cout << "/" << p; }
	            cout << endl;
	            return false;
	        }
	        parent = current;
	        current = current->children[part];
	        key = part;
	    }
	
	    // Remove any symbolic links that point to this node (both directions)
	    // Remove from all other nodes' symbolic links where they point to 'current'
	    for (auto& node : root->children) {
	        auto& symbolicLinks = node.second->symbolicLinks;
	        symbolicLinks.erase(remove_if(symbolicLinks.begin(), symbolicLinks.end(), [&current](FileSystemNode* node) { return node == current; }), symbolicLinks.end());
	    }
	
	    // Also clean up the reverse link from the symbolic links in the node being deleted
	    for (auto& link : current->symbolicLinks) {
	        auto& targetSymbolicLinks = link->symbolicLinks;
	        targetSymbolicLinks.erase(remove_if(targetSymbolicLinks.begin(), targetSymbolicLinks.end(), [&current](FileSystemNode* node) { return node == current; }), targetSymbolicLinks.end());
	    }
	
	    unordered_set<FileSystemNode*> visited;
	    if (parent && !key.empty()) {
	        deleteNode(current, visited);
	        parent->children.erase(key);
	        return true;
	    }
	
	    return false;
	}

    // Search: Find a file or directory by name
    bool search(string& name, FileSystemNode* node = nullptr){
	    if (!node) {node = root;}
	
	    // Check the node itself
	    if (node->name == name) {return true;}
	    // Search children normally
	    for (auto& child : node->children) {if (search(name, child.second)) {return true;}}
	    // Search through symbolic links
	    for (auto& link : node->symbolicLinks) {if (search(name, link)) {return true;}}
	
	    return false;
	}

    // Give the size in bytes of directory.
    int getDirectorySize(vector<string>& path){
        FileSystemNode* current = root;
        for (string& part : path){
            if (current->children.find(part) == current->children.end()){
                cout << "Path not found." << endl;
                return -1;
            }
            current = current->children[part];
        }

        unordered_set<FileSystemNode*> visited;
        return calculateDirectorySize(current, visited);
    }
};
