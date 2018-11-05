import javax.swing.*;
import java.util.ArrayList;
import java.util.Comparator;

public class Test {
    public static void main(String[] args) {
        Heap<Integer> heap=new Heap<>();
        heap.push(1);
        heap.push(3);
        heap.push(7);
        heap.push(0);
        heap.push(2);
        heap.push(8);
        while(!heap.isEmpty()) {
            System.out.println(heap.pop());
        }
    }
}

class Heap<T>{
    private ArrayList<T> list;
    private int sz;
    private Comparator<? super T> comparator;
    <T extends Comparable<T>>Heap () {
        list = new ArrayList<>();
        list.add(null);
        sz=0;
        this.comparator= (T a,T b)->a.compareTo(b);
    }
    Heap(Comparator<? super T> comparator){
        list = new ArrayList<>();
        list.add(null);
        sz=0;
        this.comparator=comparator;
    }

    private void swap(int a,int b){
        var tmp=list.get(a);
        list.set(a,list.get(b));
        list.set(b,tmp);
    }

    private boolean mantain(int index){
        if(index==0) return true;
        int left=index<<1;
        int right=index<<1|1;
        if(left>sz) return true;
        T cur=list.get(index);
        T lc=list.get(left);

        T rc;
        if(right<=sz) {
            rc = list.get(right);
            if (comparator.compare(cur,lc) < 0 && comparator.compare(cur,rc) < 0) return true;
            if (comparator.compare(lc,rc) < 0) {
                swap(left, index);
            } else {
                swap(right, index);
            }
        }
        else{
            if(comparator.compare(cur,lc)<0) swap(index,left);
        }
        return false;
    }

    private void pushup(int index){
        if(mantain(index)) return;
        pushup(index>>1);
    }

    private void pushdown(int index){
        if(mantain(index)) return;
        pushdown(index<<1);
        pushdown(index<<1|1);
    }

    public void push(T val){
         list.add(val);
         sz++;
         pushup((list.size()-1)>>1);
    }

    public T pop(){
        int last=sz;
        T res=list.get(1);
        swap(1,last);
        list.remove(last);
        sz--;
        pushdown(1);

        return res;
    }

    public boolean isEmpty(){
        return sz==0;
    }

}
