import java.util.Scanner;

public class AVLTree {
    static class Node {
        int data;
        int height;
        Node left;
        Node right;

        public Node(int value) {
            data = value;
            height = 1;
            left = null;
            right = null;
        }
    }

    private Node root;

    public AVLTree() {
        this.root = null;
    }

    private int getHeight(Node node) {
        if (node == null) {
            return 0;
        }
        return node.height;
    }

    private int getBalanceFactor(Node node) {
        if (node == null) {
            return 0;
        }
        return getHeight(node.left) - getHeight(node.right);
    }

    private void updateHeight(Node node) {
        if (node != null) {
            node.height = Math.max(getHeight(node.left), getHeight(node.right)) + 1;
        }
    }

    private Node rightRotate(Node y) {
        Node x = y.left;
        Node T2 = x.right;

        x.right = y;
        y.left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    private Node leftRotate(Node x) {
        Node y = x.right;
        Node T2 = y.left;

        y.left = x;
        x.right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    private Node insert(Node root, int value) {
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

    public void insert(int value) {
        root = insert(root, value);
    }

    private void calculateAverageSearchLength(Node root, int depth, int[] nodesCount, int[] sumDepth) {
        if (root != null) {
            nodesCount[0]++;
            sumDepth[0] += depth;

            calculateAverageSearchLength(root.left, depth + 1, nodesCount, sumDepth);
            calculateAverageSearchLength(root.right, depth + 1, nodesCount, sumDepth);
        }
    }

    public void calculateAverageSearchLength() {
        int[] nodesCount = {0};
        int[] sumDepth = {0};
        calculateAverageSearchLength(root, 1, nodesCount, sumDepth);
        double asl = (double) sumDepth[0] / nodesCount[0];

        System.out.println("ASL：" + (asl - 1.0));
    }
    @Override
    public String toString() {
        return toStringHelper(root, "");
    }

    /* Recursive helper method for toString. */
    private String toStringHelper(Node node, String indent) {
        if (node == null) {
            return "";
        } else {
            String toReturn = "";
            Node rightChild = node.right;
            toReturn += toStringHelper(rightChild, "        " + indent);
            if (rightChild != null) {
                toReturn += indent + "    /";
            }
            //toReturn += "\n" + indent + node.data + " (Balance Factor: " + getBalanceFactor(node) + ")\n";
            toReturn += "\n" + indent + node.data + "\n";
            Node leftChild = node.left;
            if (leftChild != null) {
                toReturn += indent + "    \\";
            }
            toReturn += toStringHelper(leftChild, "        " + indent);
            return toReturn;
        }
    }

    public static void main(String[] args) {
        AVLTree avlTree = new AVLTree();

        // Input a sequence of integers and generate an AVL tree
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a sequence of integers (end with Enter):");

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (line.isEmpty()) {
                // Stop input if an empty line is entered
                break;
            }
            try {
                int num = Integer.parseInt(line);
                avlTree.insert(num);


                //Display each step
                System.out.println("AVL Tree representation:");
                System.out.println(avlTree);

            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter integers only.");
            }
        }

        // Display the AVL Tree
        System.out.println("AVL Tree representation:");
        System.out.println(avlTree);

        avlTree.calculateAverageSearchLength();
    }
}

