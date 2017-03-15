//
// Created by Snytkine, Dmitri (CORP) on 3/14/17.
//

#ifndef ROUTER_ROUTER_NODE_H
#define ROUTER_ROUTER_NODE_H


#include <iostream>
#include <vector>
#include <sstream>


using namespace std;


class RouteParam {

public:
    const string name;
    const string val;

    RouteParam(const string nn, const string vv) : name(nn), val(vv) {}
};

typedef vector<RouteParam *> paramsList;

struct RouteResult {
    paramsList* params;
    int controller_id;
    ~RouteResult(){
        if(params != nullptr) {
            cout << " RouteResult destructor has params "  << endl;
            params->clear();
            params = nullptr;
        } else {
            cout << " RouteResult destructor has NO params "  << endl;
        }
    };
};




class RouterNode {

protected:

    string uri_;

    int controller_id;

    vector<RouterNode *> children;

public :
    RouterNode(std::string uri, int id) : uri_(uri), controller_id(id) {}

    virtual RouterNode* addChild(string uri, int id);

    virtual RouteResult* findRoute(string uri, paramsList *params =  new paramsList());

    ~RouterNode(){
        children.clear();
    }

};


#endif //ROUTER_ROUTER_NODE_H
