#ifndef LINKLIST_H
#define LINKLIST_H

template <typename T>
struct Link {
    T element;
    Link* next;

    // Default constructor with next initialized to nullptr
    Link() : next(nullptr) {}

    // Constructor with element and next
    Link(const T& elem, Link* nxt = nullptr) : element(elem), next(nxt) {}
};

template <typename T>
class LList {
public:
    Link<T>* head;

    LList() {
        head = new Link<T>();  // Dummy header
    }

    ~LList() {
        clear();
        delete head;
    }

    void clear() {
        while (head->next != nullptr) {
            Link<T>* temp = head->next;
            head->next = temp->next;
            delete temp;
        }
    }

    void insert(const T& elem) {
        head->next = new Link<T>(elem, head->next);
    }
};

#endif  // LINKLIST_H
