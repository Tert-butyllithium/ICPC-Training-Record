
class AVLTree<T> {
    private class Node<T> {
        T key;
        int height;
        Node<T> left;
        Node<T> right;

        Node(T key, Node<T> left, Node<T> right) {
            this.key = key;
            this.left = left;
            this.right = right;
            this.height = 0;
        }

        void Maintain(){
            if(this.left==null&&this.right==null){
                this.height=0;
            }
            else{
                if(this.left==null){
                    this.height=this.right.height+1;
                }
                else if(this.right==null){
                    this.height=this.left.height+1;
                }
                else{
                    this.height=Math.max(this.left.height,this.right.height)+1;
                }
            }
        }


    }

    Node<T> MaxInSubtree(Node<T> cur){
        if(cur==null) return null;
        if(cur.left==null&&cur.right==null) return cur;
            Node<T> MaxLeft=MaxInSubtree(cur.left);
            Node<T> MaxRight=MaxInSubtree(cur.right);
            if(compare(MaxLeft.key,MaxRight.key)>0) {
                if(compare(MaxLeft.key,cur.key)>0){
                    return MaxLeft;
                }
                else return cur;
            }
            else {
              if(compare(MaxRight.key,cur.key)>0)
                  return MaxLeft;
              else return cur;
            }
    }

    <T extends Comparable<? super T>> AVLTree() {
        this.sz = 0;
        this.comparator = null;
    }

    AVLTree(Comparator<? super T> comparator) {
        this.comparator = comparator;
        this.sz = 0;
    }



    private Node<T> root;
    private int sz;
    private final Comparator<? super T> comparator;

    public int height() {
        if (root == null) return 0;
        else return root.height;
    }

    private int compare(T a, T b) {
        if(a==null&&b==null) return 0;
        if(a==null) return -1;
        if(b==null) return 1;
        if (comparator == null) {
            return ((Comparable<T>) a).compareTo(b);
        } else {
            return comparator.compare(a, b);
        }
    }

    /*          left-left rotate (x with highest)
     *         CUR                         LC
     *       /   \                       /    \
     *      LC    Z      ------->       X     CUR
     *     /  \                              /   \
     *    X   Y                            Y      Z
     */

    private Node<T> LLRotate(Node<T> cur){
        Node<T> lc=cur.left;
        cur.left=lc.right;
        lc.right=cur;

        cur.Maintain();
        lc.Maintain();
        return lc;
    }

    /*          right-right rotate (Z with highest)
     *         CUR                         RC
     *       /   \                       /    \
     *      X    RC      ------->       CUR    Z
     *          /  \                `` /   \
     *         Y   Z                  X     Y
     */
    private Node<T> RRRotate(Node<T> cur){
        Node<T> rc=cur.right;
        cur.right=rc.left;
        rc.left=cur;

        cur.Maintain();
        rc.Maintain();
        return rc;
    }

    /*                                left-right rotate (A, B, C, D with same height)
     *         CUR                                            CUR                                   LRC
     *       /   \         RR-rotate (with LC)              /    \      LL-rotate(with CUR)       /    \
     *      LC    D      --------------------->           LRC    D   ---------------------->    LC    CUR
     *     /  \                                          /   \                                 /  \   /  \
     *    A   LRC                                      LC    C                                A   B  C   D
     *       /   \                                    /  \
     *      B    C                                   A   B
     */

    private Node<T> LRRotate(Node<T> cur){
        cur.left=RRRotate(cur.left);
        return LLRotate(cur);
    }

    /*                                right-left rotate (A, B, C, D with same height)
     *         CUR                                            CUR                                   RLC
     *       /   \         LL-rotate (with RC)              /    \      RR-rotate(with CUR)       /    \
     *      A     RC      --------------------->           A     RLC   ---------------------->   CUR    RC
     *           /   \                                          /   \                           /  \   /  \
     *          RLC   D                                       B      RC                        A   B  C   D
     *         /   \                                                /  \
     *        B    C                                               C    D
     */
    private Node<T> RLRotate(Node<T> cur){
        cur.right=LLRotate(cur.right);
        return RRRotate(cur);
    }

    private Node<T> insert(Node<T> root,T val){
        if(root==null){
            root=new Node<>(val,null,null);
            return root;
        }
        int cmp=compare(val,root.key);
        if(cmp<0){
            root.left=insert(root.left,val);
            if(root.left.height-root.right.height>1) {
                if (compare(val, root.left.key) < 0) root = LLRotate(root);
                else root = LRRotate(root);
            }
        }
        else if(cmp>0){
            root.right=insert(root.right,val);
            if(root.right.height-root.left.height>1){
                if(compare(val,root.right.key)<0) root=RLRotate(root);
                else root=RRRotate(root);
            }
        }
        root.Maintain();
        return root;
    }

    public void Insert(T val){
        this.root=insert(root,val);
    }

    private Node<T> remove(Node<T> root,Node<T> to_remove){
        if(root==null||to_remove==null)
            return null;

        int cmp=compare(to_remove.key,root.key);
        if(cmp<0){
            root.left=remove(root.left,to_remove);
            if(root.right.height-root.left.height>1){
                Node<T> rc=root.right;
                if(rc.left.height>rc.right.height)
                    root=RLRotate(root);
                else
                    root=RRRotate(root);
            }
        }
        else if(cmp>0){
            root.right=remove(root.left,to_remove);
            if(root.left.height-root.right.height>1){
                Node<T> lc=root.left;
                if(lc.left.height>lc.right.height)
                    root=LLRotate(root);
                else
                    root=LRRotate(root);
            }
        }
        else{
            if(root.left!=null&&root.right!=null){
                if(root.left.height>root.right.height){

                }
            }
        }
        root.Maintain();
    }
