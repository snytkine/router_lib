#include <iostream>
#include <ctime>
#include "strlib.h"
#include "PathParamNode.h"
#include "RouterNode.h"
#include "factory.h"
#include "measure.h"


using namespace std;
using namespace router_lib;


RouteResult *findRt(RouterNode rn, string uri) {
    return rn.findRoute(uri);
}

int main() {

    string mstr = "category(widgets)/";

    string prefix = mstr.substr(0, mstr.find("({") + 1);
    size_t slen = mstr.length();
    size_t startPos = mstr.find("{");
    size_t endPos = mstr.find("}");
    string ph = mstr.substr(mstr.find("(") + 1,   mstr.find(")") - mstr.find("("));

    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    string uri = "users/find/id";
    string search = "/users/";
    //cout << "Hello, World!" << std::endl;

    bool matched = startsWith(uri, search);

    size_t sepP = uri.find(PATH_SEPARATOR);
    string rest_ = uri.substr(sepP + 1, string::npos);
    string nodeUri = uri.substr(0, sepP);

    //cout << "PATH_SEPARATOR: " << sepP << " LEN: " << uri.length() << " REST: " << rest_ << " NODE_URI: " << nodeUri << endl;

    //cout << "Found: " << matched << endl;

    //clock_t start;
    //double diff;
    //start = clock();

    RouterNode *rootNode = new RouterNode();
    //rootNode->addRoute("api/v1_0/users", 1, "users");
    int route0 = 0;
    int route2 = 2;
    int route3 = 4;
    int route4 = 4;

    int route5 = 5;
    int route6 = 6;
    int route7 = 7;
    int route8 = 8;
    int route9 = 9;
    int route10 = 10;
    int route11 = 11;
    int route12 = 12;

    try {
        rootNode->addRoute("api/v2_0/users/user/", &route5, "user");
        rootNode->addRoute("myapi/v1_0/users/user/", &route6, "userX");

        rootNode->addRoute("api/v1_0/users/user", &route4, "userY");


        rootNode->addRoute("api/v1_0/users/user/123", &route3, "user123");
        rootNode->addRoute("api/v1_0/users/user/", &route5, "user");

        rootNode->addRoute("api/v1_0/user({id})/", &route8, "users/()");

        rootNode->addRoute("api/v1_0/items/{item_id}/ok.get", &route11, "api/v1_0/items/{item_id}/ok.get");
        rootNode->addRoute("api/v1_0/items/{item_id}/{user_id}/ok.get", &route12,
                           "api/v1_0/items/{item_id}/{user_id}/ok.get");

        rootNode->addRoute("api/v1_0/items/{item_id}/", &route9, "api/v1_0/items/{item_id}/");



        //cout << '\n' << '\n' << "=================" << '\n' << '\n' << endl;
        //RouteResult<int> *res = rootNode->findRoute("/api/v3_0/users/user/123");
        RouteResult *res2 = rootNode->findRoute("/api/v1_0/users/user");
        RouteResult *res3 = rootNode->findRoute("/api/v1_0/users");
        //RouteResult<int> *res4 = rootNode->findRoute("/api/v1_0/users/");
        //RouteResult<int> *res5 = rootNode->findRoute("/api/v1_0/items/544/");
        //RouteResult<int> *res6 = rootNode->findRoute("/api/v1_0/items/563/ok.get");
        RouteResult *res7 = rootNode->findRoute("/api/v1_0/items/77777/264/ok.get");
        RouteResult *res8 = rootNode->findRoute("/api/v1_0/user('mywidgets')/");


        int *ctrl7;
        // cast raw pointer void* controller to an int since we know it was an int)
        if(res7->controller != nullptr) {
            ctrl7 = (int *) (res7->controller);
        } else {
            ctrl7 = &route0;
        }


        //cout << "RES route /api/v3_0/users/user/123: " << res->toString() << endl;
        //cout << "RES2 route /api/v1_0/users/user: " << res2->toString() << endl;
        //cout << "RES3 route /api/v1_0/users: " << res3->toString() << endl;
        //cout << "RES route /api/v1_0/users/: " << res4->controller_id << endl;
        //cout << "RES-5 route /api/v1_0/items/55/: " << res5->controller_id << endl;
        //cout << "RES-6 route /api/v1_0/items/563/ok.get: " << res6->toString() << endl;
        cout << "RES-7 route api/v1_0/items/{item_id}/{user_id}/ok.get: " << res7->toString() << " ctrl7: " << *ctrl7 << endl;
        cout << "RES-8 route /api/v1_0/user('mywidgets')/: " << res8->toString() << endl;

    } catch (...) {
        cout << "SOME EXCEPTION" << endl;
    }

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

    int t = funcTime(findRt, *rootNode, "/api/v1_0/user('mywidgets')/");
    //int t2 = funcTime(findRoute, rn, "/api/v2");
    //int t3 = funcTime(findRoute, rn, "/api/v2/users");

    cout << "t1: " << t << "\n";
    //std::cout<<"t2: "<< t2 <<"\n";
    //std::cout<<"t3: "<< t2 <<"\n";
    //findRoute(rn, "/api/v2/users");


    //cout << "PREFIX=[" << prefix << "]" << " ph=[" << ph << "]" << " len=" << slen << " startPos=" << startPos <<  " endPos=" << endPos << endl;


    //std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    //std::cout << "Time MS difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
    //std::cout << "Time NANO difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;

    //diff = ( std::clock() - start ) / (double)CLOCKS_PER_SEC;
    //cout<<"printf: "<< diff <<'\n';
    return 0;

}