
#include <iostream>
#include <algorithm>
#include <stack>
#include <string>
using namespace std;
class tree {
public:
    char c;
    tree * lc, *rc;
    tree() {}
    tree(char c) : c(c), lc(nullptr), rc(nullptr) {}
};

class ExpressionTree : public tree {
    tree * root;
protected:
    void build_expression(string str);
    void proorder_print(tree * n);
    void inorder_print(tree * n);
    void postorder_print(tree * n);
    void destory(tree * & n);
    double eval(tree * n);

public:
    void show();

    ExpressionTree(string str)
    {
        build_expression(str);
    }
    ~ExpressionTree()
    {
        destory(this->root);
    }
};

void ExpressionTree::build_expression(string str)
{
    stack<tree *> treestack;
    for (auto c : str)
    {
        tree * node = new tree(c);
        if (c >= '0' && c <= '9' || c >= 'a' && c <= 'z')
            treestack.push(node);
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (!treestack.empty())
            {
                node->rc = treestack.top();
                treestack.pop();
            }
            if (!treestack.empty())
            {
                node->lc = treestack.top();
                treestack.pop();
            }
            treestack.push(node);
        }
        else
        {
            cout << "表达式有误!" << endl;
            exit(1);
        }
    }
    root = treestack.top();
    while (!treestack.empty())
        treestack.pop();
}

void ExpressionTree::proorder_print(tree * n)
{
    if (n)
    {
        cout << n->c;
        proorder_print(n->lc);
        proorder_print(n->rc);
    }
}

void ExpressionTree::inorder_print(tree * n)
{
    if (n)
    {
        if (n->c >= '0' && n->c <= '9')
            cout << n->c;
        else
        {
            cout << '(';
            inorder_print(n->lc);
            cout << ' ' << n->c << ' ';
            inorder_print(n->rc);
            cout << ')';
        }
    }
}

void ExpressionTree::postorder_print(tree * n)
{
    if (n)
    {
        postorder_print(n->lc);
        postorder_print(n->rc);
        cout << n->c;
    }
}

void ExpressionTree::show()
{
    cout << "前缀表达式:" << endl;
    proorder_print(this->root);
    cout << endl;
    cout << "中缀表达式:" << endl;
    inorder_print(this->root);
    cout << " = " << eval(this->root) << endl;
    cout << "后缀表达式:" << endl;
    postorder_print(this->root);
    cout << endl;
}

double ExpressionTree::eval(tree * n)
{
    switch (n->c)
    {
    case '+': return eval(n->lc) + eval(n->rc);
    case '-': return eval(n->lc) - eval(n->rc);
    case '*': return eval(n->lc) * eval(n->rc);
    case '/': return eval(n->lc) / eval(n->rc);
    default: return n->c - '0';
    }
}

void ExpressionTree::destory(tree * & root)
{
    if (root != nullptr)
    {
        destory(root->lc);
        destory(root->rc);
        delete root;
    }
}

int main()
{
    string str = "23+456+**";
    ExpressionTree res(str);

    res.show();

    getchar();
    return 0;
}
