#include<bits/stdc++.h>
using namespace std;

class Process{
    public:
    int id;
    int AT,BT,CT,WT,TAT,FR,RT;

    Process(int id, int AT, int BT)
    {
        this->id = id;
        this->AT = AT;
        this->BT = BT;

        this->CT = -1;
        this->TAT = -1;
        this->WT = -1;
        this->RT = -1;
        this->FR = INT_MAX;
    }
};

class ProcessList{
    public:
    int TQ=2;
    vector<Process> list;
    
    void add(Process p);
    void schedule();
};

void notations(int n)
{
    if(n==1)
    {
        cout<<"\n\nNotations:\n";
        cout<<"p.no:\tProcess NO\nBT:\tBurst Time\nAT:\tArrival Time\nCT:\tCompletion Time\nTAT:\tTurn Around Time\nWT:\tWaiting Time\nRT:\tResponse Time\nFR:\tFirst Response Time\n";
    }else
    {
        cout<<"\n\nFormula's:\n";
        cout<<"TAT:  CT  - AT\nWT :  TAT - BT\nRT :  FR  - AT\n";
    }
}

void print(vector<Process> list)
{
    cout<<"\n*********************************************************************"<<endl;
    if(list[0].CT<0)
    {
        cout<<"id\t"<<"AT\t"<<"BT\t"<<endl;
        for(int i=0;i<list.size();i++)
        {
            cout<<list[i].id+1<<"\t"<<list[i].AT<<"\t"<<list[i].BT<<endl;
        }
    }
    else
    {
        sort(list.begin(),list.end(),[](const Process &p1,const Process &p2)->bool{
            return p1.id<p2.id;
        });
        cout<<"P.no\t"<<"AT\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"FR"<<endl;
        int tTAT=0,tWT=0;
        for(int i=0;i<list.size();i++)
        {
            cout<<list[i].id+1<<"\t"<<list[i].AT<<"\t"<<list[i].BT<<"\t"<<list[i].CT<<"\t"<<list[i].TAT<<"\t"<<list[i].WT<<"\t"<<list[i].RT<<"\t"<<list[i].FR<<endl;

            tTAT+=list[i].TAT;
            tWT+=list[i].WT;
        }     
        cout<<endl;
        cout<<"AVG TAT:"<<(float)tTAT/list.size()<<"\t"<<"AVG WT:"<<(float)tWT/list.size();   
    }
}

void ProcessList::add(Process p)
{
    list.push_back(p);
}

void print4digit(int n)
{
    for(int i=2;i>=0;i--)
    {
        int div = pow(10,i);
        cout<<n/div;
        n%=div;
    }
}

void ProcessList::schedule()
{
    cout<<"\nGantt Chart:[initail time,\tprocess no,\tfinal time]\n";

    vector<Process> np=list;
    vector<bool> visited(list.size(),false);
    sort(np.begin(),np.end(),[](const Process &p1,const Process &p2)->bool{
        return p1.AT<p2.AT;
    });

    for(int i=0;i<list.size();i++)
    {
        if(!visited[i])
        {
            queue<Process*> q;
            q.push(&np[i]);
            int time=np[i].AT;
            visited[np[i].id]=true;

            while(!q.empty())
            {
                Process* temp=q.front();
                temp->FR=min(time,temp->FR);
                q.pop();

                cout<<"[";
                print4digit(time);
                cout<<"\tp(";
                print4digit(temp->id+1);
                cout<<")\t";

                if(temp->BT>TQ)
                {
                    temp->BT -= TQ;
                    time += TQ;
                }
                else
                {
                    time += temp->BT;
                    temp->BT = 0;
                }
                print4digit(time);
                cout<<"]"<<"\n";

                for(int j=0;j<list.size();j++)
                {
                    if(!visited[np[j].id] and np[j].AT<=time)
                    {
                        visited[np[j].id]=true;
                        q.push(&np[j]);
                    }
                }

                temp->CT = max(time, temp->CT);
                if(temp->BT > 0) q.push(temp);
            }
        }
    }
    sort(list.begin(),list.end(),[](const Process &p1,const Process &p2)->bool{
        return p1.AT<p2.AT;
    });

    for(int i=0;i<np.size();i++)
    {
        list[i].CT=np[i].CT;
        list[i].FR=np[i].FR;

        list[i].TAT=list[i].CT-list[i].AT;
        list[i].WT=list[i].TAT-list[i].BT;
        list[i].RT=list[i].FR-list[i].AT;
    }

    print(list);
}

int main()
{
    ProcessList pl;
    int n;
    cout<<"enter number of process:"; cin>>n;
    cout<<"enter Time Quantum:"; cin>>pl.TQ;

    notations(1);
    cout<<endl;

    int AT,BT;
    for(int i=0;i<n;i++)
    {
        cout<<"Process:"<<i+1<<endl;
        cout<<"enter AT:"; cin>>AT;
        cout<<"enter BT:"; cin>>BT;
        cout<<endl;

        pl.add(Process(i,AT,BT));

        if(i==n-1)
        {
            int choise;
            cout<<"want to enter more precosses then mention no of processes or enter 0:";
            cin>>choise;
            if(choise>0) n+=choise;
        }
    }

    print(pl.list);
    pl.schedule();
    notations(2);

    return 0;
}