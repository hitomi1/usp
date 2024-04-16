import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] initialBoard = Arrays.stream(scanner.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        String moves = scanner.nextLine();
        Board board = new Board(initialBoard);

        board.printBoard();
        System.out.println();

        for (char move : moves.toCharArray()) {
            board.move(move);
            board.printBoard();
            System.out.println();
        }

        if (board.isSolved()) {
            System.out.println("Posicao final: true");
        } else {
            System.out.println("Posicao final: false");
        }
    }
}
