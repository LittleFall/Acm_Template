//Treap.cpp 随机平衡二叉搜索树(树堆)
int root; //当前根节点
int id; //新节点插入位置
struct Treap
{
    int l; //左子树
    int r; //右子树
    int v; //节点值
    int p; //随机权重,注意堆是最大堆
    int m; //下辖数字个数
    int b; //本值重复出现的次数
} tr[M];     //从1计数
//private:
void update(int rt)
{
    tr[rt].m = tr[tr[rt].l].m + tr[tr[rt].r].m + tr[rt].b;
}
void lturn(int &rt)
{
    //左旋rt,并将nrt置为rt
    int nrt = tr[rt].r;
    tr[rt].r = tr[nrt].l;
    tr[nrt].l = rt;
    tr[nrt].m = tr[rt].m;
    update(rt);
    rt = nrt;
}
void rturn(int &rt)
{
    int nrt = tr[rt].l;
    tr[rt].l = tr[nrt].r;
    tr[nrt].r = rt;
    tr[nrt].m = tr[rt].m;
    update(rt);
    rt = nrt;
}

//public:
void insert(int &rt, int x)
{
    //rt为当前根节点,类型是引用:返回时可以置子节点.
    if(rt == 0) //插入新叶子
    {
        rt = ++id;
        tr[rt].v = x;
        tr[rt].m = tr[rt].b = 1;
        tr[rt].p = rand();
        return;
    }
    tr[rt].m++;
    if(x == tr[rt].v) tr[rt].b++;
    else if(x > tr[rt].v) //插入右子树
    {
        insert(tr[rt].r, x);
        if(tr[tr[rt].r].p > tr[rt].p) lturn(rt);
    }
    else
    {
        insert(tr[rt].l, x);
        if(tr[tr[rt].l].p > tr[rt].p) rturn(rt);    
    }
}
void del(int &rt, int x)
{
    if(rt == 0) return;
    if(tr[rt].v == x) //find it
    {
        if(tr[rt].b > 1) //重复节点
            tr[rt].b--, tr[rt].m--;
        else if(tr[rt].l * tr[rt].r == 0) //只有一个或没有孩子
            rt = tr[rt].l + tr[rt].r;
        else if(tr[tr[rt].l].p < tr[tr[rt].r].p)
            lturn(rt), del(rt, x);
        else rturn(rt), del(rt, x);
    }
    else if(x > tr[rt].v) //需要在右子树中查找
        tr[rt].m--, del(tr[rt].r, x);
    else tr[rt].m--, del(tr[rt].l, x);
}
//注意排名定义为比当前数小的数字个数+1
int getrank(int rt, int x)
{
    if(rt == 0) return 0; //查找失败,返回一个lower_bound??
    if(x == tr[rt].v) //find it
        return tr[tr[rt].l].m + 1;
    if(x > tr[rt].v) //需要在右子树中查找
        return tr[tr[rt].l].m +tr[rt].b +getrank(tr[rt].r, x);
    return getrank(tr[rt].l, x);
}
int getnum(int rt, int rank)
{
    if(rt == 0) return 0; //??
    if(rank <= tr[tr[rt].l].m) return getnum(tr[rt].l, rank);
    rank -= tr[tr[rt].l].m;
    if(rank <= tr[rt].b) return tr[rt].v;
    return getnum(tr[rt].r, rank - tr[rt].b);
}
int getprev(int rt, int x)
{
    if(rt == 0) return INT_MIN; //本区域无解
    if(tr[rt].v >= x)return getprev(tr[rt].l, x);
    return max(tr[rt].v, getprev(tr[rt].r, x));
}
int getnext(int rt, int x)
{
    if(rt == 0) return INT_MAX;
    if(tr[rt].v <= x) return getnext(tr[rt].r, x);
    return min(tr[rt].v, getnext(tr[rt].l, x));
}
