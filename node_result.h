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
        T *controller;
        string restString = "";

        RouteResult() {}

        RouteResult(paramsList *p, T *cid = nullptr, string rest = "") : restString(rest), controller(cid) {
            params = p;
        }


        virtual bool isEmpty();

        virtual string toString() {
            string ret = "RouteResult isEmpty: ";
            ret = ret + ((isEmpty()) ? "TRUE" : "FALSE");
            ret = ret + " CID=";
            if (controller != nullptr) {
                ret = ret + to_string(*controller);
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

            cout << "~~~~ NodeRetult Destructor called ~~~~" << endl;
            /*if (params != nullptr) {

                params->clear();
                params = nullptr;
                //delete controller;
            } else {

            }*/
        };
    };


    template<typename T>
    class EmptyResult : public RouteResult<T> {
        bool isEmpty() {
            return true;
        }

        ~EmptyResult() {
            cout << "EMPTY RESULT Desctuctor called" << endl;
        }
    };



    template<typename T>
    bool RouteResult<T>::isEmpty() {
        return false;
    }


}

#endif //ROUTER_NODE_RESULT_H
