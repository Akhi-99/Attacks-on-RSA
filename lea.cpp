#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i,eve[100];
char msg[100];
int fin_msg[100];
ll r;

ll c1[100],c2[100],c3[100];
ll m1,m2,m3;
ll M,M1,M2,M3;
ll i_M1,i_M2,i_M3;




ll inv(ll a, ll m) 
{ 
    ll m0 = m, t, q; 
    ll x0 = 0, x1 = 1; 

    if (m == 1) 
    return 0; 
    // Apply extended Euclid Algorithm 
    while (a > 1) 
    { 
        // q is quotient 
        q = a / m;  t = m; 
        // m is remainder now, process same as 
        // euclid's algo 
        m = a % m, a = t; 
        t = x0; 
        x0 = x1 - q * x0; 
        x1 = t; 
    } 
    // Make x1 positive 
    if (x1 < 0) 
    x1 += m0; 

    return x1; 
}

ll gcd(ll a, ll b) 
{ 
    if (b == 0) 
        return a; 
    return gcd(b, a % b);  
      
} 

ll check_gcd(ll a,ll b,ll c)
{
    ll g1=gcd(a,b);
    ll g2=gcd(b,c);
    ll g3=gcd(a,c);
    if(g1==1 && g2==1 && g3==1) return 1;
    else return 0;
}

ll gcdExtended(ll a, ll b, ll *x, ll *y) 
{ 
    // Base Case 
    if (a == 0) 
    { 
        *x = 0, *y = 1; 
        return b; 
    } 
  
    ll x1, y1; // To store results of recursive call 
    ll gcd = gcdExtended(b%a, a, &x1, &y1); 
  
    // Update x and y using results of recursive 
    // call 
    *x = y1 - (b/a) * x1; 
    *y = x1; 
  
    return gcd; 
} 

ll modInverse(ll a, ll m) 
{ 
    ll x, y; 
    ll g = gcdExtended(a, m, &x, &y); 
    if (g != 1) 
        //cout << "Inverse doesn't exist"; 
        return 0;
    else
    { 
        // m is added to handle negative x 
        ll res = (x%m + m) % m; 
        return res;
        //cout << "Modular multiplicative inverse is " << res; 
    } 
} 
 


ll power(ll x, ll y, ll p)  
{  
    ll res = 1;     // Initialize result    
    x = x % p; // Update x if it is more than or  
                // equal to p  
    if (x == 0) return 0; // In case x is divisible by p; 
    while (y > 0)  
    {  
        // If y is odd, multiply x with result  
        if (y & 1)  
            res = (res*x) % p;  
        // y must be even now  
        y = y>>1; // y = y/2  
        x = (x*x) % p;  
    }  
    return res;  
}  

ll prime(ll pr)
{
    ll i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}



void encrypt(ll e_val)
{
    ll i = 0;
    ll len = strlen(msg); //.length();
    while (i <len)
    {
        c1[i] = power(msg[i],e_val,m1);
        c2[i] = power(msg[i],e_val,m2);
        c3[i] = power(msg[i],e_val,m3);
        i++;
    }
    

    cout << "\nTHE ENCRYPTED Cipher text IS\n";
    for (i = 0; i<len; i++)
    {
        char val= c1[i];
        cout<<c1[i]<<" ";
    }
    cout<<endl;
    for (i = 0; i<len; i++)
    {
        char val= c2[i];
        cout<<c2[i]<<" ";
    }
    cout<<endl;
    for (i = 0; i<len; i++)
    {
        char val= c3[i];
        cout<<c3[i]<<" ";
    }
    cout<<endl;
}



ll compute(ll c1,ll c2,ll c3)
{
    //cout<<"started"<<endl; 
    i_M1=2225; i_M2=389301; i_M3=2099309;
    ll x= (( (c1*M1)%M *i_M1)%M +((c2*M2)%M *i_M2)%M+((c3*M3)%M *i_M3))%M;
    cout<<x<<endl;
    ll res= cbrt(x);
    //cout<<"ended "<<res<<endl;
    return res;
}




void decrypt()
{
    ll i = 0;
    ll len = strlen(msg);
    cout << "\nTHE DECRYPTED MESSAGE IS\n";
    while (i<len)
    {
        //cout<<"computing character"<<i<<endl;
        m[i]= compute(c1[i],c2[i],c3[i]);
        char val= m[i];
        cout<<m[i]<<" "<<val<<endl;
        i++;
    }
    cout<<endl;
}

 


ll findMinX(ll num[], ll rem[], ll k) 
{ 
    // Compute product of all numbers 
    ll prod = 1; 
    for (ll i = 0; i < k; i++) 
        prod *= num[i]; 

    // Initialize result 
    ll result = 0; 
    ll pp[3];
    pp[0]=num[1]*num[2];pp[1]=num[0]*num[2];pp[2]=num[1]*num[0];

    // Apply above formula 
    for (ll i = 0; i < k; i++) 
    { 
        //ll pp = prod / num[i]; //pp=pp%num[i];
        //cout<<pp[i]<<" "<<num[i]<<" "<<inv(pp[i], num[i])<<endl;
        //cout<<inv(pp[i], num[i]) * pp[i]<<endl;
        result += (rem[i] * modInverse(pp[i], num[i]) * pp[i]) %prod;
        //cout<<result<<endl; 
    } 

    return result % prod; 
} 



void decrypt_new()
{

    ll num[] = {m1, m2, m3};
    ll k = sizeof(num)/sizeof(num[0]);
    ll len =strlen(msg);
    for(ll i=0;i<len;i++)
    {
        ll rem[] = {c1[i],c2[i],c3[i]}; 
         
        m[i]= findMinX(num, rem, k);
        //cout<<m[i]<<" before cuberoot"<<endl;
        double tt= cbrt(m[i]); 
        fin_msg[i]= int(0.5 + tt);
        //cout<<tt<<" "<<char(tt)<<" "<<int(tt)<<endl;
    }
    for(ll i=0;i<len;i++) cout<<char(fin_msg[i]);
    cout<<endl;
}


// A C++ program to demonstrate working of Chinise remainder 
// Theorem 

// Returns modulo inverse of a with respect to m using extended 
// Euclid Algorithm. Refer below post for details: 
// https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/ 

// k is size of num[] and rem[]. Returns the smallest 
// number x such that: 
// x % num[0] = rem[0], 
// x % num[1] = rem[1], 
// .................. 
// x % num[k-2] = rem[k-1] 
// Assumption: Numbers in num[] are pairwise coprime 
// (gcd for every pair is 1) 


    















int main()
{


    cout<<"Say Alice choses 3 public keys for 3 diff persons with low exponent"<<endl;
    cout<<"Give Low exponent"<<endl;
    ll exp;
    cin>>exp;
    ll p1,q1,p2,q2,p3,q3;
    
    cout<<"Enter p.qs for each of N1,N2,N3 values"<<endl;
    cin>>p1>>q1>>p2>>q2>>p3>>q3;
    //cin>>m1>>m2>>m3;
    m1= p1*q1;m2=p2*q2;m3=p3*q3;

    if(check_gcd(m1,m2,m3)==0) {cout<<"Invalid N1,N2,N3 since they are coprime with each other"<<endl; exit(1);}


    cout << "\nENTER MESSAGE\n";
    fflush(stdin);

    scanf(" %[^\n]s",msg);



    /*M = m1*m2*m3;
    M1 = (m2*m3)%m1 ,M2= (m1*m3)%m2, M3=(m1*m2)%m3;
    cout<<"M ="<<M<<endl;
    cout<<"M1,M2,M3 ="<<M1<<","<<M2<<","<<M3<<endl;

    ll mm1= M1%m1,mm2= M2%m2, mm3=M3%m3;
    cout<<mm1<<" "<<mm2<<" "<<mm3<<endl;

    //i_M1= inv(mm1,m1);
    //i_M2= inv(mm2,m2);
    //i_M3= inv(mm3,m3);

    i_M1= modInverse(M1,m1);
    i_M2= modInverse(M2,m2);
    i_M3= modInverse(M3,m3);

    cout<<"i_M1 ="<<i_M1<<endl;
    cout<<"i_M2 ="<<i_M1<<endl;
    cout<<"i_M3 ="<<i_M1<<endl; */

    encrypt(exp);
    //compute();
    decrypt_new();
    return 0;

   /* cout << "\nENTER FIRST PRIME NUMBER\n";
    cin >> p;
    flag = prime(p);

    if (flag == 0)
    {
        cout << "\nWRONG INPUT\n";
        exit(1);
    }
    cout << "\nENTER ANOTHER PRIME NUMBER\n";

    cin >> q;
    flag = prime(q);

    if (flag == 0 || p == q)
    {
        cout << "\nWRONG INPUT\n";
        exit(1);
    }

    n = p * q;
    cout<<"n="<<p<<"*"<<q<<"="<<n<<endl;
    t = (p - 1) * (q - 1);

    ce();

    cout << "\nPOSSIBLE VALUES OF e AND d ARE\n";

    for (i = 0; i < j - 1; i++)
        cout << e[i] << "\t" << d[i] << "\n";

    cout<<"Choose the value of e,d pair"<<endl;
    ll e_val ,d_val;
    cin>>e_val>>d_val; */

    
}




