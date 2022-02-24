#ifndef LISTTEMPLATE_H
#define LISTTEMPLATE_H
template <typename T>
class ListNode {
public:
    ListNode(const T& x) : data(x) { }
    T data;
    ListNode* next {nullptr};
    ListNode* prev {nullptr};
};

template <typename T> class List {
public:
    List() = default;
    void append(const T& item) {
        ListNode<T>* new_node = new ListNode<T>(item);
        if (!tail)
            head = tail = new_node;
        else
        { 
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
    }
    ListNode<T>* head {nullptr};
    ListNode<T>* tail {nullptr};
};
#endif