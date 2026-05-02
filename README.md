# C File System Simulator 📂

This project is an in-memory file system simulator developed in C. It uses an **N-ary Tree** data structure (specifically the "First Child / Next Sibling" representation) to manage directories and files hierarchically.

The system allows you to navigate through folders, create new files/directories, list contents, and perform safe deletions with proper dynamic memory management.

---

## 🚀 Features and Commands

The system runs in an interactive terminal loop. The following commands are available:

*   **`mp <name>`** *(Make Folder)*: Creates a new directory inside the current folder.
*   **`ma <name>`** *(Make File)*: Creates a new file inside the current folder.
*   **`cd <name>`** *(Change Directory)*: Enters the specified directory.
*   **`cd ..`**: Returns to the parent directory.
*   **`ls`** *(List)*: Lists the contents of the current folder. Folders are displayed with a `-` at the end of their name (e.g., `folder-`), while files are displayed with their normal names.
*   **`rm <name>`** *(Remove)*: Deletes a file or directory (including all its internal content) from the current folder.
*   **`ex`** *(Exit)*: Exits the system and frees all allocated memory.

---

## 🛠️ Project Structure

The source code has been modularized for better organization:

*   **`main.c`**: Contains the main execution loop, command reading, and user interface.
*   **`tree.c`** *(and its header, if applicable)*: Contains the data structure logic, memory allocation/deallocation, and tree manipulation functions (insert, search, delete).

---

## ⚙️ How to Compile and Run

To compile the project, you will need **GCC** installed on your machine.

### Standard Compilation

Open the terminal in the project root and run:
```bash
gcc main.c tree.c -o programa.exe
