//  Iterator
//
//  Created by Александр on 5/1/19.
//  Copyright © 2019 Александр. All rights reserved.

#include <iostream>
using namespace std;

//Simple binary tree
template<class T>
struct TreeNode
{
private:
    template<class Iter>
    struct NodeIterator
    {
        friend class TreeNode; //Add friend
    public:
        //Iterator traits
        typedef Iter iterator_type; //Iterator class
        typedef input_iterator_tag iterator_category; //its Input Iterator (can be changed:random acces iterator or something else)
        typedef iterator_type value_type; //Iterator type
        typedef ptrdiff_t difference_type; //Differ (int) like a size_t
        typedef iterator_type& reference; //Reference
        typedef iterator_type* pointer; //Pointer
        
        iterator_type* value; //Pointer of template type value
        
    private:
        NodeIterator(Iter* p): value(p) { }
    public:
        NodeIterator(const NodeIterator& it): value(it.value) {}
        
        //Opearators
        // !=
        bool operator!=(NodeIterator const&other) const
        {
            return value != other.value;
        }
        
        // ==
        bool operator==(NodeIterator const&other) const
        {
            return value == other.value;
        }
        
        // *
        typename NodeIterator::reference operator*() const
        {
            return *value;
        }
        
        // ++
        //Сначала отображаем леавый, затем правый и последним бедет корень
        NodeIterator& operator++()
        {
            //Есть ли родитель
            if(value->parent == nullptr)
                value = nullptr;
            //Равен ли родитель и правый елемент
            else if(value->parent->right.get() == value)
                value = value->parent;
            else
            {
                value = value->parent;
                //Есть ли правый елемент
                if(value->right.get() != nullptr)
                {
                value = value->right.get();
                //Есть ли левый елемент
                while(value->left.get() != nullptr)
                    value = value->left.get();
                }
            }
            return *this;
        }
    };
    
public:
    T value;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;
    TreeNode* parent;
    
    TreeNode(const T& value, std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right, TreeNode* parent)
    : value(value),left(std::move(left)), right(std::move(right)),parent(parent) {}
    
    TreeNode(const TreeNode&) = delete; //Удаляем конструктор копирования C++11
    
    //Typedefs
    typedef NodeIterator<TreeNode> iterator;
    typedef NodeIterator<const TreeNode> const_iterator;
    
    //Iterator
    iterator begin()
    {
        TreeNode* node = this;
        while(node->left != nullptr)
            node = node->left.get();
        return iterator(node);
    };
    
    iterator end()
    {
        //Так это не двунаправленный итератор можно просто вернуть nullptr
        return  nullptr;
    };
    
    //Const Iterator
    const_iterator begin() const
    {
        const TreeNode* node = this;
        while(node->left != nullptr)
            node = node->left.get();
        return const_iterator(node);
    };
    
    const_iterator end() const
    {
        //Так это не двунаправленный итератор можно просто вернуть nullptr
        return nullptr;
    };
    
    friend std::ostream&operator<<(std::ostream& os,const TreeNode& n)
    {
        return os << n.value;
    }

};

//Template print
template<class T>
void print(const T& t)
{
    for(typename T::const_iterator it = t.begin(); it != t.end(); ++it)
    {
        cout<<*it<<" ";
    }
};

int main(int argc, const char * argv[]) {
    
    string str = {"Hello World\n"};
    
//    print(str);
    
//    for (auto &&s:str)
//    {
//        cout<<s<<endl;
//    }
    
    auto root = make_unique<TreeNode<string>>("a1", nullptr, nullptr, nullptr);
    
    root->left = make_unique<TreeNode<string>>("b1", nullptr, nullptr, root.get());
    root->right = make_unique<TreeNode<string>>("b2", nullptr, nullptr, root.get());
    
    auto b1 = root->left.get();
    auto b2 = root->right.get();
    
    //Lv1
    b1->left = make_unique<TreeNode<string>>("c1", nullptr, nullptr, b1);
    b1->right = make_unique<TreeNode<string>>("c2", nullptr, nullptr, b1);
    
    //Lv2
    b2->left = make_unique<TreeNode<string>>("c3", nullptr, nullptr, b2);
    b2->right = make_unique<TreeNode<string>>("c4", nullptr, nullptr, b2);
    
    auto c1 = b1->left.get();
    auto c2 = b1->right.get();
    
    auto c3 = b2->left.get();
    auto c4 = b2->right.get();
    
//    cout<<root->value<<endl;
//    cout<<b1->value<<endl;
//    cout<<b2->value<<endl;
//    cout<<c1->value<<endl;
//    cout<<c2->value<<endl;
//    cout<<c3->value<<endl;
//    cout<<c4->value<<endl;
    
//    auto it = root->begin();
//    ++it;
//    cout<<*it<<endl;
    
    for(auto &&node: *root) //root - unique_ptr
    {
        cout<<node<<endl;
    }

    return 0;
}
