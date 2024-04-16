public class Board {
    private final int[] board;

    public Board(int[] board) {
        this.board = board;
    }

    public void move(char direction) {
        int zeroIndex = findZeroIndex();
        int targetIndex = -1;
        int rows = (int) Math.sqrt(board.length);
        switch (direction) {
            case 'u':
                targetIndex = zeroIndex + rows;
                break;
            case 'd':
                targetIndex = zeroIndex - rows;
                break;
            case 'l':
                if ((zeroIndex + 1) % rows != 0) {
                    targetIndex = zeroIndex + 1;
                }

                break;
            case 'r':
                if (zeroIndex % rows != 0) {
                    targetIndex = zeroIndex - 1;
                }

                break;
            default:
                throw new IllegalStateException("Unexpected value: " + direction);
        }
        if (targetIndex >= 0 && targetIndex < board.length) {
            int temp = board[targetIndex];
            board[targetIndex] = board[zeroIndex];
            board[zeroIndex] = temp;
        }
    }

    public boolean isSolved() {
        for (int i = 0; i < board.length - 1; i++) {
            if (board[i] != i) {
                return false;
            }
        }
        return true;
    }

    private int findZeroIndex() {
        for (int i = 0; i < board.length; i++) {
            if (board[i] == 0) {
                return i;
            }
        }
        return -1;
    }

    public void printBoard() {
        int rows = (int) Math.sqrt(board.length);
        int cellWidth = 6;
        String horizontalBorder = "+" + ("-".repeat(cellWidth) + "+").repeat(rows);
        System.out.println(horizontalBorder);
        for (int i = 0; i < board.length; i++) {
            if (i % rows == 0 && i != 0) {
                System.out.println(horizontalBorder);
            }
            if (board[i] < 10) {
                System.out.printf("|   %d  ", board[i]);
            } else {
                System.out.printf("|  %d  ", board[i]);
            }

            if ((i + 1) % rows == 0) {
                System.out.println("|");
            }
        }
        System.out.println(horizontalBorder);
    }
}