import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class ArvBin {

    protected final ArrayList<String> heap;

    public ArvBin() {
        this.heap = new ArrayList<>();
    }
    protected int getParentIndex(int index) {
        return (index - 1) / 2;
    }
    protected int getLeftChildIndex(int index) {
        return 2 * index + 1;
    }

    protected int getRightChildIndex(int index) {
        return 2 * index + 2;
    }

    public boolean find(String value) {
        return heap.contains(value);
    }

    public void insert(String value) {
        heap.add(value);

    }

    public int len() {
        return heap.size();
    }

    public boolean remove(String value) {
        return heap.remove(value);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("digraph {\n");
        for (int i = 0; i < heap.size(); i++) {
            if (heap.get(i) != null) {
                int leftChild = getLeftChildIndex(i);
                int rightChild = getRightChildIndex(i);
                if (leftChild < heap.size() && heap.get(leftChild) != null) {
                    sb.append(String.format("\"%d %s\" ->\"%d %s\"\n", i, heap.get(i), leftChild, heap.get(leftChild)));
                }
                if (rightChild < heap.size() && heap.get(rightChild) != null) {
                    sb.append(String.format("\"%d %s\" ->\"%d %s\"\n", i, heap.get(i), rightChild, heap.get(rightChild)));
                }
            }
        }
        sb.append("}");
        return sb.toString();
    }

    public void printHeap() {
        for (String integer : heap) {
            System.out.printf(" " + integer);
        }
        System.out.println();
    }
}

class ArvAVL extends ArvBin {

    private class AVLNode {
        String value;
        AVLNode left;
        AVLNode right;
        int height;

        AVLNode(String value) {
            this.value = value;
            this.height = 1;
        }
    }

    private AVLNode root;

    public boolean find(String value) {
        return findRecursive(root, value);
    }

    private boolean findRecursive(AVLNode node, String value) {
        if (node == null) {
            return false;
        }
        if (value.equals(node.value)) {
            return true;
        }
        if (value.compareTo(node.value) < 0) {
            return findRecursive(node.left, value);
        } else {
            return findRecursive(node.right, value);
        }
    }

    public void insert(String value) {
        root = insertRecursive(root, value);
    }

    private AVLNode insertRecursive(AVLNode node, String value) {
        if (node == null) {
            return new AVLNode(value);
        }

        if (value.compareTo(node.value) < 0) {
            node.left = insertRecursive(node.left, value);
        } else if (value.compareTo(node.value) > 0) {
            node.right = insertRecursive(node.right, value);
        } else {
            return node; // Duplicate value
        }

        // Update height of this ancestor node
        node.height = 1 + Math.max(getHeight(node.left), getHeight(node.right));

        // Get the balance factor of this ancestor node to check whether this node became unbalanced
        int balance = getBalance(node);

        // If this node becomes unbalanced, there are four cases:
        // Left Left Case
        if (balance > 1 && value.compareTo(node.left.value) < 0) {
            return rotateRight(node);
        }
        // Right Right Case
        if (balance < -1 && value.compareTo(node.right.value) > 0) {
            return rotateLeft(node);
        }
        // Left Right Case
        if (balance > 1 && value.compareTo(node.left.value) > 0) {
            node.left = rotateLeft(node.left);
            return rotateRight(node);
        }
        // Right Left Case
        if (balance < -1 && value.compareTo(node.right.value) < 0) {
            node.right = rotateRight(node.right);
            return rotateLeft(node);
        }

        return node;
    }

    private AVLNode rotateRight(AVLNode y) {
        AVLNode x = y.left;
        AVLNode T = x.right;

        // Perform rotation
        x.right = y;
        y.left = T;

        // Update heights
        y.height = Math.max(getHeight(y.left), getHeight(y.right)) + 1;
        x.height = Math.max(getHeight(x.left), getHeight(x.right)) + 1;

        // Return new root
        return x;
    }

    private AVLNode rotateLeft(AVLNode x) {
        AVLNode y = x.right;
        AVLNode T = y.left;

        // Perform rotation
        y.left = x;
        x.right = T;

        // Update heights
        x.height = Math.max(getHeight(x.left), getHeight(x.right)) + 1;
        y.height = Math.max(getHeight(y.left), getHeight(y.right)) + 1;

        // Return new root
        return y;
    }

    private int getHeight(AVLNode node) {
        return node == null ? 0 : node.height;
    }

    private int getBalance(AVLNode node) {
        return node == null ? 0 : getHeight(node.left) - getHeight(node.right);
    }

    public boolean remove(String value) {
        root = removeRecursive(root, value);
        return true;
    }

    private AVLNode removeRecursive(AVLNode node, String value) {
        if (node == null) {
            return null;
        }

        if (value.compareTo(node.value) < 0) {
            node.left = removeRecursive(node.left, value);
        } else if (value.compareTo(node.value) > 0) {
            node.right = removeRecursive(node.right, value);
        } else {
            // Node to delete found

            // Node with only one child or no child
            if (node.left == null || node.right == null) {
                AVLNode temp = null;
                if (temp == node.left) {
                    temp = node.right;
                } else {
                    temp = node.left;
                }

                // No child case
                if (temp == null) {
                    temp = node;
                    node = null;
                } else { // One child case
                    node = temp; // Copy the contents of the non-empty child
                }
            } else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                AVLNode temp = minValueNode(node.right);

                // Copy the inorder successor's data to this node
                node.value = temp.value;

                // Delete the inorder successor
                node.right = removeRecursive(node.right, temp.value);
            }
        }

        // If the tree had only one node then return
        if (node == null) {
            return null;
        }

        // Update the height of the current node
        node.height = Math.max(getHeight(node.left), getHeight(node.right)) + 1;

        // Get the balance factor of this node (to check whether this node became unbalanced)
        int balance = getBalance(node);

        // If this node becomes unbalanced, there are four cases:

        // Left Left Case
        if (balance > 1 && getBalance(node.left) >= 0) {
            return rotateRight(node);
        }

        // Left Right Case
        if (balance > 1 && getBalance(node.left) < 0) {
            node.left = rotateLeft(node.left);
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && getBalance(node.right) <= 0) {
            return rotateLeft(node);
        }

        // Right Left Case
        if (balance < -1 && getBalance(node.right) > 0) {
            node.right = rotateRight(node.right);
            return rotateLeft(node);
        }

        return node;
    }

    private AVLNode minValueNode(AVLNode node) {
        AVLNode current = node;
        while (current.left != null) {
            current = current.left;
        }
        return current;
    }
    protected int countNodes() {
        return countNodesRecursive(root);
    }

    private int countNodesRecursive(AVLNode node) {
        if (node == null) {
            return 0;
        }
        return 1 + countNodesRecursive(node.left) + countNodesRecursive(node.right);
    }
    protected String getNode(int i) {
        if (i < 0 || i >= heap.size()) {
            throw new IndexOutOfBoundsException("Index out of bounds: " + i);
        }
        return heap.get(i);
    }

    protected boolean isBalance() {
        return isBalanceRecursive(root);
    }

    private boolean isBalanceRecursive(AVLNode node) {
        if (node == null) {
            return true;
        }

        int balance = getBalance(node);
        if (balance > 1 || balance < -1) {
            return false;
        }

        return isBalanceRecursive(node.left) && isBalanceRecursive(node.right);
    }

    protected int nodeLeft(int i) {
        int leftIndex = getLeftChildIndex(i);
        return leftIndex < heap.size() ? leftIndex : -1;
    }

    protected int nodeRight(int i) {
        int rightIndex = getRightChildIndex(i);
        return rightIndex < heap.size() ? rightIndex : -1;
    }

    protected void setNode(int i, String v) {
        if (i < 0 || i >= heap.size()) {
            throw new IndexOutOfBoundsException("Index out of bounds: " + i);
        }
        heap.set(i, v);
    }
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("digraph {\n");

        if (root != null) {
            buildGraphString(sb, root, 0);
        }

        sb.append("}");

        return sb.toString();
    }

    private int buildGraphString(StringBuilder sb, AVLNode node, int index) {
        if (node == null) {
            return index;
        }
        int currentIndex = index++;

        if (node.left != null) {
            sb.append(String.format("\"%d %s\" ->\"%d %s\"\n",currentIndex, node.value, index, node.left.value));
//
        }
        index = buildGraphString(sb, node.left, index);
        if (node.right != null) {
            sb.append(String.format("\"%d %s\" ->\"%d %s\"\n", currentIndex, node.value, index, node.right.value));
        }
        index = buildGraphString(sb, node.right, index);

        return index;
    }



}

class ArvBal extends ArvBin {

    private class BalNODE {
        String value;
        BalNODE left;
        BalNODE right;
        int height;

        BalNODE(String value) {
            this.value = value;
            this.height = 1;
        }
    }

    private BalNODE root;

    public boolean find(String value) {
        return findRecursive(root, value);
    }

    private boolean findRecursive(BalNODE node, String value) {
        if (node == null) {
            return false;
        }
        if (value.equals(node.value)) {
            return true;
        }
        if (value.compareTo(node.value) < 0) {
            return findRecursive(node.left, value);
        } else {
            return findRecursive(node.right, value);
        }
    }

    public void insert(String value) {
        root = insertRecursive(root, value);
    }

    private BalNODE insertRecursive(BalNODE node, String value) {
        if (node == null) {
            return new BalNODE(value);
        }

        if (value.compareTo(node.value) < 0) {
            node.left = insertRecursive(node.left, value);
        } else if (value.compareTo(node.value) > 0) {
            node.right = insertRecursive(node.right, value);
        } else {
            return node; // Duplicate value
        }

        // Update height of this ancestor node
        node.height = 1 + Math.max(getHeight(node.left), getHeight(node.right));

        // Get the balance factor of this ancestor node to check whether this node became unbalanced
        int balance = getBalance(node);

        // If this node becomes unbalanced, there are four cases:
        // Left Left Case
        if (balance > 1 && value.compareTo(node.left.value) < 0) {
            return rotateRight(node);
        }
        // Right Right Case
        if (balance < -1 && value.compareTo(node.right.value) > 0) {
            return rotateLeft(node);
        }
        // Left Right Case
        if (balance > 1 && value.compareTo(node.left.value) > 0) {
            node.left = rotateLeft(node.left);
            return rotateRight(node);
        }
        // Right Left Case
        if (balance < -1 && value.compareTo(node.right.value) < 0) {
            node.right = rotateRight(node.right);
            return rotateLeft(node);
        }

        return node;
    }

    private BalNODE rotateRight(BalNODE y) {
        BalNODE x = y.left;
        BalNODE T = x.right;

        // Perform rotation
        x.right = y;
        y.left = T;

        // Update heights
        y.height = Math.max(getHeight(y.left), getHeight(y.right)) + 1;
        x.height = Math.max(getHeight(x.left), getHeight(x.right)) + 1;

        // Return new root
        return x;
    }

    private BalNODE rotateLeft(BalNODE x) {
        BalNODE y = x.right;
        BalNODE T = y.left;

        // Perform rotation
        y.left = x;
        x.right = T;

        // Update heights
        x.height = Math.max(getHeight(x.left), getHeight(x.right)) + 1;
        y.height = Math.max(getHeight(y.left), getHeight(y.right)) + 1;

        // Return new root
        return y;
    }

    private int getHeight(BalNODE node) {
        return node == null ? 0 : node.height;
    }

    private int getBalance(BalNODE node) {
        return node == null ? 0 : getHeight(node.left) - getHeight(node.right);
    }

    public boolean remove(String value) {
        root = removeRecursive(root, value);
        return true;
    }

    private BalNODE removeRecursive(BalNODE node, String value) {
        if (node == null) {
            return null;
        }

        if (value.compareTo(node.value) < 0) {
            node.left = removeRecursive(node.left, value);
        } else if (value.compareTo(node.value) > 0) {
            node.right = removeRecursive(node.right, value);
        } else {
            // Node to delete found

            // Node with only one child or no child
            if (node.left == null || node.right == null) {
                BalNODE temp = null;
                if (temp == node.left) {
                    temp = node.right;
                } else {
                    temp = node.left;
                }

                // No child case
                if (temp == null) {
                    temp = node;
                    node = null;
                } else { // One child case
                    node = temp; // Copy the contents of the non-empty child
                }
            } else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                BalNODE temp = minValueNode(node.right);

                // Copy the inorder successor's data to this node
                node.value = temp.value;

                // Delete the inorder successor
                node.right = removeRecursive(node.right, temp.value);
            }
        }

        // If the tree had only one node then return
        if (node == null) {
            return null;
        }

        // Update the height of the current node
        node.height = Math.max(getHeight(node.left), getHeight(node.right)) + 1;

        // Get the balance factor of this node (to check whether this node became unbalanced)
        int balance = getBalance(node);

        // If this node becomes unbalanced, there are four cases:

        // Left Left Case
        if (balance > 1 && getBalance(node.left) >= 0) {
            return rotateRight(node);
        }

        // Left Right Case
        if (balance > 1 && getBalance(node.left) < 0) {
            node.left = rotateLeft(node.left);
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && getBalance(node.right) <= 0) {
            return rotateLeft(node);
        }

        // Right Left Case
        if (balance < -1 && getBalance(node.right) > 0) {
            node.right = rotateRight(node.right);
            return rotateLeft(node);
        }

        return node;
    }

    private BalNODE minValueNode(BalNODE node) {
        BalNODE current = node;
        while (current.left != null) {
            current = current.left;
        }
        return current;
    }
    protected int countNodes() {
        return countNodesRecursive(root);
    }

    private int countNodesRecursive(BalNODE node) {
        if (node == null) {
            return 0;
        }
        return 1 + countNodesRecursive(node.left) + countNodesRecursive(node.right);
    }
    protected String getNode(int i) {
        if (i < 0 || i >= heap.size()) {
            throw new IndexOutOfBoundsException("Index out of bounds: " + i);
        }
        return heap.get(i);
    }

    protected boolean isBalance() {
        return isBalanceRecursive(root);
    }

    private boolean isBalanceRecursive(BalNODE node) {
        if (node == null) {
            return true;
        }

        int balance = getBalance(node);
        if (balance > 1 || balance < -1) {
            return false;
        }

        return isBalanceRecursive(node.left) && isBalanceRecursive(node.right);
    }

    protected int nodeLeft(int i) {
        int leftIndex = getLeftChildIndex(i);
        return leftIndex < heap.size() ? leftIndex : -1;
    }

    protected int nodeRight(int i) {
        int rightIndex = getRightChildIndex(i);
        return rightIndex < heap.size() ? rightIndex : -1;
    }

    protected void setNode(int i, String v) {
        if (i < 0 || i >= heap.size()) {
            throw new IndexOutOfBoundsException("Index out of bounds: " + i);
        }
        heap.set(i, v);
    }
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("digraph {\n");

        if (root != null) {
            buildGraphString(sb, root, 0);
        }

        sb.append("}");

        return sb.toString();
    }

    private int buildGraphString(StringBuilder sb, BalNODE node, int index) {
        if (node == null) {
            return index;
        }
        int currentIndex = index++;

        if (node.left != null) {
            sb.append(String.format("\"%d %s\" ->\"%d %s\"\n",currentIndex, node.value, index, node.left.value));
//
        }
        index = buildGraphString(sb, node.left, index);
        if (node.right != null) {
            sb.append(String.format("\"%d %s\" ->\"%d %s\"\n", currentIndex, node.value, index, node.right.value));
        }
        index = buildGraphString(sb, node.right, index);

        return index;
    }



}

public class Main {
public static void main(String[] args) {
    ArvBin heap = new ArvBin();
    ArvAVL avl = new ArvAVL();
    ArvBal bal = new ArvBal();

//  String john = "John";
//  String doe = "Doe";
//  heap.insert(john);
//  avl.insert(john);
//  bal.insert(john);
//  heap.insert(doe);
//  avl.insert(doe);
//  bal.insert(doe);
//  heap.insert("Jeremias");
//  avl.insert("Jeremias");
//  bal.insert("Jeremias");
//  heap.insert("Marta");
//  avl.insert("Marta");
//  bal.insert("Marta");
//  heap.insert("Guta");
//  avl.insert("Guta");
//  bal.insert("Guta");
//  heap.insert("Walter");
//  avl.insert("Walter");
//  bal.insert("Walter");
//  heap.insert("Andre");
//  avl.insert("Andre");
//  bal.insert("Andre");

    try (Scanner scanner = new Scanner(System.in)) {
        while (scanner.hasNext()) {
        String command = scanner.next();
        String value = scanner.next();
    
        System.out.println("Command:" + command + ", Value:" + value);

        if ("i".equals(command)) {
            System.out.println("Entrou insert");

            System.out.println(command);
            System.out.println(value);
            heap.insert(value);
            avl.insert(value);
            bal.insert(value);
        } else if ("d".equals(command)) {
            System.out.println("Entrou delete");

            heap.remove(value);
            avl.remove(value);
            bal.remove(value);
        }
    }
}

    System.out.println(heap);
    System.out.println(avl);
    System.out.println(bal);
}
}