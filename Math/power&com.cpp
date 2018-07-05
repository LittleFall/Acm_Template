//快速幂power()
//求组合数: ab较小p较大时使用com(),ab较大p较小时使用lucas(),需要预处理阶乘
ll fac[M];
ll power(ll a, ll b, ll p)
{
    ll ans = 1;
    while(b)
    {
        if(b & 1)  ans = ans * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return  ans;
}
ll com(ll n, ll m, ll p)
{
    if (m > n) return 0;
    return fac[n] * power(fac[m], p - 2, p) % p * power(fac[n - m], p - 2, p) % p;
}
ll lucas(ll n, ll m, ll p)
{
    if(m == 0)  return 1;
    return (com(n % p, m % p, p) * lucas(n / p, m / p, p)) % p;
}
