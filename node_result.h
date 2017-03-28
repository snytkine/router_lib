//
// Created by Snytkine, Dmitri (CORP) on 3/21/17.
//

#ifndef ROUTER_NODE_RESULT_H
#define ROUTER_NODE_RESULT_H

#include <iostream>
#include <vector>
#include "t_controller.h"


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

        // todo test with vector of pointers to controller instead!
        //
        paramsList *params;
        std::vector<TController<T>> *controllers = new std::vector<TController<T>>();
        std::string restString;

        RouteResult<T>() {}

        RouteResult<T>(paramsList *p) : params(p) {}

        RouteResult<T>(paramsList *p, std::vector<TController<T>> *ctrls, std::string rest = "") : params(p),
                                                                                                   controllers(ctrls),
                                                                                                   restString(rest) {}

        //TController<T> forMethod(std::string m);

        TController<T> forMethod(std::string m) {
            HTTP_METHOD hm = str_to_method(m);
            std::cout << "\nMY hm: " << int(hm) << std::endl;
            /*try {
                 hm = str_to_method(m);
            } catch (std::invalid_argument e){
                return nullptr;
            }*/

            for (auto &&c: *controllers) {
                if (c.httpMethod == hm) {
                    return c;
                }
                //std::cout << " CTRL-httpMethod: " << http_method_to_string(c.httpMethod) << std::endl;
                //return c;
            }

            return TController<T>{"_", HTTP_METHOD::CONNECT, T()};

        };

        std::string getSupportedMethods() {

            bool begin = false;
            std::string res = "";
            if (controllers->size() == 0) {
                return res;
            }

            for (auto &&ctrl: *controllers) {
                if (begin) {
                    res += ",";
                }
                res += http_method_to_string(ctrl.httpMethod);
                begin = true;
            }

            return res;
        }

        virtual bool isEmpty() {
            return false;
        }

        std::string toString() {
            std::string ret = "RouteResult isEmpty: ";
            ret = ret + ((isEmpty()) ? "TRUE" : "FALSE");
            ret = ret + " CID=";
            if (!isEmpty()) {
                if (controllers->size() > 0) {
                    //ret = ret + to_string(*controller);
                    ret = ret + "\nNUM CONTROLLERS: " + std::to_string(controllers->size());
                    ret = ret + "\nHAVE CONTROLLERS FOR:";


                    for (auto &&ctrl: *controllers) {
                        ret = ret + "\n" + http_method_to_string(ctrl.httpMethod) + " ctrlName=[" + ctrl.name + "]";
                    }
                } else {
                    ret = ret + " NO CONTROLLERS IN RESULT ";
                }
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
        bool isEmpty() {
            return true;
        }
    };


    template
    class RouteResult<int>;

    template
    class EmptyResult<int>;
}

#endif //ROUTER_NODE_RESULT_H
