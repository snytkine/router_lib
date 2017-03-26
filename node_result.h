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


    class RouteResult {

    public:

        paramsList *params;
        void *controller;
        std::string restString;

        RouteResult() {}

        RouteResult(paramsList *p, void *cid = nullptr, std::string rest = "") : restString(rest), controller(cid) {
            params = p;
        }


        virtual bool isEmpty() {
            return false;
        };

        virtual std::string toString() {
            std::string ret = "RouteResult isEmpty: ";
            ret = ret + ((isEmpty()) ? "TRUE" : "FALSE");
            ret = ret + " CID=";
            if (controller != nullptr) {
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

        ~RouteResult() {

            //cout << "~~~~ NodeRetult Destructor called ~~~~" << endl;
            if (params != nullptr && params->size() > 0) {
                params->clear();
                delete params;
            }

        };
    };


    class EmptyResult : public RouteResult {
        bool isEmpty() {
            return true;
        }
    };


}

#endif //ROUTER_NODE_RESULT_H
