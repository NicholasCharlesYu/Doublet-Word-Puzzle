# Doublets Word Puzzle

This project implements the classic Doublets Word Puzzle. Originated by Lewis Carroll, Doublet is a word transformation puzzle where the goal is to transform the starting word into the ending word in the least number of steps by forming successive valid words and changing only one letter at a time.

## Features

- **Templated d-ary MinHeap**: Designed a robust templated d-ary MinHeap class in C++ to streamline data access and enhance efficiency.
- **A* Search Algorithm**: Integrated the A* search algorithm to ensure rapid and accurate traversal from the starting word to the ending word.
- **Heuristic Function**: Incorporated a heuristic function based on the "Incorrect Letters" strategy. This counts the number of mismatched letters between the current word and the target word to guide the search.

### Templated d-ary MinHeap

Found in `MinHeap.h`, the d-ary MinHeap class offers:

- A customizable degree `d` to adapt the number of child nodes for each parent.
- Standard heap operations including adding elements, peeking at the top element, and removing the top element.
- Built upon the `vector<T>` container for efficient storage and retrieval.
- Precise indexing calculations to determine parent and child nodes in the heap structure.

### Doublets with A* Search

The A* search algorithm is applied to the Doublets puzzle to identify the shortest transformation sequence between words:

- Words are treated as nodes, and edges are established between words differing by a single letter.
- The A* algorithm utilizes the MinHeap to decide on the next word to consider, taking advantage of the heuristic function for guidance.
- The output comprises the minimum number of transformations needed and the number of words examined (expansions) to reach the solution.

## Testing

Run the program with the following command:

./doublet [START_WORD] [END_WORD] [WORD_LIST_FILE]
- WORD_LIST_FILE refers to /doublet_tests/words
