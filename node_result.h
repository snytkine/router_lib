//
// Created by Snytkine, Dmitri (CORP) on 3/21/17.
//

#ifndef ROUTER_NODE_RESULT_H
#define ROUTER_NODE_RESULT_H

#include <iostream>
#include <vector>

namespace router_lib {

    class RouteParam {

    public:
        const std::string name;
        const std::string val;

        RouteParam(const std::string nn, const std::string vv) : name(nn), val(vv) {}
    };

    typedef std::vector<RouteParam *> paramsList;


    template<class T>
    class RouteResult {

    public:

        paramsList *params;
        T controller;
        std::string restString;


        RouteResult<T>() {}

        RouteResult<T>(paramsList *p) : params(p) {}

        RouteResult<T>(paramsList *p, T cid, std::string rest = "") : params(p), controller(cid), restString(rest) {}


        virtual bool isEmpty(){
            return false;
        }

        std::string toString() {
            std::string ret = "RouteResult isEmpty: ";
            ret = ret + ((isEmpty()) ? "TRUE" : "FALSE");
            ret = ret + " CID=";
            if (!isEmpty()) {
                //ret = ret + to_string(*controller);
                ret = ret + " HAVE CONTROLLER";
            } else {
                ret = ret + " NO CONTROLLER ";
            }
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

            //cout << "~~~~ NodeRetult Destructor called ~~~~" << endl;
            if (params != nullptr && params->size() > 0) {
                params->clear();
                delete params;
            }

        };
    };

    template<class T>
    class EmptyResult : public RouteResult<T> {
        bool isEmpty(){
            return true;
        }
    };


    template
    class RouteResult<int>;

    template
    class EmptyResult<int>;
}

#endif //ROUTER_NODE_RESULT_H
