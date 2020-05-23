#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll en[100] = {0};
ll p,q,t,len,n,e;
ll m[100];

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

void decrypt(ll d_val)
{
    ll i = 0;
    //ll len = strlen(msg);
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
	decrypt(d); 
	return 0;
}