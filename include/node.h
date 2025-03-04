#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
    T m_data;
    Node* m_next;

    explicit Node(T value) : m_data(value), m_next(nullptr) {}
};

#endif //NODE_H
