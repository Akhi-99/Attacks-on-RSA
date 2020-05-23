#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100];

//string msg;

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

ll cd(ll x)
{
    ll k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}


void ce()
{
    ll k;
    k = 0;
    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;

        flag = prime(i);
        if (flag == 1 && i != p && i != q)
        {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}





void encrypt(ll e_val)
{
    ll pt, ct, key = e_val, k, len;
    i = 0;
    len = strlen(msg); //.length();
    while (i <len)
    {
        pt = msg[i];
         //num
        //pt = pt - 96; //char
        k = 1;

        //cout<<pt<<endl;

        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        //ct = k + 96;
        en[i] = temp[i];

        i++;
    }
    //en[i] = -1;

    cout << "\nTHE ENCRYPTED MESSAGE IS\n";
    for (i = 0; i<len; i++)
    {
        char val= en[i];
        cout<<en[i]<<" ";
    }
    cout<<endl;
}


void decrypt(ll d_val)
{
    ll pt, ct, key = d_val, k;
    i = 0;
    ll len = strlen(msg);
    while (i<len)
    {
        ct = en[i];
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        //pt = k + 96;
        //m[i] = pt;
        m[i]=k;
        //cout<<m[i]<<endl;
        i++;
    }
    //m[i] = -1;
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
    cout << "\nENTER FIRST PRIME NUMBER\n";
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
    cin>>e_val>>d_val;

    cout << "\nENTER MESSAGE\n";
    fflush(stdin);

    scanf(" %[^\n]s",msg);


    encrypt(e_val);
    decrypt(d_val);
    return 0;
}




