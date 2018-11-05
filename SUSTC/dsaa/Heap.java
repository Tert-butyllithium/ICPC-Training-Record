import java.util.*;

// public class Help {

//     public static void main(String[] args) {
//        Heap<Integer> heap=new Heap<>((a,b)->(Integer.compare(b,a)));
//        heap.addAll(new Integer[]{1, 5, 6, 3, 2, 1, 5, 9, 0, 2});
//        System.out.println(heap);
//     }
// }


class Heap<T> implements Queue<T>{
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

    private boolean enqueue(T val){
        if(val==null) return false;
        list.add(val);
        sz++;
        pushup((sz)>>1);
        return true;
    }


    private T dequeue(){
        if(sz==0) throw new NoSuchElementException();
        int last=sz;
        T res=list.get(1);
        swap(1,last);
        list.remove(last);
        sz--;
        pushdown(1);

        return res;
    }

    @Override
    public int size() {
        return sz;
    }

    @Override
    public boolean isEmpty(){
        return sz==0;
    }

    @Override
    public boolean contains(Object o) {
        return list.contains(o);
    }

    @NotNull
    @Override
    public Iterator<T> iterator() {
        return list.iterator();
    }

    @NotNull
    @Override
    public Object[] toArray() {
        return list.toArray();
    }

    @NotNull
    @Override
    public <T1> T1[] toArray(@NotNull T1[] a) {
        return list.toArray(a);
    }

    @Override
    public boolean addAll(Collection<? extends T> col){
        if(col==null) return false;
        for(T t:col){
            enqueue(t);
        }
        return true;
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

    @Override
    public boolean add(T t) {
        return enqueue(t);
    }

    @Override
    public boolean remove(Object o) {
        int index=1;
        for(;index<=sz;index++){
            if(list.get(index).equals(o)){
                swap(1,index);
                dequeue();
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean containsAll(@NotNull Collection<?> c) {
        return list.containsAll(c);
    }

    @Override
    public boolean removeAll(@NotNull Collection<?> c) {
        Objects.requireNonNull(c);
        boolean modified=false;
        for(int i=1;i<=sz;i++){
            T t=list.get(i);
            if(c.contains(t)){
                remove(t);
                modified=true;
            }
        }
        return modified;
    }

    @Override
    public boolean retainAll(@NotNull Collection<?> c) {
        Objects.requireNonNull(c);
        boolean modified=false;
        for(int i=1;i<=sz;i++){
            T t=list.get(i);
            if(!c.contains(t)){
                remove(t);
                modified=true;
            }
        }
        return modified;
    }

    @Override
    public void clear() {
        list.clear();
        sz=0;
    }

    @Override
    public boolean offer(T t) {
        return enqueue(t);
    }

    @Override
    public T remove() {
        return dequeue();
    }

    @Override
    public T poll() {
        if(sz==0)
        return null;
        else return dequeue();
    }

    @Override
    public T element() {
        if(sz<1) throw new NoSuchElementException();
        return list.get(1);
    }

    @Override
    public T peek() {
        if(sz<1) return null;
        return list.get(1);
    }

}
