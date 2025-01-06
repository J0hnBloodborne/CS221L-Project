# File System Manager

## Overview
The File System Manager is a comprehensive implementation of a virtual file system. 
It provides a user-friendly interface in the command line for interacting with the file 
system, supporting a hierarchical structure with features such as:
- Adding, deleting, renaming, copying, and moving files and directories.
- Symbolic link management.
- Directory size calculation.
- DFS-based display of the file system structure.

## Components
### 1. Main File (`main.cpp`)
**Purpose:**
- Serves as the entry point of the program.

**Key Features:**
- Includes `userIOControl.hpp`.
- Contains a simple `main` function that calls the `runner()` function.
- Delegates all functional operations to the `runner()` function.

### 2. File System Implementation (`fileSystem.hpp`)
**Purpose:**
- Implements the core functionality of the File System Manager.

#### **Key Classes:**
##### **a. `FileSystemNode` Class**
**Description:** Represents files or directories in the file system.

**Attributes:**
- `name`: Name of the file or directory.
- `isFile`: Boolean flag differentiating files from directories.
- `children`: A map storing child nodes for hierarchical traversal.
- `size`: Integer storing file size (default is 0 for directories).
- `symbolicLinks`: Vector to handle symbolic links to other nodes.

**Constructor:** Initializes node attributes based on input parameters.

##### **b. `FileSystemTree` Class**
**Description:** Represents the hierarchical structure of the file system.

**Functionalities:**
1. **Traversal:**
   - Implements DFS traversal to display the file system structure.
   - Includes symbolic link representation.
2. **Insertion:**
   - Adds files or directories to the structure.
   - Initializes attributes like `isFile` and `size` based on user input.
3. **Deletion:**
   - Deletes files or directories.
   - Cleans up associated symbolic links.
4. **Search:**
   - Searches for files or directories by name.
   - Includes symbolic link traversal in the search.
5. **Directory Size Calculation:**
   - Recursively computes the total size of a directory, including files and subdirectories.
6. **Symbolic Links:**
   - Supports adding symbolic links between nodes.
7. **Copy and Move Operations:**
   - Allows copying and moving files or directories within the structure.
8. **Renaming:**
   - Enables renaming of files or directories.

**Helper Methods:**
- `dfsHelper`: Implements recursive DFS traversal for displaying the file system.
- `deleteNode`: Handles recursive deletion of nodes and their children.
- `calculateDirectorySize`: Computes the total size of a directory.
- `deepCopy`: Creates a deep copy of a file or directory for copy operations.

### 3. User Interaction Handler (`userIOControl.hpp`)
**Purpose:**
- Provides a user interface for managing the file system.

#### **Key Features:**
##### **a. Helper Function**
- `splitPath`: Splits a user-provided path string into components for hierarchical traversal.

##### **b. Menu System**
- `displayMenu`: Displays a menu of available actions to the user.

##### **c. Runner Function**
Manages the interaction loop between the user and the file system.

**Provides the following options:**
1. **Display File System:** Displays the hierarchical structure using DFS traversal.
2. **Add File/Directory:** Prompts the user for details and inserts the item into the file system.
3. **Delete File/Directory:** Deletes the specified file or directory.
4. **Search for File/Directory:** Searches the file system by name.
5. **Calculate Directory Size:** Computes the total size of a specified directory.
6. **Add Symbolic Link:** Creates a symbolic link from one node to another.
7. **Copy File/Directory:** Copies a file or directory to a new location.
8. **Rename File/Directory:** Renames a file or directory.
9. **Move File/Directory:** Moves a file or directory to a new location.
10. **Exit:** Exits the program gracefully.

**User Input Handling:**
- Uses `cin` and `getline` to ensure proper handling of strings and integers.

## How to Compile and Run
1. **Compile the program:**
   ```sh
   g++ -o file_system_manager main.cpp fileSystem.cpp userIOControl.cpp
   ```
2. **Run the program:**
   ```sh
   ./file_system_manager
   ```

## License
This project is open-source and available for modification and distribution under the Apache-2.0 license.

