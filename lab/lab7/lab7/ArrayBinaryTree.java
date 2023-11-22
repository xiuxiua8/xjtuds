

import java.util.Scanner;
public class ArrayBinaryTree<T> {
    private Object[] contents;
    private int size;

    public ArrayBinaryTree() {
        contents = new Object[16];
        size = 0;
    }

    private static int leftIndex(int i) {
        return 2 * i;
    }

    private static int rightIndex(int i) {
        return 2 * i + 1;
    }

    private static int parentIndex(int i) {
        return i / 2;
    }

    private boolean inBounds(int index) {
        return index > 0 && index <= size;
    }

    private  Object getNode(int index) {
        if (!inBounds(index)) {
            return null;
        }
        return contents[index];
    }

    private void swap(int index1, int index2) {
        Object temp = contents[index1];
        contents[index1] = contents[index2];
        contents[index2] = temp;
    }

    private void validateIndex(int index) {
        if (!inBounds(index)) {
            throw new IllegalArgumentException("Index out of bounds");
        }
    }

    public void insert(T item) {
        if (size + 1 == contents.length) {
            resize(contents.length * 2);
        }

        size += 1;
        contents[size] = item;
    }

    public void remove(T item) {
        for (int i = 1; i <= size; i++) {
            if (contents[i].equals(item)) {
                swap(i, size);
                contents[size] = null;
                size -= 1;
                return;
            }
        }
    }

    public void inOrderTraversal() {
        inOrderTraversal(1);
        System.out.println(); // Move to the next line after traversal
    }

    private void inOrderTraversal(int index) {
        if (inBounds(index)) {
            inOrderTraversal(leftIndex(index));
            System.out.print(contents[index] + " ");
            inOrderTraversal(rightIndex(index));
        }
    }

    public void preOrderTraversal() {
        preOrderTraversal(1);
        System.out.println(); // Move to the next line after traversal
    }

    private void preOrderTraversal(int index) {
        if (inBounds(index)) {
            System.out.print(contents[index] + " ");
            preOrderTraversal(leftIndex(index));
            preOrderTraversal(rightIndex(index));
        }
    }

    public void postOrderTraversal() {
        postOrderTraversal(1);
        System.out.println(); // Move to the next line after traversal
    }

    private void postOrderTraversal(int index) {
        if (inBounds(index)) {
            postOrderTraversal(leftIndex(index));
            postOrderTraversal(rightIndex(index));
            System.out.print(contents[index] + " ");
        }
    }

    private void resize(int capacity) {
        Object[] temp = new Object[capacity];
        System.arraycopy(contents, 0, temp, 0, size + 1);
        contents = temp;
    }

    public String toString() {
        return toStringHelper(1, "");
    }

    /* Recursive helper method for toString. */
    private String toStringHelper(int index, String soFar) {
        if (getNode(index) == null) {
            return "";
        } else {
            String toReturn = "";
            int rightChild = rightIndex(index);
            toReturn += toStringHelper(rightChild, "        " + soFar);
            if (getNode(rightChild) != null) {
                toReturn += soFar + "    /";
            }
            toReturn += "\n" + soFar + getNode(index) + "\n";
            int leftChild = leftIndex(index);
            if (getNode(leftChild) != null) {
                toReturn += soFar + "    \\";
            }
            toReturn += toStringHelper(leftChild, "        " + soFar);
            return toReturn;
        }
    }



    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Create an ArrayBinaryTree
        ArrayBinaryTree<Integer> binaryTree = new ArrayBinaryTree<>();

        // Input a sequence of integers to build the binary tree
        System.out.println("Enter a sequence of integers for the binary tree (end with Enter):");

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();

            if (line.isEmpty()) {
                // Stop input if an empty line is entered
                break;
            }

            try {
                int num = Integer.parseInt(line);
                binaryTree.insert(num);
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter integers only.");
            }
        }


        // Display the binary tree
        System.out.println("Binary Tree representation:");
        System.out.println(binaryTree);

        // In-order traversal
        System.out.print("In-order traversal: ");
        binaryTree.inOrderTraversal();

        // Pre-order traversal
        System.out.print("Pre-order traversal: ");
        binaryTree.preOrderTraversal();

        // Post-order traversal
        System.out.print("Post-order traversal: ");
        binaryTree.postOrderTraversal();

        // Remove a node from the binary tree
        System.out.println("Enter an integer to remove from the binary tree:");
        int numToRemove = scanner.nextInt();
        binaryTree.remove(numToRemove);

        // Display the binary tree after removal
        System.out.println("Binary Tree representation after removal:");
        System.out.println(binaryTree);

        // Close the scanner
        scanner.close();
    }


}
