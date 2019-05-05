/* 
    Your main program goes here
*/
#include <iostream>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();

int main(int argc, char** argv){

    /* start your program */
    nm->interpret("graph.txt");
    nm->print_all_e();
    nm->print_all_v();

    //divide node by in-degree and out-degree
    class DEGREE{
        public:
	    string vertex;
	    int in_degree;
	    int out_degree;
    };
    
    vector <DEGREE> all_degree;
    Vertex* start=nm->get_all_nodes();
    for (Vertex* x=start;x!=NULL;x=x->next)//count diffence of degree
    {
	DEGREE temp;
	temp.vertex=x->name;
	temp.in_degree=0;
	temp.out_degree=0;
        for (Vertex* y=start;y!=NULL;y=y->next)
	{
            //if (x->name!=y->name)
            //{
            if(nm->connected_d(x->name,y->name)==0)
	    {
		temp.out_degree=temp.out_degree+=1;
	    }
	    if(nm->connected_d(y->name,x->name)==0)
	    {
		temp.in_degree=temp.in_degree+=1;
	    }
	    //}    
	}
	cout<<endl;
	all_degree.push_back(temp);
	//cout<<x->name<<" "<<y->name<<endl;
    }

    for (int i=0;i<all_degree.size();i++)//print DEGREE
    {
	cout<<all_degree[i].vertex<<" "<<all_degree[i].out_degree<<" "<<all_degree[i].in_degree<<endl;
    }

    //two degree class
    class BI_DEGREE{
        public:
	    string name;
	    int diff_degree;
    };
    vector<BI_DEGREE> out_list;
    vector<BI_DEGREE> in_list;
    for (int i=0;i<all_degree.size();i++)
    {
	int dif=all_degree[i].out_degree-all_degree[i].in_degree;
	BI_DEGREE temp;
	temp.name=all_degree[i].vertex;
	if (dif>0)
	{
            temp.diff_degree=dif;
	    out_list.push_back(temp);
	}
	else if (dif<0)
	{
	    temp.diff_degree=-dif;
	    in_list.push_back(temp);
	}
    }
    
    for (int i=0;i<in_list.size();i++)
    {
	    cout<<in_list[i].name<<" "<<in_list[i].diff_degree<<endl;
    }
    for (int i=0;i<out_list.size();i++)
    {
	    cout<<out_list[i].name<<" "<<out_list[i].diff_degree<<endl;
    }

    //mini cut flow
    cout<<"MCF"<<endl;
    Path *path;
    path=new Path();
    path->append(nm->elist);
    for (int i=0;i<out_list.size();i++)
    {
	while (out_list[i].diff_degree>0){
	    string min_name=in_list[0].name;
	    int min_size=999;
	    int min_index=0;
	    for(int j=0;j<in_list.size();j++)
	    {
		if (in_list[j].diff_degree>0){
                    std::vector<std::vector<Edge *>> find_paths = path->find_paths(out_list[i].name,in_list[j].name);
                    if(min_size>find_paths.size()){
		        min_size=find_paths.size();
		        min_name=in_list[j].name;
			min_index=j;
		    }
		}
	    }
	    cout<<min_name<<" "<<min_size<<endl;
	    out_list[i].diff_degree-=1;
	    in_list[min_index].diff_degree-=1;
            //add flow for edge on the path
	    std::vector<std::vector<Edge *>> avail_paths = path->find_paths(min_name,out_list[i].name);
	    path->debug();
	    if(path->paths.at(0).size()==0)
	    {
		cout<<"This is not the strong connected graph."<<endl;
		return 0;
	    }
	    else
	    {
		for(int x=0;x<path->paths.at(0).size();x++)
		{
		    string edge_h=path->paths.at(0).at(x)->head->name;//get edge head
		    string edge_t=path->paths.at(0).at(x)->tail->name;//get edge tail
		    cout<<edge_h<<"->"<<edge_t<<" ";
		    Edge *edge=nm->get_edge(edge_h,edge_t);//get edge
		    int edge_flow=edge->flowval;//get edge flow
		    cout<<edge_flow<<endl;
		    nm->setlink(edge_h,edge_t,1,edge_flow+1);//edge flow+1
		}
		cout<<endl;
	    }
	}
    }




    // using gplot to export a  plot file
    Gplot *gp = new Gplot();
    gp->gp_add(nm->elist);
    gp->gp_dump(true);
    gp->gp_export("middle");

    //find path
    class SIMPLE_EDGE{
        public:
            string head;
	    string tail;
    };
    vector<SIMPLE_EDGE> all_edge;

    Edge *tra = nm->elist;
    while(tra!=NULL){
	SIMPLE_EDGE one_edge;
	one_edge.head=tra->head->name;
	one_edge.tail=tra->tail->name;
	for (int i=0;i<tra->flowval;i++){
	    all_edge.push_back(one_edge);
	}
        cout<<tra->head->name<<"->"<<tra->tail->name<<":"<<tra->flowval<<endl;
	tra=tra->next;
    }
    cout<<endl;
/*
    SIMPLE_EDGE test;
    test=all_edge[3];
    all_edge[3]=all_edge[0];
    all_edge[0]=test;
*/
    bool right=0;
    int t=10;
    int re=0;
    while(!right&&(t--)){
    right=1;
    int begin=0;
		for(int num=1;num<=re;num++){
		    SIMPLE_EDGE swap;
		    swap=all_edge[1];
		    for(int k=1;k<=all_edge.size()-1-1;k++){
		        all_edge[k]=all_edge[k+1];
		    }
		    all_edge[all_edge.size()-1]=swap;
		}
    for(int i=0;i<all_edge.size(); i++){
        for(int j=i+1;j<all_edge.size(); j++){
	    if(all_edge[i].tail==all_edge[j].head){
	        SIMPLE_EDGE swap;
		swap=all_edge[j];
		for (int k=j;k>=i+1+1;k--){
		    all_edge[k]=all_edge[k-1];
		}
		all_edge[i+1]=swap;
		break;
	    }
	    else if(j==all_edge.size()-1){
		begin=i+1;
		right=0;
		re=i;
		i=j=all_edge.size();break;//break double loops
		/*
		for(int num=1;num<=i;num++){
		    SIMPLE_EDGE swap;
		    swap=all_edge[1];
		    for(int k=1;k<=all_edge.size()-1-1;k++){
		        all_edge[k]=all_edge[k+1];
		    }
		    all_edge[all_edge.size()-1]=swap;
		}
		i=0;
		*/
	    }
        }
    }
    }

    cout<<"answer path:"<<endl;
    for(int i=0;i<all_edge.size(); i++){
        cout<<all_edge[i].head<<"->"<<all_edge[i].tail<<endl;
    }


    return 0;
}
