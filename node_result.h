//
// Created by Snytkine, Dmitri (CORP) on 3/21/17.
//

#ifndef ROUTER_NODE_RESULT_H
#define ROUTER_NODE_RESULT_H

#include <iostream>
#include <vector>

namespace router_lib {

    using namespace std;

    class RouteParam {

    public:
        const string name;
        const string val;

        RouteParam(const string nn, const string vv) : name(nn), val(vv) {}
    };

    typedef vector<RouteParam *> paramsList;

    template<typename T>
    class RouteResult {

    public:

        paramsList *params;
        T controller_id;
        string restString = "";

        RouteResult() {}

        RouteResult(paramsList *p, T cid = 0, string rest = "") : restString(rest) {
            params = p;
            controller_id = cid;
        }


        virtual bool isEmpty() {
            return false;
        }

        virtual string toString() {
            string ret = "RouteResult isEmpty: ";
            ret = ret + ((isEmpty()) ? "TRUE" : "FALSE");
            ret = ret + " CID=";
            ret = ret + to_string(controller_id);
            ret = ret + "\n PARAMS:";
            if (params != nullptr && params->size() > 0) {
                for (auto &&i : *params) {
                    ret = ret + "\nParamName=";
                    ret = ret + i->name;
                    ret = ret + "   ParamVal=";
                    ret = ret + i->val;
                }
            }

            return ret;
        }

        ~RouteResult<T>() {
            if (params != nullptr) {
                cout << " RouteResult destructor has params " << endl;
                params->clear();
                params = nullptr;
            } else {
                //cout << " RouteResult destructor has NO params " << endl;
            }
        };
    };


    template<typename T>
    class EmptyResult : public RouteResult<T> {

        bool isEmpty() {
            return true;
        }
    };

}

#endif //ROUTER_NODE_RESULT_H
