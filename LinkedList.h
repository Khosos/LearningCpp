
template<typename T>
class Node{
public:
    T val;
    Node* next;

    Node(T val) :val(val) {
        this->next = nullptr;
    }
};
