#include <iostream>

using namespace std;

template <typename T>
class Node {
    private:
        T Data;
        Node *right_child;
        Node *left_child;
        
    public:
        int height;
        Node(T value):Data(value),right_child(nullptr),left_child(nullptr),height(0){}
        T get_data(){
            return Data;
        }
        Node *get_right(){
            return right_child;
        }
        Node *get_left(){
            return left_child;
        }
        void set_right(Node *new_right){
            Node::right_child=new_right;
        }
        void set_left(Node *new_left){
            Node::left_child=new_left;
        }

};

template <typename T>
class AVL{
    private:
    Node <T> *Root;
    public:
    AVL() : Root(nullptr) {}
    void Insert(T value){
        Root = insert(value,Root);
    }
    Node <T> *insert(T value,Node <T> *selected){
        if(selected==nullptr){
            return new Node <T> (value);
        }
        if(value < selected->get_data()){
            selected->set_left(insert(value,selected->get_left()));
        }else if(value >= selected->get_data()){
            selected->set_right(insert(value,selected->get_right()));
        }else{
        return selected;
        }

        selected->height =1 + max(height(selected->get_left()), height(selected->get_right()));

        int balance = getBalance(selected);

        if (balance > 1 && value < selected->get_left()->get_data()){
            return rotateRight(selected);
        }

        if (balance < -1 && value > selected->get_right()->get_data()){
            return rotateLeft(selected);
        }

        if (balance > 1 && value > selected->get_left()->get_data()) {
            selected->set_left(rotateLeft(selected->get_left()));
            return rotateRight(selected);
        }

        if (balance < -1 && value < selected->get_right()->get_data()) {
            selected->set_right(rotateRight(selected->get_right()));
            return rotateLeft(selected);
        }
        return selected;
    }

    int getBalance(Node<T> *N) {
        if (N == nullptr)
            return 0;
        return height(N->get_left()) - height(N->get_right());
    }

    int height(Node<T> *N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    Node <T> *rotateLeft(Node <T> *selected){
        Node <T> *main_point = selected->get_right();
        Node <T> *minor_point = main_point->get_left();

        main_point->set_left(selected);
        selected->set_right(minor_point);

        selected->height = max(height(selected->get_left()), height(selected->get_right())) + 1;
        main_point->height = max(height(main_point->get_left()), height(main_point->get_right())) + 1;

        return main_point;
    }

    Node <T> *rotateRight(Node <T> *selected){
        Node <T> *main_point = selected->get_left();
        Node <T> *minor_point = main_point->get_right();

        main_point->set_right(selected);
        selected->set_left(minor_point);

        selected->height = max(height(selected->get_left()), height(selected->get_right())) + 1;
        main_point->height = max(height(main_point->get_left()), height(main_point->get_right())) + 1;

        return main_point;
    }

    void Inorder(){
        inorder_build(Root);
    }
    void inorder_build(Node <T> *selected){
        if(selected!=nullptr){
            inorder_build(selected->get_left());
            cout<<selected->get_data()<<",";
            inorder_build(selected->get_right());
        }
    }
    void Preorder(){
        preorder_build(Root);
    }
    void preorder_build(Node <T> *selected){
        if(selected!=nullptr){
            cout<<selected->get_data()<<",";
            preorder_build(selected->get_left());
            preorder_build(selected->get_right());
        }
    }
    void Postorder(){
        postorder_build(Root);
    }
    void postorder_build(Node <T> *selected){
        if(selected!=nullptr){
            cout<<selected->get_data()<<",";
            postorder_build(selected->get_right());
            postorder_build(selected->get_left());
        }
    }
}; 
//Mehrchian