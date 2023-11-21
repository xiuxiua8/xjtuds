
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

/**
 * Implementation of interface Map61B with BST as core data structure.
 *
 * @author Wang Zilong
 */
public class BSTMap<K extends Comparable<K>, V> implements myMap<K, V> {

    private Set<K> keyset = new HashSet<>();

    private class Node {
        /* (K, V) pair stored in this Node. */
        private K key;
        private V value;

        /* Children of this Node. */
        private Node left;
        private Node right;

        private Node(K k, V v) {
            key = k;
            value = v;
        }
    }

    private Node root;  /* Root node of the tree. */
    private int size; /* The number of key-value pairs in the tree */

    /* Creates an empty BSTMap. */
    public BSTMap() {
        this.clear();
    }

    /* Removes all the mappings from this map. */
    @Override
    public void clear() {
        root = null;
        size = 0;
    }

    /** return node */
    private Node go(Node node, K key) {
        if (key.compareTo(node.key) < 0) {
            return node.left;
        } else if (key.compareTo(node.key) > 0) {
            return node.right;
        } else {
            return null;
        }
    }
    /** go to the right node, then return that node
     * */
    private Node gotothebottom(Node node, K key) {
        Node ndptr = node;
        while (go(ndptr, key) != null) {
            ndptr = gotothebottom(go(ndptr, key), key);
        }
        //System.out.println("1");
        return ndptr;
    }

    private Node gotoparentnode(Node node, Node cnode, K key) {
        Node ndptr = node;
        while (go(ndptr, key) != cnode) {
            if (go(ndptr, key) == null) {
                return null;
            }
            ndptr = gotoparentnode(go(ndptr, key), cnode, key);
        }
        //System.out.println("1");
        return ndptr;
    }

    private Node gotoleft(Node node) {
        Node ndptr = node.left;
        if (ndptr == null) {
            return null;
        } else {
            while (ndptr.right != null) {
                ndptr = ndptr.right;
            }
            return ndptr;
        }
    }

    private Node gotoright(Node node) {
        Node ndptr = node.right;
        if (ndptr == null) {
            return null;
        } else {
            while (ndptr.left != null) {
                ndptr = ndptr.left;
            }
            return ndptr;
        }
    }



    private Node find(Node T, K sk) {
        if (T == null) {
            return null;
        }
        if (sk.equals(T.key)) {
            return T;
        } else if (sk.compareTo(T.key) < 0) {
            return find(T.left, sk);
        } else {
            return find(T.right, sk);
        }
    }

    /** Returns the value mapped to by KEY in the subtree rooted in P.
     *  or null if this map contains no mapping for the key.
     */
    private V getHelper(K key, Node p) {
        if (p.key.equals(key)) {
            return p.value;
        } else {
            return null;
        }
    }

    /** Returns the value to which the specified key is mapped, or null if this
     *  map contains no mapping for the key.
     */
    @Override
    public V get(K key) {
        if (root == null) {
            return null;
        }
        Node node = gotothebottom(root, key);
        //Node node = find(root, key);
        return getHelper(key, node);

    }

    /** Returns a BSTMap rooted in p with (KEY, VALUE) added as a key-value mapping.
      * Or if p is null, it returns a one node BSTMap containing (KEY, VALUE).
     */
    private Node putHelper(K key, V value, Node p) {
        if (p == null) {
            p = new Node(key, value);
            return p;
        } else if (key.compareTo(p.key) == 0) {
            //Node node = go(p, key);
            p.value = value;
            return p;
        } else {
            Node node = new Node(key, value);
            if (key.compareTo(p.key) < 0) {
                p.left = node;
                return p.left;
            }
            if (key.compareTo(p.key) > 0) {
                p.right = node;
                return p.right;
            }
            return null;
        }
    }


    /** Inserts the key KEY
     *  If it is already present, updates value to be VALUE.
     */
    @Override
    public void put(K key, V value) {
        if (!keySet().contains(key)) {
            keyset.add(key);
        }
        if (root == null) {
            root = putHelper(key, value, root);
            size += 1;
            return;
        }

        Node node = gotothebottom(root, key);
        //Node node = find(root, key);
        putHelper(key, value, node);
        //throw new UnsupportedOperationException();
        size += 1;
    }

    /* Returns the number of key-value mappings in this map. */
    @Override
    public int size() {
        return size;
    }

    //////////////// EVERYTHING BELOW THIS LINE IS OPTIONAL ////////////////

    /* Returns a Set view of the keys contained in this map. */
    @Override
    public Set<K> keySet() {
        return keyset;
    }

    /** Delete the instance of key from Node that is closest
     *  to the root and return the modified tree. The nodes of
     *  the original tree may be modified. */
    public Node removehelper(Node node, K key) {
        if (node == null) {
            return null;
        }
        if (key.compareTo(node.key) < 0) {
            node.left = removehelper(node.left, key);
        } else if (key.compareTo(node.key) > 0) {
            node.right = removehelper(node.right, key);
        } else if (node.left == null) {
            // Otherwise, we’ve found key
            return node.right;
        } else if (node.right == null) {
            return node.left;
        } else {
            node.right = swapSmallest(node.right, node);
        }
        return node;
    }

    /** Move the label from the first node in node (in an inorder
     *  traversal) to node R (over-writing the current label of R),
     *  remove the first node of node from node, and return the resulting tree. */
    private Node swapSmallest(Node node, Node R) {
        if (node.left == null) {
            R.key = node.key;
            return node.right;
        } else {
            node.left = swapSmallest(node.left, R);
            return node;
        }
    }

    /** Removes KEY from the tree if present
     *  returns VALUE removed,
     *  null on failed removal.
     */
    @Override
    public V remove(K key) {
        if (removehelper(root, key) == null) {
            return null;
        }
        size -= 1;
        keyset.remove(key);
        return removehelper(root, key).value;
    }


    /** Removes the key-value entry for the specified key only if it is
     *  currently mapped to the specified value.  Returns the VALUE removed,
     *  null on failed removal.
     **/
    @Override
    public V remove(K key, V value) {
        if (get(key).equals(value)) {
            return remove(key);
        } else {
            return null;
        }
    }

    @Override
    public Iterator<K> iterator() {
        //throw new UnsupportedOperationException();
        return new BSTIterator();
    }


    private class BSTIterator implements Iterator<K> {
        private int currentIndex = 0;
        //private Node[] Queue = new Node[16];

        @Override
        public boolean hasNext() {
            //return root.left == null || root.right == null;
            return false;
        }

        @Override
        public K next() {
            return root.key;
        }

    }



    public static void main(String[] args) {
        BSTMap<String, Integer> bstmap = new BSTMap<>();
        bstmap.put("hello", 5);
        System.out.println(bstmap.get("hello"));
        bstmap.put("cat", 10);
        bstmap.put("fish", 22);
        bstmap.put("zebra", 90);
        bstmap.put("apple", 1);
        bstmap.put("batman", 2);
        bstmap.put("catman", 2);
        bstmap.put("datman", 2);
        bstmap.put("eatman", 2);
        bstmap.put("fatman", 2);
        bstmap.remove("cat");
        //System.out.println(bstmap.gotoleft(bstmap.root).key);
        System.out.println(bstmap.get("hello"));
        System.out.println(bstmap.get("hello1"));
    }
}

