#include <bits/stdc++.h>
using namespace std;

// Helper function to print vector
void printVector(vector<int>& v){
    for(auto x: v) cout << x << " ";
    cout << endl;
}

int main(){
    // ==================== Category 1: Frequency / HashMap Based ====================

    // Q1
    vector<int> q1 = {1,2,2,3,3,3};
    unordered_map<int,int> freq1;
    for(int x:q1) freq1[x]++;
    unordered_set<int> s1;
    bool uniqueFreq = true;
    for(auto [k,v]:freq1){
        if(s1.count(v)) uniqueFreq=false;
        s1.insert(v);
    }
    cout << (uniqueFreq ? "true" : "false") << endl; // output: true

    // Q2
    vector<int> q2 = {5,5,6,6};
    unordered_map<int,int> freq2;
    for(int x:q2) freq2[x]++;
    unordered_set<int> s2;
    bool uniqueFreq2 = true;
    for(auto [k,v]:freq2){
        if(s2.count(v)) uniqueFreq2=false;
        s2.insert(v);
    }
    cout << (uniqueFreq2 ? "true" : "false") << endl; // output: false

    // Q3 - Majority element (>n/2)
    vector<int> q3 = {10,20,20,10,10};
    unordered_map<int,int> freq3;
    for(int x:q3) freq3[x]++;
    for(auto [k,v]:freq3){
        if(v>q3.size()/2){ cout << k << endl; break; }
    }

    // Q4 - First non-repeating
    vector<int> q4 = {4,4,1,2,1,2,1};
    unordered_map<int,int> freq4;
    for(int x:q4) freq4[x]++;
    for(int x:q4){ if(freq4[x]==1){ cout << x << endl; break; }}

    // Q5 - Element with highest frequency
    vector<int> q5 = {1,2,3,1,4,5,1};
    unordered_map<int,int> freq5;
    for(int x:q5) freq5[x]++;
    int maxFreq=0,maxElem;
    for(auto [k,v]:freq5){ if(v>maxFreq){ maxFreq=v; maxElem=k;}}
    cout << maxElem << endl;


    // ==================== Category 2: Move / Rearranging ====================

    // Q6 - Move zeros to end
    vector<int> q6 = {0,1,0,3,12};
    int idx=0;
    for(int x:q6) if(x!=0) q6[idx++]=x;
    while(idx<q6.size()) q6[idx++]=0;
    printVector(q6); // output: 1 3 12 0 0

    // Q7
    vector<int> q7 = {1,0,2,0,3,0};
    idx=0;
    for(int x:q7) if(x!=0) q7[idx++]=x;
    while(idx<q7.size()) q7[idx++]=0;
    printVector(q7); // output: 1 2 3 0 0 0

    // Q8 - Negatives to front
    vector<int> q8 = {1,-1,3,-5,7};
    vector<int> neg, pos;
    for(int x:q8) (x<0 ? neg : pos).push_back(x);
    neg.insert(neg.end(), pos.begin(), pos.end());
    printVector(neg); // output: -1 -5 1 3 7

    // Q9 - Evens front, odds back
    vector<int> q9 = {2,4,1,3,6,7};
    vector<int> even, odd;
    for(int x:q9) (x%2==0 ? even : odd).push_back(x);
    even.insert(even.end(), odd.begin(), odd.end());
    printVector(even); // output: 2 4 6 1 3 7

    // Q10 - Reverse array
    vector<int> q10 = {1,2,3,4,5};
    reverse(q10.begin(),q10.end());
    printVector(q10); // output: 5 4 3 2 1


    // ==================== Category 3: Interleaving / Pattern ====================

    // Q11 - Reverse interleave last, first ...
    vector<int> q11 = {1,2,3,4,5,6,7};
    vector<int> res11;
    int i=0,j=q11.size()-1;
    while(i<=j){
        if(i!=j) res11.push_back(q11[j--]);
        res11.push_back(q11[i++]);
    }
    printVector(res11); // output: 7 1 6 2 5 3 4

    // Q12 - Swap in pairs
    vector<int> q12 = {1,2,3,4,5,6};
    for(int i=0;i<q12.size()-1;i+=2) swap(q12[i],q12[i+1]);
    printVector(q12); // output: 2 1 4 3 6 5

    // Q13 - Reverse in groups of size 3
    vector<int> q13 = {10,20,30,40,50,60};
    int k=3;
    for(int i=0;i<q13.size();i+=k){
        int end=min(i+k-1,(int)q13.size()-1);
        reverse(q13.begin()+i,q13.begin()+end+1);
    }
    printVector(q13); // output: 30 20 10 60 50 40

    // Q14 - Interleave odd/even index
    vector<int> q14 = {1,2,3,4,5,6};
    vector<int> oddIdx, evenIdx;
    for(int i=0;i<q14.size();i++) (i%2==0 ? evenIdx : oddIdx).push_back(q14[i]);
    evenIdx.insert(evenIdx.end(), oddIdx.begin(), oddIdx.end());
    printVector(evenIdx); // output: 1 3 5 2 4 6

    // Q15 - Zig-zag a<b>c<d...
    vector<int> q15 = {1,3,5,2,4,6};
    for(int i=0;i<q15.size()-1;i++){
        if(i%2==0 && q15[i]>q15[i+1]) swap(q15[i],q15[i+1]);
        else if(i%2==1 && q15[i]<q15[i+1]) swap(q15[i],q15[i+1]);
    }
    printVector(q15); // output: 1 5 3 4 2 6


    // ==================== Category 4: Two Pointer / Index ====================

    // Q16 - Pair sum
    vector<int> q16 = {1,4,45,6,10,8};
    int target16 = 16;
    sort(q16.begin(),q16.end());
    int left=0,right=q16.size()-1;
    bool found=false;
    while(left<right){
        int sum=q16[left]+q16[right];
        if(sum==target16){found=true; break;}
        else if(sum<target16) left++; else right--;
    }
    cout << (found ? "true" : "false") << endl; // output: true

    // Q17 - Right rotate by k
    vector<int> q17 = {1,2,3,4,5}; int k17=2;
    rotate(q17.rbegin(),q17.rbegin()+k17,q17.rend());
    printVector(q17); // output: 4 5 1 2 3

    // Q18 - Left rotate by k
    vector<int> q18 = {1,2,3,4,5}; int k18=2;
    rotate(q18.begin(),q18.begin()+k18,q18.end());
    printVector(q18); // output: 3 4 5 1 2

    // Q19 - Pair sum = target
    vector<int> q19 = {2,3,4,7,11}; int target19=9;
    sort(q19.begin(),q19.end());
    left=0; right=q19.size()-1;
    while(left<right){
        int sum=q19[left]+q19[right];
        if(sum==target19){cout << q19[left] << " " << q19[right] << endl; break;}
        else if(sum<target19) left++; else right--;
    }

    // Q20 - Prefix sum
    vector<int> q20 = {1,2,3,4,5};
    for(int i=1;i<q20.size();i++) q20[i]+=q20[i-1];
    printVector(q20); // output: 1 3 6 10 15


    // ==================== Category 5: Mathematical Transformation ====================

    // Q21 - Product except self
    vector<int> q21 = {1,2,3,4};
    vector<int> res21(q21.size(),1);
    int prod=1;
    for(int i=0;i<q21.size();i++){res21[i]=prod; prod*=q21[i];}
    prod=1;
    for(int i=q21.size()-1;i>=0;i--){res21[i]*=prod; prod*=q21[i];}
    printVector(res21); // output: 24 12 8 6

    // Q22 - Running sum
    vector<int> q22 = {1,2,3,4,5};
    for(int i=1;i<q22.size();i++) q22[i]+=q22[i-1];
    printVector(q22); // 1 3 6 10 15

    // Q23 - Sort ascending
    vector<int> q23 = {5,4,3,2,1}; sort(q23.begin(),q23.end()); printVector(q23); //1 2 3 4 5

    // Q24 - Sort minimum comparisons (same as Q23)
    vector<int> q24 = {10,5,20,40}; sort(q24.begin(),q24.end()); printVector(q24); //5 10 20 40

    // Q25 - Double even index
    vector<int> q25 = {1,2,3,4};
    for(int i=0;i<q25.size();i+=2) q25[i]*=2;
    printVector(q25); //2 2 6 4


    // ==================== Category 6: Sorting / Custom ====================

    // Q26 - Largest number
    vector<int> q26 = {3,30,34,5,9};
    vector<string> s26;
    for(int x:q26) s26.push_back(to_string(x));
    sort(s26.begin(),s26.end(),[](string &a,string &b){return a+b>b+a;});
    for(string x:s26) cout << x; cout << endl; // 9534330

    // Q27 - Sort ascending
    vector<int> q27 = {5,3,9,7}; sort(q27.begin(),q27.end()); printVector(q27); //3 5 7 9

    // Q28 - Sort string by length
    vector<string> q28 = {"a","bb","c"};
    sort(q28.begin(),q28.end(),[](string a,string b){return a.length()<b.length();});
    for(string x:q28) cout << x << " "; cout << endl; // a c bb

    // Q29 - Alternate min/max
    vector<int> q29 = {1,2,3,4,5,6};
    sort(q29.begin(),q29.end());
    vector<int> res29;
    int l=0,r=q29.size()-1;
    while(l<=r){
        if(l!=r) res29.push_back(q29[l++]);
        res29.push_back(q29[r--]);
    }
    printVector(res29); //1 6 2 5 3 4

    // Q30 - Dutch National Flag
    vector<int> q30 = {0,1,2,1,2,0};
    int low=0,mid=0,high=q30.size()-1;
    while(mid<=high){
        if(q30[mid]==0) swap(q30[low++],q30[mid++]);
        else if(q30[mid]==1) mid++;
        else swap(q30[mid],q30[high--]);
    }
    printVector(q30); //0 0 1 1 2 2

    return 0;
}
/*
true
false
10
1
1 3 12 0 0 
1 2 3 0 0 0 
-1 -5 1 3 7 
2 4 6 1 3 7 
5 4 3 2 1 
7 1 6 2 5 3 4 
2 1 4 3 6 5 
30 20 10 60 50 40 
1 3 5 2 4 6 
1 5 2 4 3 6 
true
4 5 1 2 3 
3 4 5 1 2 
2 7
1 3 6 10 15 
24 12 8 6 
1 3 6 10 15 
1 2 3 4 5 
5 10 20 40 
2 2 6 4 
9534330
3 5 7 9 
a c bb 
1 6 2 5 3 4 
0 0 1 1 2 2 
*/