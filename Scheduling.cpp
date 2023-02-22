#include<bits/stdc++.h>
using namespace std;

class Process{
    public:
    int id;
    int AT,BT,CT,WT,TAT,P;

    Process(int id,int AT,int BT,int P)
    {
        this->id=id;
        this->AT=AT;
        this->BT=BT;
        this->P=P;
    }
    Process(){}
};


class ProcessList{
    public:
    vector<Process> schedule;
    void Add(Process p);
    void SJF();
    void FCFS();
    void priorityS();
};

struct mycmp
{
    bool operator()(Process &p1,Process &p2)
    {
        if(p1.BT!=p2.BT)
            return p1.BT>p2.BT;
        return p1.AT>p2.AT;
    }
};

struct cmp
{
    bool operator()(Process &p1,Process &p2)
    {
        if(p1.P!=p2.P)
            return p1.P<p2.P;
        else if(p1.AT!=p2.AT)
            return p1.AT>p2.AT;
        return p1.id>p2.id;
    }
};

void ProcessList::Add(Process p)
{
    schedule.push_back(p);
}

void print(vector<Process> ans,string str)
{
    int Tat=0,Wt=0;

    cout<<"********************"<<str<<"******************"<<endl;
    cout<<"pId\t"<<"AT\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT";
    if(str=="Priority") cout<<"\tPriority\n";
    else cout<<endl;
    for(int i=0;i<ans.size();i++)
    {
        Tat+=ans[i].TAT;
        Wt+=ans[i].WT;
        
        cout<<ans[i].id<<"\t"<<ans[i].AT<<"\t"<<ans[i].BT<<"\t"<<ans[i].CT<<"\t"<<ans[i].TAT<<"\t"<<ans[i].WT;
        if(str=="Priority") cout<<"\t"<<ans[i].P<<endl;
        else cout<<endl;
    }
    cout<<"Avarage TAT:"<<Tat/(float)ans.size()<<"\t"<<"Avarage Wt:"<<Wt/(float)ans.size()<<endl;
}

void ProcessList::FCFS()
{
    vector<Process> temp=schedule;
    sort(temp.begin(),temp.end(),[](Process p1,Process p2)->bool{
            return p1.AT<p2.AT;
    });

    int time=0;
    for(int i=0;i<temp.size();i++)
    {
        if(time<temp[i].AT)
            time=temp[i].AT+temp[i].BT;
        else
            time+=temp[i].BT;

        temp[i].CT=time;
        temp[i].TAT=temp[i].CT-temp[i].AT;
        temp[i].WT=temp[i].TAT-temp[i].BT;
    }

    print(temp,"FCFS");
}

void SJFUtil(vector<Process> &ans,vector<bool> &visited,vector<Process> &temp)
{
    priority_queue<Process,vector<Process>,mycmp> pq;

    int minAt=INT_MAX;
    for(int i=0;i<temp.size();i++)
    {   if(!visited[temp[i].id])
            minAt=min(minAt,temp[i].AT);
    }
    for(int i=0;i<temp.size();i++)
    {
        if(!visited[temp[i].id] and minAt==temp[i].AT)
        {
            pq.push(temp[i]);
            visited[temp[i].id]=true;
        }
    }

    int time=minAt;
    while(!pq.empty())
    {
        Process ptemp=pq.top();
        pq.pop();
        time+=ptemp.BT;
        
        ptemp.CT=time;
        ptemp.TAT=ptemp.CT-ptemp.AT;
        ptemp.WT=ptemp.TAT-ptemp.BT;
        ans.push_back(ptemp);

        for(int i=0;i<temp.size();i++)
        {
            if(temp[i].AT<=time and !visited[temp[i].id])
            {
                pq.push(temp[i]);
                visited[temp[i].id]=true;
            }
        }
    }
}

void PriorityUtil(vector<Process> &ans,vector<bool> &visited,vector<Process> &temp)
{
    priority_queue<Process,vector<Process>,cmp> pq;

    int minAt=INT_MAX;
    for(int i=0;i<temp.size();i++)
    {   if(!visited[temp[i].id])
            minAt=min(minAt,temp[i].AT);
    }
    for(int i=0;i<temp.size();i++)
    {
        if(!visited[temp[i].id] and minAt==temp[i].AT)
        {
            pq.push(temp[i]);
            visited[temp[i].id]=true;
        }
    }

    int time=minAt;
    while(!pq.empty())
    {
        Process ptemp=pq.top();
        pq.pop();
        time+=ptemp.BT;
        
        ptemp.CT=time;
        ptemp.TAT=ptemp.CT-ptemp.AT;
        ptemp.WT=ptemp.TAT-ptemp.BT;
        ans.push_back(ptemp);

        for(int i=0;i<temp.size();i++)
        {
            if(temp[i].AT<=time and !visited[temp[i].id])
            {
                pq.push(temp[i]);
                visited[temp[i].id]=true;
            }
        }
    }
}

void Util(vector<Process> &ans,vector<Process> schedule,string str)
{
    vector<Process> temp=schedule;
    int n=temp.size();
    sort(temp.begin(),temp.end(),[](Process p1,Process p2)->bool{
            return p1.AT<p2.AT;
    });

    vector<bool> visited(n,false);

    for(int i=0;i<n;i++)
    {
        if(!visited[temp[i].id])
        {
            if(str=="SJF") SJFUtil(ans,visited,temp);
            else PriorityUtil(ans,visited,temp);
        }
    }
}

void ProcessList::SJF()
{
    vector<Process> ans;
    vector<Process> temp=schedule;
    for(int i=0;i<temp.size();i++) temp[i].P=1;
    Util(ans,temp,"SJF");
    print(ans,"SJF");
}

void ProcessList::priorityS()
{
    vector<Process> ans;
    Util(ans,schedule,"priority");
    print(ans,"Priority");    
}

int main()
{
    ProcessList pl;

    int n,type,p=1;
    cout<<"you want input with priority yes(1) or No(0):"; cin>>type;
    cout<<"enter number of process:"; cin>>n;
    int AT,BT,P;
    for(int i=0;i<n;i++)
    {
        cout<<"enter AT:"; cin>>AT;
        cout<<"enter BT:"; cin>>BT;
        if(type!=0)
        {
            cout<<"enter priority:";
            cin>>p;
        }

        pl.Add(Process(i,AT,BT,p));

        if(i==n-1)
        {
            int choise;
            cout<<"want to enter more precosses then mention no of processes or enter 0:";
            cin>>choise;
            if(choise>0) n+=choise;
        }
    }

    pl.FCFS();
    cout<<"\n\n";
    pl.SJF();
    cout<<"\n\n";
    pl.priorityS();
    return 0;
}