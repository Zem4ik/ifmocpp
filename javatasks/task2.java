/**
 * Created by vlad on 19.02.2016.
 */
public class BinarySearch {
    static int binarySearch(int[] array, int key) {
        int left = 0;
        int right = array.length;
        int mid = 0;
        //pre: l = 0; right = array.length
        //inv: l <= r
        while (left < right) {
            mid = (right + left) / 2;
            if (array[mid] <= key) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        //post: l <= r; a[l] <= key; l->max
        return right;
    }

    public static void main(String[] args) {
        int key = Integer.parseInt(args[0]); //число, которое надо найти
        int[] array = new int[args.length - 1]; // массив чисел
        for (int i = 0; i < args.length - 1; i++){
            array[i] = Integer.parseInt(args[i + 1]); //заполнение массива чисел
        }
        int pos = binarySearch(array, key); //array[pos] <= key, pos->max
        System.out.println(pos);
    }
}
