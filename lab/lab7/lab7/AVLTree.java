class Node {
    int data;
    int height;
    Node left;
    Node right;

    public Node(int value) {
        data = value;
        height = 1;
        left = right = null;
    }
}

public class AVLTree {
    public static int getHeight(Node node) {
        if (node == null) {
            return 0;
        }
        return node.height;
    }

    public static int getBalanceFactor(Node node) {
        if (node == null) {
            return 0;
        }
        return getHeight(node.left) - getHeight(node.right);
    }

    public static void updateHeight(Node node) {
        if (node != null) {
            node.height = Math.max(getHeight(node.left), getHeight(node.right)) + 1;
        }
    }

    public static Node rightRotate(Node y) {
        Node x = y.left;
        Node T2 = x.right;

        x.right = y;
        y.left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    public static Node leftRotate(Node x) {
        Node y = x.right;
        Node T2 = y.left;

        y.left = x;
        x.right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    public static Node insert(Node root, int value) {
        if (root == null) {
            return new Node(value);
        }

        if (value < root.data) {
            root.left = insert(root.left, value);
        } else if (value > root.data) {
            root.right = insert(root.right, value);
        } else {
            return root;
        }

        updateHeight(root);

        int balance = getBalanceFactor(root);

        if (balance > 1 && value < root.left.data) {
            return rightRotate(root);
        }

        if (balance < -1 && value > root.right.data) {
            return leftRotate(root);
        }

        if (balance > 1 && value > root.left.data) {
            root.left = leftRotate(root.left);
            return rightRotate(root);
        }

        if (balance < -1 && value < root.right.data) {
            root.right = rightRotate(root.right);
            return leftRotate(root);
        }

        return root;
    }

    public static void calculateAverageSearchLength(Node root, int depth, int[] nodesCount, int[] sumDepth) {
        if (root != null) {
            nodesCount[0]++;
            sumDepth[0] += depth;

            calculateAverageSearchLength(root.left, depth + 1, nodesCount, sumDepth);
            calculateAverageSearchLength(root.right, depth + 1, nodesCount, sumDepth);
        }
    }

    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        int n = arr.length;

        Node root = null;

        for (int i = 0; i < n; i++) {
            root = insert(root, arr[i]);
        }

        int[] nodesCount = {0};
        int[] sumDepth = {0};
        calculateAverageSearchLength(root, 1, nodesCount, sumDepth);

        System.out.println("平均查找长度：" + (double) sumDepth[0] / nodesCount[0]);
    }
}
