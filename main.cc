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

    //find path
    Path *path;
    path=new Path();
    path->append(nm->elist);
    std::vector<std::vector<Edge *>> avail_paths = path->find_paths(std::string("c"),std::string("b"));
    path->debug();
    for(int x=0;x<path->paths.at(0).size();x++)
    {
        cout<<path->paths.at(0).at(x)->head->name<<"->"<<path->paths.at(0).at(x)->tail->name<<" ";
    }


    // using gplot to export a  plot file
    Gplot *gp = new Gplot();
    gp->gp_add(nm->elist);
    gp->gp_dump(true);
    gp->gp_export("plot");

    return 0;
}
