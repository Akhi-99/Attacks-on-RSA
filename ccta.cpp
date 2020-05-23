#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll p, q, n, t, flag, temp[100], j, m[100], en[100], i,eve[100];
char msg[100];
ll r,e,d,len;



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

ll power(ll x, ll y, ll p)  
{  
    int res = 1;     // Initialize result    
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



void eve_encrypt(ll e_val)
{
    cout<<"Enter eve's chosen constant"<<endl;
    cin>>r;
    //ll len = strlen(msg);
    cout<<"ENCRYPTED Eve's Cipher text"<<endl;
    for(ll i=0;i<len;i++)
    {
        eve[i]= (en[i]*power(r,e_val,n))%n;
        cout<<eve[i]<<" ";
    }
    cout<<endl;
}


void encrypt(ll e_val)
{
    ll i = 0;
    ll len = strlen(msg); //.length();
    while (i <len)
    {
        en[i++] = power(msg[i],e_val,n);
    }
    

    cout << "\nTHE ENCRYPTED Cipher text IS\n";
    for (i = 0; i<len; i++)
    {
        char val= en[i];
        cout<<en[i]<<" ";
    }
    cout<<endl;
    eve_encrypt(e_val);
}


void eve_decrypt(ll d_val)
{
    ll i = 0;
    //ll len = strlen(msg);
    cout << "\nTHE DECRYPTED MESSAGE which BOB see IS\n";
    while (i<len)
    {
        m[i]= power(eve[i],d_val,n);
        char ch = m[i]; cout<<ch;
        i++;
    }
    cout<<endl;
    cout << "\nTHE DECRYPTED Original MESSAGE which Eve gets IS\n"<<endl;
    for(ll i=0;i<len;i++)
    {
        //m[i]= m[i]*inv(r,n);
        m[i]= m[i]/r ;
        char ch = m[i]; cout<<ch;
    }
    cout<<endl;
}



void decrypt(ll d_val)
{
    ll i = 0;
    ll len = strlen(msg);
    while (i<len)
    {
        m[i++]= power(en[i],d_val,n);
    }
    
    cout << "\nTHE DECRYPTED MESSAGE IS\n";

    for (i = 0; i<len; i++)
    {
        char val= m[i];
        cout<<val;
    }
    cout<<endl;
}



int main()
{
    cout<<"Give the public key e,N"<<endl;
    cin>>e>>n;
    //cout<<n<<endl;
    cout<<"Enter the Cipher text"<<endl;
    cin>>len;
    for(ll i=0;i<len;i++) cin>>en[i];
    //cin>>n;
    ll cnt=0;
    ll sqn= sqrt(n);
    
    if(n%2==0) { cout<<"2 "<<n/2<<endl; return 0;}

    clock_t start, end; 
  
    /* Recording the starting clock tick.*/
    start = clock(); 
  
    for(ll i=3;i<=sqn;)
    {
        if((n%i)==0)
        {
            cout<<"factor found"<<endl;
            cout<<"p= "<<i<<endl;
            p=i;
            cout<<"q= "<<n/i<<endl;
            q=n/i;
            break;
        }
        i=i+2;
    }
    end = clock(); 
    
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Time taken by program is : " << fixed  
         << time_taken << setprecision(5); 
    cout << " sec " << endl; 

    t= (p-1)*(q-1);
    ll d= inv(e,t);
    cout<<"Privated key Cracked is "<<d<<endl;
    eve_encrypt(e);
    eve_decrypt(d);
    return 0;
}




