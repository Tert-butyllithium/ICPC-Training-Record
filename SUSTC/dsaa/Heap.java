import java.util.*;

// public class Help {

//     public static void main(String[] args) {
//        Heap<Integer> heap=new Heap<>((a,b)->(Integer.compare(b,a)));
//        heap.addAll(new Integer[]{1, 5, 6, 3, 2, 1, 5, 9, 0, 2});
//        System.out.println(heap);
//     }
// }


public class Heap<T>{
    private ArrayList<T> list;
    private int sz;
    private final Comparator<? super T> comparator;

    <T extends Comparable<T>>Heap () {
        list = new ArrayList<>();
        list.add(null);
        sz=0;
        this.comparator=null;
    }

    Heap(Comparator<? super T> comparator){
        list = new ArrayList<>();
        list.add(null);
        sz=0;
        this.comparator=comparator;
    }

    private boolean smaller(T a,T b){
        if(this.comparator==null){
            Comparable<? super T> c= (Comparable<? super T>) a;
            return c.compareTo(b)<0;
        }
        else{
            return comparator.compare(a,b)<0;
        }
    }

    private void swap(int a,int b){
        var tmp=list.get(a);
        list.set(a,list.get(b));
        list.set(b,tmp);
    }

    private boolean maintain(int index){
        if(index==0) return true;
        int left=index<<1;
        int right=index<<1|1;
        if(left>sz) return true;
        T cur=list.get(index);
        T lc=list.get(left);

        T rc;
        if(right<=sz) {
            rc = list.get(right);
            if (smaller(cur,lc)&& smaller(cur,rc)) return true;
            if (smaller(lc,rc)) {
                swap(left, index);
            } else {
                swap(right, index);
            }
        }
        else{
            if(smaller(lc,cur)) swap(index,left);
            else return true;
        }
        return false;
    }

    private void pushup(int index){
        if(maintain(index)) return;
        pushup(index>>1);
    }

    private void pushdown(int index){
        if(maintain(index)) return;
        pushdown(index<<1);
        pushdown(index<<1|1);
    }

    public void enqueue(T val){
        list.add(val);
        sz++;
        pushup((sz)>>1);
    }


    public T dequeue(){
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

    public void addAll(Collection<T> col){
        for(T t:col){
            enqueue(t);
        }
    }

    public void addAll(T[] arr){
        for(T t:arr){
            enqueue(t);
        }
    }

    public ArrayList<T> HeapSort(){
        ArrayList<T> res=new ArrayList<>();
        while(!isEmpty()){
            res.add(dequeue());
        }
        /*list=res;
        sz=res.size()-1;
        */
        addAll(res);
        return res;
    }

    @Override
    public String toString() {
        return HeapSort().toString();
    }
}
