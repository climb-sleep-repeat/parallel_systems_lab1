#ifndef NODE_H
#define NODE_H

class node{
public:
    node(int * data) : m_data(data){}
    void set_children(node * left, node * right);
    void set_parent(node * parent){m_parent = parent;}
    void set_data(int data) {*m_data = data;}
    int get_data(){return *m_data;}
private:
    node * m_left_child;
    node * m_right_child;
    node * m_parent;
    int * m_data;
};

inline void node::set_children(node* left, node* right){
    m_left_child = left;
    m_right_child = right;
}
#endif //NODE_H