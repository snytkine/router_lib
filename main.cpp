#include <iostream>
#include <ctime>
#include "strlib.h"
#include "node_result.h"
#include "strlib.h"
//#include "RouterNodeInt.h"
#include "RouterNode.h"
#include "measure.h"
#include "counter.h"



using namespace std;
using namespace router_lib;

typedef RouterNode<int> MyRouter;

RouteResult<int> *findRt(RouterNode<int> rn, string uri) {
    return rn.findRoute(uri);
}

int main() {

    //auto g = template class router_lib::RouterNode<int>;

    string mstr = "category({widgets})/";

    string prefix = mstr.substr(0, mstr.find("({") + 1);
    size_t slen = mstr.length();
    size_t startPos = mstr.find("{");
    size_t endPos = mstr.find("}");
    size_t parenEndPos = mstr.find(")");
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

    MyRouter *rootNode = new MyRouter();
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
        ///api/v1_0/user/123
        rootNode->addRoute("api/ok/bla/", route5, "GET", "user");
        rootNode->addRoute("api/ok/na/kk/gg", route5, "GET", "user");
        rootNode->addRoute("api/ok/na/kk/ok", route5, "GET", "user");
        rootNode->addRoute("api/ok/na/dd/gg", route5, "GET", "user");
        rootNode->addRoute("api/ok/na/cc/gg", route5, "GET", "user");


        //rootNode->addRoute("myapi/v1_0/users/user/", route6, "GET", "userX");
/*
        rootNode->addRoute("api/v1_0/users/user", route4,/ "GET", "userY");


        rootNode->addRoute("api/v1_0/users/user/123", route3, "GET", "user123");

        rootNode->addRoute("api/v1_0/users/user/", route5, "GET", "user A");

        //rootNode->addRoute("api/v1_0/users/user/", route5, "GET", "user DDD");

        rootNode->addRoute("api/v1_0/user({id})/", route8, "GET", "users/()");

        rootNode->addRoute("api/v1_0/items/{item_id}/ok.get", route11, "GET", "Z api/v1_0/items/{item_id}/ok.get");
        rootNode->addRoute("api/v1_0/items/{item_id}/{user_id}/ok.get", route12, "GET",
                           "Z1 api/v1_0/items/{item_id}/{user_id}/ok.get");

        rootNode->addRoute("api/v1_0/items/{item_id}/", route9, "GET", "Z2 api/v1_0/items/{item_id}/");
        //rootNode->addRoute("api/v3_0/user({user_id})/ok", 13, "oData");
        rootNode->addRoute("api/v4_0/{my_category}/user({user_id})/{item_id}", 14, "GET", "oDataX");
        rootNode->addRoute("api/v4_0/{my_category}/user({user_id})/{item_id}", 14, "POST", "oDataX-POST");

        *///rootNode->addRoute("api/v4_0/{my_category}/user({user_id})/{item_id}", 14, "oData");



        cout << '\n' << '\n' << "=================" << '\n' << '\n' << endl;
        int totalNodes = 1;
        rootNode->totalNodes(totalNodes);
        cout << "Num Nodes=" <<  to_string(totalNodes) << endl;


        cout << '\n' << '\n' << "+++++++++++++++++" << '\n' << '\n' << endl;
        int totalControllers = 0;
        rootNode->totalControllers(totalControllers);
        cout << "Num Controllers=" <<  to_string(totalControllers) << endl;

        cout << '\n' << '\n' << "+++++++++++++++++" << '\n' << '\n' << endl;
        //int myTotalNodee = 0;
        int myTotalX = getNodesCount<int>(rootNode);
        cout << "myTotalX=" <<  myTotalX << endl;

        //RouteResult<int> *res = rootNode->findRoute("/api/v3_0/users/user/123");
        //RouteResult<int> *res2 = rootNode->findRoute("/api/v1_0/users/user");
        //RouteResult<int> *res3 = rootNode->findRoute("/api/v1_0/users");
        //RouteResult<int> *res4 = rootNode->findRoute("/api/v1_0/users/");
        //RouteResult<int> *res5 = rootNode->findRoute("/api/v1_0/items/544/");
        //RouteResult<int> *res6 = rootNode->findRoute("/api/v1_0/items/563/ok.get");
        //RouteResult<int> *res7 = rootNode->findRoute("/api/v1_0/items/77777/264/ok.get");
        //RouteResult<int> *res8 = rootNode->findRoute("/api/v1_0/user('mywidgets')/");
       // RouteResult<int> *res9 = rootNode->findRoute("/api/v3_0/user('ba')/ok");
        RouteResult<int> *res10 = rootNode->findRoute("/api/v4_0/books/user('dada')/333");

        //int ctrl7;
        // cast raw pointer void* controller to an int since we know it was an int)
        /*if(!res7->isEmpty()) {
            ctrl7 = res7->controller;
        } else {
            ctrl7 = route0;
        }*/


        //cout << "RES route /api/v3_0/users/user/123: " << res->toString() << endl;
        //cout << "RES2 route /api/v1_0/users/user: " << res2->toString() << endl;
        //cout << "RES3 route /api/v1_0/users: " << res3->toString() << endl;
        //cout << "RES route /api/v1_0/users/: " << res4->controller_id << endl;
        //cout << "RES-5 route /api/v1_0/items/55/: " << res5->controller_id << endl;
        //cout << "RES-6 route /api/v1_0/items/563/ok.get: " << res6->toString() << endl;
        //cout << "RES-7 route api/v1_0/items/{item_id}/{user_id}/ok.get: " << res7->toString() << " ctrl7: " << ctrl7 << endl;
        //cout << "RES-8 route /api/v1_0/user('mywidgets')/: " << res8->toString() << endl;
//        cout << "RES-9 route /api/v3_0/user('ba')/ok: " << res9->toString() << endl;

        //std::tuple<TController<int>, std::string> tpl10 = res10->forMethod("GET");
        TController<int> ctrl10 = res10->forMethod("GET");
        std::string ctrl10name = ctrl10.name;
        cout << "???" << endl;
        cout << "RES-10 route /api/v4_0/books/user('dada')/333: " << res10->toString() << "\n ?GET CTRL=[" <<  ctrl10name << "] Supported methods:"  << res10->getSupportedMethods() << endl;

    } catch (std::invalid_argument e) {
        cout << "~~~~~~~~~ EXCEPTION ~~~~~~~~~~~~~~" << endl;
        cout << "SOME EXCEPTION: " << e.what() << endl;
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


    cout << "PREFIX=[" << prefix << "]" << " ph=[" << ph << "]" << " len=" << slen << " startPos=" << startPos <<  " endPos=" << endPos << " parenEndPos=" << parenEndPos<< endl;


    //std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    //std::cout << "Time MS difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
    //std::cout << "Time NANO difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;

    //diff = ( std::clock() - start ) / (double)CLOCKS_PER_SEC;
    //cout<<"printf: "<< diff <<'\n';
    return 0;

}