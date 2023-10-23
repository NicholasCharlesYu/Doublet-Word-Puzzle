#include <stdexcept>
#include <utility>
#include <vector>

template<class T>
class MinHeap {
public:
    MinHeap(int d);
    /* Constructor that builds a d-ary Min Heap
      This should work for any d >= 2,
      but doesn't have to do anything for smaller d.*/

    ~MinHeap();

    void add(T item, int priority);
    /* adds the item to the heap, with the given priority. */

    const T& peek() const;
    /* returns the element with smallest priority.
            Break ties however you wish.
            Throws an exception if the heap is empty. */

    void remove();
    /* removes the element with smallest priority.
           Break ties however you wish.
     Throws an exception if the heap is empty. */

    bool isEmpty();
    /* returns true iff there are no elements on the heap. */

private:
    std::vector<std::pair<T, int>> heap;

    int d_;

    void bubbleUp(int pos);  // bubble new item to right pos

    void trickleDown(int pos);  // trickle item to right pos
};

template<class T>
MinHeap<T>::MinHeap(int d) : d_(d) {
    if (d < 2) {
        std::exit(0);
    }
}

template<class T>
MinHeap<T>::~MinHeap() {}

template<class T>
void MinHeap<T>::add(T item, int priority) {
    heap.push_back(std::make_pair(item, priority));
    bubbleUp(heap.size() - 1);
}

template<class T>
const T& MinHeap<T>::peek() const {
    if (heap.empty()) {
        throw std::invalid_argument("The heap is empty");
    }
    return heap[0].first;
}

template<class T>
void MinHeap<T>::remove() {
    if (heap.empty()) {
        throw std::invalid_argument("The heap is empty");
    }
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    trickleDown(0);
}

template<class T>
bool MinHeap<T>::isEmpty() {
    return heap.empty();
}

template<class T>
void MinHeap<T>::bubbleUp(int pos) {
    // check if valid and if current is less than parent
    if (pos > 0 && heap[pos].second < heap[(pos - 1) / d_].second) {
        // if it is less, swap
        std::swap(heap[pos], heap[(pos - 1) / d_]);
        bubbleUp((pos - 1) / d_);
    }
    // if tie, choose smaller string according to operator<
    else if (pos > 0 && heap[pos].second == heap[(pos - 1) / d_].second) {
        if (heap[pos].first < heap[(pos - 1) / d_].first) {
            std::swap(heap[pos], heap[(pos - 1) / d_]);
            bubbleUp((pos - 1) / d_);
        }
    }
}

template<class T>
void MinHeap<T>::trickleDown(int pos) {
    int child = d_ * pos + 1;
    if (child < heap.size()) {
        // checks for all children of node
        for (int i = 1; i < d_ && d_ * pos + 1 + i < heap.size(); i++) {
            // if next child is less, set as current
            if (heap[child].second > heap[d_ * pos + 1 + i].second) {
                child = d_ * pos + 1 + i;
            } else if (heap[child].second == heap[d_ * pos + 1 + i].second) {
                if (heap[child].first > heap[d_ * pos + 1 + i].first) {
                    child = d_ * pos + 1 + i;
                }
            }
        }
        // if current is more than child, swap
        if (heap[child].second < heap[pos].second) {
            std::swap(heap[child], heap[pos]);
            trickleDown(child);
        }
        // if tie, if current string is larger than child, swap
        else if (heap[child].second == heap[pos].second) {
            if (heap[child].first < heap[pos].first) {
                std::swap(heap[child], heap[pos]);
                trickleDown(child);
            }
        }
    }
}