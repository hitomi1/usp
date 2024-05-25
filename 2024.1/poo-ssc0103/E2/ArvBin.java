import java.util.ArrayList;

public class ArvBin {

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
