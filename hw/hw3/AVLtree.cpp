#include <iostream>
#include <cmath>

using namespace std;

// 二叉排序树的节点
struct TreeNode {
    int data;
    int height; // 节点的高度
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), height(1), left(nullptr), right(nullptr) {}
};

// 获取节点的高度
int getHeight(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// 获取节点的平衡因子
int getBalanceFactor(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// 更新节点的高度
void updateHeight(TreeNode* node) {
    if (node != nullptr) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }
}

// 右旋操作
TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    // 执行右旋
    x->right = y;
    y->left = T2;

    // 更新节点高度
    updateHeight(y);
    updateHeight(x);

    return x;
}

// 左旋操作
TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    // 执行左旋
    y->left = x;
    x->right = T2;

    // 更新节点高度
    updateHeight(x);
    updateHeight(y);

    return y;
}

// 插入节点，并保持树平衡
TreeNode* insert(TreeNode* root, int value) {
    // 执行标准BST插入
    if (root == nullptr) {
        return new TreeNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        // 重复元素不插入
        return root;
    }

    // 更新节点高度
    updateHeight(root);

    // 获取平衡因子
    int balance = getBalanceFactor(root);

    // 左子树不平衡，右旋操作
    if (balance > 1 && value < root->left->data) {
        return rightRotate(root);
    }

    // 右子树不平衡，左旋操作
    if (balance < -1 && value > root->right->data) {
        return leftRotate(root);
    }

    // 左右不平衡，先左旋后右旋操作
    if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // 右左不平衡，先右旋后左旋操作
    if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// 计算平均查找长度
void calculateAverageSearchLength(TreeNode* root, int depth, int& nodesCount, int& sumDepth) {
    if (root != nullptr) {
        nodesCount++;
        sumDepth += depth;

        calculateAverageSearchLength(root->left, depth + 1, nodesCount, sumDepth);
        calculateAverageSearchLength(root->right, depth + 1, nodesCount, sumDepth);
    }
}

int main() {
    // 数列L
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    TreeNode* root = nullptr;

    // 插入元素构建AVL树
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);    
    }

    // 计算平均查找长度
    int nodesCount = 0;
    int sumDepth = 0;
    calculateAverageSearchLength(root, 1, nodesCount, sumDepth);

    // 输出结果
    cout << "平均查找长度：" << static_cast<double>(sumDepth) / nodesCount << endl;

    return 0;
}
