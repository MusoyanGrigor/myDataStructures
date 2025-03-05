#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
    T m_data;
    Node* m_next;
    Node* m_prev;

    explicit Node(T value) : m_data(value), m_next(nullptr), m_prev(nullptr) {}
};

#endif // NODE_H
