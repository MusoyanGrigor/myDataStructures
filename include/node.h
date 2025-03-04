#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
    T data;
    Node* next;

    explicit Node(T value);
};

#endif //NODE_H
