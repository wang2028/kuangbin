#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

/*
    以下实现为指针（非数组）的实现，但跑不起来...一直出错...改不下去了...
*/

typedef struct node {
    struct node *up, *down, *left, *right;
    int row;
    struct node *col;
} Node;

class DL {
  public:
    DL(int m, int n) {
        // 初始化，建辅助元素 head 和 Cn，
        // 参数： n 为列数，m 行数
        this->cols = new Node[n + 1];
        this->head.right = &cols[1];
        cols[1].left = &head;
        for (int i = 1; i < n; i++) {
            cols[i].right = &cols[i + 1];
            cols[i + 1].left = &cols[i];
            cols[i].up = &cols[i];
            cols[i].down = &cols[i];
            cols[i].row = 0;
        }
        cols[n].up = &cols[n];
        cols[n].down = &cols[n];
        cols[n].row = 0;
        cols[n].right = &head;
        this->head.left = &cols[n];

        this->rows = new Node[m + 1];
        for (int i = 1; i <= m; i++) {
            rows[i].left = &rows[i];
            rows[i].right = &rows[i];
            rows[i].row = i;
            cout << rows[i].row << endl;
            rows[i].col = &cols[n];
        }
    }
    void addNode(int i, int j) {
        // 添加节点 (i,j)，矩阵从 (1,1) 开始
        Node *tempp;
        Node *newn = new Node;
        newn->col = &cols[j];
        newn->row = i;
        tempp = cols[j].down;
        if (tempp != &cols[j]) {
            while (tempp->down->row > tempp->row) {
                tempp = tempp->down;
            }
        }
        // 在 tempp 下面添加 node
        tempp->down->up = newn;
        newn->down = tempp->down;
        tempp->down = newn;
        newn->up = tempp;

        if (rows[i].right != &rows[i]) {
            tempp = rows[i].right;
            while (tempp->right->col > tempp->col) {
                tempp = tempp->right;
            }
            // 在 tempp 右面添加 node
            tempp->right->left = newn;
            newn->left = tempp;
            newn->right = tempp->right;
            tempp->right = newn;
        } else {
            rows[i].right = newn;
            newn->right = newn;
            newn->left = newn;
        }
    }
    bool dance() {
        Node *tempp = head.right;
        if (tempp = &head)
            return true;
        Node *temp1 = tempp->down;
        if (temp1 == tempp)
            return false;
        while (temp1 != tempp) {
            Node *temp2;
            ans.push_back(temp1->row);
            temp2 = temp1->right;
            removeCol(temp1->col);
            while (temp2 != temp1) {
                removeCol(temp2->col);
                temp2 = temp2->right;
            }
            if (dance()) {
                return true;
            } else {
                ans.pop_back();
                temp2 = temp1->right;
                resumeCol(temp1->col);
                while (temp2 != temp1) {
                    resumeCol(temp2->col);
                    temp2 = temp2->right;
                }
            }
            temp1 = temp1->down;
        }
        return false;
    }

  private:
    Node head;
    Node *cols;
    Node *rows; // 设行辅助元素方便新建行
    vector<int> ans;
    void removeCol(Node *j) {
        // 删除 Cj 列的节点及节点所在行
        Node *tempp = j->down;
        while (tempp != j) {
            Node *tempp1 = tempp->right;
            while (tempp1 != tempp) {
                // 把该行其他所有元素的上下剪断
                tempp1->up->down = tempp1->down;
                tempp1->down->up = tempp1->up;
                tempp1 = tempp1->right;
            }
        }
        j->left->right = j->right;
        j->right->left = j->left;
        // 这样从 cols 遍历的时候就没有这一列了
    }
    void resumeCol(Node *j) {
        j->left->right = j;
        j->right->left = j;

        Node *tempp = j->down;
        while (tempp != j) {
            Node *tempp1 = tempp->right;
            while (tempp1 != tempp) {
                // 把该行其他所有元素的上下重连
                tempp1->up->down = tempp1;
                tempp1->down->up = tempp1;
            }
        }
    }
};

int main() {
    int m = 6, n = 7;
    DL dl = DL(m, n);
    int tempi;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> tempi;
            if (tempi) {
                dl.addNode(i, j);
            }
        }
    }
    cout << dl.dance() << endl;

    return 0;
}

/*
0 0 1 0 1 1 0
1 0 0 1 0 0 1
0 1 1 0 0 1 0
1 0 0 1 0 0 0
0 1 0 0 0 0 1
0 0 0 1 1 0 1


*/