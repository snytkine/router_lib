#include <iostream>
#include <ctime>
#include "strlib.h"
#include "RouterNode.h"


using namespace std;


void findRoute(RouterNode<int> *rn, string uri){
    RouteResult<int> *res = rn->findRoute(uri);
    cout << "Controller Found: " << res->controller_id << endl;
}

int main() {
    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    string uri = "/users/find/id";
    string search = "/users/";
    //cout << "Hello, World!" << std::endl;

    bool matched = startsWith(uri, search);

    //cout << "Found: " << matched << endl;

    //clock_t start;
    //double diff;
    //start = clock();

    RouterNode<int> *rn = new RouterNode<int>("/api", 3);
    rn->addChild("/v1", 5);
    rn->addChild("/v2", 6)->addChild("/users", 7);



    RouteResult<int> *res = rn->findRoute("/api/v2/users");
    /*if(res->controller_id > 0){
        cout << "Controller Found: " << res->controller_id << endl;
    } else {
        cout << "Controller NOT FOUND " << res->controller_id << endl;
    }*/

    //int t = funcTime(findRoute, rn, "/api/v2/users");

    //std::cout<<"norm: "<< funcTime(findRoute, rn, "/api/v2/users") <<"\n";
    //findRoute(rn, "/api/v2/users");


    //std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    //std::cout << "Time MS difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
    //std::cout << "Time NANO difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;

    //diff = ( std::clock() - start ) / (double)CLOCKS_PER_SEC;
    //cout<<"printf: "<< diff <<'\n';
    return 0;

}