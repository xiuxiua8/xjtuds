

import java.util.Scanner;
public class ArrayBinaryTree<T extends Comparable<T>> {
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
        return index > 0 && index <= contents.length;
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

        size += 1;
        //contents[size] = item;
        inserthelper(item, 1);
    }

    private void inserthelper(T item, int root) {
        if (root >= contents.length) {
            resize(contents.length * 2);
        }
        if (contents[root] == null) {
            contents[root] = item;
        } else {
            if (item.compareTo((T) contents[root]) > 0) {
                inserthelper(item, rightIndex(root));
            } else if (item.compareTo((T) contents[root]) < 0) {
                inserthelper(item, leftIndex(root));
            } else {
                // Item is already in the tree
                size -= 1; // Decrement size as the item is not actually inserted
                return;
            }
        }
    }



    public void remove(T item) {
        Object[] temp = new Object[16];
        //System.arraycopy(contents, 0, temp, 0, contents.length);
        //System.arraycopy(contents, 0, temp, 0, contents.length);
        int j = 0;
        for (int i = 1; i < contents.length; i += 1) {
            if (contents[i] != null) {
                if (!contents[i].equals(item)) {
                    temp[j] = contents[i];
                    j++;
                }
            }
        }
        contents = new Object[16];
        size = 0;
        for (int k = 0; k < j; k += 1) {
            insert((T) temp[k]);
        }
    }


    public void inOrderTraversal() {
        inOrderTraversal(1);
        System.out.println(); // Move to the next line after traversal
    }

    private void inOrderTraversal(int index) {
        if (inBounds(index)) {
            if (inBounds(leftIndex(index))) {
                if (contents[leftIndex(index)] != null) {
                    inOrderTraversal(leftIndex(index));
                }
            }
            System.out.print(contents[index] + " ");
            if (inBounds(rightIndex(index))) {
                if (contents[rightIndex(index)] != null) {
                    inOrderTraversal(rightIndex(index));
                }
            }
        }
    }

    public void preOrderTraversal() {
        preOrderTraversal(1);
        System.out.println(); // Move to the next line after traversal
    }

    private void preOrderTraversal(int index) {
        if (inBounds(index)) {
            System.out.print(contents[index] + " ");
            if (inBounds(leftIndex(index))) {
                if (contents[leftIndex(index)] != null) {
                    preOrderTraversal(leftIndex(index));
                }
            }
            if (inBounds(rightIndex(index))) {
                if (contents[rightIndex(index)] != null) {
                    preOrderTraversal(rightIndex(index));
                }
            }
        }
    }

    public void postOrderTraversal() {
        postOrderTraversal(1);
        System.out.println(); // Move to the next line after traversal
    }

    private void postOrderTraversal(int index) {
        if (inBounds(index)) {
            if (inBounds(leftIndex(index))) {
                if (contents[leftIndex(index)] != null) {
                    postOrderTraversal(leftIndex(index));
                }
            }
            if (inBounds(rightIndex(index))) {
                if (contents[rightIndex(index)] != null) {
                    postOrderTraversal(rightIndex(index));
                }
            }
            System.out.print(contents[index] + " ");
        }
    }

    public double averageSearchLength() {
        return (double) depthSum(1, 0) / size;
    }

    private int depthSum(int index, int depth) {
        if (!inBounds(index) || getNode(index) == null) {
            return 0;
        }
        return depth + depthSum(leftIndex(index), depth + 1) + depthSum(rightIndex(index), depth + 1);
    }

    private void resize(int capacity) {
        Object[] temp = new Object[capacity];
        System.arraycopy(contents, 0, temp, 0, contents.length);
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

        System.out.println("Average Search Length: " + binaryTree.averageSearchLength());

        // Remove a node from the binary tree
        System.out.println("Enter an integer to remove from the binary tree:");
        int numToRemove = scanner.nextInt();
        binaryTree.remove(numToRemove);

        // Display the binary tree after removal
        System.out.println("Binary Tree representation after removal:");
        System.out.println(binaryTree);

        // In-order traversal
        System.out.print("In-order traversal: ");
        binaryTree.inOrderTraversal();

        // Close the scanner
        scanner.close();
    }


}
