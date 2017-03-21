#include <iostream>
#include <ctime>
#include "strlib.h"
#include "RouterNode.h"


using namespace std;
using namespace router_lib;


void findRoute(RouterNode<int> *rn, string uri){
    RouteResult<int> *res = rn->findRoute(uri);
    cout << "Controller Found: " << res->controller_id << endl;
}



int main() {


    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    string uri = "users/find/id";
    string search = "/users/";
    //cout << "Hello, World!" << std::endl;

    bool matched = startsWith(uri, search);

    size_t sepP = uri.find(PATH_SEPARATOR);
    string rest = uri.substr(sepP + 1, string::npos);
    string nodeUri = uri.substr(0, sepP);

    cout << "PATH_SEPARATOR: " << sepP << " LEN: " << uri.length() << " REST: " << rest << " NODE_URI: " << nodeUri << endl;

    //cout << "Found: " << matched << endl;

    //clock_t start;
    //double diff;
    //start = clock();

    RouterNode<int> *rootNode = new RouterNode<int>();
    //rootNode->addRoute("api/v1_0/users", 1, "users");


    rootNode->addRoute("api/v2_0/users/user/", 5, "user");
    rootNode->addRoute("myapi/v1_0/users/user/", 6, "user");

    rootNode->addRoute("api/v1_0/users/user", 4, "user");

    rootNode->addRoute("api/v1_0/users/user/", 2, "user");

    rootNode->addRoute("api/v1_0/users/user/123", 3, "user123");

    rootNode->addRoute("api/v1_0/user({id})/", 8, "users/");

    rootNode->addRoute("api/v1_0/items/{item_id}/ok.get", 11, "api/v1_0/items/{item_id}/ok.get");
    rootNode->addRoute("api/v1_0/items/{item_id}/{user_id}/ok.get", 12, "api/v1_0/items/{item_id}/{user_id}/ok.get");

    rootNode->addRoute("api/v1_0/items/{item_id}/", 9, "api/v1_0/items/{item_id}/");


    cout << '\n' << '\n' << "=================" << '\n' << '\n' << endl;
    RouteResult<int> *res = rootNode->findRoute("/api/v3_0/users/user/123");
    //RouteResult<int> *res2 = rootNode->findRoute("/api/v1_0/users/user");
    //RouteResult<int> *res3 = rootNode->findRoute("/api/v1_0/users");
    //RouteResult<int> *res4 = rootNode->findRoute("/api/v1_0/users/");
    //RouteResult<int> *res5 = rootNode->findRoute("/api/v1_0/items/544/");
    //RouteResult<int> *res6 = rootNode->findRoute("/api/v1_0/items/563/ok.get");
    RouteResult<int> *res7 = rootNode->findRoute("/api/v1_0/items/77777/264/ok.get");

    cout << "RES route /api/v3_0/users/user/123: " << res->toString() << endl;
    //cout << "RES route /api/v1_0/users/user: " << res2->controller_id << endl;
    //cout << "RES route /api/v1_0/users: " << res3->controller_id << endl;
    //cout << "RES route /api/v1_0/users/: " << res4->controller_id << endl;
    //cout << "RES-5 route /api/v1_0/items/55/: " << res5->controller_id << endl;
    //cout << "RES-6 route /api/v1_0/items/563/ok.get: " << res6->toString() << endl;
    cout << "RES-7 route api/v1_0/items/{item_id}/{user_id}/ok.get: " << res7->toString() << endl;



    //string myTest = "blahblah/cool";
    /*string myuri = "{id}/";
    string paramName = myuri.substr(1, myuri.length() - 3);
    string myurisub = myuri.substr(0, myuri.find("/"));
    cout << "EXTRACTED=" << paramName << endl;
    cout << "MY_SUB=" << myurisub << endl;*/

    //RouterNode<int> *rn = new RouterNode<int>("/api", 3);
    //rn->addChild("/v1", 5);
    //rn->addChild("/v2", 6)->addChild("/users", 7);



    //RouteResult<int> *res = rn->findRoute("/api/v2/users");
    /*if(res->controller_id > 0){
        cout << "Controller Found: " << res->controller_id << endl;
    } else {
        cout << "Controller NOT FOUND " << res->controller_id << endl;
    }*/

    int t = funcTime(findRoute, rootNode, "/api/v1_0/items/77777/264/ok.get");
    //int t2 = funcTime(findRoute, rn, "/api/v2");
    //int t3 = funcTime(findRoute, rn, "/api/v2/users");

    std::cout<<"t1: "<< t <<"\n";
    //std::cout<<"t2: "<< t2 <<"\n";
    //std::cout<<"t3: "<< t2 <<"\n";
    //findRoute(rn, "/api/v2/users");




    //std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    //std::cout << "Time MS difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
    //std::cout << "Time NANO difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;

    //diff = ( std::clock() - start ) / (double)CLOCKS_PER_SEC;
    //cout<<"printf: "<< diff <<'\n';
    return 0;

}