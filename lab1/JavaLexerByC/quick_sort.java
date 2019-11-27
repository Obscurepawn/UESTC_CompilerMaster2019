/***test comment***/package qsort; //////

class divide_array {
    int partition(int array[], int Low, int High) {
        if (Low >= High) {
            return -1;
        }
        int low = Low + 1;
        int high = High;
        int tmp;
        while (low <= high) {
            while (low <= high && array[low] < array[Low])
                low++;
            while (low <= high && array[high] >= array[Low])
                high--;
            if (low <= high) {
                tmp = array[low];
                array[low] = array[high];
                array[high] = tmp;
            }
        }
        if (array[high] < array[Low]) {
            tmp = array[Low];
            array[Low] = array[high];
            array[high] = tmp;
        }
        return high;
    }

    void test() {
        int array[] = { 3, 7, 1, 2, 3, 2, 9, 0, 7, 6, 5, 4 };
        partition(array, 0, 11);
        for (int i = 0; i < 12; ++i)
            System.out.print(array[i] + "  ");
    }

    void Quicksort(int array[], int Low, int High) {
        if (Low >= High) {
            return;
        }
        int high = partition(array, Low, High);
        Quicksort(array, Low, high - 1);
        Quicksort(array, high + 1, High);
    }
}

public class quick_sort {
    public static void main(String[] args) {
        int array[] = { 4, 5, 9, 7, 3, 2, 3, 4, 5, 0, 2, 3, 7, 2, 997, 3, 65, 3 };
        divide_array test = new divide_array();
        test.Quicksort(array, 0, 17);
        for (int i = 0; i < 18; ++i)
            System.out.print(array[i] + "  ");
        return;
    }
}
