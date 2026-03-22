Inverted Index System in C

📌 Overview

Developed an Inverted Index System in C to efficiently search words across multiple text files, track their frequency, and identify file-level occurrences.

This project optimizes search performance by using **Hash Tables and Linked Lists**, avoiding inefficient linear scans.

⚙️ Features

* Indexes words from multiple files
* Stores:
  * Unique words
  * File names containing each word
  * Frequency of occurrence per file
* Supports:
  * 📂 Create Database
  * 🔍 Search Word
  * 📊 Display Index
  * 💾 Save & Restore Database
* Handles invalid inputs and edge cases efficiently

🧠 Core Design

🔹 Data Structures

* Hash Table (size = 27)

  * Indexed using first character (`a–z`, others mapped to last index)

* Two-Level Linked List Structure

  * Main Node (Word Level)

    * Stores:

      * Word
      * File count
      * Link to sub-nodes
  * Sub Node (File Level)

    * Stores:

      * File name
      * Word count

🔹 Token Normalization

* Converts words to lowercase
* Removes special characters
* Ensures consistent indexing

Implementation Details

📥 Database Creation

* Reads files word-by-word
* Normalizes each token
* Computes hash index

Handles cases:

* New word → Create main node + sub node
* Existing word + new file → Add sub node
* Existing word + same file → Increment count

🔍 Searching

* Normalize input word
* Compute hash index
* Traverse linked list

✔ Displays:

* Number of files containing the word
* Count per file

 📁 File Validation

* Invalid file extension
* File not found
* Empty files
* Duplicate file handling

💾 Persistence

* Save:
* Stores database in structured format
* **Restore**:

  * Reconstructs hash table from saved file

🖥️ User Interface

* Menu-driven program
* Input validation
* Clear error handling
* Prevents invalid operations (e.g., duplicate DB creation)

🚀 Result

* Achieved fast search performance (O(1) average) using hashing
* Efficient memory usage with linked structures
* Successfully handled:

  * Multiple files
  * Large datasets
  * Duplicate and invalid inputs

🎯 Key Learnings

* Strong understanding of:

  * **Hashing techniques**
  * **Linked List implementation**
  * **File handling in C**
  * **Dynamic memory management**
* Improved problem-solving for real-world search systems
* Built a scalable and modular architecture

⚠️ Challenges Faced

* Handling special characters in tokens
* Avoiding duplicate entries
* Managing dynamic memory safely
* Efficient file parsing
